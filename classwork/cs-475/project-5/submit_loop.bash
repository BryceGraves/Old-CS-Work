#!/bin/bash
#SBATCH -J project_5
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o project_5.out
#SBATCH -e project_5.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=joeparallel@oregonstate.edu
for i in 16 32 64 128; do
  /usr/local/apps/cuda/cuda-10.1/bin/nvcc -DBLOCKSIZE=$i -DNUMTRIALS=$i * 1024 -o project_5 project_5.cu
  ./project_5
done
