#!/bin/bash
#SBATCH --output=/dev/null  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest              # Nome della partizione
#SBATCH --qos=cpu_guest              # Nome della partizione
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=32         # numero di cpu per nodo
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo


echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"

module purge
module load intel impi
mpiicc -O2  mpi_cpi.c -o mpi_cpi -lm

N=100000000

# cancello eventuali file .dat preesistenti
rm  -f mpi_cpi_strong.dat
rm  -f mpi_cpi_weak.dat

#for P in 1 2 4 8 16 32 64 128 256
for P in 1 2 4 8 16 32
do
mpirun -np $P mpi_cpi -n $N          >> mpi_cpi_strong.dat
mpirun -np $P mpi_cpi -n $(($N*$P))  >> mpi_cpi_weak.dat
done
