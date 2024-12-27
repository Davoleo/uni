#!/bin/bash

#SBATCH --partition=cpu,cpu_guest
#SBATCH --job-name=omp_overh
#SBATCH --output=%x.o%j

##SBATCH --error=%x.e%j  #If error is not specified stderr is redirected to stdout
#SBATCH --nodes=1
#SBATCH --cpus-per-task=28
##SBATCH --time=0-00:05:00

## Uncomment the following line if you want to use an account other than your default account (see hpc-show-user-account)
##SBATCH --account=<account>

##SBATCH --exclusive  # uncomment to require a whole node with at least 28 cores

echo "#SLURM_JOB_NODELIST: $SLURM_JOB_NODELIST"

gcc -fopenmp omp_overhead.c -o omp_overhead

./omp_overhead 28 1000 1000
./omp_overhead 8 1000 1000
./omp_overhead 4 1000 1000
./omp_overhead 2 1000 1000
./omp_overhead 1 1000 1000


./omp_overhead 28 1000 2000
./omp_overhead 8 1000 2000
./omp_overhead 4 1000 2000
./omp_overhead 2 1000 2000
./omp_overhead 1 1000 2000


