# Laboratorio: Performance [GPU]

## `deviceQuery`

| deviceQuery | Global Memory | L2 Cache Size | GPU Max Clock rate | CUDA cores |
| ----------- | ------------- | ------------- | ------------------ | ---------- |
| P100        | 12.198 GB     | 3.145 MB      | 1.33 GHz           | 3584       |
| A100 40GB   | 40.354 GB     | 41.943 MB     | 1.41 GHz           | 6912       |
| V100        | 32.511 GB     | 6.291 MB      | 1.38 GHz           | 5120       |

## `bandwidthTest`

| bandwidthTest | Host to Device | Device to Host | Device to Device
| ------------- | -------------- | -------------- | ------------------ |
| P100          | 8.8 GB/s       | 12.8 GB/s      | 382.4 GB/s         |
| A100 40GB     | 19.9 GB/s      | 18.4 GB/s      | 1159.4 GB/s        |
| V100          | 13.1 GB/s      | 13.6 GB/s      | 726.6 GB/s         |

## `nbody simulation`

| nbody       | GFLOPS/s double precision |
| ----------- | ------------------------- |
| P100        | 2815.744 GFLOPS/s         |
| A100 40GB   | 7112.216 GFLOPS/s         |
| V100        | 5228.293 GFLOPS/s         |