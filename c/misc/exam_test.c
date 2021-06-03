#include <stdlib.h>
#include <stdio.h>

void doWork(int vec[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i+1; j < length; j++) {
            if (vec[j] > vec[i]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

int main() {

    int length;

    do {
        scanf("%d", &length);
    }
    while (length <= 0);

    int array[length];

    for (int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
    }

    //La funzione ordina l'array in maniera decrescente 
    //Ha una complessità di O(n^2) poiché per n tendente ad un numero molto alto è come se l'array sia looppato una volta per ogni suo elemento
    //e ciò porta ad un tempo totale di esecuzione asintotico pari al quadrato della lunghezza dell'array a meno di costanti.
    doWork(array, length);

    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }

    return EXIT_SUCCESS;
}