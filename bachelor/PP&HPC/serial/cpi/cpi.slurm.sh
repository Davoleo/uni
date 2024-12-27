#!/bin/bash

#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest              # Nome della partizione, cpu per job paralleli
#SBATCH --qos=cpu_guest              # Nome della partizione, cpu per job paralleli
#SBATCH --nodes=1                    # numero di nodi richiesti
#SBATCH --cpus-per-task=1            # numero di cpu 
##SBATCH --mem=2G                    # massima memoria utilizzata
#SBATCH --time=0-00:10:00            # massimo tempo di calcolo
##SBATCH --account=T_2022_HPCPROGPAR  # account da utilizzare (per gli studenti del corso e' il default)

gcc cpi.c -o cpi -lm -O2

./cpi -n 1000000000 

