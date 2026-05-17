import timm
import torch
from torch import nn
from torchvision import models

NUM_CLASSES = 100
IMAGE_SIZE = 224

def resnet18(class_names, load_weights=True):
	model = models.resnet18(weights='IMAGENET1K_V1' if load_weights else None)
	
	# Complete Freeze [conv layers], except classifier
	for param in model.parameters():
		param.requires_grad = False
	
	#* Partial Freeze V4
	#model_base.layer1.requires_grad_(False)
	#model_base.layer2.requires_grad_(False)
	#model_base.layer3.requires_grad_(False)

	# Fully connected layer input features
	num_features = model.fc.in_features
	# Replace new Fully connected layer
	model.fc = nn.Linear(num_features, len(class_names))
	return model

def efficientnet_b3():
	model = timm.create_model('tf_efficientnetv2_b3.in21k', pretrained=True, num_classes=100)
	
	# Add dropout
	infeatures: Tensor = model.classifier.in_features # type: ignore
	model.classifier = nn.Sequential(
		nn.Dropout(0.5),
		nn.Linear(infeatures, 100)
	)
	return model


class Baseline1(nn.Module):
	r"""
	Baseline V1
	Overfitting
	"""

	def __init__(self, dropout=False, batchnorm=False):
		super(Baseline1, self).__init__()

		self.dropout = dropout
		self.batchnorm = batchnorm

		# Convolutional layer
		self.conv1 = nn.Conv2d(in_channels=3, out_channels=32, kernel_size=3, padding=0)
		if (batchnorm): self.bn1 = nn.BatchNorm2d(32)
		self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)

		self.conv2 = nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=0)
		if (batchnorm): self.bn2 = nn.BatchNorm2d(64)
		self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)

		self.conv3 = nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, padding=0)
		if (batchnorm): self.bn3 = nn.BatchNorm2d(128)
		self.pool3 = nn.MaxPool2d(kernel_size=2, stride=2)

		self.conv4 = nn.Conv2d(in_channels=128, out_channels=256, kernel_size=3, padding=0)
		if (batchnorm): self.bn4 = nn.BatchNorm2d(256)
		self.pool4 = nn.MaxPool2d(kernel_size=2, stride=2)

		# Fully conected layers
		self.fc = nn.Linear(256 * 12 * 12, 100)

	def forward(self, x):
		x = self.conv1(x)
		if (self.batchnorm): x = self.bn1(x)
		x = self.pool1(nn.functional.relu(x))

		x = self.conv2(x)
		if (self.batchnorm): x = self.bn2(x)
		x = self.pool2(nn.functional.relu(x))

		x = self.conv3(x)
		if (self.batchnorm): x = self.bn3(x)
		x = self.pool3(nn.functional.relu(x))

		x = self.conv4(x)
		if (self.batchnorm): x = self.bn4(x)
		x = self.pool4(nn.functional.relu(x))


		# Flattening to linear
		x = torch.flatten(x, 1)

		# dropout
		if (self.dropout):
			x = nn.functional.dropout(x, 0.5)

		x = self.fc(x)
		return x