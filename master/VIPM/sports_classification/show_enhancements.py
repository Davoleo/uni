from torchvision import transforms

from transforms import *

composed = transforms.Compose([
    WhiteBalance(WBAlgorithm.GRAY_WORLD),
    ContrastStretch(low_percentile=8)
])

contrast_stretch = ContrastStretch(low_percentile=8)

posterize = v2.RandomPosterize(2, p=1.0)

show_enhancement(posterize, test_dir='data/test', n=5)