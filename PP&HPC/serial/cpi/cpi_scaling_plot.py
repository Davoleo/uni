import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

cpi = pd.read_csv("cpi_scaling.csv") 

plt.title('CPI  Legge di Amdahl  -   Roberto Alfieri  <data>')
plt.grid()
plt.xlabel('Intervalli')
#plt.yscale('log')
plt.ylabel('tempo')
plt.plot(cpi.iter,cpi.t_np,'r-o',label='Tnp')
plt.plot(cpi.iter,cpi.t_p,'g-o',label='Tp')
plt.legend(shadow=True)
plt.savefig('cpi_scaling_tempo.png')

plt.clf()

plt.title('CPI  Legge di Amdahl  -   Roberto Alfieri  <data>')
plt.grid()
plt.xlabel('Intervalli')
#plt.yscale('log')
plt.ylabel('quote')
plt.plot(cpi.iter,cpi.t_np/(cpi.t_p+cpi.t_np),'r-o',label='Qnp')
plt.plot(cpi.iter,cpi.t_p/(cpi.t_p+cpi.t_np),'g-o',label='Qp')
plt.legend(shadow=True)
plt.savefig('cpi_scaling_quote.png')

