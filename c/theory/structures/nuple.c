
#include "nuple.h"

#include <stdio.h>
#include <stdlib.h>

nuple create_nuple(int length) {
    nuple n;
    if (length <= 0) {
        n.data = NULL;
        n.length = 0;
        return n;
    }

    n.data = (int*)malloc(length * sizeof(int));

    if (n.data == NULL)
        n.length = 0;
    else
        n.length = length;

    return n;
}

bool delete_nuple(nuple nup) {
    if (nup.data == NULL)
        return false;

    free(nup.data);
    nup.length = 0;
    nup.data = NULL;
    return true;
}

nuple copy_nuple(nuple old) {
    if (old.data == NULL)
        return create_nuple(0);

    if (old.length < 1)
        return create_nuple(0);

    nuple res = create_nuple(old.length);

    for (int i = 0; i < old.length; i++) {
        res.data[i] = old.data[i];
    }

    return res;
}

bool fill_nuple(nuple nup, int data[], int length) {
    if (data == NULL || nup.data == NULL)
        return false;

    if (nup.length < 1)
        return false;

    if (nup.length > length)
        nup.length = length;

    for (int i = 0; i < nup.length; i++) {
        nup.data[i] = data[i];
    }

    return true;
}

bool print_nuple(nuple nup) {
    if (nup.length < 1 || nup.data == NULL)
        return false;

    for (int i = 0; i < nup.length; i++) {
        printf("%d ", nup.data[i]);
    }
    printf("\n");

    return true;
}

int search_nuple(nuple nup, int key) {
    int length = nup.length;

    if (length < 1)
        return VALUE_NOT_FOUND;

    if (nup.data == NULL)
        return VALUE_NOT_FOUND;

    for (int i = 0; i < length; i++) {
        if (nup.data[i] = key)
            return i;
    }

    return VALUE_NOT_FOUND;
}

int search_sorted_nuple(nuple nup, int key) {
    int length = nup.length;

    if (length < 1 || nup.data == NULL)
        return VALUE_NOT_FOUND;

    int* arr = nup.data;
    int low = 0;
    int high = length - 1;

    while (high - low > 1) {
        int mid = (high + low) / 2;

        if (arr[mid] == key)
            return mid;
        
        if (arr[mid] > key)
            high = mid;
        else
            low = mid;
    }
    
    if (arr[low] == key)
        return low;

    if (arr[high] == key)
        return high;

    return VALUE_NOT_FOUND;
}

bool insertion_sort(nuple nup) {

    if (nup.length < 1 || nup.data == NULL)
        return false;

    if (nup.length == 1)
        return true;

    int* arr = nup.data;
    for (int i = 1; i < nup.length; ++i) {
        int j;
        int temp = arr[i];

        for (j = i - 1; j >= 0 && arr[j] > temp; --j)
            arr[j + 1] = arr[j];
        
        if (j != i - 1)
            arr[j + 1] = temp;
    }

    return true;
}

bool selection_sort(nuple nup) {

    if (nup.length < 1 || nup.data)
        return false;

    if (nup.length == 1)
        return true;

    int* arr = nup.data;
    for (int i = 0; i < nup.length - 1; ++i) {
        int min = arr[i];
        int min_index = i;
        
        for (int j = i + 1; j < nup.length; ++j)
            if (arr[j] < min) {
                min = arr[j];
                min_index = j;
            }
        
        if (min_index != i) {
            arr[min_index] = arr[i];

            arr[i] = min;
        }
    }

    return true;
}