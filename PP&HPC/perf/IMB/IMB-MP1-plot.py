#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

shm_data = pd.read_csv("IMB-MPI1.shm.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )
opa_data = pd.read_csv("IMB-MPI1.opa.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )
iba_data = pd.read_csv("IMB-MPI1.ib.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )


plt.title('IMB-MP1 Bandwith Comparison')
plt.grid()
plt.xlabel('bytes')
plt.xscale('log')
plt.ylabel('MBps')
plt.plot(shm_data.bytes, shm_data.MBps, '-d', label='Shared Memory')
plt.plot(opa_data.bytes, opa_data.MBps, '-d', label='OmniPath')
plt.plot(iba_data.bytes, iba_data.MBps, '-d', label='Infiniband')
plt.legend(shadow=True, loc='upper left')
plt.savefig('IMB-MP1-Bandwidth.png')
plt.clf()

plt.title('IMB-MP1 Latency Comparison')
plt.xscale('log')
plt.xlabel('bytes')
plt.ylabel('time(us)')
plt.plot(shm_data.bytes, shm_data.time, 'b-', label='Shared Memory', color='blue')
plt.plot(opa_data.bytes, opa_data.time, 'b-', label='OmniPath', color='green')
plt.plot(iba_data.bytes, iba_data.time, 'b-', label='Infiniband', color='red')
plt.legend(shadow=True, loc='upper left')

plt.savefig('IMB-MP1-Latency.png')
plt.show()
