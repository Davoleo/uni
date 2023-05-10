#!/bin/sh

#SBATCH --output=/dev/null
#SBATCH --partition=cpu_guest        # Nome della partizione
#SBATCH --qos=cpu_guest              # Nome della partizione
#SBATCH --nodes=2                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=8          # numero di cpu per nodo
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo


echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"

module purge
module load intel impi
mpicc -O2 mpi_heat.c -o mpi_heat.out

rm -f mpi_heat_strong.dat

for P in 1 2 4 8 16
do
    mpirun -np $P mpi_heat.out -c 2048 -r 2048  1> /dev/null  2>> mpi_heat_strong.dat
done 
