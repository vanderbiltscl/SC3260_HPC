#!/bin/bash
#SBATCH --nodes=2
#SBATCH --tasks-per-node=8
#SBATCH --time=00-00:30:00
#SBATCH --mem-per-cpu=1G
#SBATCH --mail-user=alex.trebek321@vanderbilt.edu
#SBATCH --mail-type=ALL

setpkgs -a intel_cluster_studio_compiler
srun -l /bin/hostname
srun ./mpi_trap