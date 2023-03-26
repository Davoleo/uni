#!/bin/bash

gcc cpi.c -o cpi -lm -O2

echo "function,iter,pi,error,time,hostname" > cpi_scaling.csv

for N in $(seq 100000 10000 900000)
#for N  in  1000 2000 3000
do
./cpi -n $N -f 1 >> cpi_scaling.csv
./cpi -n $N -f 2 >> cpi_scaling.csv
done

