#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

int main(int argc, char **argv)
{

   if ( argc != 3 ) {
      printf("Usage: %s matrixSize blockSize\n", argv[0]);
      exit(0);
   }

   int n = atoi(argv[1]);
   int b = atoi(argv[2]);
   if (b > n){
      printf("Usage: %s matrixSize blockSize\n", argv[0]);
      printf("blockSize must be smaller or equal to the matrixSize\n");
      exit(0);
   }
   int i, j;

   int **x = (int **) malloc(n * sizeof(int *));
   int **y = (int **) malloc(n * sizeof(int *));
   for(i=0; i<n; i++){
	  x[i] = (int *) malloc(n * sizeof(int));
	  y[i] = (int *) malloc(n * sizeof(int));
   }

   for(i=0; i<n ; i++)
	  for(j=0; j<n; j++)
	  	x[i][j] = i*10 + j;

   clock_t start, end;
   start = clock();
   // add code for assigning values to y so that y[i][j] = x[j][i]
   int idx_i, idx_j;
   for(idx_j=0; idx_j<n; idx_j+=b)
	  for(idx_i=0; idx_i<n; idx_i+=b)
	     for(j=idx_j; j<idx_j+b; j++)
		    for(i=idx_i; i<idx_i+b; i++)
			   y[i][j] = x[j][i];
   
   end = clock();
   printf("Execution time %f\n",
		  ((double) (end - start)) / CLOCKS_PER_SEC);

   for(i=0; i<n; i++){
	  free(x[i]);
	  free(y[i]);
   }
   free(x);
   free(y);

   return 0;
}
