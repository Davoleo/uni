#!/bin/bash
#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest              # Nome della partizione
#SBATCH --qos=cpu_guest              # Nome della partizione
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=8          # numero di cpu per nodo
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo


echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"

module purge
module load intel impi
mpiicc -O2  mpi_cpi.c -o mpi_cpi -lm

N=100000000


mpirun  mpi_cpi -n $N  
