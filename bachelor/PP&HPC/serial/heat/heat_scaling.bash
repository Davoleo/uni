#!/bin/bash


echo "nx,ny,iter,T,Tp,Tnp" > heat_scaling.csv

#for N in $(seq 1000000 100000 9000000)
for N  in  256 512 758 1024  
do
./heat -c $N  -r $N -s 1000  >> heatmap.out
done   2>> heat_scaling.csv

