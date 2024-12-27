#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numtasks, rank, rc, nl;
    char name[20];
    double time;
    rc = MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(name, &nl);

    time = MPI_Wtime();
    sleep(3);
    time = MPI_Wtime() - time;

    printf("TotProcessi=%d MyRank=%d MyHost=%s ExecTime:%f\n", numtasks, rank, name, time);

    MPI_Finalize();
}
