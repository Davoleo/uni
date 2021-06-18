#ifndef _ENNUPLE_H_
#define _ENNUPLE_H_
//^ Header guard (se l'header è già stato definito non viene ridefinito)

#include <stdbool.h>
#include <stdlib.h>

//ADT Ennupla:
//- Sequenza di valori dello stesso tipo
//- Lunghezza nota
//- Possibile accesso tramite indice
//- Possibile scrittura su indice
typedef struct {
    int* data;
    int length;
} nuple;

//Interfaccia del tipo astratto

//const controlla che la variabile sia costante a compile time
//static significa che il nome non viene inserito nel file oggetto (variabile visibile solo in questo file)
static const int VALUE_NOT_FOUND = -1;

//extern fa in modo che chi implementa si aspetta solo i nomi delle funzioni e non la loro implementazione
//dice al compilatore di non cercare nemmeno la definizione della funzione in quanto sarà in un altro file

extern nuple create_nuple(int length);
//rilascia le risorse
extern bool delete_nuple(nuple tup);

extern nuple copy_nuple(nuple tup);
extern bool fill_nuple(nuple tup, int data[], int length);

extern bool print_nuple(nuple nup);

extern int search_nuple(nuple nup, int k);
extern int search_sorted_nuple(nuple nup, int k);

extern int lis_nuple(nuple nup);

extern bool insertion_sort(nuple nup);
extern bool selection_sort(nuple nup);
//extern bool bubble_sort(nuple nup);
//extern bool merge_sort(nuple nup);
//extern bool quick_sort(nuple nup);
//extern bool heap_sort(nuple nup);

//Se le funzioni sono molto semplici è utile dichiararle inline in modo che la loro chiamata venga sostituita col corpo della funzione
//Però non forza il compilatore a metterla inline, glielo consiglia
//Per fare in modo che nel caso non vengano messe inline dal compilatore non generino problemi di nomi si dichiarano anche static
static inline bool set_nuple_elem(nuple nup, int pos, int value) {
    if (nup.data == NULL)
        return false;

    if (pos < 0 || pos >= nup.length)
        return false;

    int* arr = nup.data;
    arr[pos] = value;
    return true;
}

static inline bool get_nuple_elem(nuple nup, int pos, int* outValue) {
    if (nup.data == NULL)
        return false;

    if (pos < 0 || pos >= nup.length)
        return false;

    int* arr = nup.data;
    *outValue = arr[pos];
    return true;
}

#endif