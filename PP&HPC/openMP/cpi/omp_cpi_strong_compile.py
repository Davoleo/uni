#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')   # Backend per PNG 
import matplotlib.pyplot as plt
import pandas as pd

g5 = pd.read_csv("omp_cpi_strong.gnu5.dat", sep='\s+', names=["f", "n","pi","error","time","thr","host"])
g4 = pd.read_csv("omp_cpi_strong.gnu4.dat", sep='\s+', names=["f", "n","pi","error","time","thr","host"])
g8 = pd.read_csv("omp_cpi_strong.gnu8.dat", sep='\s+', names=["f", "n","pi","error","time","thr","host"])
int = pd.read_csv("omp_cpi_strong.intel.dat", sep='\s+', names=["f", "n","pi","error","time","thr","host"])


#print (data)

plt.title('CPI omp scaling <nome e data>')

plt.grid()
plt.title('strong scaling')
plt.xlabel('threads')
plt.ylabel('time')
plt.plot(g4.thr,g4.time[0]/g4.time,  '-o', label='gnu4')
plt.plot(g5.thr,g5.time[0]/g5.time,  '-o', label='gnu5')
plt.plot(g8.thr,g8.time[0]/g8.time,  '-o', label='gnu8')
plt.plot(int.thr,int.time[0]/int.time,  '-o', label='intel')
plt.plot(range(1,10),range(1,10),'-r', label='Ideal')
plt.legend(shadow=True,loc="best")

plt.savefig('omp_cpi_strong_compile_speedup.png')

plt.clf()


plt.grid()
plt.title('strong scaling')
plt.xlabel('threads')
plt.ylabel('time')
plt.plot(g5.thr,g5.time,  '-o', label='gnu5')
plt.plot(g4.thr,g4.time,  '-o', label='gnu4')
plt.plot(g8.thr,g8.time,  '-o', label='gnu8')
plt.plot(int.thr,int.time,  '-o', label='intel')
#plt.plot(range(1,10),range(1,10),'-r', label='Ideal')
plt.legend(shadow=True,loc="best")

plt.savefig('omp_cpi_strong_compile_time.png')

