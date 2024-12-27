#include <stdio.h>
#include "mpi.h"
#define MSIZE 10

int main(int argc, char **argv)
{
  MPI_Status status;
  int rank;
  int i;

  /*data to communicate */
  float a[MSIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0)
  {
    //Initialize data to send [just on the master process]
    for (i = 0; i < MSIZE; i++)
      a[i] = (float)i;
    
    //count = MSIZE
    MPI_Send(a, MSIZE, MPI_FLOAT, 1, 666, MPI_COMM_WORLD);
  }
  else if (rank == 1)
  {
    MPI_Recv(a, MSIZE, MPI_FLOAT, 0, 666, MPI_COMM_WORLD, &status);
    
    printf("Process 1 receives the following array from process 0.\n");
    for (i = 0; i < MSIZE; i++)
      printf("%6.2f\n", a[i]);
  }
  
  MPI_Finalize();
  return 0;
}
