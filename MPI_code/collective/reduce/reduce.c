#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define ARRAY_SIZE 10

void fillOutArray(int * array, int myrank)
{

   srand((unsigned) myrank*12+34); // initialize random number generator
   int i;
   for ( i=0; i < ARRAY_SIZE ; i++) {
      array[i] = rand() % 100; // random int between 0 and 100
   }

}

void print_process_data(int * data,int myrank,int np)
{

  // We need a barrier to ensure that the results are printed correctly,
  // otherwise data may overlap and be difficult to read
  int rank = 0;
  while (rank < np) {
    if (myrank == rank) {
      printf("rank %d, data: ",myrank);
      int i;
      for ( i=0; i<ARRAY_SIZE; i++ ) {
        printf("%d ",data[i]);
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

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &mype);

  int data[10];
  fillOutArray(data,mype);

  if (mype==0) printf("\nInitial Data:\n");
  print_process_data(data,mype,nprocs);

  int reduced_data[10];
  int i;
  for (i=0;i<ARRAY_SIZE;i++)
    reduced_data[i] = 0;

  MPI_Reduce(data,reduced_data,10,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

  if (mype==0) printf("\nResult of MPI_Reduce w/ MPI_SUM:\n");
  print_process_data(reduced_data,mype,nprocs);
  
  MPI_Allreduce(data,reduced_data,10,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

  if (mype==0) printf("\nResult of MPI_Allreduce w/ MPI_SUM:\n");
  print_process_data(reduced_data,mype,nprocs);
  
  MPI_Allreduce(data,reduced_data,10,MPI_INT,MPI_MAX,MPI_COMM_WORLD);

  if (mype==0) printf("\nResult of MPI_Allreduce w/ MPI_MAX:\n");
  print_process_data(reduced_data,mype,nprocs);
  
  MPI_Allreduce(data,reduced_data,10,MPI_INT,MPI_LAND,MPI_COMM_WORLD);

  if (mype==0) printf("\nResult of MPI_Allreduce w/ MPI_LAND:\n");
  print_process_data(reduced_data,mype,nprocs);
  
  MPI_Finalize();
  
  return 0;

}
