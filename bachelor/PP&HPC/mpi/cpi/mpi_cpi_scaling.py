#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg') 
import matplotlib.pyplot as plt
from numpy import *

data1 = loadtxt("mpi_cpi_strong.dat")
INTS=data1[:,1]  # intervalli
ERRS=data1[:,3]  # errore
TIMS=data1[:,4]  # time
RANKS=data1[:,5]  # rank

data2 = loadtxt("mpi_cpi_weak.dat")
INTW=data2[:,1]  # intervalli
ERRW=data2[:,3]  # errore
TIMW=data2[:,4]  # time
RANKW=data2[:,5]  # rank


fig = plt.figure() # 
top = fig.add_subplot(111) # 1 riga, 1 colonna, figura 1

top.grid()
top.set_title('CPI MPI Strong Scaling')
top.set_xlabel('numero di task')
top.set_ylabel('Speedup')

top.plot(RANKS,TIMS[0]/TIMS,'o-',label='CPI Strong')
top.plot(RANKW,RANKW*TIMW[0]/TIMW,'o-',label='CPI Weak')
top.plot([1,16],[1,16],'r--',    label='Ideal')

top.legend(shadow=True,loc="best")

plt.savefig('mpi_cpi_scaling.png')
