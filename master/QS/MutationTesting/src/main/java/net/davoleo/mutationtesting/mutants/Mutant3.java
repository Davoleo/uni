package net.davoleo.mutationtesting.mutants;

import net.davoleo.mutationtesting.IQuickSort;

public class Mutant3 implements IQuickSort {

    static int partition(int[] arr, int low, int high) {
        int pivot = arr[(low + high) / 2];
        int i = low;  //removed - 1

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }

        swap(arr, i + 1, high);
        return i + 1;
    }

    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public void quickSort(int[] arr, int low, int high) {
        if (low < high) {

            int pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}