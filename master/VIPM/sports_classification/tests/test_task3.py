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
