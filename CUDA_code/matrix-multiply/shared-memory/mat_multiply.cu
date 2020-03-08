// A shared memory matrix multiplication program

#include "stdio.h"
#include "stdlib.h"

// Keep the SIZE evenly divisible by TILE_WIDTH 
#define SIZE 512
#define TILE_WIDTH 16

// kernels that are called by another kernel use the __device__ identifier
__device__ float * GetSubMatrix(float * large_matrix, int row, int col)
{
    // this returns the address of the first element in a sub-matrix
    // when using this sub-matrix you have to jump ahead SIZE elements per row
    float * subMatrix = &large_matrix[ row * SIZE * TILE_WIDTH + col * TILE_WIDTH  ];
    return subMatrix;
}

// matrix multiplication kernel definition
__global__ void MatrixMulKernel(float * A,float * B,float * C)
{

    int blockRow = blockIdx.y;
    int blockCol = blockIdx.x;

    // Each thread block computes one sub-matrix Csub of C
    // Here we call another kernel from within a kernel. 
    // Note that we do not need to pass any grid or block
    // information between the <<< >>> symbols.
    float * Csub = GetSubMatrix(C, blockRow, blockCol);

    // Each thread computes on element of Csub
    // by accumulating results into Csub
    float Cvalue = 0.0;

    // Thread row and column within Csub
    int row = threadIdx.y;
    int col = threadIdx.x;

    // Iterate through n sub_matrices, where n depends on the size of the tile and matrix
    int sub_matrices_per_row = gridDim.x;

    int i;
    for ( i = 0; i < sub_matrices_per_row; i++ )
    {
        // Get sub-matrices
        // Block threads will work on these sub-matrices
        float * Asub = GetSubMatrix(A, blockRow, i);
        float * Bsub = GetSubMatrix(B, i, blockCol);
        
        // Shared memory used to store Asub and Bsub
        __shared__ float As[TILE_WIDTH][TILE_WIDTH];
        __shared__ float Bs[TILE_WIDTH][TILE_WIDTH];

        // Load Asub and Bsub from device memory into shared memory
        // Each thread loads one element of each sub-matrix
        As[row][col] = Asub[ row*SIZE + col ];
        Bs[row][col] = Bsub[ row*SIZE + col ];

        // Sync threads to make sure sub-matrices are completely loaded into shared memory
        // Remember, this only syncs threads within a block
        __syncthreads();

        int j;
        // Multiply Asub and Bsub together, using fast shared memory for data access
        for ( j = 0; j < TILE_WIDTH ; j++ )
            Cvalue += As[row][j] * Bs[j][col]; 

        // Sync threads to ensure the preceding computation is done before loading
        // two new sub-matrices of A and B in the next iteration
        __syncthreads();
    }

    Csub[ row*SIZE + col ] = Cvalue;
    
}

int main(int argc, char ** argv) 
{
   float h_A[SIZE*SIZE],h_B[SIZE*SIZE],h_C[SIZE*SIZE];
   float * d_A, * d_B, * d_C;

   // initialize host matrices with arbitrary data
   int i;
   for (i=0;i<SIZE*SIZE;i++) {
      h_A[i] = (float)i;
      h_B[i] = (float)SIZE * (float)SIZE - (float)i - 1.00;
      h_C[i] = 0.0;
   }

   // allocate space on device
   size_t size = SIZE*SIZE*sizeof(float);
   cudaMalloc(&d_A,size);
   cudaMalloc(&d_B,size);
   cudaMalloc(&d_C,size);

   //copy data to device
   cudaMemcpy(d_A,h_A,size,cudaMemcpyHostToDevice);
   cudaMemcpy(d_B,h_B,size,cudaMemcpyHostToDevice);
   cudaMemcpy(d_C,h_C,size,cudaMemcpyHostToDevice);

   dim3 threadsPerBlock(TILE_WIDTH,TILE_WIDTH); // 2d block
   int blocks = ( SIZE + TILE_WIDTH - 1 ) / TILE_WIDTH;
   dim3 blocksPerGrid(blocks,blocks); // 2d grid

   // invoke the kernel here
   MatrixMulKernel<<< blocksPerGrid, threadsPerBlock >>>(d_A,d_B,d_C);
   
   // copy results back to host
   cudaMemcpy(h_C,d_C,size,cudaMemcpyDeviceToHost);

   // Free up device memory
   cudaFree(d_A);
   cudaFree(d_B);
   cudaFree(d_C);

   return 0;
}
