#!/bin/bash
#SBATCH --nodes=1
#SBATCH --tasks-per-node=2
#SBATCH --time=00-00:30:00
#SBATCH --mem-per-cpu=1G
#SBATCH --mail-user=alex.trebek321@vanderbilt.edu
#SBATCH --mail-type=ALL

setpkgs -a intel_cluster_studio_compiler
make
srun -l /bin/hostname
srun ./allgatherv