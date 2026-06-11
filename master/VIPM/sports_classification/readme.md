# VIPM - FINAL PROJECT

### NOTES ON THE ARCHITECTURES
- For RX6000 series use --extra stable decorator for the scripts 
- For RX9000 series run rocm_nightly.sh and then use --extra nightly decorator

note that every script must be executed with the proper environment dependencies, 
for example: `uv run --extra stable python conv_benchmark.py`

### TODO
- [x] improve model evaluations steps (more than just accuracy)
- [x] Add CNN from scratch values to iterations.log (either via tensorflow or pytorch)
- Model 1: Clean dataset
	- [x] attempt to improve training times
	- [x] more model generalization
- Model 2: Degraded dataset
	- [x] Data Augmentation techniques
	- [x] Unsupervised degraded image enhancement
- Model 3: Shot in the dark
	- [x] Allenare il modello su validation set