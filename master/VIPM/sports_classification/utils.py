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

from transforms import JPEGCompression


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


def get_val_transforms():
    return v2.Compose([
        v2.ToImage(),
        v2.ToDtype(torch.float32, scale=True)
    ])

def get_train_transforms(degraded=False):
    steps = [
        v2.ToImage(),
        v2.RandomHorizontalFlip(),
        v2.RandomResizedCrop(224, scale=(0.6, 1.0)),
    ]
    if degraded:
        steps.append(v2.ColorJitter(
            brightness=0.35, contrast=0.4,
            saturation=(0.7, 3.0), hue=0.25,
        ))
        #steps.append(v2.RandomErasing(p=0.4, scale=(0.02, 0.2)))
    steps.append(v2.RandomAdjustSharpness(sharpness_factor=2))
    steps.append(v2.ToDtype(torch.float32, scale=True))
    return v2.Compose(steps)


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


def mixup_data(x, y, alpha=0.2):
    if alpha > 0:
        # the beta distribution is U-shaped so most of the times 0.2 would give blended images with 10/90% and 90/10% proportions
        lam = np.random.beta(alpha, alpha)
    else:
        lam = 1.0

    batch_size = x.size(0)
    index = torch.randperm(batch_size, device=x.device)

    mixed_x = lam * x + (1 - lam) * x[index]
    y_a, y_b = y, y[index]
    return mixed_x, y_a, y_b, lam


def mixup_criterion(criterion, pred, y_a, y_b, lam):
    """
    Loss function is changed to make use of the lam (proportions of the 2 images)
    to instruct the model of the mixup between the 2 classes as the answer.
    """
    return lam * criterion(pred, y_a) + (1 - lam) * criterion(pred, y_b)


def train(model, lossfun, optimizer, *, train_loader, val_loader, train_size, val_size,
          device, metrics, scheduler=None, num_epochs=20,
          train_gpu_transform=None, use_amp=False):
    since = time.time()
    scaler = torch.GradScaler() if use_amp else None

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
                    inputs = inputs.to(device, non_blocking=True)
                    labels = labels.to(device, non_blocking=True)
                    if phase == 'train' and train_gpu_transform is not None:
                        inputs = train_gpu_transform(inputs)
                    optimizer.zero_grad()

                    with torch.set_grad_enabled(phase == 'train'):
                        with torch.autocast(device_type=device, dtype=torch.float16, enabled=(use_amp and phase == 'train')):
                            outputs = model(inputs)
                            _, preds = torch.max(outputs, 1)
                            loss = lossfun(outputs, labels)
                        if phase == 'train':
                            if scaler is not None:
                                scaler.scale(loss).backward()
                                scaler.step(optimizer)
                                scaler.update()
                            else:
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


def write_training_log(name, elapsed, num_epochs, metrics, degraded=True, log_path='iterations.log'):
    mins, secs = int(elapsed // 60), int(elapsed % 60)
    result = subprocess.run(
        [sys.executable, 'evaluate.py', '--name', name],
        capture_output=True, text=True
    )
    clean_test_line = next(
        (line.strip() for line in result.stdout.splitlines() if line.startswith('F1-Score:')),
        'evaluation failed'
    )

    degraded_test_line = None
    if (degraded):
        result = subprocess.run(
            [sys.executable, 'evaluate.py', '--name', name, '--degraded' if degraded else ''],
            capture_output=True, text=True
        )
        degraded_test_line = next(
        (line.strip() for line in result.stdout.splitlines() if line.startswith('F1-Score:')),
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
        f"\nClean Test Set results: {clean_test_line}\n"
        f"Degraded Test Set Results: {degraded_test_line}" if degraded else ""
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

def predict_tta(model, images, tta_transforms):
    """
    Averaged softmax probabilities across tta_transforms.
    """
    n_transf = len(tta_transforms)
    batch = len(images)
    # Stacking: [batch*n_transf, channels, height, width] - all augmentations are part of the same batch
    augmented_batch = torch.cat([transf(images) for transf in tta_transforms], dim=0)
    all_probs = model(augmented_batch).softmax(dim=1)
    # reshapin to [n_transf, batch_size, classes] and average over transforms
    return all_probs.view(n_transf, batch, -1).mean(dim=0)