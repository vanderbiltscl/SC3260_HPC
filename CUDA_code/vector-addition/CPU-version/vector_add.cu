/*  Vector addition on the GPU: C = A + B  */
#include <stdio.h>
#include <stdlib.h>

/* The GTX 480 can handle a max of 1024
   threads per block. Since we're only using
   a single block in this code, the max array
   size we can use is 1024 */
#define SIZE 1024

// Device function (i.e. kernel) goes here!

// CPU version of the vector addition function
void vecAddCPU(float * A, float * B, float * C, int N)
{

   int i;
   for (i=0; i<N; i++)
   {
      C[i] = A[i] + B[i];
   }

}

// Function compares two 1d arrays
void compareVecs( float * vec1, float * vec2, int N )
{

   int i;
   int vecsEqual = 1;
   for (i=0; i<N; i++)
   {
      if ( abs (vec1[i] - vec2[i]) > 0.00001 )
      {
         printf("vectors not equal! i: %d  vec1[i]: %f  vec2[i]: %f\n",i,vec1[i],vec2[i]);
         vecsEqual = 0;
      }
   }
   if ( vecsEqual ) printf("GPU vector addition agrees with CPU version!\n");

}

/* Host function for filling vector (1d array) with 
   random numbers between -20.0 and 20.0 */
void fillOutVector( float * vec, int vec_length )
{

   time_t t;
   srand((unsigned) time(&t)); // initialize random number generator
   int i;
   for (i=0; i<vec_length; i++)
   {
      vec[i] = ( (float)rand() / (float)(RAND_MAX) ) * 40.0;
      vec[i] -= 20.0;
   }

}

// Host function for printing a vector (1d array)
void printVector( float * vec, int vec_length )
{
   int i;
   for (i=0; i<vec_length; i++) {
      printf("i: %d vec[i]: %f\n",i,vec[i]);
   }

}

// program execution begins here
int main( int argc, char ** argv )
{

   size_t vec_bytes = SIZE * sizeof(float);

   // host arrays
   float * h_A = (float *)malloc( vec_bytes );
   float * h_B = (float *)malloc( vec_bytes );
   float * h_C = (float *)malloc( vec_bytes );

   // fill array with random floats
   fillOutVector( h_A, SIZE );
   fillOutVector( h_B, SIZE );

   // compute the sum of vector A and B on CPU
   float * gold_C = (float *)malloc( vec_bytes );
   vecAddCPU( h_A, h_B, gold_C, SIZE );

   // print result of vector addition
   printVector( gold_C, SIZE );

   /* compare two arrays; use this function to compare the array
      that was computed on the GPU to the one that was computed on the CPU */
   //compareVecs( gold_C, h_C, SIZE );

   // free memory on host
   free(h_A);
   free(h_B);
   free(h_C);
   free(gold_C);

   return 0;
}