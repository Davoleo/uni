Alias:
- .         -> Corrisponde ad un riferimento alla cartella corrente
- ..        -> Corrisponde ad un riferimento alla cartella madre
- ~user     -> Corrisponde ad un riferimento alla cartella home dell'utente (/home/user)

Nota: La shell sostituisce gli alias con i loro rispettivi significati durante il parsing, prima di eseguire il comando.

Comandi:
alias nome_alias='ls -a'    -> Permette di definire un alias per un altro comando o percorso, in generale stringa
unalias nome_alias          -> Permettere di rimuovere un alias precedentemente creato, dato il suo nome.
set                         -> Stampa l'elenco di tutte le variabili settate
export nome_var             -> fa in modo che la variabile sia disponibile anche ad altri processi generati da questa shell
printenv                    -> stampa tutte le variabili esportate
whereis -bms comando        -> cerca la locazione di un programma tra i sorgenti eseguibili e i manuali
which                       -> cerca il path completo o alias di un comando
altri comandi per ottenere informazioni di quel tipo sono: locate, type, file
tar -cf <nomearchivio> file_da_archiviare     -> crea un archivio
tar -tf <nomearchivio>      -> mostra il contenuto dell'archivio
tar -xf <nomearchivio>      -> estrare l'archivio
gzip file                   -> crea un archivio usando la codifica Lempel-Ziv
gunzip file.gz              -> ripristina il file precedentemente compressato tramite gzip
tar -czf                    -> crea un archivio e lo comprime con gzip (.tar.gz)
tar -xzf                    -> estrae un archivio compresso (.tar.gz)
wc                          -> fornisce il numero di: righe, parole, caratteri di un input


Nota: Gli alias creati con il comando alias sono automaticamente rimossi all'uscita della shell.

Variabili in BASH:
- Una variabile è un nome che può essere associato ad una stringa
- Una variabile non definita è associata alla stringa vuota
- per definire una variabile: nome_var=stringa [Spaces DO matter]
- per leggere il suo contenuto: $nome_var

Variabili predefinite con contenuto speciale:
- PATH: Elenco di directories dove vengono cercati gli eseguibili
- TERM: tipo di terminale usato per le sessioni interattive
- LANG: stabilisce in quale lingua mostrare i messaggi.
- UID: Unique ID dell'utente
- HOME: la home directory di questo utente
- PWD: la directory di lavoro dell'utente
- PS1: Prompt (Sono possibili diverse personalizzazioni grazie alle seguenti escape sequences)
    - \d -> data (e.g. Sat Nov 20)
    - \h -> l'hostname fino al primo '.'
    - \H -> l'hostname
    - \s -> il nome della shell, il nome base di $0
    Nota: La shell di login è lanciata dopo l'accesso ed ha il nome "-bash", mentre le shell successive (interattive e non) avranno il nome di "bash"
    - \t -> l'ora corrente nel formato 24-ore HH:mm:ss
    - \u -> lo username dell'utente corrente
    - \w -> la directory di lavoro corrente (pwd)
    - \W -> il nome di base della directory di lavoro corrente
    - \! -> il numero cronologico (history number)  di questo comando
    - \# -> il numero di questo comando
    - \$ -> se l'UID effettivo è 0, un # altrimenti $

Variabili di stato automatiche read-only:
- $?: Codice di uscita dell'ultimo comando eseguito (0 se terminato correttamente)
- $$: PID della shell corrente
- $!: PID dell'ultimo comando eseguito in background
- $-: opzioni della shell corrente
- $#: numero di parametri forniti allo script sulla linea di comando
- $*, $@: lista di tutti i parametri passati allo script da linea di comando

Metacaratteri:
* -> Wildcard per 0 o più caratteri
? -> Wildcard per un singolo carattere
[] -> Wildcard per un singolo carattere tra quelli elencati
{abc,def} -> stringa tra quelle elencate

Quoting:
- il metacarattere di escape '\' inibisce l'effetto del metacarattere seguente (E.g.: \? \*)
- tutti i metacaratteri presenti in una stringa racchiusa tra singoli apici perdono l'effetto speciale
- i metacaratteri per l'abbreviazione del pathname in una stringa racchiusa tra doppi apici perdono l'effetto speciale (tranne $, ', e \)

ogni processo possiede un certo numero di file aperti con cui può leggere e scrivere dati, 
ad ogni file aperto corrisponde un descrittore identificato da numero.
3 descrittore base:
- 0 = standard input    ==> tastiera
- 1 = standard output   ==> video
- 2 = standard error    ==> video
con la shell è possibile ridirezionare questi input/output:
- > ridirezione dell'output
- >> ridirezione dell'output (append)
- < ridirezione dell'input
- << ridirezione dell'input (append fino ad un certo delimitatore)
- 2> ridirezione dei messaggi di errore

- ;     -> Sequenza di comandi (pwd;ls;whoami) [input e output non è ridirezionato]
- |     -> Pipe, sequenza di comandi [eseguiti in parallelo, input e output sono ridirezionati]
- &     -> Esecuzione concorrente di comandi (e.g.: nano & ls) [per riprendere il primo comando che finisce in background si usa il comando fg]
- ||    -> Esecuzione Condizionale: Esegue il secondo comando se il primo fallisce
- &&    -> Esecuzione Condizionale: Esegue il secondo comando se il primo termina con successo
- (...) -> Raggruppamento di comandi (e.g.: (pwd;ls;whoami)>out.txt)
- #     -> Introduce un commento (ignorato)
- \     -> Protegge il metacarattere seguente (anche l'"a capo")

il carattere | serve a comporre comandi in cascata .. L'output del primo comando va come input al secondo

Si può personalizzare la shell in modo permanente modificando il file ~.bashrc
- aggiungendo alias
- modificando il prompt
- impostando una maschera di permessi (umask)
