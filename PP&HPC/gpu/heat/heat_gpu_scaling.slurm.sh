#!/bin/sh
 
# Richiedi un nodo con una gpu
##SBATCH --partition=gpu_guest
#SBATCH --partition=gpu
#SBATCH --nodes=1 
#SBATCH --mem=4G

#SBATCH --qos=gpu
#SBATCH --gres=gpu:p100:1

# Dichiara che il job durera' al massimo 30 minuti
#SBATCH --time=0-0:30:00

#stampa il nome del nodo assegnato e argomenti                 
echo "#SLURM_JOB_NODELIST   : $SLURM_JOB_NODELIST"
echo "#CUDA_VISIBLE_DEVICES : $CUDA_VISIBLE_DEVICES"

#dir setup
mkdir -p maps

module load cuda/11.6.0


echo "# NX, NY, MAX_ITER, CPU_TIME, GPU_TIME" > "time/timings.dat"
echo "# NX, NY, MAX_ITER, CPU_TIME, GPU_TIME" > "time/timings_shared.dat"
echo "# NX, NY, MAX_ITER, CPU_TIME, GPU_TIME" > "time/timings_block_4.dat"
echo "# NX, NY, MAX_ITER, CPU_TIME, GPU_TIME" > "time/timings_block_8.dat"
echo "# NX, NY, MAX_ITER, CPU_TIME, GPU_TIME" > "time/timings_block_32.dat"

# Test on multiple sizes
for S in 64 128 256 512 1024 2048
do
    nvcc -O2  heat_gpu.cu -o heat_gpu.out
    heat_gpu.out -c $S -r $S -s 100000 1> "maps/heatmap_$S.out" 2>> "time/timings.dat"
    nvcc -DUSE_SHARED_MEMORY -O2  heat_gpu.cu -o heat_gpu.out
    heat_gpu.out -c $S -r $S -s 100000 1> "/dev/null" 2>> "time/timings_shared.dat"

    for B in 4 8 32
    do 
        nvcc -O2 -DBLOCK_SIZE_Y=$B -DBLOCK_SIZE_X=$B heat_gpu.cu -o heat_gpu.out
        heat_gpu.out -c $S -r $S -s 100000 1> "/dev/null" 2>> "time/timings_block_$B.dat"
    done
done

