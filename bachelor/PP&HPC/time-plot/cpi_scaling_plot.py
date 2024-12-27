#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

cpi = pd.read_csv("cpi_scaling.csv") 

cpi1 = cpi[cpi.function==1]
cpi2 = cpi[cpi.function==2]

plt.title('CPI performance   <NOME>  <data>')
plt.grid()
plt.xlabel('tempo')
plt.yscale('log')
plt.ylabel('errore')
plt.plot(cpi1.time,cpi1.error,'ro',label='CPI_F1')
plt.plot(cpi2.time,cpi2.error,'go',label='CPI_F2')
plt.legend(shadow=True)


plt.savefig('cpi_scaling_plot.png')
#plt.show()
