#include <stdlib.h>
#include <stdio.h>
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

//L'insertion sort può essere usato come ordinamento online man mano che i dati arrivano
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

bool selection_sort(int array[], int n) {
    if (n <= 0)
        return false;
    if (n < 2)
        return true;

    for (int i = 0; i < n - 1; i++) {
        int min = array[i];
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if (array[j] < min) {
                min = array[j];
                min_index = j;
            }

            if (min_index != i) {
                array[min_index] = array[i];
                array[i] = min;
            }
        }
    }

    return true;
}

bool bubble_sort(int array[], int n) {
    if (array == NULL || n <= 0)
        return false;

    if (n == 1)
        return true;

    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            if (array[j] < array[j - 1]) {
                int temp = array[j - 1];

                array[j - 1] = array[j];
                array[j] = temp;
            }
        }
    }
    return true;
}


void merge(int array[], int left, int mid, int right) {
    int temp[right - left + 1];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (array[i] < array[j]) {
            temp[k] = array[i];
            i++;
        }
        else {
            temp[k] = array[j];
            j++;
        }

        k++;
    }

    while (i <= mid) {
        temp[k] = array[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = array[j];
        j++;
        k++;
    }

    for (k = left; k <= right; k++) {
        array[k] = temp[k - left];
    }
}

bool merge_sort(int array[], int left, int right) {
    if (left > right || left < 0 || right < 0)
        return false;

    if (left == right) 
        return true;

    int mid = (left + right) / 2;

    merge_sort(array, left, mid);

    merge_sort(array, mid + 1, right);

    merge(array, left, mid, right);

    return true;
}

bool quick_sort(int array[], int left, int right) {

    //Mancano le precondizioni perché non c'è stato su

    int pivot = array[(left + right) / 2];
    //Builds the right zone and starts from the left because the zone could be the whole array
    int i = left;
    //Builds the left zone and starts from the right because the zone could be the whole array
    int j = right;

    while(i <= j) {
        while (array[i] < pivot)
            i++;
        
        while(array[j] > pivot)
            j--;

        if (i <= j) {
            if (i != j) {
                int temp = array[i];

                array[i] = array[j];

                array[j] = temp;
            }

            i++;
            j--;
        }
    }

    if (left < j) {
        quick_sort(array, left, j);
    }

    if (i < right) {
        quick_sort(array, i, right);
    }

    return true;
}

void heap(int array[], int left, int right) {
    if (array == NULL)
        return;
    
    if (left > right || left < 0 || right < 0)
        return;

    int x = array[left];
    int i = left;
    int j = 2 * left;

    while (j <= right) {
        if (j != right && array[j + 1] > array[j])
            j++;

        if (x >= array[j])
            break;
        else {
            array[i] = array[j];
            i = j; 
            j = 2 * i;
        }
    }

    if (i != left)
        array[i] = x;
}

bool heap_sort(int array[], int n) {
    if (array == NULL)
        return false;
    if (n == 1)
        return true;

    for (int left = n / 2; left >= 0; --left)
        heap(array, left, n - 1);
    
    for (int right = n - 1; right > 0; --right) {
        int temp = array[0];

        array[0] = array[right];
        array[right] = temp;

        heap(array, 0, right - 1);
    }

    return true;
}

int main() {
    int array[] = {-5, -1, 0, 4, 5, 10, 11, 13, 20, 55, 130, 200};

    //Ricerca Lineare Iterativa
    int index1 = linear_search(55, array, 10);

    //if (index != VALUE_NOT_FOUND)
    //    printf("Il valore e' presente nell'array in posizione %d\n", index);
    //else
    //    printf("Il valore non è presente nell'array");

    //Ricerca Dicotomica Iterativa
    int index2 = dichotomic_search(55, array, 10);

    //if (index != VALUE_NOT_FOUND)
    //    printf("Il valore e' presente nell'array in posizione %d\n", index);
    //else
    //    printf("Il valore non è presente nell'array");


    int array1[] = {4, 1, 5, 6, 1, 8, 20, 3, 14, 24, 15, 25};
    const int length = 12;
    
    bool sorted = merge_sort(array1, 0, length - 1);

    for(int i=0; i < length; i++)
    {
        printf("%d ", array1[i]);        
    }


    return EXIT_SUCCESS;
}