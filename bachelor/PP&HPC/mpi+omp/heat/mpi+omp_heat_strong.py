#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg') # backend per png
import matplotlib.pyplot as plt
import pandas as pd

data_ser     = pd.read_csv("heat_strong.dat"     ,comment="#", sep=',',    names=["r",   "c","iter", "time", "tp", "tnp"])
data_omp     = pd.read_csv("omp_heat_strong.dat" ,comment="#", sep=',',  names=["r",    "c","iter", "time","tp", "tnp","thr"])
data_mpi     = pd.read_csv("mpi_heat_strong.dat" ,comment="#", sep='\s+',  names=["time", "task","r", "c","iter"])
data_hyb     = pd.read_csv("mpi+omp_heat_strong.dat" ,comment="#", sep='\s+',  names=["r", "c","iter", "time", "task","thr"])

plt.subplot(211)
plt.suptitle('Heat strong scaling,  1000 iter ')
plt.grid()
plt.xlabel('threads')
plt.ylabel('Speedup')
plt.plot(data_omp.thr, data_ser.time[0]/data_omp.time,'-o', label='openMP')
plt.plot(data_mpi.task,data_ser.time[0]/data_mpi.time,'-o', label='MPI')
plt.plot(data_hyb.task*data_hyb.thr,data_ser.time[0]/data_hyb.time,'-o', label='MPI+openMP')
plt.plot(range(1,10),range(1,10),'-r', label='Ideal')
plt.legend(shadow=True,loc="best")

plt.subplot(212)
plt.grid()
plt.xlabel('tasks x threads')
plt.ylabel('time (s)')
plt.plot(data_omp.thr,data_omp.time,'-o', label='openMP')
plt.plot(data_mpi.task,data_mpi.time,'-o', label='MPI')
plt.plot((data_hyb.task*data_hyb.thr),data_hyb.time,'-o', label='MPI+openMP')
plt.plot(1,data_ser.time,'-o', label='serial')
plt.legend(shadow=True,loc="best")

plt.savefig('mpi+omp_heat_strong.png')

