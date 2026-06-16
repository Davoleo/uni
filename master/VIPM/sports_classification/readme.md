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
| `nightly` | AMD RX9000 series (ROCm nightly) |

For RX9000 cards, install ROCm SDK libs first:
```bash
./rocm_nightly.sh
```

Every script must be prefixed with `uv run --extra <extra>`. Examples below use `stable`; substitute as needed.

---

## Evaluation

### Tasks 1 & 2 — CNN models WARNIIIIIIIING: we can't choose which architecture we should use! maybe we should fix it.

`evaluate.py` loads a `Baseline2` checkpoint and reports F1, Top-1/3/5 accuracy.

```bash
# Clean test set
uv run --extra stable python evaluate.py --name <checkpoint_name>

# Degraded test set
uv run --extra stable python evaluate.py --name <checkpoint_name> --degraded

# With Test-Time Augmentation (TTA)
uv run --extra stable python evaluate.py --name <checkpoint_name> --degraded --tta

# With unsupervised image enhancement (combinable)
uv run --extra stable python evaluate.py --name <checkpoint_name> --degraded --enhance wb
uv run --extra stable python evaluate.py --name <checkpoint_name> --degraded --enhance gamma
uv run --extra stable python evaluate.py --name <checkpoint_name> --degraded --enhance wb gamma
```

`--name` is the checkpoint filename without extension (e.g. `v2.3_jitter_param_tuning`). Checkpoints are loaded from `models/<name>.pt`.

Available `--enhance` options:

| Flag | Transform |
|---|---|
| `wb` | White-patch white balance |
| `gamma` | Auto gamma correction (pulls mean brightness toward 0.5) |
| `cs` | Contrast stretch (percentile-based, 8th–92nd) |

> **Note:** `evaluate.py` is hardcoded for `Baseline2`. To evaluate `Baseline3` or EfficientNet checkpoints, change the import at line 9 to the appropriate class (`Baseline3` or `efficientnet_b3` from `models.py`).

### Task 3 — BoVW + SVM

Re-run the full pipeline (extracts dense SIFT, builds codebook, trains SVM, evaluates on both test sets, saves confusion matrices):

```bash
uv run --extra stable python oneshot.py
```

Results are appended to `iterations.log`. Confusion matrices are saved to `models/task3_confusion_clean.png` and `models/task3_confusion_degraded.png`.

---

## Training

### Task 1 — Scratch CNN (Baseline2)

```bash
uv run --extra stable python baseline.py --name <checkpoint_name>
```

### Task 2 — Degradation-robust CNN (Baseline3)

```bash
uv run --extra stable python degraded.py --name <checkpoint_name>
```

The `degraded.py` script extends the training pipeline with color-jitter augmentation calibrated to match the degraded test set distribution (brightness ±0.35, contrast ±0.4, saturation 0.7–3.0×, hue ±0.25).

Both scripts save the best-validation-accuracy checkpoint to `models/<name>.pt` and log results to `iterations.log`.

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
