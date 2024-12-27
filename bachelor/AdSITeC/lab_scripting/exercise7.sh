#!/bin/bash

# Create uno script chiamato /exam/exercise7/users.sh
# Lo script accetterà come primo argomento quale azione lo script dovrà eseguire (list/add/remove) e come secondo un nome utente
# Se chiamato con l’opzione list dovrà restituire la lista degli utenti presenti sul sistema
# Se chiamato con l’opzione add dovrà aggiungere l’utente passato come argomento
# Se chiamato con l’opzione remove, dovrà eliminare l’utente passato come argomento
# Se lo script viene chiamato senza argomenti o errati dovrà tornare il messaggio "Usage: /exam/exercise7/createuser.sh list/add/remove <username> "  
# Si utilizzi il case statement per gestire lo script

#check arguments 
if [ "$#" -lt "2" ] && [ "$1" != "list" ]; then
    echo "Usage: /exam/exercise7/createuser.sh list/add/remove <username>"
    exit 1
fi

#variables
USER=$2
ACTION=$1

case $ACTION in
    list)
        cut -d: -f1 /etc/passwd 
    ;;
    add)
        useradd $USER 1>/dev/null
        if [ $? -eq 0 ]; then
            echo "User $USER succesfully added"
        else
            echo "Error adding user $USER"
        fi
    ;;
    remove)
        userdel -r $USER 1>/dev/null
        if [ $? -eq 0 ]; then
            echo "User $USER succesfully removed"
        else
            echo "Error deleting user $USER"
        fi
    ;;
    *)
        echo "Usage: /exam/exercise7/createuser.sh list/add/remove <username>"
        exit 1
    ;;
esac