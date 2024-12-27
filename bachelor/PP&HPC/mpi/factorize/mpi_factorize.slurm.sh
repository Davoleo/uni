#!/bin/bash
#SBATCH --output=%x.o%j  # Nome del file per lo strandard output
#SBATCH --partition=cpu_guest        # Nome della partizione
#SBATCH --qos=cpu_guest              # Nome della partizione
#SBATCH --nodes=2                    # numero di nodi richiesti
#SBATCH --ntasks-per-node=8          # numero di cpu per nodo
#SBATCH --time=1-00:00:00            # massimo tempo di calcolo

echo  "#SLURM_JOB_NODELIST      : $SLURM_JOB_NODELIST"
echo  "#SLURM_JOB_CPUS_PER_NODE : $SLURM_JOB_CPUS_PER_NODE"

module purge
module load intel impi
mpicc -O2  mpi_factorize.c -o mpi_factorize.out -lcrypto -lm

#openssl genrsa -out rsa_key.pem 68
#openssl rsa -in rsa_key.pem -modulus -noout

#Modulus=97219FA6BD3D7735                  # 64 bit
#Modulus=B81915BC0A2222F4B                # 68 bit
#Modulus=F27F04CC3A51A3090B7D             # 80 bit
#Modulus=CD2C32D00F3E6CC158F1E069         # 96 bit
Modulus=D44DC0CA2A7C693B46A96E01B47C8F15 #128 bit

mpirun mpi_factorize.out -m $Modulus -a 6
