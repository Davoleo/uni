#!/usr/bin/env python2

#https://www.easytweaks.com/bar-plot-python-pandas-dataframe-example/

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import pandas as pd 

df = pd.read_csv("networks.dat",comment="#", sep='\s+')
#print df

df.plot(kind='bar' , x='device', title='High Speed Networks');
#df.plot(kind='bar' , x='device', y=['cost','band']);

plt.savefig('networks_barplot.png')
