import torch
from torch import Tensor
from torchvision import datasets, transforms

from sklearn.metrics import accuracy_score, f1_score, confusion_matrix

from project_models import *

import scipy
import os

device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu' # type: ignore
print(f"Accelerator: {device}")

test_dir = 'data/test'
test_ds = datasets.ImageFolder(test_dir, transform=transforms.ToTensor())

loader = torch.utils.data.DataLoader(test_ds, batch_size=len(test_ds))
# Classes
class_names = test_ds.classes

# TODO : Implement confidence intervals (very confused)
def compute_confidence_interval(data: Tensor, confidence: float = 0.95) -> Tensor:
	"""
	Compute confidence intervals analitically for :param data: to obtain interval in which the mean should fall :param confidence:% of the times 
	"""
	n = len(data)
	mean: Tensor = data.mean()
	se: Tensor = data.std(unbiased=True) / (n**0.5)
	t_p: float = float(scipy.stats.t.ppf((1+confidence) / 2., n-1))
	ci = t_p * se
	return torch.tensor([mean, ci])

# Model init
# model = resnet18(class_names, load_weights=False)
model = efficientnet_b3()
# model load
model.load_state_dict(torch.load(os.path.join('models', 'v5.1efficientnet_b3_adamw.pt')))
model.eval()


with torch.no_grad():
	for images, labels in loader:
		outputs = model(images)
		_, preds = torch.max(outputs, 1)
		
		accuracy = accuracy_score(labels, preds)
		f1 = f1_score(labels, preds, average='macro')
		#cm = confusion_matrix(labels, preds, labels=class_names)

		print(f"Accuracy: {accuracy}, F1-Score: {f1}")
		print('-'*20)
#print(cm)