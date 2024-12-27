import matplotlib
matplotlib.use('Agg')   # Backend per PNG 
import matplotlib.pyplot as plt
from numpy import *

data1 = loadtxt("omp_cpi_strong.dat")
INTS=data1[:,1]  # intervalli
TIMS=data1[:,4]  # gettimeofday
THRS=data1[:,5]  # numthreads

plt.figure(1) #
plt.suptitle('CPI omp scaling <nome e data>')

plt.grid()
plt.title('strong scaling')
plt.xlabel('threads')
plt.ylabel('speedup')
plt.plot(THRS,TIMS[0]/TIMS,      '-o', label='Strong')
plt.plot(range(1,10),range(1,10),'-r', label='Ideal')
plt.legend(shadow=True,loc="best")

plt.savefig('omp_cpi_strong.png')


