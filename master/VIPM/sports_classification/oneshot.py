# task3.py
import os
import pickle
import time
import numpy as np
import cv2
from sklearn.cluster import MiniBatchKMeans
from sklearn.svm import LinearSVC
from sklearn.model_selection import StratifiedKFold, cross_val_score
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

IMG_SIZE = 224
SIFT_STEP = 8
CODEBOOK_SIZE = 500
SPM_LEVELS = [0, 1, 2]
SPM_WEIGHTS = {0: 0.25, 1: 0.25, 2: 0.5}


def load_dataset(split_dir):
    """
    Scan a directory of class subfolders and return image paths with integer labels.

    Expects the layout:
        split_dir/
            class_a/  img1.jpg  img2.jpg  ...
            class_b/  img1.jpg  ...

    Class names are sorted alphabetically so label indices are deterministic across
    calls — label 0 always maps to the lexicographically first class. Non-image files
    and nested subdirectories are silently skipped.

    Args:
        split_dir: Path to the split root (e.g. 'data/valid', 'data/test').

    Returns:
        paths:       List[str] — absolute paths to every image found.
        labels:      List[int] — integer class index, parallel to `paths`.
        class_names: List[str] — sorted class names; class_names[i] is the name for label i.
    """
    class_names = sorted(
        d for d in os.listdir(split_dir)
        if os.path.isdir(os.path.join(split_dir, d))
    )
    paths, labels = [], []
    for idx, cls in enumerate(class_names):
        cls_dir = os.path.join(split_dir, cls)
        for fname in sorted(os.listdir(cls_dir)):
            if fname.lower().endswith(('.jpg', '.jpeg', '.png')):
                paths.append(os.path.join(cls_dir, fname))
                labels.append(idx)
    return paths, labels, class_names


def load_image(path, size=IMG_SIZE):
    """
    Load an image from disk, resize it to a square, and convert it to grayscale.

    Resizing to a fixed square (default 224×224) ensures every image produces the
    same number of dense SIFT keypoints, which is required for fixed-length SPM
    feature vectors. The BGR→grayscale conversion discards colour because SIFT
    operates on intensity gradients only.

    Args:
        path: Path to the image file.
        size: Side length in pixels for the output square (default: IMG_SIZE=224).

    Returns:
        np.ndarray of shape (size, size), dtype uint8 — grayscale pixel values.

    Raises:
        FileNotFoundError: If cv2.imread cannot decode the file at `path`.
    """
    img = cv2.imread(path)
    if img is None:
        raise FileNotFoundError(f"Could not read image: {path}")
    img = cv2.resize(img, (size, size))
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def extract_dense_sift(img_gray, step=SIFT_STEP):
    """
    Compute SIFT descriptors at every point on a regular grid (dense sampling).

    Unlike standard SIFT, which first detects salient keypoints, this function
    places keypoints unconditionally every `step` pixels in both axes. This ensures
    uniform spatial coverage — including flat regions like grass or sky that have no
    detectable corners but are highly discriminative for scene classification.

    Each descriptor is a 128-dimensional histogram of gradient orientations in a
    16×16 patch around the keypoint, computed at scale `step`.

    Args:
        img_gray: np.ndarray of shape (H, W), dtype uint8 — grayscale input image.
        step:     Grid spacing in pixels (default: SIFT_STEP=8). Smaller values
                  produce more descriptors but increase computation and memory.

    Returns:
        kps:   List[cv2.KeyPoint] of length N — grid keypoints with (x, y) positions.
        descs: np.ndarray of shape (N, 128), dtype float32 — descriptor for each keypoint.
        N = (H // step) * (W // step) is the number of grid points.
    """
    H, W = img_gray.shape
    kps = [cv2.KeyPoint(float(x), float(y), float(step))
           for y in range(0, H, step)
           for x in range(0, W, step)]
    sift = cv2.SIFT_create()
    _, descs = sift.compute(img_gray, kps)
    return kps, descs


def build_codebook(all_descriptors, K=CODEBOOK_SIZE):
    """
    Cluster a large set of SIFT descriptors into K visual words (the codebook).

    The codebook is the vocabulary for the Bag of Visual Words model. Each cluster
    center represents a prototypical local patch appearance. MiniBatchKMeans is used
    instead of standard KMeans because the descriptor matrix (millions of 128-d
    vectors) is too large to fit comfortably in memory all at once.

    Args:
        all_descriptors: np.ndarray of shape (M, 128) — all SIFT descriptors pooled
                         from the training set (one row per descriptor).
        K:               Number of clusters / visual words (default: CODEBOOK_SIZE=500).

    Returns:
        sklearn MiniBatchKMeans fitted on `all_descriptors`. Use kmeans.predict()
        to assign new descriptors to their nearest visual word.
    """
    kmeans = MiniBatchKMeans(
        n_clusters=K, batch_size=4096, random_state=42, n_init=3
    )
    kmeans.fit(all_descriptors)
    return kmeans


def encode_spm(img_gray, kmeans, K=CODEBOOK_SIZE, step=SIFT_STEP, levels=SPM_LEVELS):
    """
    Encode an image as a Spatial Pyramid Matching (SPM) feature vector.

    SPM extends plain BoVW by computing visual-word histograms at multiple spatial
    resolutions and concatenating them. This preserves rough spatial layout information
    that a single global histogram would discard.

    For each level L in `levels`, the image is divided into a (2^L × 2^L) grid of cells.
    Inside each cell, the visual words of the keypoints that fall within it are counted
    into a normalized histogram. All per-cell histograms are weighted and concatenated:

        level 0 → 1×1  = 1  cell  × K visual words, weight 0.25  (global context, standard BoVW)
        level 1 → 2×2  = 4  cells × K visual words, weight 0.25  (coarse layout)
        level 2 → 4×4  = 16 cells × K visual words, weight 0.50  (fine layout)

    Total feature length = (1 + 4 + 16) × K = 21 × 500 = 10 500 dimensions.

    The higher weight on level 2 follows Lazebnik et al. (CVPR 2006), who show that
    finer spatial resolution carries more discriminative information.

    The final vector is L2-normalized so that SVM distances are not affected by
    differences in image texture density.

    Args:
        img_gray: np.ndarray (H, W) uint8 — grayscale image, must be the same size
                  used when building the codebook because the codebook is trained on dense SIFT.
        kmeans:   Fitted MiniBatchKMeans codebook (from build_codebook).
        K:        Codebook size, must match the K used in build_codebook.
        step:     Dense SIFT grid spacing in pixels.
        levels:   List of pyramid levels to include (default [0, 1, 2]).

    Returns:
        np.ndarray of shape (len(levels_cells_total * K,), dtype float32 — L2-normalised
        SPM feature vector ready for LinearSVC.
    """
    H, W = img_gray.shape
    kps, descs = extract_dense_sift(img_gray, step)
    words = kmeans.predict(descs)
    kp_xy = np.array([(kp.pt[0], kp.pt[1]) for kp in kps])  # (N, 2)

    parts = []
    for level in levels:
        n_cells = 2 ** level
        w = SPM_WEIGHTS[level]
        cell_w = W / n_cells
        cell_h = H / n_cells
        for ci in range(n_cells):       # row
            for cj in range(n_cells):   # col
                mask = (
                    (kp_xy[:, 0] >= cj * cell_w) &
                    (kp_xy[:, 0] < (cj + 1) * cell_w) &
                    (kp_xy[:, 1] >= ci * cell_h) &
                    (kp_xy[:, 1] < (ci + 1) * cell_h)
                )
                hist = np.bincount(words[mask], minlength=K).astype(np.float32)
                hist /= (hist.sum() + 1e-8)
                parts.append(w * hist)

    feature = np.concatenate(parts)
    return feature / (np.linalg.norm(feature) + 1e-8)


def train_classifier(X, y, C=1.0):
    """
    Train a LinearSVC on SPM features and estimate generalization accuracy via CV.

    LinearSVC is the standard choice for BoVW/SPM pipelines: the high-dimensional
    sparse histograms are linearly separable in practice, and LinearSVC scales to
    tens of thousands of samples much faster than kernel SVM.

    Cross-validation is run first (for reporting) and then the classifier is
    re-fitted on the full dataset so the returned model uses all available data.

    Args:
        X: np.ndarray of shape (N, D) — SPM feature matrix (one row per image).
        y: np.ndarray of shape (N,)   — integer class labels.
        C: SVM regularization parameter. Smaller C = stronger regularization.
           Default 1.0 works well for L2-normalised SPM features.

    Returns:
        clf: Fitted LinearSVC trained on the full (X, y).
        scores: np.ndarray of shape (5,) — per-fold accuracy from 5-fold CV,
                useful for reporting mean ± std without a separate held-out set.
    """
    clf = LinearSVC(C=C, max_iter=2000, random_state=42)
    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
    scores = cross_val_score(clf, X, y, cv=cv, scoring='accuracy')
    clf.fit(X, y)
    return clf, scores


def evaluate(clf, X, y, class_names):
    """
    Run inference and compute classification metrics on a labeled set.

    Macro-averaged F1 is reported alongside accuracy because the dataset may have
    class imbalance — macro F1 weights all classes equally regardless of size, so
    it penalizes poor performance on minority classes that accuracy would mask.

    Args:
        clf:         Fitted classifier with a predict() method.
        X:           np.ndarray (N, D) — feature matrix for the evaluation set.
        y:           np.ndarray (N,)   — ground-truth integer labels.
        class_names: List[str]         — class name for each label index (used
                     as keys in the confusion matrix; not used here directly but
                     kept for interface consistency with save_confusion_matrix).

    Returns:
        dict with keys:
            'accuracy':         float — fraction of correctly classified images.
            'f1':               float — macro-averaged F1 across all classes.
            'predictions':      np.ndarray (N,) — predicted label for each image.
            'confusion_matrix': np.ndarray (C, C) — row = true, col = predicted.
    """
    preds = clf.predict(X)
    return {
        'accuracy': accuracy_score(y, preds),
        'f1': f1_score(y, preds, average='macro', zero_division=0),
        'predictions': preds,
        'confusion_matrix': confusion_matrix(y, preds),
    }


def save_confusion_matrix(cm, class_names, save_path):
    fig, ax = plt.subplots(figsize=(20, 20))
    im = ax.imshow(cm, interpolation='nearest', cmap='Blues')
    plt.colorbar(im, ax=ax)
    tick_marks = np.arange(len(class_names))
    ax.set_xticks(tick_marks)
    ax.set_xticklabels(class_names, rotation=90, fontsize=4)
    ax.set_yticks(tick_marks)
    ax.set_yticklabels(class_names, fontsize=4)
    ax.set_xlabel('Predicted')
    ax.set_ylabel('True')
    ax.set_title('Confusion Matrix — Task 3 BoVW+SPM')
    plt.tight_layout()
    plt.savefig(save_path, dpi=100)
    plt.close()


def log_results(tag, clean_metrics, degraded_metrics, cv_scores):
    lines = [
        "\n======================================================",
        tag,
        f"CV accuracy (5-fold): {cv_scores.mean():.4f} ± {cv_scores.std():.4f}",
        f"Clean Test    — Accuracy: {clean_metrics['accuracy']:.4f}  "
        f"F1: {clean_metrics['f1']:.4f}",
        f"Degraded Test — Accuracy: {degraded_metrics['accuracy']:.4f}  "
        f"F1: {degraded_metrics['f1']:.4f}",
    ]
    with open('iterations.log', 'a') as f:
        f.write('\n'.join(lines) + '\n')


def main():
    DATA_DIR = 'data'
    MODELS_DIR = 'models'
    K = CODEBOOK_SIZE

    # 1. Load validation set (Task 3 training data)
    print("Loading validation set...")
    val_paths, val_labels, class_names = load_dataset(os.path.join(DATA_DIR, 'valid'))
    print(f"  {len(val_paths)} images, {len(class_names)} classes")

    # 2. Extract dense SIFT from all validation images
    print("Extracting dense SIFT descriptors from validation set...")
    all_descs, val_grays = [], []
    for path in val_paths:
        img = load_image(path)
        val_grays.append(img)
        _, descs = extract_dense_sift(img)
        all_descs.append(descs)
    all_descs_flat = np.vstack(all_descs)
    print(f"  Total descriptors: {all_descs_flat.shape[0]}")

    # 3. Build codebook
    print(f"Building codebook (K={K})...")
    t0 = time.time()
    kmeans = build_codebook(all_descs_flat, K=K)
    print(f"  Done in {time.time() - t0:.1f}s")

    # 4. Encode validation images with SPM
    print("Encoding validation images (SPM)...")
    X_val = np.array([encode_spm(img, kmeans, K) for img in val_grays])
    y_val = np.array(val_labels)

    # 5. Train SVM with cross-validation
    print("Training LinearSVC (5-fold CV)...")
    clf, cv_scores = train_classifier(X_val, y_val, C=1.0)
    print(f"  CV accuracy: {cv_scores.mean():.4f} ± {cv_scores.std():.4f}")

    # 6. Save models
    os.makedirs(MODELS_DIR, exist_ok=True)
    with open(os.path.join(MODELS_DIR, 'task3_codebook.pkl'), 'wb') as f:
        pickle.dump(kmeans, f)
    with open(os.path.join(MODELS_DIR, 'task3_svm.pkl'), 'wb') as f:
        pickle.dump(clf, f)
    print("Models saved to models/")

    # 7. Evaluate on clean test set
    print("Evaluating on clean test set...")
    test_paths, test_labels, _ = load_dataset(os.path.join(DATA_DIR, 'test'))
    X_test = np.array([encode_spm(load_image(p), kmeans, K) for p in test_paths])
    y_test = np.array(test_labels)
    clean_m = evaluate(clf, X_test, y_test, class_names)
    print(f"  Accuracy: {clean_m['accuracy']:.4f}   F1: {clean_m['f1']:.4f}")

    # 8. Evaluate on degraded test set
    print("Evaluating on degraded test set...")
    deg_paths, deg_labels, _ = load_dataset(os.path.join(DATA_DIR, 'test_degradato'))
    X_deg = np.array([encode_spm(load_image(p), kmeans, K) for p in deg_paths])
    y_deg = np.array(deg_labels)
    deg_m = evaluate(clf, X_deg, y_deg, class_names)
    print(f"  Accuracy: {deg_m['accuracy']:.4f}   F1: {deg_m['f1']:.4f}")

    # 9. Save confusion matrices
    save_confusion_matrix(
        clean_m['confusion_matrix'], class_names,
        os.path.join(MODELS_DIR, 'task3_confusion_clean.png')
    )
    save_confusion_matrix(
        deg_m['confusion_matrix'], class_names,
        os.path.join(MODELS_DIR, 'task3_confusion_degraded.png')
    )

    # 10. Log results
    log_results(
        'Task3 BoVW+SPM (K=500, step=8, levels=[0,1,2], LinearSVC C=1.0)',
        clean_m, deg_m, cv_scores
    )
    print("Results logged to iterations.log")


if __name__ == '__main__':
    main()
