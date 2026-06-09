# tests/test_task3.py
import sys
import os
import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
import task3


def make_gray(H=224, W=224, seed=0):
    rng = np.random.default_rng(seed)
    return rng.integers(0, 256, (H, W), dtype=np.uint8)


def make_descs(n=1000, seed=0):
    rng = np.random.default_rng(seed)
    return rng.random((n, 128)).astype(np.float32)


class TestLoadDataset:
    def test_returns_three_elements(self, tmp_path):
        for cls in ['alpha', 'beta', 'gamma']:
            d = tmp_path / cls
            d.mkdir()
            for i in range(2):
                img = np.zeros((10, 10, 3), dtype=np.uint8)
                import cv2
                cv2.imwrite(str(d / f"{i}.jpg"), img)
        paths, labels, class_names = task3.load_dataset(str(tmp_path))
        assert len(paths) == 6
        assert len(labels) == 6
        assert len(class_names) == 3

    def test_labels_are_contiguous_ints(self, tmp_path):
        for cls in ['aaa', 'bbb']:
            d = tmp_path / cls
            d.mkdir()
            img = np.zeros((10, 10, 3), dtype=np.uint8)
            import cv2
            cv2.imwrite(str(d / "0.jpg"), img)
        _, labels, _ = task3.load_dataset(str(tmp_path))
        assert set(labels) == {0, 1}

    def test_class_names_are_sorted(self, tmp_path):
        for cls in ['zzz', 'aaa', 'mmm']:
            d = tmp_path / cls
            d.mkdir()
            img = np.zeros((10, 10, 3), dtype=np.uint8)
            import cv2
            cv2.imwrite(str(d / "0.jpg"), img)
        _, _, class_names = task3.load_dataset(str(tmp_path))
        assert class_names == ['aaa', 'mmm', 'zzz']


class TestLoadImage:
    def test_returns_grayscale_224x224(self, tmp_path):
        import cv2
        img = np.zeros((100, 150, 3), dtype=np.uint8)
        p = str(tmp_path / "test.jpg")
        cv2.imwrite(p, img)
        result = task3.load_image(p)
        assert result.shape == (224, 224)
        assert result.dtype == np.uint8


class TestExtractDenseSift:
    def test_returns_2d_float32_array(self):
        img = make_gray()
        descs = task3.extract_dense_sift(img, step=8)
        assert descs.ndim == 2
        assert descs.dtype == np.float32

    def test_descriptor_dim_is_128(self):
        img = make_gray()
        descs = task3.extract_dense_sift(img, step=8)
        assert descs.shape[1] == 128

    def test_keypoint_count_matches_grid(self):
        img = make_gray(224, 224)
        descs = task3.extract_dense_sift(img, step=8)
        assert descs.shape[0] == 784

    def test_larger_step_gives_fewer_descriptors(self):
        img = make_gray(224, 224)
        d8 = task3.extract_dense_sift(img, step=8)
        d16 = task3.extract_dense_sift(img, step=16)
        assert d8.shape[0] > d16.shape[0]


class TestBuildCodebook:
    def test_cluster_centers_shape(self):
        descs = make_descs(2000)
        kmeans = task3.build_codebook(descs, K=50)
        assert kmeans.cluster_centers_.shape == (50, 128)

    def test_predict_returns_valid_indices(self):
        descs = make_descs(2000)
        kmeans = task3.build_codebook(descs, K=50)
        words = kmeans.predict(make_descs(10, seed=1))
        assert words.shape == (10,)
        assert words.min() >= 0
        assert words.max() < 50


class TestEncodeSpm:
    def setup_method(self):
        self.K = 50
        self.kmeans = task3.build_codebook(make_descs(5000), K=self.K)

    def test_output_shape_is_k_times_21(self):
        feat = task3.encode_spm(make_gray(), self.kmeans, K=self.K)
        assert feat.shape == (self.K * 21,)

    def test_output_is_l2_normalized(self):
        feat = task3.encode_spm(make_gray(), self.kmeans, K=self.K)
        assert abs(np.linalg.norm(feat) - 1.0) < 1e-5

    def test_different_images_differ(self):
        f1 = task3.encode_spm(make_gray(seed=0), self.kmeans, K=self.K)
        f2 = task3.encode_spm(make_gray(seed=99), self.kmeans, K=self.K)
        assert not np.allclose(f1, f2)

    def test_feature_is_non_negative(self):
        feat = task3.encode_spm(make_gray(), self.kmeans, K=self.K)
        assert (feat >= 0).all()


class TestTrainClassifier:
    def _make_data(self, n_classes=10, n_per_class=10, n_features=50):
        rng = np.random.default_rng(0)
        X = rng.random((n_classes * n_per_class, n_features)).astype(np.float32)
        y = np.repeat(np.arange(n_classes), n_per_class)
        return X, y

    def test_returns_clf_and_five_cv_scores(self):
        X, y = self._make_data()
        clf, scores = task3.train_classifier(X, y, C=1.0)
        assert scores.shape == (5,)
        assert hasattr(clf, 'predict')

    def test_cv_scores_in_valid_range(self):
        X, y = self._make_data()
        _, scores = task3.train_classifier(X, y, C=1.0)
        assert (scores >= 0.0).all() and (scores <= 1.0).all()

    def test_clf_predicts_correct_shape(self):
        X, y = self._make_data()
        clf, _ = task3.train_classifier(X, y, C=1.0)
        preds = clf.predict(X[:5])
        assert preds.shape == (5,)


class TestEvaluate:
    def _fitted_clf(self):
        rng = np.random.default_rng(0)
        X = rng.random((100, 50)).astype(np.float32)
        y = np.repeat(np.arange(10), 10)
        clf, _ = task3.train_classifier(X, y, C=1.0)
        return clf, X, y

    def test_returns_accuracy_and_f1(self):
        clf, X, y = self._fitted_clf()
        m = task3.evaluate(clf, X, y, [str(i) for i in range(10)])
        assert 'accuracy' in m and 'f1' in m
        assert 0.0 <= m['accuracy'] <= 1.0
        assert 0.0 <= m['f1'] <= 1.0

    def test_predictions_shape(self):
        clf, X, y = self._fitted_clf()
        m = task3.evaluate(clf, X, y, [str(i) for i in range(10)])
        assert m['predictions'].shape == (100,)

    def test_confusion_matrix_shape(self):
        clf, X, y = self._fitted_clf()
        m = task3.evaluate(clf, X, y, [str(i) for i in range(10)])
        assert m['confusion_matrix'].shape == (10, 10)
