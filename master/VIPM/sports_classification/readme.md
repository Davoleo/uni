# VIPM - Sports Image Classification

100-class sports image classification project with three tasks: scratch CNN, degradation-robust CNN, and traditional BoVW+SVM.

---

## Setup

Install [uv](https://docs.astral.sh/uv/getting-started/installation/), then sync dependencies for your hardware:

```bash
uv sync --extra <cpu|stable|nightly>
```

| Extra | Target |
|---|---|
| `cpu` | CPU-only |
| `stable` | AMD RX6000 series (ROCm 7.2) |
| `nightly` | AMD RX9070 (XT) cards (ROCm nightly) |

For RX9070 cards, install ROCm SDK libs after syncing:
```bash
./rocm_nightly.sh
```

Every script must be prefixed with `uv run --extra <extra>`. Examples below use `stable`; substitute as needed.

---

## Evaluation

### Tasks 1 & 2 — CNN models

`evaluate.py` reports F1, Top-1/3/5 accuracy for a given checkpoint and model architecture.

```bash
# Clean test set
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name>

# Degraded test set
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name> --degraded

# With Test-Time Augmentation (TTA)
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name> --degraded --tta

# With unsupervised image enhancement (combinable)
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name> --degraded --enhance wb
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name> --degraded --enhance gamma
uv run --extra <target> python evaluate.py --model <model> --weights <checkpoint_name> --degraded --enhance wb gamma
```

`--weights` is the checkpoint filename without extension (e.g. `v2.3_jitter_param_tuning`). Checkpoints are loaded from `models/<weights>.pt`.

`--model` must match the architecture the checkpoint was trained with (`baseline1`, `baseline2`, `baseline3`, `efficient-net`).

Available `--enhance` options:

| Flag | Transform |
|---|---|
| `wb` | White-patch white balance |
| `gamma` | Auto gamma correction (pulls mean brightness toward 0.5) |
| `cs` | Contrast stretch (percentile-based, 8th–92nd) |

### Task 3 — BoVW + SVM

Re-run the full pipeline (extracts dense SIFT, builds codebook, trains SVM, evaluates on both test sets, saves confusion matrices):

```bash
uv run --extra <cpu|stable|nightly> python oneshot.py
```

Results are appended to `iterations.log`. Confusion matrices are saved to `models/task3_confusion_clean.png` and `models/task3_confusion_degraded.png`.

---

## Training

### Task 1 — Scratch CNN (Baseline2)

```bash
uv run --extra <target> python baseline.py --weights <checkpoint_name>
```

### Task 2 — Degradation-robust CNN (Baseline3)

```bash
uv run --extra <target> python degraded.py --weights <checkpoint_name>
```

The `degraded.py` script extends the training pipeline with color-jitter augmentation calibrated to match the degraded test set distribution (brightness ±0.35, contrast ±0.4, saturation 0.7–3.0×, hue ±0.25).

Both scripts save the best-validation-accuracy checkpoint to `models/<name>.pt` and log results to `iterations.log`.

---

## Inference

`predict.py` runs a single image through a saved checkpoint and prints the top-k class probabilities.

```bash
uv run --extra <target> python predict.py <image_path> --model <model> --weights <checkpoint_name>

# Example
uv run --extra stable python predict.py my_photo.jpg --model efficient-net --name v5.3efficientnet_b3_partialfreeze+dropout

# Show top 3 predictions instead of the default 5
uv run --extra stable python predict.py my_photo.jpg --model efficient-net --name v5.3efficientnet_b3_partialfreeze+dropout --topk 3
```

`--model` must match the architecture the checkpoint was trained with (`baseline1`, `baseline2`, `baseline3`, `efficient-net`).

---

## Other Scripts

| Script | Purpose |
|---|---|
| `conv_benchmark.py` | GPU convolution throughput benchmark (TFLOP/s) |
| `show_enhancements.py` | Visualize before/after of image enhancement transforms |

### Cache cleanup

```bash
uv cache prune   # remove unreachable packages
uv cache clean   # remove all cached packages
```
