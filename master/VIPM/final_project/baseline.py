import timm
import torch
import torch.nn as nn
import torch.optim as optim
from torch.optim import lr_scheduler
import torch.backends.cudnn as cudnn

import torchvision
from torchvision import datasets, models, transforms

from torchinfo import summary

import numpy as np
import matplotlib.pyplot as plt

import os
import time
from tempfile import TemporaryDirectory

cudnn.benchmark = True
plt.ion()

data_transforms = {
	'train': transforms.Compose(transforms=[
		transforms.RandomHorizontalFlip(),
		transforms.ToTensor()
	]),
	'val': transforms.ToTensor(),
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
train_loader = torch.utils.data.DataLoader(train_ds, batch_size=128, shuffle=True, num_workers=4)
val_loader = torch.utils.data.DataLoader(val_ds, batch_size=128, shuffle=True, num_workers=4)

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
device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu'
print(f"Accelerator: {device}")

#* CPU training
# device = 'cpu'

def imdisplay(input, title=None):
	"""Display tensor as image"""
	input = input.numpy().transpose((1,2,0))
	input = np.clip(input, 0, 1)
	plt.imshow(input)
	if title is not None:
		plt.title(title)
	plt.pause(0.001)	# Pause allows to display current pyplot

def plotflush():
	plt.ioff()
	plt.show()	

# Load a batch
inputs, classes = next(iter(train_loader))

grid = torchvision.utils.make_grid(inputs)
imdisplay(grid, title=[class_names[x] for x in classes])


def train(model, lossfun, optimizer, scheduler, num_epochs=20):
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
				running_corrects = 0

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
					scheduler.step()

				epoch_loss = running_loss / (train_size if phase == 'train' else val_size)
				epoch_accuracy = running_corrects.double() / (train_size if phase == 'train' else val_size)
				metrics[f"{phase}_loss"].append(epoch_loss)
				metrics[f"{phase}_accuracy"].append(epoch_accuracy.cpu())

				print(f"{phase} Loss: {epoch_loss:.4f}, Accuracy: {epoch_accuracy:.4f}")

				# deep copy
				if phase == 'val' and epoch_accuracy > max_accuracy:
					max_accuracy = epoch_accuracy
					torch.save(model.state_dict(), best_model_path)
			print()
		
		time_elapsed = time.time() - since
		print(f'training time: {time_elapsed // 60:.0f}mins {time_elapsed % 60:.0f}secs')
		print(f'Best Val Accuracy: {max_accuracy:4f}')

		model.load_state_dict(torch.load(best_model_path, weights_only=True))
	return model

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
	plt.show()


#from project_models import resnet18
#model_base = resnet18()

model_base = timm.create_model('efficientnet_b3.in21k', pretrained=True, num_classes=100)

model_ft = model_base.to(device)
loss = nn.CrossEntropyLoss()

summary(model_ft)

optimizer_ft = optim.Adam(model_ft.parameters(), lr=1e-4)

# Learning rate decay: 0.1 factor every 7 epochs
# from 1e-4 to 1e-6 with a cosine slope
ft_lr_scheduler = lr_scheduler.CosineAnnealingLR(optimizer_ft, T_max=45, eta_min=1e-6)

# Training
model_ft = train(model_ft, loss, optimizer_ft, ft_lr_scheduler, num_epochs=16)

plot_performance(metrics)

# Display some predictions
display_predicts(model_ft)

# Save model for evaluation
torch.save(model_ft.state_dict(), os.path.join('models', 'v4adam.pt'))

plotflush()