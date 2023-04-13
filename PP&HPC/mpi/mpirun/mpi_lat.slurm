#!/bin/bash
#SBATCH --job-name=mpi-lat     # Nome del file per lo strandard output
#SBATCH --output=%x.o%j     # Nome del file per lo strandard output
##SBATCH --error=%x.e%j      # Se non specificato stderr e' rediretto su stdout
#SBATCH --partition=cpu_guest,cpu    # Nome della partizione
#SBATCH --nodes=2                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=2          # numero di cpu per nodo
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo
#SBATCH --account=T_2022_HPCPROGPAR  # account da utilizzare

echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"
echo  "#SLURM_JOB_PARTITION     : $SLURM_JOB_PARTITION"


echo " ###################### GNU "
module purge
module load gnu8 openmpi3

mpicc mpi_latency.c   -o mpi_latency

echo gnu8 senza-opzioni
mpirun                      hostname
mpirun                      mpi_latency  | grep Avg

echo gnu8 npernode 1
mpirun  -np 2  -npernode 1  hostname
mpirun  -np 2  -npernode 1  mpi_latency  | grep Avg

echo gnu8 npernode 2
mpirun  -np 2  -npernode 2  hostname
mpirun  -np 2  -npernode 2  mpi_latency  | grep Avg

echo " ###################### INTEL "
module purge
module load intel impi
mpicc mpi_latency.c   -o mpi_latency

echo intel senza opzioni
mpirun     hostname
mpirun     mpi_latency | grep Avg

echo intel  mpicc -ppn 2 
mpirun  -np 2  -ppn 2    hostname
mpirun  -np 2  -ppn 2    mpi_latency | grep Avg

mpiicc mpi_latency.c   -o mpi_latency

echo intel  mpiicc ppn 1
mpirun  -np 2  -ppn 1   hostname
mpirun  -np 2  -ppn 1  mpi_latency | grep Avg

echo intel  mpiicc ppn 2
mpirun  -np 2  -ppn 2    hostname
mpirun  -np 2  -ppn 2    mpi_latency | grep Avg

