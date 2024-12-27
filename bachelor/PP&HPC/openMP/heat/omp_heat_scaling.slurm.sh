#!/bin/bash
#SBATCH --output=/dev/null
#SBATCH --error=%x.e%j
#SBATCH --partition=cpu_guest
#SBATCH --qos=cpu_guest
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --time=1:00:00


gcc -O2 omp_heat.c -fopenmp -o omp_heat

echo "nx,ny,iter,T,Tp,Tnp,nthreads" > omp_heat_scaling_gnu4.csv

for T in 1 2 4 8 16
do
    ./omp_heat -c 2048 -r 2048 -s 1000 -t $T > heatmap.out
done  2>> omp_heat_scaling_gnu4.csv

# -----------

module purge
module load gnu8

gcc -O2 omp_heat.c -fopenmp -o omp_heat
echo "nx,ny,iter,T,Tp,Tnp,nthreads" > omp_heat_scaling_gnu8.csv

for T in 1 2 4 8 16
do
    ./omp_heat -c 2048 -r 2048 -s 1000 -t $T > heatmap.out
done  2>> omp_heat_scaling_gnu8.csv

# ---

module purge
module load gnu

gcc -O2 omp_heat.c -fopenmp -o omp_heat
echo "nx,ny,iter,T,Tp,Tnp,nthreads" > omp_heat_scaling_gnu5.csv

for T in 1 2 4 8 16
do
    ./omp_heat -c 2048 -r 2048 -s 1000 -t $T > heatmap.out
done  2>> omp_heat_scaling_gnu5.csv


# ---

module purge
module load intel

icc -O2 omp_heat.c -fopenmp -o omp_heat
echo "nx,ny,iter,T,Tp,Tnp,nthreads" > omp_heat_scaling_intel.csv

for T in 1 2 4 8 16
do
    ./omp_heat -c 2048 -r 2048 -s 1000 -t $T > heatmap.out
done  2>> omp_heat_scaling_intel.csv