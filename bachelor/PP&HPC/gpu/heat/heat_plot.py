import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import sys
import os
from numpy import genfromtxt

name='heat'

if len(sys.argv) == 2:
  name=sys.argv[1]
infile=name
outfile=name+".png"

a = genfromtxt(infile, delimiter=' ')
plt.imsave(outfile,a, cmap='hot')
print ("outfile: " + outfile)
