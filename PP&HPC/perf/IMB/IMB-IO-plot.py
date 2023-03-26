#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

home_read = pd.read_csv("IMB-IO-S_Read-indv.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )
home_write = pd.read_csv("IMB-IO-S_Write-indv.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )

#print (imb.MBps)

plt.title('IMB IO throughput /hpc/home/')
plt.grid()
plt.xlabel('bytes')
plt.xscale('log')
plt.ylabel('MBps')
plt.plot(home_read.bytes, home_read.MBps, '-d', color='green', label='Read Throughput')
plt.plot(home_write.bytes, home_write.MBps, '-d', color='orange', label='Write Throughput')
plt.legend(shadow=True)
plt.savefig('IMB-IO_home_throughput.png')
plt.clf()

scratch_read = pd.read_csv("SSD-IMB-IO-S_Read-indv.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )
scratch_write = pd.read_csv("SSD-IMB-IO-S_Write-indv.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )

plt.title('IMB IO throughput /hpc/scratch')
plt.grid()
plt.xlabel('bytes')
plt.xscale('log')
plt.ylabel('MBps')
plt.plot(scratch_read.bytes, scratch_read.time, '-d', color='green', label='read Throughput')
plt.plot(scratch_write.bytes, scratch_write.time, '-d', color='orange', label='Write Throughput')
plt.legend(shadow=True)
plt.savefig('IMB-IO_scratch_throughput.png')
plt.show()
