// gcc -fopenmp  parallel2.c  -o parallel2

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1000000
#define NUMTHR 16

double array[NUMTHR][SIZE];

int main(int argc, char *argv[])
{
  int i = 0, j = 0;

#pragma omp parallel shared(array) private(j, i) num_threads(NUMTHR)
  {

    j = omp_get_thread_num();
    srand48((unsigned)time(NULL)); // inizializzazione del seme per drand48()

    printf("Esecuzione del thread %d: inizio calcolo \n", j);
    for (i = 1; i < SIZE; i++)
      array[j][i] = drand48() * drand48() * drand48();
    printf("Esecuzione del thread %d: fine calcolo \n", j);

#pragma omp single
    {
      printf("THR SINGLE: entra  sleep 4 \n");
      sleep(4);
      printf("THR SINGLE esce sleep 4 \n");
    }

    //    if (j==2) { printf("THR2 entra  sleep 4 \n"); sleep(4);  printf("THR2 esce sleep 4 \n"); }

    //   #pragma omp barrier

    printf("%d ha finito\n", j);
  }
}
