// compila con:  gcc semthread.c -o semthread -lpthread
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

/*!
\mainpage Esempio Semafori con Pthreads
\section intro Introduzione
Esempio di utilizzo semafori

\date 10/05/2006
\version   0.0.0.1
\author    A.Dal Palu
*/



static sem_t s1,s2;  /// semafori 



/*!
    \brief  Codice del thread1 
    
    Il thread fa Ping e fa UP sul semaforo dell`altro thread
*/
void *thread1(void * arg)
{
  int i;
  for (i=0;i<10;i++){
    sem_wait(&s1);
    printf("Ping\n");
    sem_post(&s2);
  }
  printf("T1 exit\n");
  pthread_exit (0);
}


/*!
    \brief  Codice del thread2
    
    Il thread fa Pong e fa UP sul semaforo dell`altro thread
*/
void *thread2(void * arg)
{
  int i;
  for (i=0;i<10;i++){
    sem_wait(&s2);
    printf("Pong\n");
    sem_post(&s1);
  }
  printf("T2 exit\n");
  pthread_exit (0);
}


int main()
{
  pthread_t tid1,tid2;
  void * ret;

  sem_init(&s1,0,1);
  sem_init(&s2,0,0);

  if (pthread_create(&tid1, NULL, thread1, NULL) < 0)
    { fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
    }

  if (pthread_create(&tid2, NULL, thread2, NULL) < 0)
    { fprintf (stderr, "pthread_create error for thread 2\n");
    exit (1);
    }

  pthread_join (tid1, &ret);
  pthread_join (tid2, &ret);

  printf("Exit\n");
}

