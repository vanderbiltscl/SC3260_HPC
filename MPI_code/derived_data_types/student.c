#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // offsetof()
#include "mpi.h"

typedef struct
{
   int height;
   float grades[4];
   double stuff[2];
} student;

void printStudent( student * student_x , int prank, int np )
{

    int rank = 0;
    while (rank < np) {
       if (prank == rank) {
          printf("rank %d: \n",prank);
          printf("height: %d\n",student_x->height);
          printf("grades: %f %f %f %f\n",student_x->grades[0],
                    student_x->grades[1],student_x->grades[2],
                    student_x->grades[3]);
          printf("stuff: %f %f\n",student_x->stuff[0],
                                  student_x->stuff[1]);
       }
       rank++;
       //printf("rank %d waiting at barrier, rank: %d\n",prank,rank);
       MPI_Barrier(MPI_COMM_WORLD); // procs wait here until all arrive
    }

}

int main( int argc, char ** argv )
{
   int nprocs,myrank;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

   student Frank = { 0,{0,0,0,0},{0,0} };
   if ( myrank == 0 ) {
      Frank.height = 72;
      Frank.grades[0] = 92.0;
      Frank.grades[1] = 81.0;
      Frank.grades[2] = 90.0;
      Frank.grades[3] = 77.7;
      Frank.stuff[0] = 1.2345;
      Frank.stuff[1] = 6.789;
   }

   MPI_Datatype MPI_STUDENT; // define name of MPI type
   MPI_Datatype type[3] = { MPI_INT, MPI_FLOAT, MPI_DOUBLE };
   int blocklen[3] = { 1, 4, 2 }; // size of each data element in struct

   /* offsetof(): provides the offset in bytes of each data member 
                  within a struct                                     */
   MPI_Aint disp[3]; // array of displacements; one for each data member
   disp[0] = offsetof(student,height);
   disp[1] = offsetof(student,grades);
   disp[2] = offsetof(student,stuff);

   // build derived datatype
   MPI_Type_create_struct(3,blocklen,disp,type,&MPI_STUDENT);
   // have MPI optimize the (memory) layout of our derived datatype
   MPI_Type_commit(&MPI_STUDENT);

   if ( myrank == 0 ) printf("Before data sent...\n");
   printStudent(&Frank,myrank,nprocs);

   // send Frank from rank 0 to all others in communicator.
   // You can also use derived data type in collective communication,
   // if appropriate.
   if ( myrank == 0 ) {
      printf("\n");
      int i;
      for (i=1;i<nprocs;i++) {
         MPI_Send(&Frank,1,MPI_STUDENT,i,123,MPI_COMM_WORLD);
      }
   }
   else {
      MPI_Recv(&Frank,1,MPI_STUDENT,0,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   }


   if ( myrank == 0 ) printf("After data sent...\n");
   printStudent(&Frank,myrank,nprocs);

   MPI_Type_free(&MPI_STUDENT); // free space for derived datatype
   MPI_Finalize();
   return 0;
}