#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define ARRAY_SIZE 1000
#define BUFSIZE 100000

float dowork()
{

  int i;
  float x=0.0,y=0.0;
  for (i=0; i<100000; i++) {
    x = (float)i * 0.121;
    y += x + 2.0 * (float)(i + 4);
  }

  return y;

}

int main(int argc, char ** argv)
{

  int nprocs,rank;
  int * buf = malloc ( BUFSIZE * sizeof(int) );

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Buffer_attach( buf, BUFSIZE );

  printf("nprocs: %d rank: %d\n",nprocs,rank);  

  int * array = malloc( ARRAY_SIZE * sizeof(int) );
  int i,j,jmax = 50;

  for ( j=0; j<jmax; j++) {

    int tag = j + 1;
    for (i=0;i<ARRAY_SIZE;i++) {
      array[i] = rank * i + j;
    }

    //printf("process: %d j: %d\n",rank,j);    

    if ( rank == 0 && nprocs > 1 ) {
       for (i=1; i<nprocs; i++) {
          MPI_Recv(array,ARRAY_SIZE,MPI_INT,i,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
          float junk = dowork();
          if ( junk == 0.00 ) printf("Broken\n");
       }
    }
    else {
       MPI_Bsend(array,ARRAY_SIZE,MPI_INT,0,tag,MPI_COMM_WORLD);
       float junk = dowork();
       if ( junk == 0.00 ) printf("Broken\n");
    }

  }

  int * bufaddress, bufsize; 
  MPI_Buffer_detach( &bufaddress, &bufsize );
  free(array);
  free(buf);
  MPI_Finalize();
  return 0;

}