#include <stdio.h>
#include "mpi.h"

//The MASTER task [first process] has rank == 0
#define MASTER 0

int main(int argc, char **argv)
{
  int numtasks, taskid, len;
  //maximum processor name buffer size constant [see Get_processor_name below]
  char hostname[MPI_MAX_PROCESSOR_NAME];

  //MPI_COMM_WORLD is the default and global communicator, it will be used most of the times we need a communicator around in the app

  //Initializes MPI env, must be called before any other API call
  //Can be used to pass program arguments to all processes
  MPI_Init(&argc, &argv);
  //Number of MPI proceses in the communicator, if the communicator is MPI_COMM_WORLD => it will be the total number of processes in your MPI app
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  //Return the id [rank] of the calling process in the given communicator
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  //Returns the calling processor name and its length
  MPI_Get_processor_name(hostname, &len);
  printf("Hello from task %d on %s!\n", taskid, hostname);

  if (taskid == MASTER)
    printf("MASTER: Number of MPI tasks is: %d\n", numtasks);

  //Terminates MPI env. should be the last MPI routine called in every program
  MPI_Finalize();
}
