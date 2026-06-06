import argparse
import os

import torch
from sklearn.metrics import f1_score
from torchvision import datasets
from torchvision.transforms import v2

from project_models import Baseline2
from project_transforms import *
from project_utils import get_device, topk_accuracy

ENHANCEMENTS = {
    'wb': WhiteBalance(algorithm=WBAlgorithm.WHITE_PATCH),
    'gamma': AutoGammaCorrection(),
}

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (loaded from models/<name>.pt)')
parser.add_argument('--degraded', action='store_true', default=False, help='Use degraded test set instead of the clean one')
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

topks = (1,3,5)
topkacc = []
f1 = None

for k in topks:
    all_accuracies = []
    all_labels = []
    all_preds = []

    with torch.no_grad():
        for images, labels in loader:
            images = images.to(device)
            outputs = model(images)
            all_accuracies.append(topk_accuracy(outputs, labels.to(device), topk=k))
            if k == 1:
                _, preds = torch.max(outputs, 1)
                all_preds.extend(preds.cpu().tolist())
                all_labels.extend(labels.tolist())

    topkacc.append(sum(all_accuracies) / len(all_accuracies))

    if k == 1:
        f1 = f1_score(all_labels, all_preds, average='macro')

print(f"F1-Score: {f1:.4f}, Accuracy: {topkacc[0]:.4f}, Top-3 Acc: {topkacc[1]:.4f}, Top-5 Acc: {topkacc[2]:.4f}")
