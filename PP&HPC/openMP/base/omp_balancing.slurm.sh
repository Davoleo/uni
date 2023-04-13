#!/bin/bash

#SBATCH --partition=cpu_guest
#SBATCH --qos=cpu_guest
#SBATCH --output=%x.o%j

#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --time=0-00:05:00


echo "#SLURM_JOB_NODELIST: $SLURM_JOB_NODELIST"

gcc -fopenmp omp_balancing.c -o omp_balancing


./omp_balancing -n  1000
