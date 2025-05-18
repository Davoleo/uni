package net.davoleo.mutationtesting;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;

public abstract class AbstractQuickSortTest {

    private IQuickSort instance;

    protected abstract IQuickSort createInstance();

    @BeforeEach
    public void setUp() {
        instance = createInstance();
    }

    @Test
    void testCaseSortingSingleNum() {
        int[] arr = {5};
        int[] expected = {5};
        instance.quickSort(arr, 0, arr.length - 1);
        assertArrayEquals(expected, arr,
                "expected: " + Arrays.toString(expected) + " | actual: " + Arrays.toString(arr)
        );
    }

    @Test
    void testCaseAlreadySorted() {
        int[] arr = {1, 2, 3, 4, 5};
        int[] expected = {1, 2, 3, 4, 5};
        instance.quickSort(arr, 0, arr.length - 1);
        assertArrayEquals(expected, arr,
                "expected: " + Arrays.toString(expected) + " | actual: " + Arrays.toString(arr)
        );
    }

    @Test
    void testCaseSortingReverse() {
        int[] arr = {5, 4, 3, 2, 1};
        int[] expected = {1, 2, 3, 4, 5};
        instance.quickSort(arr, 0, arr.length - 1);
        assertArrayEquals(expected, arr,
                "expected: " + Arrays.toString(expected) + " | actual: " + Arrays.toString(arr)
        );
    }

    @Test
    void testCaseSortingWithDupes() {
        int[] arr = {3, 1, 2, 3, 1, 2};
        int[] expected = {1, 1, 2, 2, 3, 3};
        instance.quickSort(arr, 0, arr.length - 1);
        assertArrayEquals(expected, arr,
                "expected: " + Arrays.toString(expected) + " | actual: " + Arrays.toString(arr)
        );
    }

    @Test
    void testCaseSorting() {
        int[] arr = {3, 6, 1, 5, 9, 2};
        int[] expected = {1, 2, 3, 5, 6, 9};
        instance.quickSort(arr, 0, arr.length - 1);
        assertArrayEquals(expected, arr,
                "expected: " + Arrays.toString(expected) + " | actual: " + Arrays.toString(arr)
        );
    }

}
