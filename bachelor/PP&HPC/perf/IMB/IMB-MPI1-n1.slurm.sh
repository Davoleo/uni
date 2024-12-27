#!/bin/bash
#SBATCH --job-name=IMB-MPI1-shm     #
#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
##SBATCH --error=%x.e%j  # Se non specificato stderr e' rediretto su stdout
#SBATCH --partition=cpu    # Nome della partizione
#SBATCH --qos=cpu          
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=2          # numero di cpu per nodo
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo

echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"

module load intel impi

CMD="mpirun    IMB-MPI1 pingpong"
echo "# $CMD"
eval $CMD   >  IMB-MPI1.shm.dat

