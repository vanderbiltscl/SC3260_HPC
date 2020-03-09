#include <stdio.h>
#include <mpi.h>     /* For MPI functions, etc */ 


/* This program is hard-coded to run with two processes! 
 */

int main(int argc, char ** argv) 
{

   int nprocs; /* Number of processes    */
   int rank;   /* My process rank        */

   /* Start up MPI */
   MPI_Init(&argc, &argv); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

   int n = 5;
   float xx[n];

   int i;
   for (i=0;i<n;i++)
   {
      if ( rank == 0 )
         xx[i] = (float)i;
      else
         xx[i] = -1.0*(float)i;

      printf("BEFORE***   rank: %d i: %d xx[i]: %f\n",rank,i,xx[i]);
   }

   int scounts[2];
   scounts[0] = 3; // slice one is 3 pieces of data
   scounts[1] = 2; // slice two is 2 pieces of data

   int displs[2];
   displs[0] = 0; // slice one starts at array element 0
   displs[1] = 3; // slice two starts at array element 3

   MPI_Allgatherv(MPI_IN_PLACE,0,MPI_FLOAT,xx,scounts,displs,MPI_FLOAT,MPI_COMM_WORLD);

   for (i=0;i<n;i++)
      printf("AFTER***  rank: %d i: %d xx[i]: %f\n",rank,i,xx[i]);
   
   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;

}  