/*
mpi_heat.c

module load intel impi
mpicc -O2 mpi_heat.c -o mpi_heat

mpirun mpi_heat -h
mpirun mpi_heat -r 2048 -c 2048

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h> //gettimeofday
#include <mpi.h>

void options(int argc, char *argv[]);
void usage(char *argv[]);
void Jacobi_Iterator_CPU(float *__restrict T, float *__restrict T_new, const int NX, const int NY);
void Jacobi_Iterator_CPU_internal(float *__restrict T, float *__restrict T_new, const int NX, const int NY);
void Jacobi_Iterator_CPU_external(float *__restrict T, float *__restrict T_new, const int NX, const int NY);
void Init_center(float *__restrict h_T, const int NX, const int NY);    // center
void Init_left(float *__restrict h_T, const int NX, const int NY);      // left border
void Init_top(float *__restrict h_T, const int NX, const int NY);       // top border
void copy_rows(float *__restrict h_T, const int NX, const int NY);      // periodic boundary conditions
void copy_cols(float *__restrict h_T, const int NX, const int NY);      // periodic boundary conditions
void print_colormap(float *__restrict h_T, const int NX, const int NY); //

int WNX = 256;       // --- Number of discretization points along the x axis
int WNY = 256;       // --- Number of discretization points along the y axis
int MAX_ITER = 1000; // --- Number of Jacobi iterations
int NX, NY;

// variabili globali per MPI
int mpi_rank = 0, mpi_size = 0;
int prev_rank = 0, next_rank = 0;
int tag = 999;

MPI_Status status;
MPI_Request request1;
MPI_Request request2;
MPI_Request request3;
MPI_Request request4;

float *h_T_new;
float *h_T_old;
float *h_T_temp;
float *h_T_whole; // Intero dominio gestito da rank 0

/********/
/* MAIN */
/********/
int main(int argc, char **argv)
{

    int iter, i, j;

    double t1, t2;

    options(argc, argv); /* optarg management */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    // scomposizione di dominio:
    // dividiamo le righe tra i rank MPI
    prev_rank = (mpi_rank - 1 + mpi_size) % mpi_size;
    next_rank = (mpi_rank + 1) % mpi_size;
    NX = WNX;                // Local NX: numero colonne per rank
    NY = WNY / mpi_size + 2; // Local NY: numero righe   per rank

    // stampa tutti i dati della simulazione
    fprintf(stderr, "#WNX: %d, WNY: %d, MAX_ITER: %d, MPI_RANK: %d, MPI_SIZE: %d, NX: %d, NY: %d \n", WNX, WNY, MAX_ITER, mpi_rank, mpi_size, NX, NY);

    h_T_new = (float *)calloc(NX * NY, sizeof(float));
    h_T_old = (float *)calloc(NX * NY, sizeof(float));
    if (mpi_rank == 0)
        h_T_whole = (float *)calloc(WNX * WNY, sizeof(float));

    t1 = MPI_Wtime();

    for (iter = 0; iter < MAX_ITER; iter = iter + 1)
    {

        h_T_temp = h_T_new;
        h_T_new = h_T_old;
        h_T_old = h_T_temp;

        //    Init_center(h_T_old,  NX, NY);
        Init_left(h_T_old, NX, NY);
        //  if (mpi_rank==0)   Init_top(h_T_old,     NX, NY);
        copy_cols(h_T_old, NX, NY);


        if (mpi_size > 1) {
            // scambio delle righe di bordo
            MPI_Irecv(h_T_old + mpi_rank * NX, NX, MPI_FLOAT, prev_rank, 111, MPI_COMM_WORLD, &request1);
            MPI_Irecv(h_T_old + mpi_rank * NX + NY + 2, NX, MPI_FLOAT, next_rank, 222, MPI_COMM_WORLD, &request2);

            //top row
            MPI_Isend(h_T_old + mpi_rank * NX, NX, MPI_FLOAT, prev_rank, 222, MPI_COMM_WORLD, &request2);

            //bottom row
            MPI_Isend(h_T_old + mpi_rank * NX + NY + 2, NX, MPI_FLOAT, next_rank, 111, MPI_COMM_WORLD, &request1);
        }

        Jacobi_Iterator_CPU(h_T_old, h_T_new, NX, NY);
    }

    t2 = MPI_Wtime();

    if (mpi_rank == 0)
        fprintf(stderr, "%f %d %d %d %d \n", t2 - t1, mpi_size, WNX, WNY, MAX_ITER);

    // invio dei sottodomini a rank 0
    MPI_Gather(h_T_new + NY * mpi_rank, NX * NY, MPI_FLOAT, h_T_whole + NY * mpi_rank, NX * NY, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (mpi_rank == 0)
        print_colormap(h_T_whole, WNX, WNY);

    free(h_T_new);
    free(h_T_old);
    if (mpi_rank == 0)
        free(h_T_whole);

    MPI_Finalize();

    return 0;
}

/***********************************/
/* JACOBI ITERATION FUNCTION - CPU */
/***********************************/
void Jacobi_Iterator_CPU(float *__restrict T, float *__restrict T_new, const int NX, const int NY)
{
    int i, j;

    // --- Only update "interior" (not boundary) node points
    for (j = 1; j < NY - 1; j++)
        for (i = 1; i < NX - 1; i++)
        {
            float T_E = T[(i + 1) + NX * j];
            float T_W = T[(i - 1) + NX * j];
            float T_N = T[i + NX * (j + 1)];
            float T_S = T[i + NX * (j - 1)];
            T_new[NX * j + i] = 0.25 * (T_E + T_W + T_N + T_S);
        }
}

/***********************************/
/* JACOBI ITERATION ITERNAL FUNCTION - CPU */
/***********************************/
void Jacobi_Iterator_CPU_internal(float *__restrict T, float *__restrict T_new, const int NX, const int NY)
{
    int i, j;

    // Dalla riga 2 alla penultima
    for (j = 2; j < NY - 2; j++)
        for (i = 1; i < NX - 1; i++)
        {
            float T_E = T[(i + 1) + NX * j];
            float T_W = T[(i - 1) + NX * j];
            float T_N = T[i + NX * (j + 1)];
            float T_S = T[i + NX * (j - 1)];
            T_new[NX * j + i] = 0.25 * (T_E + T_W + T_N + T_S);
        }
}

/***********************************/
/* JACOBI ITERATION ITERNAL FUNCTION - CPU */
/***********************************/
void Jacobi_Iterator_CPU_external(float *__restrict T, float *__restrict T_new, const int NX, const int NY)
{
    int i, j;

    j = 1; // prima riga
    for (i = 1; i < NX - 1; i++)
    {
        float T_E = T[(i + 1) + NX * j];
        float T_W = T[(i - 1) + NX * j];
        float T_N = T[i + NX * (j + 1)];
        float T_S = T[i + NX * (j - 1)];
        T_new[NX * j + i] = 0.25 * (T_E + T_W + T_N + T_S);
    }

    j = NY - 2; // ultima riga
    for (i = 1; i < NX - 1; i++)
    {
        float T_E = T[(i + 1) + NX * j];
        float T_W = T[(i - 1) + NX * j];
        float T_N = T[i + NX * (j + 1)];
        float T_S = T[i + NX * (j - 1)];
        T_new[NX * j + i] = 0.25 * (T_E + T_W + T_N + T_S);
    }
}

/********************************/
/* TEMPERATURE INITIALIZATION : */
/* parte centrale della griglia */
/********************************/
void Init_center(float *__restrict h_T, const int NX, const int NY)
{
    int i, j;
    int startx = NX / 2 - NX / 10;
    int endx = NX / 2 + NX / 10;
    int starty = NY / 2 - NY / 10;
    int endy = NY / 2 + NY / 10;
    //    int starty=NY/4;
    //    int endy=NY-NY/4;
    for (i = startx; i < endx; i++)
        for (j = starty; j < endy; j++)
            h_T[NX * j + i] = 1.0;
}

/********************************/
/* TEMPERATURE INITIALIZATION : */
/* bordo sinistro               */
/********************************/
void Init_left(float *__restrict h_T, const int NX, const int NY)
{

    int i, j;
    int startx = 1;
    int endx = 2;
    int starty = 0;
    int endy = NY - 1;
    for (i = startx; i < endx; i++)
        for (j = starty; j < endy; j++)
            h_T[NX * j + i] = 1.0;
}

/********************************/
/* TEMPERATURE INITIALIZATION : */
/* bordo alto                   */
/********************************/
void Init_top(float *__restrict h_T, const int NX, const int NY)
{

    int i, j;
    int startx = 0;
    int endx = NX - 1;
    for (i = startx; i < endx; i++)
        h_T[NX + i] = 1.0;
}

/********************************/
/* Periodic boundary conditions */
/* COPY BORDER: COLS            */
/********************************/
void copy_cols(float *__restrict h_T, const int NX, const int NY)
{

    int i;

    // copy cols
    for (i = 1; i < NY - 1; ++i)
    {
        h_T[NX * i + 0] = h_T[NX * i + NX - 2];
        h_T[NX * i + NX - 1] = h_T[NX * i + 1];
    }
}

/********************************/
/* Periodic boundary conditions */
/* COPY BOREDER: ROWS           */
/********************************/
void copy_rows(float *__restrict h_T, const int NX, const int NY)
{

    memcpy(&(h_T[NX * 0]), &(h_T[NX * (NY - 2)]), NX * sizeof(float));
    memcpy(&(h_T[NX * (NY - 1)]), &(h_T[NX * 1]), NX * sizeof(float));
}

/******************************************/
/* print color map                        */
/******************************************/

void print_colormap(float *__restrict h_T, int NX, int NY)
{
    int i, j;

    for (j = 0; j < NY; j++)
    {
        for (i = 0; i < NX; i++)
        {
            printf("%2.2f ", h_T[NX * j + i]);
        }
        printf("\n");
    }
}

/******************************************/
/* options management                     */
/******************************************/
void options(int argc, char *argv[])
{

    int i;
    while ((i = getopt(argc, argv, "c:r:s:h")) != -1)
    {
        switch (i)
        {
        case 'c':
            WNX = strtol(optarg, NULL, 10);
            break;
        case 'r':
            WNY = strtol(optarg, NULL, 10);
            break;
        case 's':
            MAX_ITER = strtol(optarg, NULL, 10);
            break;
        case 'h':
            usage(argv);
            exit(1);
        case '?':
            usage(argv);
            exit(1);
        default:
            usage(argv);
            exit(1);
        }
    }
}

/******************************************/
/* print help                             */
/******************************************/
void usage(char *argv[])
{

    printf("\n%s [-c ncols] [-r nrows] [-s nsteps] [-h]", argv[0]);
    printf("\n");
}
