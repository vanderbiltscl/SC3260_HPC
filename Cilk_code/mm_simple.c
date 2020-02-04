#include <cilk/cilk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define n 512
double A[n][n];
double B[n][n];
double C[n][n];

int main(int argc, char *argv[]) {

  // initialize matrix with random values
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      A[i][j] = (double)rand()/(double)RAND_MAX;
      B[i][j] = (double)rand()/(double)RAND_MAX;
      C[i][j] = 0;
    }
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);

  // simple for-loop implementation
  cilk_for (int i=0; i<n; i++){
    cilk_for (int j=0; j<n; j++){
      for (int k=0; k<n; k++){
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  gettimeofday(&end, NULL);
  printf("Simple MM (%d x %d) in %f seconds\n", n, n, ((double)(end.tv_sec-start.tv_sec)*1e6+(end.tv_usec-start.tv_usec))*1e-6);
  return 0;
}
