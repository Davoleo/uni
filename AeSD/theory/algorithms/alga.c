#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
- Algoritth tests
* Linear Search
* Dichotomic Search
* Insertion Sort
* Selection Sort
* Bubble Sort
* Merge Sort
* Quick Sort
* Heap Sort
*/

#define VALUE_NOT_FOUND 404

/* Linear Search */
int linear_search(int array[], int length, int value) {
    if (array == NULL)
        return VALUE_NOT_FOUND;

    if(length == 0)
        return VALUE_NOT_FOUND;

    for(int i=0; i < length; i++)
    {
        if(array[i] == value)
            return i;
    }

    return VALUE_NOT_FOUND;
}

/* Dichotomic Search */
int dichotomic_search(int array[], int begin, int end, int value) {
    if(array == NULL)
        return VALUE_NOT_FOUND;
    
    if(end <= begin)
        return VALUE_NOT_FOUND;

    int mid = end / 2;

    if(value == array[mid])
        return mid;
    else if(value > array[mid])
        return dichotomic_search(array, mid, end, value);
    else if(value < array[mid])
        return dichotomic_search(array, begin, mid, value);

    return VALUE_NOT_FOUND;
}

bool insertion_sort(int array[], int length) {
    if(array == NULL)
        return VALUE_NOT_FOUND;

    if(length <= 0)
        return VALUE_NOT_FOUND;

    for (int i = 1; i < length; i++) {

        if (array[i] < array[i-1]) {
            
            int temp = array[i]; 
            int index = i;       

            for (int j = i-1; j >= 0; j--) {
                if (temp < array[j]) {
                    array[j + 1] = array[j];
                    index--;
                }
                else {
                    break;
                }
            }

            array[index] = temp;
        }
    }

    return true;

}

/* Selection sort */
bool selection_sort(int array[], int length) {
    if (array == NULL)
        return false;

    if (length <= 0)
        return false;
    
    if (length == 1)
        return true;

    for (int i = 0; i < length; i++) {

        int min = array[i];
        int min_index = i;

        for (int j = i + 1; j < length; j++) {
            if (min > array[j]) {
                min = array[j];
                min_index = j;
            }
        }

        array[min_index] = array[i];
        array[i] = min;
    }

    return true;
}

/* Bubble sort */
bool bubble_sort(int array[], int length)
{
    for(int i=0; i < length; i++)
    {
        for(int j = 0; j < length - 1; j++)
        {
            if(array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    return true;
}

void merge(int array[], int left, int mid, int right) {

    //puts("\n-------------\nmerge: START");
    const int tempLength = right - left + 1;
    //printf("tempLength is %d\n", tempLength);

    //printf("\nArray: ");
    //for(int i=left; i <= right; i++)
    //    printf("%d ", array[i]);
    
    printf("\n");

    const int tempLeft = left;
    int temp[tempLength];
    int index = 0;
     
    //printf("left %d - mid %d - right %d", left, mid, right);
    while(left <= mid && right >= mid + 1)
    {
        if (array[right] < array[left]) {
            temp[index] = array[right];
            right--;
        }
        else {
            temp[index] = array[left];
            left++;
        }

        index++;
    
        //printf("\nTemp: ");
        //for(int i=0; i < index; i++)
        //    printf("%d ", temp[i]);
    }

    //puts("\nwhile 1");
    while (left <= mid) {
        temp[index] = array[left];
        left++;
        index++;
    }

    //printf("\nTemp: ");
    //for(int i=0; i < index; i++)
    //    printf("%d ", temp[i]);


    //puts("\nwhile 2");
    while(right >= mid + 1) {
        temp[index] = array[right];
        right--;
        index++;
    }

    //printf("\nTemp: ");
    //for(int i=0; i < index; i++)
        //printf("%d ", temp[i]);

    //printf("\ntempLeft: %d\n", tempLeft);

    //printf("Array: ");
    for(int i=0, j = tempLeft; i < tempLength; i++, j++) {
        array[j] = temp[i];
        //printf("%d ", array[j]);
    }
    //puts("\nmerge: END\n-------------");
}

//3 7 4 9 2 5 8
//3 7 4 9 
//3 7
//

//2 5 8
bool merge_sort(int array[], int top, int end) {

    if(array == NULL || end < top)
    {
        printf(" ERRORE: NULL o end minore di top");
        return false;
    }

    if(end == top)
        return true;

    int mid = (end - top) / 2;

    printf("\nBefore left split: ");
    for(int i=top; i < mid; i++)
        printf("%d ", array[i]);

    merge_sort(array, top, mid); // array = 7

    printf("\nBefore right split: ");
    for(int i=mid + 1; i < end; i++)
        printf("%d ", array[i]);

    merge_sort(array, mid + 1, end); // array = 4 9

    printf("\nBefore merge: ");
    for(int i=top; i < end; i++)
        printf("%d ", array[i]);

    merge(array, top, mid, end); // top = 1, mid = 2 end = 3

    printf("After merge: ");
    for(int i=top; i < end; i++)
        printf("%d ", array[i]);

    puts("SORT END\n----------\n");

    return true;
}

int main()
{
    int array[] = {4, 1, 5, 6, 1, 8, 20, 3, 14, 24, 15, 25};
    const int length = 12;
    
    bool sorted = merge_sort(array, 0, length - 1);
    
    if(sorted)
    {
        for(int i=0; i < length; i++)
            printf("%d ", array[i]);        
    }

    
    return EXIT_SUCCESS;
}