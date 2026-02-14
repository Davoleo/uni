import torch
from torchvision import models

import os

# Accelerator
device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu'
print(f"Accelerator: {device}")

# Model init
model = models.resnet18()

# model load
model.load_state_dict(os.path.join('models', 'fullfinetuning+horflip.pt'))