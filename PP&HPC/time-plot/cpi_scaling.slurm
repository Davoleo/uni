#!/bin/bash

#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
##SBATCH --error=%x.e%j  # Se non specificato stderr e' rediretto su stdout
#SBATCH --partition=cpu_guest              # Nome della partizione, cpu per job paralleli
#SBATCH --qos=cpu_guest              # 
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --cpus-per-task=1            # numero di cpu 
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo


gcc cpi.c -o cpi -lm -O2

echo "function,iter,pi,error,time,hostname" > cpi_scaling.csv

for N in $(seq 100000 10000 900000)
#for N  in  1000 2000 3000
do
./cpi -n $N -f 1 >> cpi_scaling.csv
./cpi -n $N -f 2 >> cpi_scaling.csv
done


