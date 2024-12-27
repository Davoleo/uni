// gcc reduction.c -o reduction -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

main(int argc, char *argv[])
{
  int i, n, inside = 0;
  double x, y;

  /////////////////////////////
  int num_threads = 0;
  int omp_rank, omp_size;
  /////////////////////////////

  if (argc > 1)
    n = atoi(argv[1]);
  else
    n = 100;

  ////////////////////////////////////
  num_threads = 4;
  omp_set_num_threads(num_threads);
  /////////////////////////////////////

#pragma omp parallel shared(i, n, omp_size) private(omp_rank, x, y)
  {
    omp_rank = omp_get_thread_num();
    srand48((unsigned)time(NULL) * omp_rank); // inizializzazione del seme

#pragma omp for schedule(static) reduction(+ : inside)
    for (i = 0; i < n; i++)
    {
      x = drand48();
      y = drand48();
      if (x * x + y * y < 1)
        ++inside;
      //    printf("thr: %d  i:%d,  inside: %d\n", omp_rank, i, inside);
    }
  }

  printf("INSIDE: %d PI:%.10e  \n", inside, inside / (double)n * 4.0);

  return 0;
}
