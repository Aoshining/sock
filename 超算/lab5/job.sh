#!/bin/bash
#SBATCH -o out.txt
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -p 2080Ti
#SBATCH --cpus-per-task=24
#SBATCH --gpus=1

CUDA_VISIBLE_DEVICES=0 python pytorch.py
