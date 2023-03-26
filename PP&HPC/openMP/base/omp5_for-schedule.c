#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
 int i,j;
 omp_set_num_threads(4);
        
 #pragma omp parallel  private(j)
 {

   #pragma omp for schedule(dynamic)
   for(i=0; i<20; i++)
      {
      j=omp_get_thread_num();
      printf("Esecuzione del thread %d: i=%d\n", j,i);
      }

   #pragma omp single
   { printf("Esecuzione single  del thread %d \n", j); sleep (4);}

   printf("%d ha finito\n", j);
 }
return 0;
}

