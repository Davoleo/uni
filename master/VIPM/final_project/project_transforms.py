import math
import os
import random
from enum import Enum
from statistics import median, mean

import matplotlib.pyplot as plt
import torch
import torchvision.transforms.functional as F
from PIL import Image
from torch import nn
from torchvision.transforms import v2


class AutoGammaCorrection(nn.Module):
    """
    Per-image unsupervised gamma correction.

    Estimates gamma from the image mean brightness to pull it towards `target`
    (default 0.5, midgray), without requiring a clean ground-truth reference.

    Formula: gamma = log(target) / log(mean)
      - dark image (mean < target) → gamma < 1 → brightening
      - bright image (mean > target) → gamma > 1 → darkening

    Expects a float tensor in [0, 1] (apply after ToDtype).
    """

    def __init__(self, target: float = 0.5, gamma_range: tuple = (0.2, 5.0)):
        super().__init__()
        self.target = target
        self.gamma_range = gamma_range

    def forward(self, img: torch.Tensor) -> torch.Tensor:
        mean = img.mean().item()
        if mean <= 0.0 or mean >= 1.0:
            return img
        gamma = math.log(self.target) / math.log(mean)
        gamma = float(max(self.gamma_range[0], min(self.gamma_range[1], gamma)))
        return F.adjust_gamma(img, gamma)

_to_tensor = v2.Compose([v2.ToImage(), v2.ToDtype(torch.float32, scale=True)])

class WBAlgorithm(Enum):
	WHITE_PATCH = 1
	GRAY_WORLD = 2
    

class WhiteBalance(nn.Module):
    """
    White Balance transform.
    Supports different 'WBAlgorithm's
    """
    def __init__(self, algorithm: WBAlgorithm) -> None:
        super().__init__()
        self.algorithm = algorithm

    def forward(self, img: torch.Tensor) -> torch.Tensor:

        match self.algorithm:
            case WBAlgorithm.WHITE_PATCH:
                # max: reducing the last 2 dimensions (keep channels)
                imageMaxRGB = img.amax((1,2))
                # White Patch
                coeffs = imageMaxRGB / 1
                print('WP coeffs: ', coeffs)
                # Patch application // need to fill last 2 dimensions w/None
                wbImage = img * coeffs[:, None, None]
                return wbImage
            case WBAlgorithm.GRAY_WORLD:
                # mean: reducing the last 2 dimensions (keep channels)
                imageMeanRGB = img.mean(dim=(1,2))
                # gray world
                coeffs = 0.5 / imageMeanRGB
                print('GW coeffs: ', coeffs)
                # apply
                wbImage = img * coeffs[:, None, None]
                return wbImage

def show_enhancement(transform, test_dir='data/test_degradato', n=3, seed=None):
    """Show n random images from test_dir before and after applying transform."""
    if seed is not None:
        random.seed(seed)

    paths = [
        os.path.join(root, f)
        for root, _, files in os.walk(test_dir)
        for f in files if f.lower().endswith(('.jpg', '.jpeg', '.png'))
    ]
    sample = random.sample(paths, min(n, len(paths)))

    fig, axes = plt.subplots(n, 2, figsize=(7, n * 3), squeeze=False)
    axes[0][0].set_title('degraded', fontsize=14)
    axes[0][1].set_title('restored', fontsize=14)

    for i, path in enumerate(sample):
        tensor = _to_tensor(Image.open(path).convert('RGB'))
        enhanced = transform(tensor)
        label = os.path.basename(os.path.dirname(path))

        axes[i][0].imshow(tensor.permute(1, 2, 0).clamp(0, 1))
        axes[i][0].set_ylabel(label, fontsize=9)
        axes[i][0].axis('off')

        axes[i][1].imshow(enhanced.permute(1, 2, 0).clamp(0, 1))
        axes[i][1].axis('off')

    fig.tight_layout()
    plt.show()
