/*
mpi_sendrecv_n.c
N task si scambiano circolarmente il proprio rank:
- il task con rank n  invia il proprio rank al task n+1
- l'ultimo task invia il rank al task 0

module load intel, impi
mpicc mpi_sendrecv_n.c -o  mpi_sendrecv_n
mpurun mpi_sendrecv_n
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Status status;
    int rank, size;
    int prev_rank, next_rank;

    /* data to communicate */
    int data_send, data_recv;
    /* initialize MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    prev_rank = (rank - 1 + size) % size;
    next_rank = (rank + 1) % size;

    data_send = rank;

    MPI_Sendrecv(&data_send, 1, MPI_INT, next_rank, 100, &data_recv, 1, MPI_INT, prev_rank, 100, MPI_COMM_WORLD, &status);

    printf("Process %d/%d receives %d from process %d.\n", rank, size, data_recv, status.MPI_SOURCE);

    MPI_Finalize();
    return 0;
}
