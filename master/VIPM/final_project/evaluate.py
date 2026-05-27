import argparse
import os

import torch
from sklearn.metrics import accuracy_score, f1_score
from torchvision import datasets
from torchvision.transforms import v2

from project_models import Baseline2
from project_transforms import AutoGammaCorrection
from project_utils import get_device

ENHANCEMENTS = {
    'gamma': AutoGammaCorrection(),
}

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (loaded from models/<name>.pt)')
parser.add_argument('--test-dir', default='data/test', help='Test set directory')
parser.add_argument('--enhance', default=None, choices=list(ENHANCEMENTS),
                    help='Unsupervised enhancement applied before classification')
args = parser.parse_args()

device = get_device()

transform_steps = [v2.ToImage(), v2.ToDtype(torch.float32, scale=True)]
if args.enhance:
    transform_steps.append(ENHANCEMENTS[args.enhance])
transform = v2.Compose(transform_steps)

test_ds = datasets.ImageFolder(args.test_dir, transform=transform)
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
