#!/usr/bin/env python2

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

imb = pd.read_csv("IMB.dat",comment="#", sep='\s+',  names=["bytes", "repetitions","time","MBps"] )

#print (imb.MBps)

plt.title('IMB Throughput   <NOME>  <data>')
plt.grid()
plt.xlabel('bytes')
plt.xscale('log')
plt.ylabel('MBps')
plt.plot(imb.bytes, imb.MBps, 'ro', label='throughput')

plt.savefig('IMB_thr.png')

plt.clf()

plt.title('IMB Latency  <NOME>  <data>')
plt.xscale('log')
plt.xlabel('bytes')
plt.ylabel('time(us)')
plt.plot(imb.bytes,imb.time,'b-', label='latency')
plt.axis([1,10000,0,200])

plt.savefig('IMB_lat.png')
plt.show()
