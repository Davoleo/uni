// gcc cpi.c -o cpi -lm -O2
// gcc cpi.c -pg  -o cpi-pg -lm -O2

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

 struct timespec t_np1,t_np2,t_p1,t_p2;
 double t_np, t_p; 

/********************************************/

int main( int argc, char *argv[])
{

////////////////////////////////////////////////
   clock_gettime( CL, &t_np1);

    int done = 0,  i;

    double  PI = 3.14159265358979323846264338327950288 ;

    double  pi, h, sum, x;

    n=10000000; // default
    f=f1 ;      // default 
    gethostname(hostname, 100); 
 
   options(argc, argv);  /* optarg management */ 

   if (nf==2) f=f2;  

    h   = 1.0 / (double) n;
    sum = 0.0;

   clock_gettime( CL, &t_np2);
////////////////////////////////////////////////

   clock_gettime( CL, &t_p1);
    for (i = 1; i <= n; i++)
     {
        x = h * ((double)i - 0.5);
        sum += f(x);
      }
   clock_gettime( CL, &t_p2);
////////////////////////////////////////////////



t_np = (double) ( t_np2.tv_sec - t_np1.tv_sec )
          + (double) ( t_np2.tv_nsec - t_np1.tv_nsec )
            / BILLION;


t_p = (double) ( t_p2.tv_sec - t_p1.tv_sec )
          + (double) ( t_p2.tv_nsec - t_p1.tv_nsec )
            / BILLION;


    fprintf(stderr,"#Funct  Inter  pi    error   time   hostname \n");
    fprintf(stdout,"%d, %d,  %.10f, %.10e, %.5f,  %.5f, %s \n", 
                nf, n, 4*h*sum , fabs(pi-PI),t_np,t_p,hostname);

    return 0;
}

/************************************************/
double f1( double x )
{
  return (1.0 / (1.0 + x*x));  }

/************************************************/
double f2( double x )
{   return (sqrt(1-x*x));     }

/************************************************/

void options(int argc, char * argv[]) 
{
  char i;
  while ((i = getopt(argc, argv, "n:f:h")) != -1) {
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

