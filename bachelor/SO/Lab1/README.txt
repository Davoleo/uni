https://www.biblioteche.unipr.it/it/node/2366

Hostname VPS scuola: didattica-linux.unipr.it

e' una variabile $SHELL si riferisce al percorso eseguibile di bash

date: visualizza la data corrente
who: utenti connessi al sistema
uname: versione e nome dell'OS
ps: processi in esecuzione
man: <nome_programma> manuale per un certo programma
ls: lista degli elementi del filesystem in una certa cartella
mkdir: crea una cartella
cp f1 f2: copia il f1 in f2
mv f1 f2: sposta f1 in f2
(cp e mv possono anche spostare una lista di file ad una nuova destinazione)
rm f: rimuove il file f completamente


Ctrl+a va ad inizio riga
Ctrl+e va a fine riga
Ctrl+k cancella riga
Ctrl+y reinserisce la riga cancellata

history -> comandi digitati in precedenza
!! -> richiama il comando precedente
!abc -> richiama l'ultimo comando immesso che inizia per "abc"
!<num> -> richiama il comando del relativo numero nel comando history
!?abc? -> richiama il comando nella history che contiene i caratteri scritti

Per concatenare 2 comandi si usa il character '|' : (l'output di quello a sinistra va in pasto a quello di destra)

Comandi di manipolazione di output di altri comandi:
cat: mostra il contenuto di un file
head: mostra le prime righe di contenuto
tail: mostra l'ultime righe di contenuto
cut:  permette di tagliare verticalmente splittandole per una stringa e scegliendo quale porzione prendere
grep: filtra le righe in output di un comando per una certa condizione
more: mostra alcune righe e il resto si può scorrere tramite invio
less: la stessa cosa di more ma puoi scorrere con le frecce

Contenuto di /:
/bin   comandi per l'utente
/sbin  programmi per l'amministrazione
/dev   dispositivi di I/O
/etc   File di configurazione di sistema
/lib   Librerie
/var   File di dimensione variabile
/usr   Programmi e Applicazioni
/home  Directory personali degli utenti
/proc  Contiene info dinamiche di sistema

la directory . è un riferimento relativo alla directory stessa
la directory .. è un riferimento relativo alla directory genitore

Ad ogni file e ogni directory è associato un identificatore, per vedere queste informazioni si usa -i in ls

ls -l mostra più informazioni sui file directory
1. tipo di file:
    l -> link
        Hard Link: Sono link a file (non dir) in questo caso sono copie collegate del file (ln filename linkname)
        Link Simbolici: Un collegamento ad un altro file o un altra directory (ln -s filename linkname)
    - -> file normale
    d -> directory
    p -> named pipe
    s -> socket per le comunicazioni send/receive
    b -> block device (dispositivi ad accesso random o dischi)
    c -> device con un flusso seriale di dati
2. Permessi
    root, owner(u), group(g), world(o)
    L'amministratore ha tutti i permessi su tutti i file.
    il resto dei permessi è grouppato a 3
    r -> esprime permesso di lettura in un file o dir
    w -> esprime il permesso di modificare un file o una cartella
    x -> esprime il permesso di eseguire un file o di attraversare una directory
    chmod cambia i permessi:
        - con triplette di numeri e.g. 744 -> 111 | 100 | 100 rispettivamente per le 9 flag
        - con 'u', 'g', 'o' e operatori '+', '-', '=' per aggiungere togliere e settare, e le lettere r, w, x,
3. Numero di HardLink collegati al file
4. Proprietario del file
5. Gruppo del proprietario del file
6. Grandezza del file in byte
7. Data di ultima modifica
8. nome del file


umask: utilizzato per assegnare i permessi di default ai nuovi file. 
    di solito viene inserito nei file di configurazione della shell.
    la sintassi è ottale come chmod ma agisce per togliere permessi 
    quindi 1 significa rimozione di una certa flag.

2 Editor standard per terminale:
- vi (curva di apprendimento complessa) [sempre presente] (vim = vi improvement)
- emacs
- nano