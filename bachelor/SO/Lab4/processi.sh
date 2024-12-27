#!/bin/bash
# Script per Gestire processi attivi

echo '+---------------------------------------------------+'
echo '|       Script di Controllo Processi Attivi         |'
#echo '| 1: Mostra Processi attivi per Utente                                 |'
#echo '| 2: Termina un Processo tramite PID                                   |'
#echo '| 3: Termina FORZATAMENTE un Processo tramite PID                      |'
#echo '| 4: Elenca gli utenti che hanno almeno un processo attivo nel sistema |'
#echo '| 5: Esci                                                              |'
echo '+---------------------------------------------------+'

select action in    "Mostra Processi attivi per Utente" \
                    "Termina un Processo tramite PID" \
                    "Termina FORZATAMENTE un Processo tramite PID" \
                    "Elenca gli utenti che hanno almeno un processo attivo nel sistema" \
                    "Esci"
do
    case $REPLY in
        1) echo -n "Utente: "
        read user
        ps -U $user | tr -s ' ' | cut -d' ' -f2,5 ;;

        2) echo -n "Process ID? "
        read pid
        echo Killing Process $pid...
        kill $pid ;;

        3) echo -n "Process ID? "
        read pid
        echo Force-Killing Process $pid...
        kill -9 $pid;;

        # Tutti gli utenti collegati hanno almeno un processo in ese
        4) ps -e -o user= | sort | uniq;;

        5) echo Exiting...; break;;

        *) echo "Scelta non valida!"
        

    esac 
done