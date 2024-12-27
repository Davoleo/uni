/******************************************************************************
* FILE: mm.cpp
* DESCRIPTION:
*   Serial Matrix Multiply - C Version
*   To make this a parallel processing progam this program would be divided into
*   two parts - the master and the worker section.  The master task would
*   distributes a matrix multiply  operation to numtasks-1 worker tasks.
* AUTHOR: Blaise Barney
* LAST REVISED: 04/02/05
*
*  g++ -O2 mm.cpp -o mm
*
******************************************************************************/
#include <stdlib.h>
#include <unistd.h>    //optarg
#include <time.h>
//clock()
#include <sys/time.h>  // gettimeofday()
#include <iostream>

using namespace std;

void options(int argc, char * argv[]);
void usage(char * argv[]);

int n; // dimensione lato matrice quadrata



int main(int argc, char *argv[])
{

 n=1000;

 options(argc, argv);  /* optarg management */


int NCB, NRA, NCA;
NCB=n; NRA=n; NCA=n;
int    i, j, k;                 /* misc */
double *a,*b,*c;

cout << "#Malloc matrices a,b,c " << n << "x" <<n << " of double \n";

a=(double *)malloc(sizeof(double)*NRA*NCA);
b=(double *)malloc(sizeof(double)*NCA*NCB);
c=(double *)malloc(sizeof(double)*NRA*NCB);

clock_t  t0, t1, t2;
double dt01, dt12;
struct timeval tempo;
double tv0, tv1, tv2;

cout << "#Set timer 0 \n";

gettimeofday(&tempo,0); tv0=tempo.tv_sec+(tempo.tv_usec/1000000.0);
t0 = clock();

cout << "#Initialize A, B, and C matrices \n";

   for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
          *(a+i*NCA+j)= i+j;
   for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
          *(b+i*NCA+j)= i*j;
   for(i=0;i<NRA;i++)
      for(j=0;j<NCB;j++)
         *(c+i*NCA+j)= 0.0;

cout << "#Perform matrix multiply\n";
cout << "#Set timer 1 \n";

 t1 = clock();//time(NULL);
 gettimeofday(&tempo,0); tv1=tempo.tv_sec+(tempo.tv_usec/1000000.0);


   for(i=0;i<NRA;i++)
      for(j=0;j<NCB;j++)
         for(k=0;k<NCA;k++)
            *(c+i*NCB+j)+= *(a+i*NCB+k) * *(b+k+j*NRA);

 t2 = clock();//time(NULL);
 gettimeofday(&tempo,0); tv2=tempo.tv_sec+(tempo.tv_usec/1000000.0);

cout << "#Set timer 2 \n";

 dt01=(double)(t1-t0)/CLOCKS_PER_SEC;
 dt12=(double)(t2-t1)/CLOCKS_PER_SEC;



cout << "#Dim     Tnp        Tp \n" ;
cout <<  n << " " << dt01 <<  "  " << dt12 << endl;

return 0;
}

/************************************************/

void options(int argc, char * argv[])
{
  int i;
   while ( (i = getopt(argc, argv, "n:h")) != -1) {
        switch (i)
        {
        case 'n':  n  = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

/***************************************/

void usage(char * argv[])
{
  cout << argv[0] << "  [-n <dim_lato_matrice> ] [-h] " << endl;
  return;

}

