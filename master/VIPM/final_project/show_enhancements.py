from torchvision import transforms

from project_transforms import *

composed = transforms.Compose([
    WhiteBalance(WBAlgorithm.GRAY_WORLD),
    AutoGammaCorrection()
])

show_enhancement(composed, n=5)
