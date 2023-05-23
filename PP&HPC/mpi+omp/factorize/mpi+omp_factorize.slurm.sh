#!/bin/bash
#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest       # Nome della partizione
#SBATCH --qos=cpu_guest              # Nome della partizione
#SBATCH --nodes=2                    # numero di nodi richiesti
#SBATCH --constraint=omnipath        # ! make sure we use intel OPAs
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8        
#SBATCH --time=0-02:00:00            # massimo tempo di calcolo

echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"

module purge
module load intel impi
#module load gnu8 openmpi3

mpicc mpi+omp_factorize.c -o mpi+omp_factorize -O2 -lcrypto -lm -fopenmp

#Modulus=97219FA6BD3D7735                  # 64 bit
#Modulus=B81915BC0A2222F4B                # 68 bit
Modulus=F27F04CC3A51A3090B7D             # 80 bit
#Modulus=CD2C32D00F3E6CC158F1E069         # 96 bit
#Modulus=D44DC0CA2A7C693B46A96E01B47C8F15 #128 bit

Address=6
#mpirun  mpi+omp_factorize   -m $Modulus -a $Address  
for T in 1 2 4 8
do
    OMP_NUM_THREADS=$T mpirun -ppn 1 mpi+omp_factorize   -m $Modulus -a $Address
done

