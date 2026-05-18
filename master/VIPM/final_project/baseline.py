
"""
TASK 1 of the project.
It uses test and train folders.
"""

import argparse
import os
import random
import subprocess
import sys
import time
from tempfile import TemporaryDirectory

import matplotlib.pyplot as plt
import numpy as np
import torch
import torch.backends.cudnn as cudnn
import torch.optim as optim
import torchvision
from torch import Tensor
from torchinfo import summary
from torchvision import datasets
from torchvision.transforms import v2

from project_models import *

SEED = 42
NUM_EPOCHS = 60
BATCH_SIZE = 32

# cudnn.benchmark = True
plt.ion()

def seed_everything(seed: int):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    # cudnn.deterministic is intentionally left False — enabling it on ROCm triggers
    # fallback kernel paths that produce NaN gradients, killing training entirely.

seed_everything(SEED)
_rng = torch.Generator()
_rng.manual_seed(SEED)

parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help='Checkpoint name (saved as models/<name>.pt)')
args = parser.parse_args()

# Data Augmentation - Horizontal flip and transform to tensor
# TODO: implement different augmentation methods
data_transforms = {
	'train': v2.Compose(transforms=[
		v2.ToImage(),
		v2.RandomHorizontalFlip(),
		v2.RandomResizedCrop(224, scale=(0.6, 1.0)),
		v2.RandomAdjustSharpness(sharpness_factor=2),
		# Using torch.float32 already normalizes the tensor channels values
		v2.ToDtype(torch.float32, scale=True)
	]),
	'val': v2.Compose(transforms=[
		v2.ToImage(),
		v2.ToDtype(torch.float32, scale=True)
	])
}

# Data Directories
train_dir = 'data/train'
val_dir = 'data/valid'
test_dir = 'data/test'

# Datasets
train_ds = datasets.ImageFolder(train_dir, data_transforms['train'])
val_ds = datasets.ImageFolder(val_dir, data_transforms['val'])
test_ds = datasets.ImageFolder(test_dir)

# Data Loading
train_loader = torch.utils.data.DataLoader(train_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=4, generator=_rng)
val_loader = torch.utils.data.DataLoader(val_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=4, generator=_rng)

# dataset sizes
train_size = len(train_ds)
val_size = len(val_ds)

# Classes
class_names = train_ds.classes

metrics = {
	'train_loss': [],
	'train_accuracy': [],
	'val_loss': [],
	'val_accuracy': []
}

# Use accelerator to train
device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu' # type: ignore | Accelerator always has a type if it's available
print(f"Accelerator: {device}")

#* CPU training
# device = 'cpu'

def imdisplay(input, title=None):
	"""Display tensor as image"""
	input = input.numpy().transpose((1,2,0))
	plt.imshow(input)
	if title is not None:
		plt.title(title)
	plt.pause(0.001)	# Pause allows to display current pyplot

def plotflush():
	plt.ioff()
	plt.show()

# Load a batch
demo_inputs, demo_classes = next(iter(train_loader))

grid = torchvision.utils.make_grid(demo_inputs)
#imdisplay(grid, title=[class_names[x] for x in demo_classes])

#plotflush()
#exit(0)

def train(model, lossfun, optimizer, scheduler=None, num_epochs=20):
	since = time.time()

	with TemporaryDirectory() as tempdir:
		best_model_path = os.path.join(tempdir, 'best_model_params.pt')
		torch.save(model.state_dict(), best_model_path)

		max_accuracy = 0.0

		for epoch in range(num_epochs):
			print(f'Epoch progress: {epoch+1}/{num_epochs}')
			print('-' * 20)

			# Phases
			for phase in ['train', 'val']:
				dataloader = None
				# Change model mode depending on phase
				if phase == 'train':
					model.train()
					dataloader = train_loader
				else:
					model.eval()
					dataloader = val_loader

				running_loss = 0.0
				# Instantiate a counter in the GPU as a tensor so it can be modified inside GPU
				running_corrects: Tensor = torch.tensor(0, device=device)

				# Iterate
				for inputs,labels in dataloader:
					# Send to gpu
					inputs = inputs.to(device)
					labels = labels.to(device)

					# Reset gradient
					optimizer.zero_grad()

					# forward - gradient only used in train phase
					with torch.set_grad_enabled(phase == 'train'):
						outputs = model(inputs)
						_, preds = torch.max(outputs, 1)
						loss = lossfun(outputs, labels)

						# backward + optimization in training
						if phase == 'train':
							loss.backward()
							optimizer.step()

					# stats
					running_loss += loss.item() * inputs.size(0)
					running_corrects += torch.sum(preds == labels.data)

				if phase == 'train':
					scheduler.step() if scheduler is not None else ""

				epoch_loss = running_loss / (train_size if phase == 'train' else val_size)
				epoch_accuracy = running_corrects.double() / (train_size if phase == 'train' else val_size)
				metrics[f"{phase}_loss"].append(epoch_loss)
				metrics[f"{phase}_accuracy"].append(epoch_accuracy.cpu())

				print(f"[{phase}] Loss: {epoch_loss:.4f}, Accuracy: {epoch_accuracy:.4f}")

				# deep copy
				if phase == 'val' and epoch_accuracy > max_accuracy:
					max_accuracy = epoch_accuracy
					torch.save(model.state_dict(), best_model_path)
			print()

		time_elapsed = time.time() - since
		print(f'training time: {time_elapsed // 60:.0f}mins {time_elapsed % 60:.0f}secs')
		print(f'Best Val Accuracy: {max_accuracy:4f}')

		model.load_state_dict(torch.load(best_model_path, weights_only=True))
	return model, max_accuracy, time_elapsed

def display_predicts(model, num_images=6):
	was_training = model.training
	model.eval()
	image_counter = 0
	_ = plt.figure()

	with torch.no_grad():
		for i, (inputs, labels) in enumerate(val_loader):
			inputs = inputs.to(device)
			labels = labels.to(device)

			outputs = model(inputs)
			_, preds = torch.max(outputs, 1)

			for j in range(inputs.size()[0]):
				image_counter += 1
				ax = plt.subplot(num_images // 2, 2, image_counter)
				ax.axis('off')
				ax.set_title(f'predicted: {class_names[preds[j]]}')
				plt.imshow(inputs.cpu().data[j].numpy().transpose(1,2,0))

				if image_counter == num_images:
					model.train(mode=was_training)
					return
		model.train(mode=was_training)

def write_training_log(name, elapsed, num_epochs, log_path='iterations.log'):
	mins, secs = int(elapsed // 60), int(elapsed % 60)
	result = subprocess.run([sys.executable, 'evaluate.py', '--name', name], capture_output=True, text=True)
	test_line = next((l.strip() for l in result.stdout.splitlines() if l.startswith('Accuracy:')), 'evaluation failed')
	entry = (
		f"\n{'=' * 54}\n"
		f"{name}\n"
		f"Epoch progress: {num_epochs}/{num_epochs}\n"
		f"--------------------\n"
		f"[train] Loss: {metrics['train_loss'][-1]:.4f}, Accuracy: {float(metrics['train_accuracy'][-1]):.4f}\n"
		f"[val] Loss: {metrics['val_loss'][-1]:.4f}, Accuracy: {float(metrics['val_accuracy'][-1]):.4f}\n"
		f"training time: {mins}mins {secs}secs\n"
		f"Best Val Accuracy: {max(float(a) for a in metrics['val_accuracy']):.6f}\n"
		f"\nTest Set results: {test_line}\n"
	)
	with open(log_path, 'a') as f:
		f.write(entry)

def plot_performance(metrics):
	fig = plt.figure()
	fig, ax = plt.subplots(1, 2)
	fig.tight_layout()
	train_acc = metrics['train_accuracy']
	valid_acc = metrics['val_accuracy']
	train_loss = metrics['train_loss']
	valid_loss = metrics['val_loss']
	ax[0].set_xlabel('Epoch')
	ax[0].set_ylabel('Loss')
	ax[0].set_title('Loss')
	ax[0].plot(train_loss)
	ax[0].plot(valid_loss)
	ax[1].set_title('Accuracy')
	ax[1].set_xlabel('Epoch')
	ax[1].set_ylabel('Accuracy')
	ax[1].plot(train_acc)
	ax[1].plot(valid_acc)
	plt.savefig(os.path.join('models', f'{args.name}.png'))
	plt.show()


#from project_models import resnet18
#model_base = resnet18()

# pretrain on imagenet 21k since it contains sport subcategories
model_base = Baseline2()

model_ft = model_base.to(device)
# Show current status of the model architectures (layers etc.)
summary(model_ft)

loss = nn.CrossEntropyLoss()
optimizer_ft = optim.Adam(model_ft.parameters(), lr=1e-3)

# Learning rate decay: 0.1 factor every 7 epochs
# from 1e-4 to 1e-6 with a cosine slope
# ft_lr_scheduler = lr_scheduler.CosineAnnealingLR(optimizer_ft, T_max=45, eta_min=1e-6)

# Training Stage 1
model_ft, _best_val, _elapsed = train(model_ft, loss, optimizer_ft, num_epochs=NUM_EPOCHS)


# Training stage 2
# Unfreeze conv head
# optimizer_ft = optim.AdamW([
# 	{"params": model_ft.classifier.parameters(), "lr": 2e-4},
# 	{"params": model_ft.global_pool.parameters(), "lr": 2e-4},
# 	{"params": model_ft.bn2.parameters(), "lr": 2e-4},
# 	{"params": model_ft.conv_head.parameters(), "lr": 2e-5},
# ], weight_decay=1e-2)
# model_ft.conv_head.requires_grad_(True)
# model_ft = train(model_ft, loss, optimizer_ft, num_epochs=15)

plot_performance(metrics)

# Display some predictions
display_predicts(model_ft)

# Save model for evaluation
torch.save(model_ft.state_dict(), os.path.join('models', f'{args.name}.pt'))
write_training_log(args.name, _elapsed, NUM_EPOCHS)

plotflush()