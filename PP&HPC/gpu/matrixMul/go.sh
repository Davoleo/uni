#!/bin/bash

for i in $(seq 100 200 4000); do
# sbatch --export=WA=$i,HA=$i,WB=$i,HB=$i --reservation=corso_T_2020_hpcprogpar-20201201 slurm\_launch\_single
sbatch --output=./go_script_out/slurm-%j.out --export=WA=$i,HA=$i,WB=$i,HB=$i slurm_launch_single.sh
done
