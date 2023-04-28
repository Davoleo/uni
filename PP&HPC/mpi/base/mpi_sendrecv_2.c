/*
mpi_sendrecv_2.c
I processi 0 e 1 si scambiano il rank.
Utilizzare MPI_Sendrecv()
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Status status;
    int rank, size;

    /* data to communicate */
    int data_send, data_recv;

    /* initialize MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        data_send = rank;
        MPI_Sendrecv(&data_send, 1, MPI_INT, 1, 100, &data_recv, 1, MPI_INT, 1, 100, MPI_COMM_WORLD, &status);
        printf("Process 0 receives %d from process 1.\n", data_recv);
    }

    if (rank == 1)
    {
        data_send = rank;
        MPI_Sendrecv(&data_send, 1, MPI_INT, 0, 100, &data_recv, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        printf("Process 1 receives %d from process 0.\n", data_recv);
    }
    MPI_Finalize();
    return 0;
}
