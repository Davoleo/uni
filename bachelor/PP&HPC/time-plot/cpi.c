// gcc cpi.c -o cpi -lm -O2

// GNU SSProfiling    https://users.cs.duke.edu/~ola/courses/programming/gprof.html
// gcc cpi.c -pg  -o cpi-pg -lm -O2 
// ./cpi-pg
// gprof cpi-pg


#include <stdio.h>
#include <math.h>
#include <unistd.h>    //optarg
#include <time.h>      //gettime
#include <stdlib.h>

void options(int argc, char * argv[]) ;
void usage(char * argv[]);
double f1( double );
double f2( double );
double (*f)();   // Function pointer

int nf=1;                 // Function number
int n=10000000;           // Intervals number 
char hostname[100];

#define BILLION  1000000000L;

#define CL     CLOCK_REALTIME           // measures wall-clock time
//#define CL     CLOCK_PROCESS_CPUTIME_ID // per-process timer from the CPU
//#define CL     CLOCK_THREAD_CPUTIME_ID   // per-process timer from the CPU

 struct timespec start, stop;
 double perf; 

/********************************************/

int main( int argc, char *argv[])
{
    int done = 0,  i;

    double  PI = 3.14159265358979323846264338327950288 ;

    double  pi, h, sum, x;

    n=10000000; // default
    f=f1 ;      // default 
    gethostname(hostname, 100); 
 
   options(argc, argv);  /* optarg management */ 

   if (nf==2) f=f2;  

   clock_gettime( CL, &start);
 
    h   = 1.0 / (double) n;
    sum = 0.0;
    for (i = 1; i <= n; i++)
     {
        x = h * ((double)i - 0.5);
        sum += f(x);
      }
     pi = 4 * h * sum;

   clock_gettime( CL, &stop);

perf = (double) ( stop.tv_sec - start.tv_sec )
          + (double) ( stop.tv_nsec - start.tv_nsec )
            / BILLION;


    fprintf(stderr,"#Funct  Inter  pi    error   time   hostname \n");
    fprintf(stdout,"%d, %d,  %.10f, %.10e, %.5f,  %s \n", 
                nf, n, pi, fabs(pi-PI),perf,hostname);

    return 0;
}

/************************************************/
double f1( double x )
{
  return (1.0 / (1.0 + x*x));  }

/************************************************/
double f2( double x )
{   return (sqrt(1-x*x) );     }

/************************************************/

void options(int argc, char * argv[]) 
{
  int i;
   while ( (i = getopt(argc, argv, "n:f:h")) != -1) {
        switch (i) 
        {
        case 'n':  n  = strtol(optarg, NULL, 10);  break;
        case 'f':  nf = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

/***************************************/

void usage(char * argv[])
{
  printf ("\n%s [-n intervals] [-f function_number]  [-h]",argv[0]); 
  printf ("\n"); 

}

