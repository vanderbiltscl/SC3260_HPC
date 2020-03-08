// A tiled matrix multiplication program

#include "stdio.h"
#include "stdlib.h"

#define SIZE 512
#define TILE_WIDTH 16

// kernel definition
__global__ void MatrixMulKernel(float * A,float * B,float * C,int len)
{

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    // if SIZE is not evenly divisible by TILE_WIDTH then
    // there will be excess threads that do nothing and should
    // not do anything to prevent out-of-bounds errors
    if ( row >= SIZE || col >= SIZE ) return;

    float sum=0.0;
    int i;
    for (i = 0;i < len;i++) {
        sum += A[ row*len + i ] * B[ i*len + col ];
    }

    C[ row*len + col ] = sum;

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
   int blocks = ( SIZE + TILE_WIDTH - 1) / TILE_WIDTH;
   dim3 blocksPerGrid(blocks,blocks); // 2d grid

   // invoke the kernel here
   MatrixMulKernel<<< blocksPerGrid, threadsPerBlock >>>(d_A,d_B,d_C,SIZE);

   // copy results back to host
   cudaMemcpy(h_C,d_C,size,cudaMemcpyDeviceToHost);

   // Free up device memory
   cudaFree(d_A);
   cudaFree(d_B);
   cudaFree(d_C);

   return 0;
}
