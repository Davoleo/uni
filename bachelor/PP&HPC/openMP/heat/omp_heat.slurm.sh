#!/bin/bash

#SBATCH --output=%x.o%j                 # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest           # Nome della partizione
#SBATCH --qos=cpu_guest    
#SBATCH --nodes=1                       # numero di nodi richiesti
#SBATCH --cpus-per-task=16               # numero di cpu 
##SBATCH --mem=2G                       # massima memoria utilizzata
#SBATCH --time=0-00:10:00               # massimo tempo di calcolo
##SBATCH --account=T_2022_HPCPROGPAR    # account da utilizzare

gcc -O2 omp_heat.c -fopenmp -o omp_heat

./omp_heat > heatmap.out 
