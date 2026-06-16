# VIPM - SPORTS CLASSIFICATION

### NOTES ON THE ARCHITECTURES
- For RX6000 series use `--extra stable` decorator for the scripts 
- For RX9070 cards run rocm_nightly.sh and then use `--extra nightly` decorator

note that every script must be executed with the proper environment dependencies, 
for example: `uv run --extra stable python conv_benchmark.py`


### Installing dependencies
Install package manager: [astral.uv](https://docs.astral.sh/uv/getting-started/installation/)

```bash
uv sync --extra <cpu|stable|nightly>
```

### Running scripts
```bash
uv run --extra <cpu|stable|nightly>  <scriptname.py>
```

### Clean UV cache
clean all unreachable objects and dependencies
```bash
uv cache prune
```
clean all dependencies
```bash
uv cache clean
```