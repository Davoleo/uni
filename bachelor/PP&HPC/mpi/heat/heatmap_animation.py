import matplotlib
matplotlib.use('Agg')
#from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np
import sys
import os
from numpy import genfromtxt

outfile='heatmap'

if len(sys.argv) == 2:
  outfile=sys.argv[1]

bashCommand="mpicc -O2 mpi_heat.c -o mpi_heat.out"
print (bashCommand)
os.system(bashCommand)

for i in xrange(0,15000,1000):
  bashCommand = "mpirun -np 4 mpi_heat.out -r 512 -c 512 -s  "+str(i) +" > heatmap.out"
  os.system(bashCommand)
  filename=outfile+str(i).rjust(6,'0') +".png"
  a = genfromtxt('heatmap.out', delimiter=' ')
  plt.imsave(filename,a, cmap='hot')
  print ("outfile: " + filename)


bashCommand="convert -delay 20 -loop 0 "+ outfile  + "*.png " + outfile + ".gif"
print (bashCommand)
os.system(bashCommand)

bashCommand="rm "+ outfile  + "*.png"
print (bashCommand)
os.system(bashCommand)
