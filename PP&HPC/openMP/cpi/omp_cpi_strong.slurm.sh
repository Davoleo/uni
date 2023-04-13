#!/bin/bash

#SBATCH --output=%x.o%j-stat
#SBATCH --partition=cpu_guest
#SBATCH --qos=cpu_guest
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --time=0-00:10:00


N=500000000

gcc -O2 -fopenmp  omp_cpi.c  -o  omp_cpi -lm
T=1
while [ $T -le ${SLURM_CPUS_PER_TASK} ]
do
./omp_cpi -f 2 -n $N -t $T  2> /dev/null
T=$((2*T))
done  > omp_cpi_strong.gnu4.dat

