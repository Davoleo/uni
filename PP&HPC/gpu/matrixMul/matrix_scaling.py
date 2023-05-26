import matplotlib
matplotlib.use('Agg')   # Backend per PNG (http://matplotlib.org/faq/usage_faq.html#what-is-a-backend )
import matplotlib.pyplot as plt
from numpy import *

data0 = loadtxt("go_script_out/0-naive_cpu.txt", usecols=(2,5), delimiter=' ')
data1 = loadtxt("go_script_out/1-naive_gpu.txt", usecols=(2,5), delimiter=' ')
data2 = loadtxt("go_script_out/2-tiling.txt", usecols=(2,5), delimiter=' ')
data3 = loadtxt("go_script_out/3-coalescing.txt", usecols=(2,5), delimiter=' ')
data4 = loadtxt("go_script_out/4-bank_conflict.txt", usecols=(2,5), delimiter=' ')
data5 = loadtxt("go_script_out/5-optimization.txt", usecols=(2,5), delimiter=' ')
data6 = loadtxt("go_script_out/6-loop_unrolling.txt", usecols=(2,5), delimiter=' ')
data7 = loadtxt("go_script_out/7-prefetching.txt", usecols=(2,5), delimiter=' ')

x = range(1,21)

#data2 = loadtxt("cpi2_scaling_2.dat")

#print INT1

fig = plt.figure()
top = fig.add_subplot(111) # 1 riga, 1 colonna, figura 1

top.set_title('matrixMul Scaling - GFLOPS')
top.grid()
top.set_xlabel('TIME')
top.set_xscale('log')
#top.set_xlabel('intervalli')
top.set_yscale('log')
top.set_ylabel('GFLOPS')
top.plot(data0[:,0], data0[:,1],'-o',label='CPU Naive')
top.plot(data1[:,0], data1[:,1],'-o',label='GPU Naive')
top.plot(data2[:,0], data2[:,1],'-o',label='Tiling')
top.plot(data3[:,0], data3[:,1],'-o',label='Mem Coalescing')
# top.plot(data4[:,0], data4[:,1],'-o',label='Mem Bank Conflict')
# top.plot(data5[:,0], data5[:,1],'-o',label='Optimization')
top.plot(data6[:,0], data6[:,1],'-o',label='Loop Unrolling')
# top.plot(data7[:,0], data7[:,1],'-o',label='Prefetching')

top.legend(shadow=True)

plt.savefig('matrix.scaling.pdf')
#plt.show()