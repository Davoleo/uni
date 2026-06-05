import os
import random
import subprocess
import sys
import time
from typing import Literal
from tempfile import TemporaryDirectory

import matplotlib.pyplot as plt
import numpy as np
import torch
from torchvision.transforms import v2


def get_device() -> str:
    device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else 'cpu'  # type: ignore
    print(f"Accelerator: {device}")
    return device


def seed_everything(seed: int):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    # cudnn.deterministic is intentionally left False — enabling it on ROCm triggers
    # fallback kernel paths that produce NaN gradients, killing training entirely.


def get_baseline_transforms() -> dict:
    return {
        'train': v2.Compose([
            v2.ToImage(),
            v2.RandomHorizontalFlip(),
            v2.RandomResizedCrop(224, scale=(0.6, 1.0)),
            v2.RandomAdjustSharpness(sharpness_factor=2),
            v2.ToDtype(torch.float32, scale=True),
        ]),
        'val': v2.Compose([
            v2.ToImage(),
            v2.ToDtype(torch.float32, scale=True),
        ]),
    }

def get_degraded_transforms() -> dict:
    base_transf = get_baseline_transforms()
    base_transf['train'] = v2.Compose([
        v2.ToImage(),
        v2.RandomHorizontalFlip(),
        v2.RandomResizedCrop(224, scale=(0.6, 1.0)),
        v2.ColorJitter(brightness=0.3, contrast=0.3, saturation=0.3, hue=0.1),
        v2.RandomAdjustSharpness(sharpness_factor=2),
        v2.ToDtype(torch.float32, scale=True)
    ])
    return base_transf


def plot_performance(metrics: dict, save_path: str):
    fig, ax = plt.subplots(1, 2, figsize=(10, 4))
    fig.tight_layout()
    ax[0].set_title('Loss')
    ax[0].set_xlabel('Epoch')
    ax[0].set_ylabel('Loss')
    ax[0].plot(metrics['train_loss'], label='train')
    ax[0].plot(metrics['val_loss'], label='val')
    ax[0].legend()
    ax[1].set_title('Accuracy')
    ax[1].set_xlabel('Epoch')
    ax[1].set_ylabel('Accuracy')
    ax[1].plot(metrics['train_accuracy'], label='train')
    ax[1].plot(metrics['val_accuracy'], label='val')
    ax[1].legend()
    plt.savefig(save_path)
    plt.show()


def train(model, lossfun, optimizer, *, train_loader, val_loader, train_size, val_size,
          device, metrics, scheduler=None, num_epochs=20):
    since = time.time()

    with TemporaryDirectory() as tempdir:
        best_model_path = os.path.join(tempdir, 'best_model_params.pt')
        torch.save(model.state_dict(), best_model_path)
        max_accuracy = 0.0

        for epoch in range(num_epochs):
            print(f'Epoch progress: {epoch + 1}/{num_epochs}')
            print('-' * 20)

            for phase in ['train', 'val']:
                dataloader = train_loader if phase == 'train' else val_loader
                model.train() if phase == 'train' else model.eval()

                running_loss = 0.0
                running_corrects = torch.tensor(0, device=device)

                for inputs, labels in dataloader:
                    inputs = inputs.to(device)
                    labels = labels.to(device)
                    optimizer.zero_grad()

                    with torch.set_grad_enabled(phase == 'train'):
                        outputs = model(inputs)
                        _, preds = torch.max(outputs, 1)
                        loss = lossfun(outputs, labels)
                        if phase == 'train':
                            loss.backward()
                            optimizer.step()

                    running_loss += loss.item() * inputs.size(0)
                    running_corrects += torch.sum(preds == labels.data)

                if phase == 'train' and scheduler is not None:
                    scheduler.step()

                n = train_size if phase == 'train' else val_size
                epoch_loss = running_loss / n
                epoch_accuracy = running_corrects.double() / n
                metrics[f'{phase}_loss'].append(epoch_loss)
                metrics[f'{phase}_accuracy'].append(epoch_accuracy.cpu())
                print(f'[{phase}] Loss: {epoch_loss:.4f}, Accuracy: {epoch_accuracy:.4f}')

                if phase == 'val' and epoch_accuracy > max_accuracy:
                    max_accuracy = epoch_accuracy
                    torch.save(model.state_dict(), best_model_path)
            print()

        time_elapsed = time.time() - since
        print(f'Training time: {time_elapsed // 60:.0f}mins {time_elapsed % 60:.0f}secs')
        print(f'Best Val Accuracy: {max_accuracy:.6f}')
        model.load_state_dict(torch.load(best_model_path, weights_only=True))
    return model, max_accuracy, time_elapsed


def write_training_log(name, elapsed, num_epochs, metrics,
                       test_dir='data/test', log_path='iterations.log'):
    mins, secs = int(elapsed // 60), int(elapsed % 60)
    result = subprocess.run(
        [sys.executable, 'evaluate.py', '--name', name, '--test-dir', test_dir],
        capture_output=True, text=True
    )
    test_line = next(
        (line.strip() for line in result.stdout.splitlines() if line.startswith('Accuracy:')),
        'evaluation failed'
    )
    entry = (
        f"\n{'=' * 54}\n"
        f"{name}\n"
        f"Epoch progress: {num_epochs}/{num_epochs}\n"
        f"--------------------\n"
        f"[train] Loss: {metrics['train_loss'][-1]:.4f}, Accuracy: {float(metrics['train_accuracy'][-1]):.4f}\n"
        f"[val] Loss: {metrics['val_loss'][-1]:.4f}, Accuracy: {float(metrics['val_accuracy'][-1]):.4f}\n"
        f"Training time: {mins}mins {secs}secs\n"
        f"Best Val Accuracy: {max(float(a) for a in metrics['val_accuracy']):.6f}\n"
        f"\nTest Set results: {test_line}\n"
    )
    with open(log_path, 'a') as f:
        f.write(entry)


@torch.no_grad()
def topk_accuracy(preds, truth, topk=1,):
    r'''
    Top-K Accuracy

    preds (batch_size, class_cnt)
    answer (batch_size)
    '''
    #save the batch size before tensor mangling
    bz = truth.size(0)
    #ignore preds values. its indices shapes: (sz,cnt) -> (sz,topk)
    _, indices = preds.topk(topk)
    #transpose the k best indice
    preds = indices.t()  #(sz,topk) -> (topk, sz)
    
    #repeat same labels topk times to match preds's shape
    truth = truth.view(1, -1)       #(sz) -> (1,sz)
    truth = truth.expand_as(preds) #(1,sz) -> (topk,sz)

    correct = (preds == truth)    #(topk,sz) of bool vals
    correct = correct.flatten()     #(topk*sz) of bool vals
    correct = correct.float()       #(topk*sz) of 1s or 0s
    correct = correct.sum()         #counts 1s (correct guesses)
    correct = correct.mul_(100/bz)  #convert into percentage

    return correct.item()