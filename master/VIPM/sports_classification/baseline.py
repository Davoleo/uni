"""
Task 1: Train the model on the training set and evaluate on the clean test set.
"""

import argparse
import os

import matplotlib.pyplot as plt
import torch
import torch.optim as optim
from torch import nn
from torchinfo import summary
from torchvision import datasets

from models import Baseline2 as Baseline
from utils import get_device, plot_performance, seed_everything, train, write_training_log
from transforms import get_train_transforms, get_val_transforms

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

train_ds = datasets.ImageFolder('data/train', get_train_transforms(degraded=False))
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


def display_predicts(model, num_images=6):
    was_training = model.training
    model.eval()
    image_counter = 0
    plt.figure()

    with torch.no_grad():
        for inputs, labels in val_loader:
            inputs = inputs.to(device)
            labels = labels.to(device)
            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)

            for j in range(inputs.size(0)):
                image_counter += 1
                ax = plt.subplot(num_images // 2, 2, image_counter)
                ax.axis('off')
                ax.set_title(f'predicted: {class_names[preds[j]]}')
                plt.imshow(inputs.cpu().data[j].numpy().transpose(1, 2, 0))
                if image_counter == num_images:
                    model.train(mode=was_training)
                    return
    model.train(mode=was_training)


model = Baseline().to(device)
summary(model)
exit()

loss_fn = nn.CrossEntropyLoss()
optimizer_ft = optim.Adam(model.parameters(), lr=1e-3)

torch.set_float32_matmul_precision('high')
model_compiled = torch.compile(model)

model_compiled, _best_val, _elapsed = train(
    model_compiled, loss_fn, optimizer_ft,
    train_loader=train_loader, val_loader=val_loader,
    train_size=len(train_ds), val_size=len(val_ds),
    device=device, metrics=metrics,
    num_epochs=NUM_EPOCHS,
    use_amp=True
)

plot_performance(metrics, os.path.join('models', f'{args.name}.png'))
display_predicts(model)

torch.save(model.state_dict(), os.path.join('models', f'{args.name}.pt'))
write_training_log(args.name, _elapsed, NUM_EPOCHS, metrics)

plt.ioff()
plt.show()
