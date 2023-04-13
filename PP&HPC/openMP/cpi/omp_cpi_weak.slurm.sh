#!/bin/sh
#SBATCH --output=%x.o%j
#SBATCH --partition=cpu_guest
#SBATCH --qos=cpu_guest
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --time=0-00:10:00

module load gnu
gcc -O2 -fopenmp omp_cpi.c -o omp_cpi -lm

rm -f omp_cpi_weak.dat

N=50000000

T=1
while [ $T -le ${SLURM_CPUS_PER_TASK} ]
do
CMD="./omp_cpi -n $((N*T)) -T $T"
echo $CMD
eval $CMD >> omp_cpi_weak.dat
T=$((2*T))
done
