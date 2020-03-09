#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // ceil()
#include "mpi.h"

void print_recv_data(float * data,int data_size,int myrank,int np)
{

  // We need a barrier to ensure that the results are printed correctly,
  // otherwise data may overlap and be difficult to read
  int rank = 0;
  while (rank < np) {
    if (myrank == rank) {
      printf("rank %d, recv_data after scatter: ",myrank);
      int i;
      for ( i=0; i<data_size; i++ ) {
        printf("%f ",data[i]);
      }
      printf("\n");
    }
    rank++;
    MPI_Barrier(MPI_COMM_WORLD); // procs wait here until all arrive
  }

}

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
  
  if ( mype == 0 )
    printf("rank: %d, data before scatter: %f %f %f %f %f %f %f %f %f %f\n", 
            mype,data[0],data[1],data[2],data[3],data[4],data[5],
            data[6],data[7],data[8],data[9]);

  int recv_buff_size = (int) ceil( 10.0/(float)nprocs ) ;
  float * recv_data = malloc( recv_buff_size * sizeof(float) );

  MPI_Scatter(data, recv_buff_size, MPI_FLOAT, recv_data, recv_buff_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // If the data you're scattering is not evenly divisible by the number of procs, you may have 
  // to get creative to ensure proper load balancing. These two lines will work well for
  // 6 processes:
  //MPI_Scatter(data, 1, MPI_FLOAT, recv_data, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  //MPI_Scatter(&data[nprocs], 1, MPI_FLOAT, &recv_data[1], 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  //
  // Or use MPI_Scatterv!!

  print_recv_data(recv_data,recv_buff_size,mype,nprocs);

  free(recv_data);
  MPI_Finalize();
  
  return 0;

}
