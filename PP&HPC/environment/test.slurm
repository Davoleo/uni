#!/bin/bash
#SBATCH --output=%x.o%j
#SBATCH --partition=cpu
#SBATCH --cpus-pert-task=1
##SBATCH --mem=2G
#SBATCH --time=0-00:10:00
#SBATCH --account=T_2022_HPCPROGPAR
#SBATCH --qos=cpu
##SBATCH --qos=cpu_guest
##SBATCH --partition=cpu_guest
#SBATCH --nodes=1

echo "test job slurm"
