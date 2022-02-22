## Shell scripts:
- Costrutti Atomici -> Comandi

**Eseguire gli shell script:**
- `/bin/bash script_name`
- `./script_name`
la seconda opzione è possibile solo se si specifica "#!/bin/bash" l'interprete alla prima riga dello script

**Comandi:**
- `echo string` -> stampa string
    - -n: non aggiunge il carattere di "a capo" dopo la stampa
- `read var_name` -> legge una stringa da standard input e la mette nella variabile var_name
    - read var1, var2 ...: legge le parole che compongono l'input e le divide nelle diverse variaibli
    - -a: legge le parole della stringa e le assegna ad un array
- `test expression` -> se expression risulta a true ritorna 0 altrimenti ritorna un exit status pari a 1
    - si può abbreviare mettendo tra parentesi quadre `[]` la condizione (si aggiunge `$` davanti alle `[]` quando si valutano espressioni numeriche complesse)
    - -e file : vero se file esiste
    - -f file : vero se file è un file ordinario
    - -d file : vero se file è una directory
    - -r file : vero se file è leggibile dall'utente
    - -w file : vero se file è scrivibile dall'utente
    - -x file : vero se file è eseguibile dall'utente
    - -z str : vero se str è di lunghezza zero
    - -n str : vero se str non è di lunghezza zero
    - str1 = str2 : vero se str1 e str2 sono uguali
    - str1 != str2 : vero se str1 e str2 sono diverse
    - num1 -eq num2 : vero se num1 è uguale a num2
    - num1 -ne num2 : vero se num1 è diverso da num2
    - num1 -lt num2 : vero se num1 è minore di num2
    - num1 -gt num2 : vero se num1 è maggiore di num2
    - num1 -le num2 : vero se num1 è minore o uguale a num2
    - num1 -ge num2 : vero se num1 è maggiore o uguale a num2
    - bool1 -a bool2 : vero se le 2 espressioni booleane sono entrambe vere
    - bool1 -o bool2 : vero se almeno 1 delle 2 espressioni booleane è vera
    - !bool : restituisce vero se bool non è vero

**Variabili:**
- `$0`: nome dello script
- `$1`, `$2`, ...: parametri posizionali passati allo script quando è lanciato
- `$*` oppure `$@`: la lista di parametri a partire dal primo

**Command Substitution:** permette di sostituire ad un comando nello script il suo output sullo standard input, si fa circondando il comando da backquotes (`)

### if-then-else
**Struttura:**
```sh
if condition_command
then
    true_commands
else
    false_commands
fi
```
**Semantica:** Se condition_command restituisce 0 come exit status -> esegue true_commands : altrimenti esegue false_commands

### while
**Sintassi:**
```sh
while condition_command
do
    commands
done
```
**Semantica:** Esegue commands finché condition_command non diventa falso

### for
**Sintassi:**
```sh
for var in wordlist
do
    commands
done
```
**Semantica:** Esegue commands per ogni var dentro a wordlist.

### select
Permette all'utente di scegliere tra le opzioni elencate dopo `in`<br>
_More in `examples.sh`_

### case
Permette di gestire una scelta multipla<br>
**Struttura:**
```sh
case string in
model1) command_list;;
model2) command_list;;
*) comandi_wildcard;;
esac
```

Check [examples.sh](./examples.sh)