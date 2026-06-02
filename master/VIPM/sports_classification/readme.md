# VIPM - FINAL PROJECT

### NOTES ON THE ARCHITECTURES
- For RX6000 series use --extra stable decorator for the scripts 
- For RX9000 series run rocm_nightly.sh and then use --extra nightly decorator

note that every script must be executed with the proper environment dependencies, 
for example: `uv run --extra stable python conv_benchmark.py`

### TODO
- [ ] improve model evaluations steps (more than just accuracy)
- [ ] Add CNN from scratch values to iterations.log (either via tensorflow or pytorch)
- Model 1: Clean dataset
	- [ ] attempt to improve training times
	- [ ] 
- Model 2: Degraded dataset
	- [ ] Data Augmentation techniques
	- [ ] Unsupervised degraded image enhancement
- Model 3: Shot in the dark
	- [ ] Allenare il modello su validation set