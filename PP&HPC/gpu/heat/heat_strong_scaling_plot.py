#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg') # backend per png
import matplotlib.pyplot as plt
import pandas as pd

data_16 = pd.read_csv("time/timings.dat", sep=',', comment='#', names=["NX", "NY", "MAX_ITER", "CPU_TIME", "GPU_TIME"])

data_shared = pd.read_csv("time/timings_shared.dat", sep=',', comment='#', names=["NX", "NY", "MAX_ITER", "CPU_TIME", "GPU_TIME"])

data_4 = pd.read_csv("time/timings_block_4.dat", sep=',', comment='#', names=["NX", "NY", "MAX_ITER", "CPU_TIME", "GPU_TIME"])
data_8 = pd.read_csv("time/timings_block_8.dat", sep=',', comment='#', names=["NX", "NY", "MAX_ITER", "CPU_TIME", "GPU_TIME"])
data_32 = pd.read_csv("time/timings_block_32.dat", sep=',', comment='#', names=["NX", "NY", "MAX_ITER", "CPU_TIME", "GPU_TIME"])

plt.figure(1)
plt.suptitle('GPU_Heat scaling')

plt.subplot(121)
plt.grid()
plt.xlabel('Size')
plt.ylabel('Time')
plt.plot(data_16.NX, data_16.GPU_TIME,'-o', label='global')
plt.plot(data_shared.NX, data_shared.GPU_TIME,'-o', label='shared')
plt.legend(shadow=True,loc="best")

plt.subplot(122)
plt.grid()
plt.xlabel('Size')
plt.ylabel('Time')
plt.plot(data_4.NX, data_4.GPU_TIME,'-o', label='block: 4')
plt.plot(data_8.NX, data_8.GPU_TIME,'-o', label='block: 8')
plt.plot(data_16.NX, data_16.GPU_TIME,'-o', label='block: 16')
plt.plot(data_32.NX, data_32.GPU_TIME,'-o', label='block: 32')
plt.legend(shadow=True, loc="best")

plt.savefig('gpu_heat_timeplot.png')

