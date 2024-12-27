// complia con gcc exCreazioneThread.c -o exCreazioneThread -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *my_thread(void * arg)
{
  int i;
  for (i = 0 ; i < 5 ; i++) {
    printf ("Thread %s: i%d\n", (char*)arg, i);
    sleep (1);
  }
  pthread_exit (0);
}


int main()
{
  pthread_t tid1, tid2;
  int retcode;

  if (pthread_create(&tid1,NULL,my_thread,"1") < 0){
    fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
  }
  if (pthread_create(&tid2,NULL,my_thread,"2") < 0){
    fprintf (stderr, "pthread_create error for thread 2\n");
    exit (1);
  }
  retcode = pthread_join (tid1, NULL);
  if (retcode != 0)
    fprintf(stderr, "join fallito %d\n", retcode);
  else printf("terminato il thread 1\n");  
  retcode = pthread_join (tid2, NULL);
  if (retcode != 0)
    fprintf (stderr, "join fallito %d\n", retcode);
  else printf("terminato il thread 2\n");  
  return 0;
}
