/*
 * This program calculates the time required to
 * execute the program specified as its first argument.
 * The time is printed in seconds, on standard out.

 * gcc clockgettime.c -o clockgettime -O2
 * ./clockgettime cpi
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 
#define BILLION  1000000000L;

#define CL     CLOCK_REALTIME           // measures wall-clock time
//#define CL     CLOCK_PROCESS_CPUTIME_ID // per-process timer from the CPU
//#define CL     CLOCK_THREAD_CPUTIME_ID   // per-thread timer from the CPU
 
int main( int argc, char **argv )
  {
    struct timespec start, stop;
    double accum;
 
    if( clock_gettime( CL, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
 
    system( argv[1] );
 
    if( clock_gettime( CL, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
 
    accum = (double) ( stop.tv_sec - start.tv_sec )
          + (double) ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
    printf( "%.9lf\n", accum );
    return( EXIT_SUCCESS );
  }
