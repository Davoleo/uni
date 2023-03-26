#include <stdio.h>
#include <stdlib.h>    // drand48()
#include <omp.h>
#include <unistd.h>    // optarg
#include <time.h>      // time()

void options(int argc, char * argv[]) ;
void usage(char * argv[]);

int n=20;

int main(int argc, char* argv[])
{
  int    i, rank;
  float  x,sum;
  double t1,t2;

  options(argc, argv);  /* optarg management */
  printf("# n=%d \n",  n);
  srand48((unsigned)time(NULL)); // inizializzazione del seme

  sum=0;
  t1=omp_get_wtime();

#pragma omp parallel for 
  for(i=0; i<n; i++)
      {
      rank= omp_get_thread_num(); 
      x = drand48();  
      printf ("i:%d r:%d x:%.4f \n", i, rank, x);
      usleep(x*100000);
      sum += x; 
      }
  t2=omp_get_wtime();

  printf ("sum:%.4f  time: %.4f \n", sum, t2-t1);
  return 0;
}


void options(int argc, char * argv[])
{
  int i;
   while ( (i = getopt(argc, argv, "n:")) != -1) {
        switch (i)
        {
        case 'n':  n = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

void usage(char * argv[])
{
  printf ("\n%s [-n iterazioni]  [-h]",argv[0]);
  printf ("\n");
}

