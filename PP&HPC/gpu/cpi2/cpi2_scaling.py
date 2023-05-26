import matplotlib
matplotlib.use('Agg')   # Backend per PNG (http://matplotlib.org/faq/usage_faq.html#what-is-a-backend )
import matplotlib.pyplot as plt
from numpy import *

data1 = loadtxt("cpi2_scaling_1.dat")
INT1=data1[:,1]  # intervalli
ERR1=data1[:,3]  # errore
TIM1=data1[:,4]  # gettimeofday

data2 = loadtxt("cpi2_scaling_2.dat")
INT2=data2[:,1]  # intervalli
ERR2=data2[:,3]  # errore
TIM2=data2[:,4]  # gettimefday

#print INT1

fig = plt.figure() # 
top = fig.add_subplot(111) # 1 riga, 1 colonna, figura 1

top.set_title('CPI performance   <NOME>  <data>')
top.grid()
top.set_xlabel('tempo')
#top.set_xlabel('intervalli')
top.set_yscale('log')
top.set_ylabel('errore')
top.plot(TIM1,ERR1,'go',label='CPI_F1')
top.plot(TIM2,ERR2,'ro',label='CPI_F2')
top.legend(shadow=True)


plt.savefig('cpi2_scaling.pdf')
#plt.show()
