#!/bin/bash
#SBATCH --job-name=IMB-IO     #
#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
##SBATCH --error=%x.e%j  # Se non specificato stderr e' rediretto su stdout
#SBATCH --partition=cpu              # Nome della partizione
#SBATCH --qos=cpu                      # Nome della partizione
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=1          # numero di cpu per nodo
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo

echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"

module load intel impi

./mpi-benchmarks-IMB/IMB-IO S_Write_indv  >  IMB-IO-S_Write-indv.dat
./mpi-benchmarks-IMB/IMB-IO S_Read_indv  >  IMB-IO-S_Read-indv.dat

