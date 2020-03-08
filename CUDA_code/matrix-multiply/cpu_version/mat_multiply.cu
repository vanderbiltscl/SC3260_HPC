// A serial (CPU-based) matrix multiplication program

#include "stdio.h"

#define SIZE 512

// Matrix multiply function
void multiply(float * A, float * B, float * C) 
{
    
    int i;
    for (i=0;i<SIZE*SIZE;i++) 
        C[i]=0.00; // initialize C to be on the safe side
    
    int row,col,row_len=SIZE,col_len=SIZE;
    for (row=0; row<row_len; row++) {
        
        for (col=0;col < col_len;col++) {
            
            for (i=0;i<SIZE;i++)
                C[row*row_len+col] += A[row*row_len+i]*B[col+i*row_len];
            
        }
        
    }
    
}

int main(int argc, char ** argv) 
{
    // create matrices and initialize A and B to arbitray values
    float A[SIZE*SIZE],B[SIZE*SIZE],C[SIZE*SIZE];
    int i;
    for (i=0;i<SIZE*SIZE;i++) {
        A[i] = (float)i;
        B[i] = (float)SIZE*(float)SIZE-(float)i-1.0;
    }
    
    multiply(A,B,C); // perform matrix multiply

    return 0;
}
