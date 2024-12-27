//gcc -fopenmp  sections.c  -o sections

#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
 int i;
 omp_set_num_threads(3);
 #pragma omp parallel private(i)
 {
  #pragma omp sections
    {
       #pragma omp section 
         {
          for(i = 0; i < 5; i++)
             printf("Th %d: %d del blocco 1\n",omp_get_thread_num(),i);
         }
       #pragma omp section 
         {
          for(i = 0; i < 5; i++) 
             printf("Th %d: %d del blocco 2\n",omp_get_thread_num(),i);
         }
       #pragma omp section 
         {
          for(i = 0; i < 5; i++)
             printf("Th %d: %d del blocco 3\n",omp_get_thread_num(),i);
          sleep(4);
         }
    } // end sections 


//   #pragma omp barrier
   printf("%d ha finito\n", omp_get_thread_num());

 } // end parallel 
}


