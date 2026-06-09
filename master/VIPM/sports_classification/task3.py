# task3.py
import os
import pickle
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
    Load image paths and labels from a directory structure.

    Args:
        split_dir: Path to directory containing class subfolders

    Returns:
        paths: List of image file paths
        labels: List of integer labels (0-indexed, contiguous)
        class_names: List of sorted class names
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
    Load and preprocess an image.

    Args:
        path: Path to image file
        size: Target image size (default: IMG_SIZE=224)

    Returns:
        Grayscale image resized to (size, size) as uint8
    """
    img = cv2.imread(path)
    img = cv2.resize(img, (size, size))
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def extract_dense_sift(img_gray, step=SIFT_STEP):
    H, W = img_gray.shape
    kps = [cv2.KeyPoint(float(x), float(y), float(step))
           for y in range(0, H, step)
           for x in range(0, W, step)]
    sift = cv2.SIFT_create()
    _, descs = sift.compute(img_gray, kps)
    return descs  # (N, 128), float32


def build_codebook(all_descriptors, K=CODEBOOK_SIZE):
    kmeans = MiniBatchKMeans(
        n_clusters=K, batch_size=4096, random_state=42, n_init=3
    )
    kmeans.fit(all_descriptors)
    return kmeans


def encode_spm(img_gray, kmeans, K=CODEBOOK_SIZE, step=SIFT_STEP, levels=SPM_LEVELS):
    H, W = img_gray.shape
    kps = [cv2.KeyPoint(float(x), float(y), float(step))
           for y in range(0, H, step)
           for x in range(0, W, step)]
    sift = cv2.SIFT_create()
    _, descs = sift.compute(img_gray, kps)
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
    clf = LinearSVC(C=C, max_iter=2000, random_state=42)
    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
    scores = cross_val_score(clf, X, y, cv=cv, scoring='accuracy')
    clf.fit(X, y)
    return clf, scores


def evaluate(clf, X, y, class_names):
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
