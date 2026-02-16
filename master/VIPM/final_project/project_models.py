import timm
from torch import nn
from torchvision import models

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
	return timm.create_model('tf_efficientnetv2_b3.in21k', pretrained=True, num_classes=100)