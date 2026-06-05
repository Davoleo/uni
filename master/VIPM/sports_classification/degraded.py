"""
Task 2: Classification on the degraded test set.
Approaches:
  A) Unsupervised image enhancement at inference time (see evaluate.py --test-dir)
  B) Training with degradation-aware data augmentation (transforms extended below)
"""

import argparse
import os

import matplotlib.pyplot as plt
import torch
import torch.optim as optim
from torch import nn
from torchinfo import summary
from torchvision import datasets
from torchvision.transforms import v2

from project_models import Baseline2
from project_utils import get_device, get_degraded_transforms, plot_performance, seed_everything, train, write_training_log

SEED = 42
NUM_EPOCHS = 80
BATCH_SIZE = 32

plt.ion()

seed_everything(SEED)
_rng = torch.Generator()
_rng.manual_seed(SEED)

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (saved as models/<name>.pt)')
args = parser.parse_args()

# Task 2B: extend training transforms with degradation simulation
data_transforms = get_degraded_transforms()


train_ds = datasets.ImageFolder('data/train', data_transforms['train'])
val_ds = datasets.ImageFolder('data/valid', data_transforms['val'])

train_loader = torch.utils.data.DataLoader(train_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=4, generator=_rng)
val_loader = torch.utils.data.DataLoader(val_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=4, generator=_rng)

class_names = train_ds.classes

metrics = {
    'train_loss': [],
    'train_accuracy': [],
    'val_loss': [],
    'val_accuracy': [],
}

device = get_device()

model_ft = Baseline2().to(device)
summary(model_ft)

loss_fn = nn.CrossEntropyLoss()
optimizer_ft = optim.Adam(model_ft.parameters(), lr=1e-3)

model_ft, _best_val, _elapsed = train(
    model_ft, loss_fn, optimizer_ft,
    train_loader=train_loader, val_loader=val_loader,
    train_size=len(train_ds), val_size=len(val_ds),
    device=device, metrics=metrics,
    num_epochs=NUM_EPOCHS,
)

plot_performance(metrics, os.path.join('models', f'{args.name}.png'))

torch.save(model_ft.state_dict(), os.path.join('models', f'{args.name}.pt'))
write_training_log(args.name, _elapsed, NUM_EPOCHS, metrics, test_dir='data/test_degradato')

plt.ioff()
plt.show()
