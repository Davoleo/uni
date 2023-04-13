#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')   # Backend per PNG 
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("omp_cpi_strong.dat", sep='\s+', names=["f", "n","pi","error","time","thr","host"])


plt.title('CPI omp scaling <nome e data>')

plt.grid()
plt.title('strong scaling')
plt.xlabel('threads')
plt.ylabel('time')
plt.plot(data.thr,data.time,  '-o', label="CPI")
plt.legend(shadow=True,loc="best")

plt.savefig('omp_cpi_strong_time.png')


plt.clf()

plt.title('CPI omp scaling <nome e data>')

plt.grid()
plt.title('strong scaling')
plt.xlabel('threads')
plt.ylabel('speedup')
plt.plot(data.thr,data.time[0]/data.time,  '-o', label="CPI")
plt.plot(range(1,10),range(1,10),'-r', label='Ideal')
plt.legend(shadow=True,loc="best")

plt.savefig('omp_cpi_strong_speedup.png')


