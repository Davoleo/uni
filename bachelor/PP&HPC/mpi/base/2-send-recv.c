#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    MPI_Status status;
    int rank, size;
    
    /* data to communicate */
    int data_int;

    /* initialize MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0)
    {
        data_int = 10;
        //Point to point communications between processes
        //void* buf, int count, MPI_Datatype, int destination_proc, int tag, MPI_Comm
        MPI_Send(&data_int, 1, MPI_INT, 1, 666, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        //Status contains info about the envelope of the message to be received [metadata] 
        //void* buf, int count, MPI_Datatype, int source_proc, int tag, MPI_Comm, MPI_Status
        MPI_Recv(&data_int, 1, MPI_INT, 0, 666, MPI_COMM_WORLD, &status);
        printf("Process 1 receives %d from process 0.\n", data_int);
    }
    
    MPI_Finalize();
    return 0;
}
