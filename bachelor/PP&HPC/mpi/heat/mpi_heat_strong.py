import matplotlib
matplotlib.use('Agg')   
import matplotlib.pyplot as plt
from numpy import *

data1 = loadtxt("mpi_heat_strong.dat")  #
TIM1=data1[:,0]  # time
PRC1=data1[:,1]  # numprocs


plt.figure(1) #
plt.suptitle('HEAT  MPI  strong scaling')

plt.subplot(211)
plt.grid()
plt.xlabel('tasks')
plt.ylabel('speedup')
plt.plot(PRC1,TIM1[0]/TIM1,'-o',label="MPI Strong")
plt.plot([1,16],[1,16],'r--',label='Ideal')
plt.legend()

plt.subplot(212)
plt.grid()
plt.xlabel('tasks')
plt.ylabel('time (s)')
plt.plot(PRC1, TIM1,'-o',label="MPI Strong")
plt.legend()


plt.savefig('mpi_heat_strong.png')

