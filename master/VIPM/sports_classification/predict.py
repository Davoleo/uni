import argparse
import os

import torch
from PIL import Image
from torchvision.transforms import v2

from models import Baseline1, Baseline2, Baseline3, efficientnet_b3
from utils import get_device

parser = argparse.ArgumentParser()
parser.add_argument('image', help='Path to the image to classify')
parser.add_argument('--name', required=True, help='Checkpoint name (loaded from models/<name>.pt)')
parser.add_argument('--model', required=True, choices=['baseline1', 'baseline2', 'baseline3', 'efficient-net'],
                    help='Model architecture matching the checkpoint')
parser.add_argument('--topk', type=int, default=5, help='Number of top predictions to show (default: 5)')
args = parser.parse_args()

class_names = sorted(os.listdir('data/train'))

device = get_device()

# Prepare transforms to be applied to the img for being feed to the model
transform = v2.Compose([
    v2.ToImage(),
    v2.Resize(224),
    v2.CenterCrop(224),
    v2.ToDtype(torch.float32, scale=True),
])

# Get image from args
img = Image.open(args.image).convert('RGB')
# Transform to tensor
tensor = transform(img).unsqueeze(0).to(device)

# Choose which model is given from args
match args.model:
    case 'baseline1': model = Baseline1()
    case 'baseline2': model = Baseline2()
    case 'baseline3': model = Baseline3()
    case 'efficient-net': model = efficientnet_b3()
    case _: raise ValueError("Unknown model")

# load weights from args and send to device
model.load_state_dict(torch.load(os.path.join('models', f'{args.name}.pt'), weights_only=True, map_location=device))
model.to(device)
# Evaluate result
model.eval()

# Get the output of the model and apply softmax to get normalized model output
with torch.no_grad():
    outputs = model(tensor)
    probs = outputs.softmax(dim=1)[0]

# Get the topk predictions -> which are the most k likely classes
topk = min(args.topk, len(class_names))
top_probs, top_indices = probs.topk(topk)

# Print the topk predictions
print(f"\nPredictions for: {args.image}")
print("-" * 40)
for i, (prob, idx) in enumerate(zip(top_probs.tolist(), top_indices.tolist())):
    print(f"  {i+1}. {class_names[idx]:<30} {prob * 100:.2f}%")
