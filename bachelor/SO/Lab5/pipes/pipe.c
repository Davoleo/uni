#include <stdio.h>
#include <unistd.h>

/*!
\mainpage Esempio Pipe
\section intro Introduzione
Esempio di creazione pipe per lanciare ls | sort\n

\date 02/05/2006
\version   0.0.0.1
\author    A.Dal Palu
*/


int main() {
  int pid;
  int fd[2];

  pipe(fd);

  if ((pid = fork()) == 0) { /* figlio */
    /* chiusura lettura da pipe */
    close(fd[0]);

    //send standard output to the pipe file descriptor
    dup2(fd[1], 1);
    //Write sample string to the pipe
    printf("oh boi I'm the child process (%d) and I'm sending stuff through a pipe. parole che non verranno stampate\n", getpid());

    //Old Example
    //redirezione stdout a pipe
    //dup2(fd[1], 1);
    //execlp("ls", "ls", NULL);
  }
  else if (pid > 0) { /* padre */
    /* chiusura scrittura su pipe */
    close(fd[1]);

    char content[128];
    //Read content from the reading end of the pipe
    read(fd[0], content, 128);

    char* current = content;
    do {
      putchar(*current);
      current++;
    } while(*current != '.');

    //Old Example
    //redirezione stdin a pipe
    //dup2(fd[0],0);
    //execlp("sort", "sort", NULL);
  }

  return 0;
}

