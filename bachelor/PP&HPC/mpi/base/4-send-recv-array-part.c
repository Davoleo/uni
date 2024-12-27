#include <stdio.h>
#include "mpi.h"

#define VSIZE 50
#define BORDER 12

int main(int argc, char *argv[])
{
  MPI_Status status;
  int rank, size;

  int start_send_buf = BORDER;
  int start_recv_buf = VSIZE - BORDER;
  
  int length = 10;
  int vector[VSIZE];

  //Initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* all processes initialize vector */
  int indx;
  for (indx = 0; indx < VSIZE; indx++)
    vector[indx] = indx;

  /* send length integers starting from the "start_send_buf"-th position of vector */
  if (rank == 0)
  {
    MPI_Send(&vector[start_send_buf], length, MPI_INT, 1, 666, MPI_COMM_WORLD);
  }

  /* receive length integers in the "start_recv_buf"-th position of vector */
  if (rank == 1)
  {
    MPI_Recv(&vector[start_recv_buf], length, MPI_INT, 0, 666, MPI_COMM_WORLD, &status);

    printf("Final array in receiving process [1]\n[ ");
    int i;
    for (i = 0; i < VSIZE; i++)
      printf("%d, ", vector[i]);
    puts("]");
  }

  MPI_Finalize();
  return 0;
}
