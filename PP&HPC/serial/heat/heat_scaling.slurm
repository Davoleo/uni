#!/bin/bash

#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest        # Nome della partizione
#SBATCH --qos=cpu_guest    
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --cpus-per-task=1            # numero di cpu 
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo
##SBATCH --account=T_2022_HPCPROGPAR  # account da utilizzare



echo "nx,ny,iter,T,Tp,Tnp" > heat_scaling.csv

#for N in $(seq 1000000 100000 9000000)
for N  in  256 512 758 1024
do
./heat -c $N  -r $N -s 1000  >> heatmap.out
done   2>> heat_scaling.csv

