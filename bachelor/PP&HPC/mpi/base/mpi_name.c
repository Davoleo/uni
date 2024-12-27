/******************************************************************************/
/* name_mpi.c
*/
/* Test dei nomi dei processori                                               
*/
/* Fabio Spataro                                                              
*/
/******************************************************************************/

#include <stdio.h>
#include "mpi.h"

/*============================================================================*/

int main(int argc, char **argv)
{
   int        rank, np;
   char       name[MPI_MAX_PROCESSOR_NAME];
   int        resultlen;
   int        i;
   MPI_Status status;

/*----------------------------------------------------------------------------*/

   // INIZIALIZZAZIONE DI MPI
   MPI_Init(&argc, &argv);

   // OTTIENE IL RANK DEL PROCESSO NEL COMMUNICATOR STANDARD
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   // OTTIENE IL NUMERO DI PROCESSI NEL COMMUNICATOR STANDARD
   MPI_Comm_size(MPI_COMM_WORLD, &np);

/*----------------------------------------------------------------------------*/

   MPI_Get_processor_name(name, &resultlen);

/*----------------------------------------------------------------------------*/

   if(rank != 0)
   {
      MPI_Send(&resultlen, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Send(name, resultlen+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
   }

   if(rank == 0)
   {
      printf("[%d] Nome del processore = %s\n", rank, name);

      for(i = 1; i < np; i++)
      {
         MPI_Recv(&resultlen, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
         MPI_Recv(name, resultlen+1, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);      
         printf("[%d] Nome del processore = %s\n", i, name);
      }
   }

/*----------------------------------------------------------------------------*/

   // FINE DELLE OPERAZIONI CON MPI
   MPI_Finalize();
}

/*============================================================================*/

