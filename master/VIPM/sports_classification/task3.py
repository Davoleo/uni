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
