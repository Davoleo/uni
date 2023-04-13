#!/bin/bash

#SBATCH --output=%x.o%j-25  # Nome del file per lo strandard output
##SBATCH --error=%x.e%j  # Se non specificato stderr e' rediretto su stdout
#SBATCH --partition=cpu_guest              # Nome della partizione, cpu per job paralleli
#SBATCH --qos=cpu_guest              # 
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --cpus-per-task=16            # numero di cpu 
##SBATCH --mem=4G                    # massima memoria utilizzata
#SBATCH --time=10:10:00            # massimo tempo di calcolo

gcc module_factorize.c -o module_factorize -O2 -lcrypto

time ./module_factorize 25
