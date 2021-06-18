#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void stampa(int sequenza[], int lunghezza) {
    if (sequenza == NULL)
        return;

    if (lunghezza < 0)
        return;

    for (int i = 0; i < lunghezza; ++i)
        printf("%d\n", sequenza[i]);
}

int cerca_posizione(int valore, int sequenza[], int lunghezza) {
    if (sequenza == NULL)
        return false;
    
    if (lunghezza < 0)
        return false;

    for (int i = 0; i < lunghezza; ++i)
        if (sequenza[i] > valore)
            return i;

    return lunghezza;
}

bool inserisci(int valore, int sequenza[], int lunghezza) {
    if (sequenza == NULL)
        return false;
    
    if (lunghezza < 0)
        return false;

    int posizione = cerca_posizione(valore, sequenza, lunghezza);

    for (int i = lunghezza; i > posizione; --i)
        sequenza[i] = sequenza[i - 1];

    sequenza[posizione] = valore;

    return true;
}

bool elabora(void) {
    int lunghezza;

    int l = scanf("%d", &lunghezza);

    if (l != 1 || lunghezza <= 0) {
        printf("Lunghezza non valida\n");

        return false;
    }

    int sequenza[lunghezza];

    for(int i = 0; i < lunghezza; ++i) {
        int valore;

        l = scanf("%d", &valore);

        if (l != 1) {
            printf("Valore non valido\n");

            return false;
        }

        bool ok = inserisci(valore, sequenza, i);

        if (!ok) {
            printf("Impossibile inserire il valore\n");

            return false;
        }
    }

    stampa(sequenza, lunghezza);

    return true;
}

int main(void) {
    if (!elabora())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}