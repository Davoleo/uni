import torch
import time

# Convolution settings
batch_size = 32
height = 256
width = 256
in_channels = 64
out_channels = 64
kernel_size = (3, 3)
stride = (1, 1)
padding = 1

# Number of warmup and measured runs
warmup = 2
runs = 10

# Dtypes to test
dtypes = {
    "float32": torch.float32,
}

def benchmark(dtype_name, dtype):
    print(f"\nTesting {dtype_name}...")

    x = torch.randn((batch_size, in_channels, height, width), dtype=dtype, device="cuda")  # NCHW
    w = torch.randn((out_channels, in_channels, *kernel_size), dtype=dtype, device="cuda") # OIHW

    conv = torch.nn.functional.conv2d

    # Warmup
    for _ in range(warmup):
        y = conv(x, w, stride=stride, padding=padding)
        torch.cuda.synchronize()

    # Timed run
    start = time.time()
    for _ in range(runs):
        y = conv(x, w, stride=stride, padding=padding)
        torch.cuda.synchronize()
    end = time.time()

    total_time = end - start
    avg_time = total_time / runs

    # Approx FLOPs for Conv2D: 2 * H * W * Cout * (Cin * Kx * Ky) * B
    flops = 2 * height * width * out_channels * (in_channels * kernel_size[0] * kernel_size[1]) * batch_size
    tflops = flops / avg_time / 1e12

    print(f"Avg time: {avg_time:.6f} s, Throughput: {tflops:.2f} TFLOP/s")


for name, dtype in dtypes.items():
    try:
        benchmark(name, dtype)
    except Exception as e:
        print(f"Skipped {name} due to error: {e}")