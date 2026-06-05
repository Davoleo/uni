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

from project_models import Baseline2
from project_utils import get_device, get_baseline_transforms, plot_performance, seed_everything, train, write_training_log

SEED = 42
NUM_EPOCHS = 60
BATCH_SIZE = 32

plt.ion()

seed_everything(SEED)
_rng = torch.Generator()
_rng.manual_seed(SEED)

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (saved as models/<name>.pt)')
args = parser.parse_args()

data_transforms = get_baseline_transforms()

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


model_ft = Baseline2().to(device)
summary(model_ft)

loss_fn = nn.CrossEntropyLoss()
optimizer_ft = optim.Adam(model_ft.parameters(), lr=1e-3)

# Cosine LR decay example (unused):
# scheduler = lr_scheduler.CosineAnnealingLR(optimizer_ft, T_max=45, eta_min=1e-6)

model_ft, _best_val, _elapsed = train(
    model_ft, loss_fn, optimizer_ft,
    train_loader=train_loader, val_loader=val_loader,
    train_size=len(train_ds), val_size=len(val_ds),
    device=device, metrics=metrics,
    num_epochs=NUM_EPOCHS,
)

plot_performance(metrics, os.path.join('models', f'{args.name}.png'))
display_predicts(model_ft)

torch.save(model_ft.state_dict(), os.path.join('models', f'{args.name}.pt'))
write_training_log(args.name, _elapsed, NUM_EPOCHS, metrics)

plt.ioff()
plt.show()
