#!/bin/bash

# Exercise 6: Bash script
# Create uno script chiamato /exam/exercise6/exercise6.sh
# Lo script accetterà come unico argomento un file
# Se il file passato non è un file o non esiste restituirà in output “File not found”
# Se il file passato esiste restituisca il formato del file
# Se non viene passato nessun argomento dovrà restituire il messaggio 
#    "Usage:/exam/exercise6/exercise6.sh <file>"



#variables 
FILE=$1

#Check if arguments exists
if [ "$#" -eq "0" ]; then
    echo "Usage:/exam/exercise6/exercise6.sh <file>"
    exit 1
fi

#Check if file exists
if [ -e $FILE ]; then
    file $FILE
else
    echo "file not found"
    exit 1
fi
