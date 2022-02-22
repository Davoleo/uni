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

## [Doxygen](www.doxygen.org)
Tool per la generazione automatica di documentazione a partire dai commenti (like javadoc)<br>
Diversi tipi di formati disponibili tra cui: html, man, latex, rtf.

### Interazione tra processi
- Unix Pipe: (le stesse che si usano in bash con '|' chiamate di sistema implicite) è una comunicazione tra 2 processi tramite stream.
  - in C (`unistd.h`) con la funzione `int pipe(int fd[2])`
  - `fd[0]` è usato per leggere dalla pipe mentre `fd[1]` è usato per scrivere sulla pipe
  - syscall `dup2(old_fd, new_fd)` sovrascrive il vecchio file descriptor con una copia del nuovo -> consente di ridirezionare il flusso (quello che avviene dietro le quinte)
- Unix RPC: (Remote Procedure Calls) Chiamata a funzione su processo remoto attraverso la rete
- BSD Socket: Stream tra 2 processi attraverso la rete
- Unix Signals: Notifica di eventi asincroni tra processi.
- SysV IPC (83) (InterProcess Communication) [headers `sys/ipc.h`, `sys/shm.h`]
  - Sezioni di memoria condivisa ()
    - `int shmget(key_t key, size_t size, int flags)` ottiene l'ID di un segmento di memoria condivisa
    - flag IPC_CREATE => creazione del segmento,  se non è utilizzato il sistema può recuperare un segmento creato da qualcun'altro e renderlo disponibile
    - chiamate di controllo (template): `int <ipc>ctl(int ipcid, [int ipcnum], int cmd, ...)`
    - ipcid: id relativo alle chiamate `<ipc>get()`
    - cmd può essere diverse cose tra cui
      - IPC_STAT: ottiene informazioni sull'oggetto
      - IPC_SET: si impostano delle informazioni
      - IPC_RMID: dealloca l'oggetto (se non viene deallocato il kernel lo considera attivo anche dopo che i processi terminano)
      - Questa cosa permette la comunicazione tra processi attivi in momenti distinti, ma c'è anche il rischio di lasciare attivo un oggetto non più utilizzato, a sprecare risorse
    - Portare la memoria condivisa nello spazio di address del processo (Attach): `int shmat(int shmid, char* shmaddr, int shmflg)`
    - Detach (operazione opposta a shmat): `shmdt()`
  - Sincronizzazione con semafori (semctl())
    - alloca e ottiene numsem semafori: `semid semget(key_t key, int numsem, int flags)`
    - `int semop(int semid, struct sembuf* sops, unsigned nsops)`: esegue una lista di operazioni in sops su nsops semafori
      - i dati di sops sono: `sem_num` (numero di semaforo a cui ci si riferisce), `sem_op` (operazione da eseguire [+1, 0, -1]), `sem_flg` (flags)
      - Con sem_op 0 il chiamante attende finché tutte le risorse non sono in uso
    - `int semctl(int semid, int semnum, int cmd, union semun arg)`
    - cmd è: `<SETVAL | GETVAL | GETNCNT | IPC_RMID>`
    - arg è ununione che cambia a seconda del cmd utilizzato, è definito in `sys/sem.h`
      ```c
      /* Arg for semctl system calls */
      union semun {
        int val;
        struct semid_ds* buf;   //Value for SETVAL cmd
        ushort *array;          //buffer for IPC_STAT & IPC_SET cmds
        struct seminfo* __buf;  //array for GETALL & SETALL cmds
        void* __pad;            //buffer for IPC_INFO cmd
      };
      ```
  - Capitolo 11 di [GaPiL](https://gapil.gnulinux.it/files/2011/12/gapil.pdf)
  - Oggetti dell'OS identificati da ID (I 2 processi devono avere una chiave unica per comunicare)
  - metodo per generare una chiave unica a seconda del percorso del processo e di un byte id `key_t ftok (char* pathname, char id)`
  - Comandi:
    - `ipcs` lista degli oggetti IPC attivi
    - `ipcrm <msg | sem | shm> <IPC_ID>` rimuove l'oggetto IPC attivo ad un certo id

- Pthread
  - Memoria condivisa tra più thread
  - Sincronizzazione con semafori (pthread_mutex_*())
