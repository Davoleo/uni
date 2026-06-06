from torchvision import transforms

from project_transforms import *

composed = transforms.Compose([
    WhiteBalance(WBAlgorithm.GRAY_WORLD),
    ContrastStretch(low_percentile=8)
])

contrast_stretch = ContrastStretch(low_percentile=8)

show_enhancement(composed, n=5)