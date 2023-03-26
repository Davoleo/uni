#!/bin/bash


echo "function,iter,pi,error,t_np,t_p,hostname" > cpi_scaling.csv

for N in $(seq 1000000 100000 9000000)
#for N  in  1000 2000 3000
do
./cpi -n $N  >> cpi_scaling.csv
done

