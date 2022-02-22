
#include <iostream>

int main() {
    std::cout <<  "Hello World!" << std::endl;
}

/*
Preprocessing:
hello.cpp --preprocessing (-E)--> hello.preproc.cpp --compiling stretto (-S)--> hello.s --compiling (-c)--> hello.o --linking--> hello(.exe)
#include con <> cerca gli header nei file di sistema tra quelli di default
         con "" cerca gli header negli include path specificati (-I) oppure nella cartella stessa

#pragma GCC system_header (fa in modo che non vengano printati warning sul file header di sistema)

nel contenuto del file di preoprocessing ci sono degli # che segnano di chi è il pezzo di codice 
(nel caso escano fuori degli errori stampa la riga e il file colpevoli)
Questo file si chiama unità di traduzione

Dichiarazione (del nome) VS Definizione della variabile

cout è bufferizzato cerr no (deve sempre essere flushato subito)

*/