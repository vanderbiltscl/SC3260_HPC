#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // ceil()
#include "mpi.h"

void print_process_data(float * data,int data_size,int myrank,int np)
{

  // We need a barrier to ensure that the results are printed correctly,
  // otherwise data may overlap and be difficult to read
  int rank = 0;
  while (rank < np) {
    if (myrank == rank) {
      printf("rank %d, data: ",myrank);
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

void print_single_rank_data(float * data, int data_size, int myrank)
{

    printf("\nrank: %d, data: ",myrank);
    int j;
    for (j=0;j<data_size;j++)
       printf("%f ",data[j]);
    printf("\n");

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
    print_single_rank_data(data,10,mype);

  int recv_buff_size = (int) ceil( 10.0/(float)nprocs ) ;
  float * recv_data = malloc( recv_buff_size * sizeof(float) );

  MPI_Scatter(data, recv_buff_size, MPI_FLOAT, recv_data, recv_buff_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (mype==0) printf("\n--- Printing received data BEFORE modifications ---\n");
  print_process_data(recv_data,recv_buff_size,mype,nprocs);

  int i;
  for (i=0; i<recv_buff_size; i++)
     recv_data[i] = (float)mype * 100.0 + (float)i; 

  if (mype==0) printf("\n--- Printing received data AFTER modifications ---\n");
  print_process_data(recv_data,recv_buff_size,mype,nprocs);

  int gather_data_size = nprocs * recv_buff_size;
  float final_data[gather_data_size];
  MPI_Gather(recv_data, recv_buff_size, MPI_FLOAT, final_data, recv_buff_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
  if ( mype == 0 ) 
    print_single_rank_data(final_data,gather_data_size,mype);
  
  free(recv_data);
  MPI_Finalize();
  
  return 0;

}
