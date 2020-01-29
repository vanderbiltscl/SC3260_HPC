#include <cilk/cilk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

  int n = atoi(argv[1]);

  // allocate memory for A, x, y;
  printf("allocating memory...\n");
  double **A = (double **)malloc(n * sizeof(double *));
  double *x, *y;
  for (int i=0; i<n; i++)
    A[i] = (double*)malloc(n * sizeof(double));
  x = (double*)malloc(n * sizeof(double));
  y = (double*)malloc(n * sizeof(double));

  // initialize A, x, y;
  printf("initializing values...\n");
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      A[i][j] = (double)rand()/(double)RAND_MAX;;
    }
    x[i] = (double)rand()/(double)RAND_MAX;;
    y[i] = 0;
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);

  // compute matrix_vector_multiply
  printf("computing...\n");
  cilk_for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      y[i] += A[i][j] * x[j];
    }
  }

  gettimeofday(&end, NULL);
  printf("Mat_Vec_Mut (%d) in %f seconds\n", n, ((double)(end.tv_sec-start.tv_sec)*1e6+(end.tv_usec-start.tv_usec))*1e-6);

  // free memory
  printf("freeing memory...\n");
  for (int i=0; i<n; i++){
    free(A[i]);
  }
  free(x);
  free(y);

  return 0;
}
