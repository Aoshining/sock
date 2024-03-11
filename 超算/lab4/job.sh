#!/bin/bash
#SBATCH --exclusive
#SBATCH -o out.txt
#SBATCH -N 4
#SBATCH -n 8
source /opt/intel/oneapi/setvars.sh
ulimit -s unlimited
ulimit -l unlimited
mpirun ./pcg input_1.bin

