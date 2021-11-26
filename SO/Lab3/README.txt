Test1
Test2
Test3
askfaasjfklsafjksajflkasjfksalfjakljfslkfjalkf

Comandi:
-> diff file1 file2 -> Mostra la differenza di content tra 2 file 
    la flag -y permette di vedere i due file side by side
-> cmp file1 file2  -> Stampa il numero del primo char e della prima linea di differenza tra i 2 file
-> find regexp      -> Stampa tutto l'elenco dei file che matchano i criteri 
    -name: e' usato come flag (ricerca ricorsiva | la stringa puo' contenere metacaratteri)
    -type: permette di scegliere (filtrare) il tipo di file deciso
    -exec: esegue un certo comando sui file trovati
-> ps: Stampa l'elenco dei processi attivi e il relativo PID
    -a: tutti i processi associati ad un terminale
    -f: per avere ulteriori informazioni
    -e: tutti i processi del sistema
    -l: piu' informazioni!!!!!!!!! (long listing [come ls])
-> tty: stampa il path del terminale nell'uso corrente
-> kill PID: termina un processo relativo al pid inserito (manda il segnale SIGTERM che conclude tutto e poi termina)
    -9: manda il segnale SIGKILL e termina forzatamente il processo
    %1: killa il primo processo tra quelli sospesi e in background listati da jobs
-> jobs: lista i processi in background
-> fg: recupera il programma che era eseguito in background e lo riporta in foreground
-> bg: recupera il processo sospeso mandandolo in background
-> Ctrl+Z: sospende il processo 
-> nice: lanciare un processo con una priorita' diversa dal normale (gli utenti non admin non possono aumentare la priorita' dei processi ma solo diminuirla)
    -n 1: numero di priorita' 1
-> renice: cambia la priorita' nice di un processo
-> top: informazioni sui processi e aggiornate dinamicamente
    - tante informazioni
-> grep: gestisce regexp semplici e filtra delle stringhe a seconda di un espressione data
    fgrep|-f: no regexp (fixed string)
    egrep|-e: extended regexp
    -i: case insensitiveness
    -l: lista dei file  che contengono il pattern/string
    -n: le linee di match sono precedute dal loro numero
    -v: nega il pattern invertendo il risultato
    -x: solo match esatto <
-> tr string1 string2: (sta per translation), permette di eseguire operazioni su maiuscole, minuscole, punteggiatura,
    tramite regex
    -c: inverte la prima condizione
    -s: comprime gli spazi adiacenti in 1
    -d: cancella i caratteri invece che sostituirli
-> sort: tratta ogni linea come un elemento e li ordina di default in ordine alfabetico crescente 
    -n: ordinamento numerico invece che letterale
    -t'c': usa c come separatore dei campi invece che \n
    -k5: usa il campo 5 come chiave di ordinamento
    -r: inverte l'ordine di tutto
-> cut: taglia verticalmente ogni linea a seconda di un carattere delimitatore selezionando alcuni campi
-> sed action files: (stream editor) cerca di applicare action per ogni linea di ogni file in input
    - e.g.: sed '4,$d' miofile.txt  [Prende in input miofile.txt e dalla riga 4 fino alla fine applica l'azione d, ovvero delete];
    - e.g.: sed '/sh/y/ab/cd' miofile.txt [sostituisce ab con cd nelle linee in cui sono presenti i caratteri sh (match e tr)] {con ! davanti a y sostituirà solo dove non trova sh}
    - e.g.: sed 's/old/new/g' miofile.txt [sostituisce old con new globalmente in miofile.txt]
    - altri esempi sulle slide
    - /w scrive tutto sul nome di file seguente
-> awk: processa un file di testo con un programma specificato dall'utente, può fare tutto ciò che fa sed
        ma in più ha anche le condizioni 
    - Sintassi: [condition] [{ action }]
    - Condition può essere applicata (in BEGIN in END)
    - variabili predefinite: Slide
    - operatori e funzioni built-in: Slide
    - esempi: Slide



Processo in foreground: processo che si aspetta di interagire con l'utente
Processo in background: viene eseguito sotto, sono eseguiti in sottoshell in parallelo alla principale (& alla fine del comando)