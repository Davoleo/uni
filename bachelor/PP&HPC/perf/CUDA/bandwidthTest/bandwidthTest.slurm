#!/bin/bash

#SBATCH --output=%x.o%j-V100  # Nome del file per lo strandard output
##SBATCH --error=%x.e%j       # Se non specificato stderr e' rediretto su stdout 
#SBATCH --partition=gpu_guest
#SBATCH --qos=gpu_guest
#SBATCH --nodes=1
#SBATCH --gres=gpu:v100_hylab:1
#SBATCH --time=0-00:10:00

#SBATCH --mem=2G
 
 
module load gnu/5.4.0   cuda/11.5.2
 
echo "#SLURM_JOB_NODELIST   : $SLURM_JOB_NODELIST"
echo "#CUDA_VISIBLE_DEVICES : $CUDA_VISIBLE_DEVICES"

cp  ${CUDA_HOME}/samples/1_Utilities/bandwidthTest/* .
sed -i 's/\/usr\/local\/cuda/$(CUDA_HOME)/g'  Makefile
sed -i 's/..\/..\/common\/inc/$(CUDA_PATH)\/samples\/common\/inc/g' Makefile
  
make

./bandwidthTest
