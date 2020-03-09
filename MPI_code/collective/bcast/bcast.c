#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mpi.h"

int main(int argc, char ** argv) 
{

  int mype, nprocs;
  float data[10] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
  FILE * file;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &mype);

  if (mype == 0){
    char input[100];
    file = fopen("data1.txt", "r");
    assert (file != NULL);
    int cnt=0;
    while ( fscanf(file, "%s\n", input) != EOF ) {
       data[cnt++] = atof(input);
    }
  }
  
  printf("rank: %d, data before: %f %f %f %f %f %f %f %f %f %f\n", 
          mype,data[0],data[1],data[2],data[3],data[4],data[5],
          data[6],data[7],data[8],data[9]);

  MPI_Bcast(data, 10, MPI_FLOAT, 0, MPI_COMM_WORLD);

  printf("rank: %d, data after: %f %f %f %f %f %f %f %f %f %f\n", 
          mype,data[0],data[1],data[2],data[3],data[4],data[5],
          data[6],data[7],data[8],data[9]);

  MPI_Finalize();
  
  return 0;

}
