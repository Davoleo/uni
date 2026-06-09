# AGENTS.md — Sports Classification (VIPM Final Project)

## Environment & toolchain

- **Python:** exactly `>=3.12,<3.13`
- **Package manager:** `uv` (not pip). Build backend: `uv_build`. Lockfile: `uv.lock`.
- **No packaging:** `package = false` in `pyproject.toml`. All `.py` files run as scripts from the project root.
- **GPU:** AMD ROCm (not CUDA). Three hardware extras, mutually exclusive:
  - `--extra stable` — RX6000 series (pre-built ROCm 7.2 wheels)
  - `--extra nightly` — RX9000 series (nightly gfx120X builds; requires `./rocm_nightly.sh` first)
  - `--extra cpu` — CPU-only PyTorch
- **Device detection** uses `torch.accelerator.current_accelerator()` (ROCm-compatible). Do NOT use `torch.cuda.*`.

## Running scripts

All scripts require an `--extra` and run from the project root (cwd = `sports_classification/`):

```bash
uv run --extra stable python baseline.py --name <checkpoint_name>
uv run --extra stable python degraded.py --name <checkpoint_name>
uv run --extra stable python evaluate.py --name <checkpoint_name> [--degraded] [--enhance wb gamma cs]
uv run --extra stable python conv_benchmark.py
uv run --extra stable python show_enhancements.py
```

Checkpoints are saved/loaded as `models/<name>.pt`; plots as `models/<name>.png`.

## Architecture

- **Flat module layout** — no `__init__.py`, no package. Everything is root-level `.py` files.
- **Models:** `project_models.py`. Only `Baseline2` is used by the main scripts (5 conv layers + AdaptiveAvgPool). `Baseline1`, `resnet18()`, `efficientnet_b3()` exist but are unused/dead code.
- **Transforms:** `project_transforms.py` — custom `AutoGammaCorrection`, `WhiteBalance`, `ContrastStretch`. Uses torchvision **v2** transforms API exclusively (not the older `torchvision.transforms`).
- **Utilities:** `project_utils.py` — shared `train()`, `seed_everything()`, `get_device()`, transform factories, logging.
- **Data layout:** `ImageFolder` convention — `data/{train,valid,test,test_degradato}/<class_name>/<images>`. Labels map: `data/sports_labels.csv`.
- **Entrypoints:**
  - `baseline.py` — Task 1: train on clean data, evaluate on clean test set (60 epochs, Adam lr=1e-3, BatchNorm+dropout)
  - `degraded.py` — Task 2: train with ColorJitter augmentation (80 epochs), evaluate on degraded test set
  - `evaluate.py` — standalone evaluation: loads a `.pt` checkpoint, computes Accuracy, F1-Score, Top-3/Top-5 accuracy

## Conventions & gotchas

- **Strict seed:** every training script calls `seed_everything(42)` with a seeded `torch.Generator()` passed to DataLoader.
- **`cudnn.deterministic` is intentionally `False`** — enabling it on ROCm triggers fallback kernels that produce NaN gradients.
- **No test suite, no linter config, no typechecker, no CI.** The project has `flake8` installed but no `.flake8` config. Do not run lint/typecheck commands — none are defined.
- **Logging:** `write_training_log()` appends to `iterations.log` and automatically calls `evaluate.py` as a subprocess to get test-set metrics. Expect nested `uv run` invocations if running from outside.
- **Transform import:** `project_transforms.py` does `from project_transforms import *` in `evaluate.py` — the custom classes are imported wildcard-style, which is intentional.

## Dead / experimental code

- `baseline_tensorflow.py` — older TensorFlow/Keras implementation (likely broken given the ROCm env).
- `test_board.ipynb` — interactive notebook for white balance testing.
- Code inside `project_models.py` beyond `Baseline2`, the commented-out CosineAnnealingLR in `baseline.py`, and unused imports (`pyqt6` is a dependency but unused).
