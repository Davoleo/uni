#include <stdlib.h>
#include <stdbool.h>

static const int VALUE_NOT_FOUND = -1;

int linear_search(int key, int array[], int n) {
    if (array == NULL)
        return VALUE_NOT_FOUND;
    
    if (n <= 0)
        return VALUE_NOT_FOUND;

    for (int i = 0; i < n; i++) {
        if (array[i] == key)
            return i;
    }

    return VALUE_NOT_FOUND;
}

int dichotomic_search(int key, int array[], int n) {
    if (array == NULL)
        return VALUE_NOT_FOUND;
    
    if (n <= 0)
        return VALUE_NOT_FOUND;

    int low = 0;
    int high = n - 1;

    while (high - low > 1) {
        int mid = (low + high) / 2;

        if (array[mid] == key)
            return mid;
        
        if (array[mid] > key)
            high = mid;
        else
            low = mid;
    }

    if (array[low] == key)
        return low;
    
    if (array[high] == key)
        return high;

    return VALUE_NOT_FOUND;
}

bool insertion_sort(int array[], int n) {
    if (array == NULL)
        return false;
    
    if (n < 1)
        return false;

    if (n == 1)
        return true;

    for (int i = 0; i < n; i++) {
        int j;
        int elem = array[i];

        //Ricerca in tutti gli indici j positivi prima di i, e se l'elemento in j è maggiore della chiave lo si sposta in avanti
        //per fare spazio per elem nel posto giusto
        for (j = i - 1; j >= 0 && array[j] > elem; --j)
            array[j + 1] = array[j];

        //Elem va a finire nel posto disponibile che si è venuto a creare
        if (j != i - 1)
            array[j + 1] = elem;
    }

    return true;
}

int main() {
    int array[] = {-5, -1, 0, 4, 5, 10, 11, 13, 20, 55, 130, 200};

    //Ricerca Lineare Iterativa
    int index = linear_search(55, array, 10);

    if (index != VALUE_NOT_FOUND)
        printf("Il valore e' presente nell'array in posizione %d\n", index);
    else
        printf("Il valore non è presente nell'array");

    //Ricerca Dicotomica Iterativa
    int index = dichotomic_search(55, array, 10);

    if (index != VALUE_NOT_FOUND)
        printf("Il valore e' presente nell'array in posizione %d\n", index);
    else
        printf("Il valore non è presente nell'array");

    return EXIT_SUCCESS;
}