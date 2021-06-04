#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c) {
    if (a < c) {
        return a < b ? a : b;
    }
    else {
        return c < b ? c : b;
    }
}

int min_occurrences(int array[], int length) {
    int occ0;
    int occ1;
    int occ2;

    for (int i = 0; i < length; i++) {
        if (i == 0)
            occ0++;
        else if (i == 1)
            occ1++;
        else
            occ2++;
    }

    return min(occ0, occ1, occ2);
}

void reverse_sort_special(int array[], int length) {
    int min_occs = min_occurrences(array, length);

    int resultArray[length];

    int count = 0;

    for (int key = 2; key >= 0; key--) {
        for (int i = 0; i < length; i++) {
            if (array[i] == key) {
                resultArray[count] = array[i];
                count++;
            }
        }
    }

    for (int i = 0; i < length; i++) {
        array[i] = resultArray[i];
    }
}

int main() {

    int length;
    printf("Lunghezza Array: ");
    if (scanf("%d", &length) != 1) {
        printf("Input non valido!\n");
        return EXIT_FAILURE;
    }

    int array[] = {0, 1, 2, 0, 1, 2, 2, 0, 1};

    reverse_sort_special(array, 9);

    for (int i = 0; i < 9; i++) {
        printf("%d ", array[i]);
    }


    for (int i = 0; i < length; i++) {
        int value;
        scanf("%d", &value);

        if (value > 2 || value < 0) {
            printf("Valore non valido, ripetere l'input.");
            i--;
            continue;
        }
        printf("Elemento %d:", i);
    }

    return EXIT_SUCCESS;
}