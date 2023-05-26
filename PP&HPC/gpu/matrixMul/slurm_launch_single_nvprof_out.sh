#!/bin/sh
 
# Richiedi un nodo con una gpu
#SBATCH --partition=gpu
#SBATCH --nodes=1 
#SBATCH --mem=4G

#SBATCH --qos=gpu
#SBATCH --gres=gpu:p100:1

# Dichiara che il job durera' al massimo 1 minuto
#SBATCH --time=0-00:01:00

#stampa il nome del nodo assegnato e argomenti                 
echo "#SLURM_JOB_NODELIST   : $SLURM_JOB_NODELIST"
echo "#CUDA_VISIBLE_DEVICES : $CUDA_VISIBLE_DEVICES"
echo "size A= $WA X $HA,B= $WB X $HB" 

#esegui il programma
module load cuda 
nvprof --analysis-metrics -o test.nvprof ./bin/matrixMul -wA=1000 -hA=1000 -wB=1000 -hB=1000
