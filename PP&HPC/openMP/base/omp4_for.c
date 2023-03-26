#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
  int i,j;
 omp_set_num_threads(4);
        
 #pragma omp parallel  private(j)
 {
   #pragma omp for
   for(i=0; i<20; i++)
      {
      j=omp_get_thread_num();
      printf("Esecuzione del thread %d: i=%d\n", j,i);
      }
   printf("%d ha finito\n", j);
 }
return 0;
}

