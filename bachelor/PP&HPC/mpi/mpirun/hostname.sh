#!/bin/bash


module purge
module load intel impi

echo "####################  INTEL"
set -x
mpirun   --host wn53,wn54         --ppn 1 hostname
mpirun   --machine machine.txt  --ppn 1 hostname
set +x


echo "####################  GNU"
module purge
#module load  gnu openmpi
module load  gnu7 openmpi3

set -x
$(which mpirun)  --host wn53,wn54         -n 2         hostname
$(which mpirun)  --host wn53,wn54         --npernode 1 hostname
$(which mpirun)  --hostfile hostfile.txt  --npernode 1 hostname
set +x

set -x
# process bind
ssh wn51 numactl -H 
ssh wn01 numactl -H 
cat  rankfile.txt
$(which mpirun)  -rf rankfile.txt                      hostname
set +x
