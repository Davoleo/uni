// mpicc mpi_cpi.c -o mpi_cpi -lm -O2

#include <stdio.h>
#include <math.h>
#include <unistd.h> //optarg
#include <stdlib.h>
#include <mpi.h>
#include <getopt.h>

void options(int argc, char *argv[]);
void usage(char *argv[]);
double f1(double);
double f2(double);
double (*f)(); // Function pointer

int nf = 1;                 // Function number
long long int n = 10000000; // Intervals number

// definitions for MPI
int mpiTasks, mpiRank;
char hostname[100];
int namelen;
double startwtime, endwtime;

/********************************************/

int main(int argc, char *argv[])
{
   long long int i;

   double PI = 3.14159265358979323846264338327950288;

   double pi, piLocal, h, sum, x;

   // MPI INIT
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &mpiTasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
   MPI_Get_processor_name(hostname, &namelen);

   options(argc, argv); /* optarg management */

   if (nf == 2)
      f = f2;

   // DEFINE AND PRINT SUBDOMAIN
   long long int rangeLocal = n / (mpiTasks);
   long long int startLocal = rangeLocal * mpiRank;
   printf("#mpiTasks=%d mpiRank=%d, n=%lld, range=%lld, StartLocal=%lld, HostLocal=%s\n",
          mpiTasks, mpiRank, n, rangeLocal, startLocal, hostname);

   startwtime = MPI_Wtime(); // START TIMER

   h = 1.0 / (double)n;
   sum = 0.0;

   for (i = startLocal; i <= startLocal + rangeLocal; i++)
   {
      x = h * ((double)i - 0.5);
      sum += f1(x);
   }

   piLocal = 4 * h * sum;

   endwtime = MPI_Wtime(); // STOP TIMER
   printf("#ID %d terminated - piLocal = %.10f  %f\n", mpiRank, piLocal, endwtime - startwtime);

   // MPI COMMUNICATION
   MPI_Reduce(&piLocal, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   // MAIN MPI TASK PRINT RESULTS
   if (mpiRank == 0)
   {
      printf("#Funct\tInter\tpi\terror\ttime\tnumtasks\thostname\n");
      printf("%d\t%lld\t%.10f\t%.10e\t%.4f\t%d\t# %s \n",
             nf, n, pi, fabs(pi - PI), endwtime - startwtime, mpiTasks, hostname);
   }

   // MPI FINALIZE
   MPI_Finalize();

   return 0;
}

/************************************************/
double f1(double x)
{
   return (1.0 / (1.0 + x * x));
}

/************************************************/
double f2(double x)
{
   return (sqrt(1 - x * x));
}

/************************************************/

void options(int argc, char *argv[])
{
   int i;
   while ((i = getopt(argc, argv, "n:f:h")) != -1)
   {
      switch (i)
      {
      case 'n':
         n = strtoll(optarg, NULL, 10);
         break;
      case 'f':
         nf = strtol(optarg, NULL, 10);
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

/***************************************/

void usage(char *argv[])
{
   printf("\n%s [-n intervals] [-f function_number]  [-h]", argv[0]);
   printf("\n");

   return;
}
