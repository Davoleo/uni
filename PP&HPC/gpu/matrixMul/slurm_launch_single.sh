#!/bin/sh
 
# Richiedi un nodo con una gpu
#SBATCH --partition=gpu
#SBATCH --nodes=1 
#SBATCH --mem=4G

#SBATCH --qos=gpu
#SBATCH --gres=gpu:p100:1
##SBATCH -–account=t_2022_hpcprogpar
##SBATCH --reservation=t_2022_hpcprogpar_20230525

# Dichiara che il job durera' al massimo 3 minuti
#SBATCH --time=0-01:00:00

#stampa il nome del nodo assegnato e argomenti                 
echo "#SLURM_JOB_NODELIST   : $SLURM_JOB_NODELIST"
echo "#CUDA_VISIBLE_DEVICES : $CUDA_VISIBLE_DEVICES"
echo "size A= $WA X $HA,B= $WB X $HB" 

#esegui il programma
module load cuda 
./bin/matrixMul -wA=$WA -hA=$HA -wB=$WB -hB=$HB
