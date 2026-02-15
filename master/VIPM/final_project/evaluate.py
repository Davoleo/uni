import torch
from torchvision import datasets, transforms

from sklearn.metrics import accuracy_score, f1_score, confusion_matrix

from project_models import resnet18

import os

device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu'
print(f"Accelerator: {device}")

test_dir = 'data/test'
test_ds = datasets.ImageFolder(test_dir, transform=transforms.ToTensor())

loader = torch.utils.data.DataLoader(test_ds, batch_size=len(test_ds))
# Classes
class_names = test_ds.classes


# Model init
model = resnet18(class_names, load_weights=False)
# model load
model.load_state_dict(torch.load(os.path.join('models', 'partialfreezingv4+horflip.pt')))
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
		