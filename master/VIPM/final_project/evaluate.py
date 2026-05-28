import argparse
import os

import torch
from sklearn.metrics import accuracy_score, f1_score
from torchvision import datasets
from torchvision.transforms import v2

from project_models import Baseline2
from project_transforms import *
from project_utils import get_device

ENHANCEMENTS = {
    'wb': WhiteBalance(algorithm=WBAlgorithm.WHITE_PATCH),
    'gamma': AutoGammaCorrection(),
}

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (loaded from models/<name>.pt)')
parser.add_argument('--degraded', action='store_true', default=False, help='Use degraded test set insteado of the clean one')
parser.add_argument('--enhance', nargs='+', default=None, choices=list(ENHANCEMENTS),
                    help='Unsupervised enhancement applied before classification')
args = parser.parse_args()

device = get_device()

transform_steps = [v2.ToImage(), v2.ToDtype(torch.float32, scale=True)]
if args.enhance:
    for name in args.enhance:
        transform_steps.append(ENHANCEMENTS[name])
transform = v2.Compose(transform_steps)

test_dir = ""
if args.degraded:
    test_dir = 'data/test_degradato'
else:
    test_dir = 'data/test'
    
print(test_dir, )

test_ds = datasets.ImageFolder(test_dir, transform=transform)
loader = torch.utils.data.DataLoader(test_ds, batch_size=64)

model = Baseline2()
model.load_state_dict(torch.load(os.path.join('models', f'{args.name}.pt'), weights_only=True, map_location=device))
model.to(device)
model.eval()

all_preds = []
all_labels = []

with torch.no_grad():
    for images, labels in loader:
        images = images.to(device)
        outputs = model(images)
        _, preds = torch.max(outputs, 1)
        all_preds.extend(preds.cpu().tolist())
        all_labels.extend(labels.tolist())

accuracy = accuracy_score(all_labels, all_preds)
f1 = f1_score(all_labels, all_preds, average='macro')
print(f"Accuracy: {accuracy:.4f}, F1-Score: {f1:.4f}")
