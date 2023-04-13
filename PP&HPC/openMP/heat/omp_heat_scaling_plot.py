import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

df_gnu = pd.read_csv("omp_heat_scaling_gnu4.csv")
df_gnu8 = pd.read_csv("omp_heat_scaling_gnu8.csv")
df_gnu5 = pd.read_csv("omp_heat_scaling_gnu5.csv")
df_intel = pd.read_csv("omp_heat_scaling_intel.csv")


plt.title('HEAT  - Time Strong Scaling')
plt.grid()
plt.xlabel('threads')
#plt.yscale('log')
plt.ylabel('tempo')
plt.plot(df_gnu.nthreads, df_gnu.Tnp, 'r-o', label='Tnp')
plt.plot(df_gnu.nthreads, df_gnu.Tp, 'g-o', label='Tp_gnu')
plt.plot(df_gnu8.nthreads, df_gnu8.Tp, 'y-o', label='Tp_gnu8')
plt.plot(df_gnu5.nthreads, df_gnu5.Tp, 'b-o', label='Tp_gnu5')
plt.plot(df_intel.nthreads, df_intel.Tp, 'm-o', label='Tp_intel')
plt.legend(shadow=True)
plt.savefig('heat_scaling_tempo.png')

plt.clf()

plt.title('HEAT - Speedup')
plt.grid()
plt.xlabel('threads')
#plt.yscale('log')
plt.ylabel('speedup')

# ideal_speedup = []
# for i in range(3):
#     ideal_speedup[i] = df.at[0, 'Tp'] / df.at[i, 'nthreads']

plt.plot(df_gnu.nthreads, (df_gnu.at[0, 'Tp']/df_gnu.nthreads)/df_gnu.Tp, 'g-o', label='Speedup_gnu')
plt.plot(df_gnu8.nthreads, (df_gnu8.at[0, 'Tp']/df_gnu8.nthreads)/df_gnu8.Tp, 'y-o', label='Speedup_gnu8')
plt.plot(df_gnu5.nthreads, (df_gnu5.at[0, 'Tp']/df_gnu5.nthreads)/df_gnu5.Tp, 'b-o', label='Speedup_gnu5')
plt.plot(df_intel.nthreads, (df_intel.at[0, 'Tp']/df_intel.nthreads)/df_intel.Tp, 'm-o', label='Speedup_intel')
plt.legend(shadow=True)
plt.savefig('heat_scaling_speedup.png')

