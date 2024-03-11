#!/bin/bash
#SBATCH --exclusive
#SBATCH -o result.txt
#SBATCH -N 4
#SBATCH -n 8
source /opt/intel/oneapi/setvars.sh
ulimit -s unlimited
ulimit -l unlimited
mpirun ./pivot uniformvector-2dim-5h.txt