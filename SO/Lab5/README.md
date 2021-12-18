### [Guida Gapil](https://gapil.gnulinux.it/download/)


# Processi in UNIX
- Creati con la syscall `fork()`, il figlio è una copia del padre ma eseguito indipendente e con un nuovo PID
- Il padre attende il figlio tramite `wait()` o `waitpid()`
- Utilizzi tipici di fork
  - Unico programma con 2 sezioni: una per il padre l'altra per i figli
  - il figlio esegue un altro programma mediante la syscall della famiglia `exec()`

## System Call in UNIX:
- Informazioni sull'ambiente
  - getenv(): variabili d'ambiente
  - getpid(): pid del processo
  - getppid(): pid del processo padre
  - getuid(): uid dell'utente che ha lanciato il processo
  - getcwd(): current working dir
- Modificazione dell'ambiente del processo
  - putenv(): Modifica variabili d'ambiente
  - setuid(): Cambia l'UID 
  - setgid(): Cambia il Group ID del processo corrente
  - chdir(): Cambia la CWD
- Creazione e terminazione nuovo processo
  - fork()
  - exit(): terminazione del processo corrente (con status)
- Sostituire il programma in esecuzione con un altro
  - execve()
  - execl()
  - execlp()
  - execle()
  - execv()
  - excvp()
- Sospendere l'esecuzione fino alla terminazione del figlio/processo: wait(), waitpid()

Interfaccia standard di UNIX (basso livello adatta per la programmazione di sistema): `unistd.h`
File descriptor: 
- numeri interi che fanno riferimento ai file aperti.
- 3 file descriptor caratteristici
  1. fd0: **standard input**, associato all'input da tastiera nel caso della shell (Costante: STDIN_FILENO)
  2. fd1: **standard output**, associato all'output su schermo nel caso della shell (Costante: STDOUT_FILENO)
  3. fd2: **standard error**, associato all'output standard degli errori, schermo nel caso della shell (Costante: STDERR_FILENO)

### Operazioni su File
- Apertura di un file: file_descriptor=open(file, flags)
  - esempio: `fd = open(filename, O_RDONLY)`
    - Second Parametro
      - `O_CREAT`: Create the file if it doesn't exist
      - `O_WRONLY`: Write Only
      - `O_TRUNC`:
    - Terzo Parametro
      - `S_IRWXU`: 
      - `S_IRGRP`: 
      - `S_IROTH`: 
- Chiusura di un file: `close(file_descriptor)`
  - Quando un processo termina vengono chiusi di default tutti i suoi file descriptor (senza nessuna garanzia su eventuali scritture in sospeso)
- Lettura su file: `n = read(int file_descriptor, char* buffer, int num_byte);`
- Scrittura di un file: `n = write(int file_descriptor, char* buffer, int num_byte)`
- ritorna il numero di byte scritti o letti oppure -1 in caso di errore
- http://www.linuxdidattica.org/docs/prg_C/cgiprg15.html

1:34:10