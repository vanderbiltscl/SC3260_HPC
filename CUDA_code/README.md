
# CUDA Examples

To run these examples you'll need to run an interactive SLURM job on one of the Maxwell GPU nodes:

	$ salloc --partition=maxwell --account=sc3260 --time=2:00:00 --gres=gpu:1

This will give you one CPU core and one NVIDIA Titan X Maxwell GPU.

To build the examples make sure you have a recent version of CUDA loaded into your environment:

	$ setpkgs -a cuda7.5

To get information about the device (i.e. GPU) try running the following:

	$ /usr/local/cuda-7.5/samples/1_Utilities/deviceQuery/deviceQuery

## Suggested Order

1. vector-addition
	- CPU-version  
	- Single-block-GPU-version
	- tiled-GPU-version


## Credit

The code has been implemented by Will French and was downloaded from here: [Github link](https://github.com/sc3260s17/cuda)
