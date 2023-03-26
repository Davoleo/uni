//  gcc -O2 -fopenmp  omp_overhead.c -o omp_overhead

#include <omp.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
  int i,j;
  int NT=1 ;
  int ITER=1000;
  int SLEEP=1000;  // Microsecondi
  double ts,tr,t1,t2;

 if (argc > 1)  NT    = atoi(argv[1]);
 if (argc > 2)  ITER  = atoi(argv[2]);
 if (argc > 3)  SLEEP = atoi(argv[3]);


printf ("# NT=%d,  ITER=%d, SLEEP=%d \n", NT, ITER, SLEEP); 

ts=ITER*SLEEP/1000000;

 omp_set_num_threads(NT);

 t1=omp_get_wtime();

 for(i=0; i< ITER; i++)
  {
  #pragma omp parallel for
  for (j=0; j< NT; j++)
    usleep(SLEEP);
  }

 t2=omp_get_wtime();
 tr=t2-t1;
 
  printf ("# Tsleep(s)     Treal(s)   Toverhead(s)   Toverheadperiter(micros) \n");
  printf ("   %.2f         %.2f           %.2f         %.2f \n ", ts, tr, tr-ts,  (tr-ts)*1000000/ITER );


 return 0;
}




