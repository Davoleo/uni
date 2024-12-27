#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

/*!
\mainpage Esempio Problema Filosofi con semafori
Esempio di utilizzo dei semafori per risolvere il problema dei 5 filosofi che mangiano.

\date 02/01/2022
\version   0.0.1.0
\author    A.Dal Palu, Leonardo Davoli
*/


#define DOWN (-1)
#define UP (1)
#define MYCODE 'a'

// Definizione della struttura semun
#ifdef _SEM_SEMUN_UNDEFINED
#define _SEM_SEMUN_UNDEFINED  1
union semun /* definita in bits/sem.h */
{
  int val;                              /* value for SETVAL */
  struct semid_ds *buf;                 /* buffer for IPC_STAT & IPC_SET */
  unsigned short int *array;            /* array for GETALL & SETALL */
  struct seminfo *__buf;                /* buffer for IPC_INFO */
};
#endif



/************************  sem_up() ***********************/
/*!
    \brief  Dello zucchero sintattico per fare la UP
    \param  ipcid Riceve il numero dell`oggetto IPC
    \param  nsem Il semaforo su cui fare UP
    
    Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/
void sem_up(int ipcid, int nsem)
{
  struct sembuf sops[1];
  sops[0].sem_num = nsem;
  sops[0].sem_op = UP;
  sops[0].sem_flg = 0;
  if (semop(ipcid, sops, 1) == -1) {
    perror("Errore in semop");
    exit(3);
  }
}

/************************  sem_up() ***********************/
/*!
  \brief  Dello zucchero sintattico per fare la DOWN
  \param  ipcid Riceve il numero dell`oggetto IPC
  \param  nsem Il semaforo su cui fare DOWN
  
  Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/void sem_down(int ipcid, int nsem)
{
  struct sembuf sops[1];
  sops[0].sem_num = nsem;
  sops[0].sem_op = DOWN;
  sops[0].sem_flg = 0;
  if (semop(ipcid, sops, 1) == -1) {
    perror("Errore in semop");
    exit(3);
  }
}

/************************  sem_set() ***********************/
/*!
  \brief  Dello zucchero sintattico per impostare il valore di un semaforo
  \param  ipcid Riceve il numero dell`oggetto IPC
  \param  nsem Il semaforo da impostare
  \param  initial Il valore iniziale del semaforo
  
  Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/
void sem_set(int ipcid, int nsem, int initial)
{
  union semun arg;
  arg.val = initial;
  if (semctl(ipcid, nsem, SETVAL, arg) == -1) {
    perror("set value sem");
    exit(2);
  }
}

/************************  think() ***********************/
/*!
  \brief  Codice tramite cui i filosofi pensano
  \param  ipcid Riceve il numero dell`oggetto IPC
  
  
*/
void think(int ipcid, int phindex)
{
  printf("Philosopher %d is Thinking...\n", phindex);
  sleep(5);
  printf("Philosopher is done thinking. Exiting...");
}

/************************  eat() ***********************/
/*!
  \brief  Codice tramite cui i filosofi mangiano.
  \param  ipcid Riceve il numero dell`oggetto IPC
  
  Ottiene 2 forchette adiacenti a sé e MANGIA
*/
void eat(int ipcid, int phindex)
{
  //acquire 2 adjacent forks
  int fork1 = phindex;
  int fork2 = (phindex + 1) % 5;
  sem_down(ipcid, fork1);
  sem_down(ipcid, fork2);
  //Simulate eating
  printf("Philosopher %d is Eating...\n", phindex);
  sleep(1);

  //release both forks
  sem_up(ipcid, fork1);
  sem_up(ipcid, fork2);

  think(ipcid, phindex);
}


int main()
{
  key_t key;
  int npro, sid, val, pid;
  char s[60];
  union semun arg;
  struct sembuf sops[2];

  // ottieni chiave IPC da pathname (".") e codice (MYCODE)
  if ((key = ftok(".", MYCODE)) == -1) { 
    perror("ftok per creare chiave");
    exit(1);
  }

  if ((sid = semget(key, 5, 0600 | IPC_CREAT )) == -1) {
    perror("creazione 5 semafori, uno per ogni forchetta");
    exit(1);
  }
  
  for (int i=0; i<5; i++)
    sem_set(sid, i, 1); //Set all forks as available

  for (int i=0; i<5; i++) {

    switch (pid = fork()) {
    case -1:
      perror("forking");
      exit(2);
    case 0: 
      printf("Figlio %d con ID %d\n", i, getpid());
      eat(sid, i);
      printf("Figlio %d: mi sono sganciato, termino\n", i);
      exit(0);
    default: 
      /*Padre: osserva e sgancia il semaforo */
      if (i < 4)
        continue;
      else {
        printf("Padre - dopo aver forkato l'ultimo processo\n");
        printf("Padre: attendo terminazione dei figli philospher\n");
        for (int i=0; i<5; i++) {
          waitpid(0, NULL, 0);
        }
        if (semctl(sid, 0, IPC_RMID, 0) == -1)
          perror("rimozione sem");
        printf("Padre: finito, exiting program...\n");
      }
    }
  }
}

