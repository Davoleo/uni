import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

df = pd.read_csv("heat_scaling.csv") 

plt.title('HEAT  Legge di Amdahl  -   Roberto Alfieri  <data>')
plt.grid()
plt.xlabel('punti')
#plt.yscale('log')
plt.ylabel('tempo')
plt.plot(df.nx*df.ny,df.Tnp,'r-o',label='Tnp')
plt.plot(df.nx*df.ny,df.Tp,'g-o',label='Tp')
plt.legend(shadow=True)
plt.savefig('heat_scaling_tempo.png')

plt.clf()

plt.title('HEAT  Legge di Amdahl  -   Roberto Alfieri  <data>')
plt.grid()
plt.xlabel('punti')
#plt.yscale('log')
plt.ylabel('quote')
plt.plot(df.nx*df.ny,df.Tnp/(df.Tp+df.Tnp),'r-o',label='Qnp')
plt.plot(df.nx*df.ny,df.Tp/(df.Tp+df.Tnp),'g-o',label='Qp')
plt.legend(shadow=True)
plt.savefig('heat_scaling_quote.png')

