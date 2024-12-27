// gcc omp_cpi.c -o omp_cpi -lm -O2 -fopenmp

#include <stdio.h>
#include <math.h>
#include <unistd.h>    //optarg
#include <stdlib.h>
#include <omp.h>

void options(int argc, char * argv[]) ;
void usage(char * argv[]);
double f1( double );
double f2( double );
double (*f)(double);   // Function pointer
 
int nf=1;                      // Function number
long long int n=10000000;      // Intervals number 
char hostname[100];

double t1, t2;
double sum; 
int t,j;

/********************************************/

int main( int argc, char *argv[])
{
    int done = 0,  i;

    double  PI = 3.14159265358979323846264338327950288 ;

    double  pi, h, x;

    n=10000000; // default
    f=f1 ;      // default 
    gethostname(hostname, 100); 
    t=omp_get_num_procs();  // numero di  core sul nodo

   options(argc, argv);  /* optarg management */ 

   if (nf==2) f=f2;  

   omp_set_num_threads(t);
 
    h   = 1.0 / (double) n;
    sum = 0.0;

   t1=omp_get_wtime();

  #pragma omp parallel  for  private(x)  reduction(+:sum) 
    for (i = 1; i <= n; i++)
     {
        x = h * ((double)i - 0.5);
        sum += f(x);
     }

   t2=omp_get_wtime();

   pi=4*h*sum;

   fprintf(stderr,"#Funct  Inter  pi    error   time  thread   hostname \n");
   fprintf(stdout,"%d %lld %.10f %.10e %.5f  %d %s \n",
                nf, n, pi , fabs(pi-PI),t2-t1,t,hostname);

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
   while ( (i = getopt(argc, argv, "t:n:f:h")) != -1) {
        switch (i) 
        {
        case 't':  t  = strtol(optarg, NULL, 10);  break;
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

