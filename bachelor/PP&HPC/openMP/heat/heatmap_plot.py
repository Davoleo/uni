import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import sys
import os
from numpy import genfromtxt

name='heatmap'

if len(sys.argv) == 2:
  name=sys.argv[1]
tmpfile=name+".dat"
outfile=name+".png"
bashCommand = "./heat > " +  tmpfile
os.system(bashCommand)

a = genfromtxt(tmpfile, delimiter=' ')
plt.imsave(outfile,a, cmap='hot')
print ("outfile: " + outfile)
