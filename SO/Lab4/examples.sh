#!/bin/bash

# String input / output
echo -n "Inserire una stringa: "
read -a vett << EOF
zero uno due tre
EOF
echo ${vett[2]}
echo "Lunghezza di vett: " ${#vett[*]} # Oppure ${#vett[@]}

# Command substitution
today=`date`
echo $today

select param in unos dos tres
do
    echo Selected option: $param
    case $param in
        unos) echo 'Hai scelto il numero spagnolo UNOS (spoiler: non esiste)';;
        dos) echo 'Hai scelto il numero spagnolo DOS (il migliore)';;
        *) echo "ogni numero spagnolo più alto di dos non è valido :))";;
    esac
    break # Senza break permette all'utente di continuare a selezionare opzioni
done

