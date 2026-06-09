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
