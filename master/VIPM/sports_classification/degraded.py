"""
Task 2: Classification on the degraded test set.
Approaches:
  A) Unsupervised image enhancement at inference time (see evaluate.py --enhance)
  B) Training with degradation-aware data augmentation (transforms extended below)
"""

import argparse
import os

import matplotlib.pyplot as plt
import torch
import torch.optim as optim
from torch import nn
from torch.optim import lr_scheduler
from torchinfo import summary
from torchvision import datasets
from torchvision.transforms import v2

from models import Baseline3
from utils import get_device, plot_performance, seed_everything, train, write_training_log
from transforms import get_train_transforms, get_val_transforms

SEED = 42
NUM_EPOCHS = 80
BATCH_SIZE = 128

plt.ion()

seed_everything(SEED)
_rng = torch.Generator()
_rng.manual_seed(SEED)

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (saved as models/<name>.pt)')
args = parser.parse_args()

# Task 2B: extend training transforms with degradation simulation
train_ds = datasets.ImageFolder('data/train',  get_train_transforms(degraded=True))
val_ds = datasets.ImageFolder('data/valid', get_val_transforms())

train_loader = torch.utils.data.DataLoader(train_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=8, pin_memory=True, prefetch_factor=2, persistent_workers=True, generator=_rng)
val_loader = torch.utils.data.DataLoader(val_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=8, pin_memory=True, prefetch_factor=2, persistent_workers=True, generator=_rng)

class_names = train_ds.classes

metrics = {
    'train_loss': [],
    'train_accuracy': [],
    'val_loss': [],
    'val_accuracy': [],
}

device = get_device()

model = Baseline3().to(device)
summary(model)

loss_fn = nn.CrossEntropyLoss(label_smoothing=0.1)
optimizer_ft = optim.Adam(model.parameters(), lr=1e-3)

#scheduler = lr_scheduler.CosineAnnealingWarmRestarts(optimizer_ft, T_0=20, T_mult=2, eta_min=1e-6)

# Set algo MIOPEN cudnn benchmark cache env var
os.environ['MIOPEN_USER_DB_PATH'] = os.path.join('models', 'miopen_conv_cache.udb')
# free optimization for fixed-size inputs
torch.backends.cudnn.benchmark = True

# use high matmul precision for matrices if we're using float32 types
torch.set_float32_matmul_precision('high')
#model_compiled = torch.compile(model)

model, _best_val, _elapsed = train(
    model, loss_fn, optimizer_ft,
    train_loader=train_loader, val_loader=val_loader,
    train_size=len(train_ds), val_size=len(val_ds),
    device=device, metrics=metrics,
    num_epochs=NUM_EPOCHS,
#    scheduler=scheduler,
	use_amp=False
)

plot_performance(metrics, os.path.join('models', f'{args.name}.png'))

torch.save(model.state_dict(), os.path.join('models', f'{args.name}.pt'))
write_training_log(args.name, _elapsed, NUM_EPOCHS, metrics, degraded=True)

plt.ioff()
plt.show()
