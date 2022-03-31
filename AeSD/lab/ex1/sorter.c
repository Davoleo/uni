#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "../bench.h"
//#include "../cmd.h"
//#include "../utils.h"
//#include "../bench.h"

/**
 * Compilation:
 * \code gcc -Wall -Wextra sorter.c -o sort
 * 
 * Execution:
 * - Windows: .\sort.exe -a=<int>
 * - UNIX: ./sort -a=<int>
 *
 * algorithm choices (-a flag) [default is 0]:
 * 0: composite algorithm [insertion|counting|mergesort]
 *  * 	Space-wise it's VERY inefficient as it allocates:
 * 		2 extra arrays of size n  [heap] (lowvalues and highvalues)
 * 		1 extra array of size 400 (LOW_HIGH_BOUND) [stack] (stores counting_sort increments)
 * 		1 extra array of size 20  [stack] (stores eventual negative values)
 * 		2 extra arrays of size n  [heap] (auxiliary for merge sort)
 * 1: composite algorithm [insertion|counting|quicksort]
 * 	*	Space-wise it's quite inefficient as it allocates:
 * 		2 extra arrays of size n  [heap] (lowvalues and highvalues)
 * 		1 extra array of size 400 (LOW_HIGH_BOUND) [stack] (stores counting_sort increments)
 * 		1 extra array of size 20  [stack] (stores eventual negative values)
 * 2: composite algorithm [insertion|counting|shellsort]
 * 	*	2 extra arrays of size n  [heap] (lowvalues and highvalues)
 * 		1 extra array of size 400 (LOW_HIGH_BOUND) [stack] (stores counting_sort increments)
 * 		1 extra array of size 20  [stack] (stores eventual negative values)
 * 3: shell sort on the whole array
 * 		simple algorithm that with decent performance
 * 4: quick sort on the whole array
 * 		original algorithm in the given file
 * 
 * \author Leonardo Davoli 
 * Special Thanks to Thomas Zambelli for the help in debugging a Segmentation Fault issue
 **/

//If running with this definition and -v it is recommended to redirect program output to a file (it logs a lot)
//#define VERBOSE_ALGORITHMS

/// Changing this constants defines how the algorithm partitions A in lowvals and highvals
/// Increasing this decreases the average number of read operations needed but also has diminishing returns 
/// 	(so increasing it over this value makes small improvements)
/// Decreasing this increases the average number of read operations but also decreases the size of the increments array
#define LOW_HIGH_BOUND 400

/// set by the -a flag when launching the program (change here to edit the default value)
int algorithm = 0;

/// Global read operations counter
int ct_read = 0;

int max_dim = 0;
int ntests = 107;
int details = 0;

int n = 0; /// dimensione dell'array

void print_array(int* arr, int dim)
{
    for (int j = 0; j < dim; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* A, int p, int r)
{

    /// copia valori delle due meta p..q e q+1..r
    ct_read++;
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        ct_read++;
        if (A[j] <= x) {
            i++;
            ct_read++;
            ct_read++;
            swap(A + i, A + j);
        }
    }
    ct_read++;
    ct_read++;
    swap(A + i + 1, A + r);

    return i + 1;
}

void quick_sort(int* A, int p, int r)
{
    /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}


void merge(int *A, int p, int q, int r, int *L, int *R)
{

	/// copia valori delle due meta p..q e q+1..r
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < q - p + 1; i++) {
		L[i] = A[p + i];
		ct_read++;
	}
	L[i] = 1000000; /// un numero grande

	for (i = 0; i < r - q; i++) {
		R[i] = A[q + 1 + i];
		ct_read++;
	}
	R[i] = 1000000; /// un numero grande

	//// dettagli
	if (details)
	{
		printf("Array L (%d .. %d): ", p, q);
		print_array(L, q - p + 1);
		printf("Array R (%d .. %d): ", q + 1, r);
		print_array(R, r - q);
	}

	i = 0; /// usato per gestire array L
	j = 0; /// usato per gestire array R

	for (k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
		ct_read += 3;
	}
}

void merge_sort(int *arr, int left_id, int right_id, int *left, int *right)
{
	/// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
	if (right_id < left_id)
	{
		int mid_id = (left_id + right_id) / 2;
		merge_sort(arr, left_id, mid_id, left, right);
		merge_sort(arr, mid_id + 1, right_id, left, right);
		merge(arr, left_id, mid_id, right_id, left, right);
		if (details)
			print_array(arr, n);
	}
}

void shellsort(int arr[], int num)
{
    for (int i = num / 2; i > 0; i = i / 2) {
        for (int j = i; j < num; ++j) {
            for (int k = j - i; k >= 0; k = k - i) {
                ++ct_read;
                ++ct_read;
                if (arr[k + i] >= arr[k])
                    break;
                else {
                    ++ct_read;
                    ++ct_read;
                    swap(arr + k, arr + k + i);
                }
            }
        }
    }
}

/**
 * \brief sorts arr using an insertion algorithm approach
 */
void insertion_sort(int* arr, int length)
{
    for (int i = 1; i < length; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            ct_read += 2;
            if (arr[j] > arr[j + 1]) {
                ct_read += 2;
                swap(arr + j, arr + j + 1);
            } else {
                break;
            }
        }

		#ifdef VERBOSE_ALGORITHMS
        /// prints algorithm steps
        if (details) {
            printf("passo %d:\n", i);
            for (int j = 0; j < length; ++j) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
		#endif
    }
}

void counting_sort(int* A, int* B, int* C, int n, int k)
{
    /// A: array in input 0..n-1
    /// B: array in output 0..n-1
    /// C: array per conteggi 0..k
    /// n: elementi da ordinare
    /// k: valore massimo contenuto in A

    for (int i = 0; i <= k; ++i) {
        C[i] = 0;
    }

    for (int j = 0; j < n; ++j) {
		assert(A[j] <= k);

        C[A[j]]++;
        ct_read += 2;
    }

	#ifdef VERBOSE_ALGORITHMS
    if (details) {
        printf("array conteggi\n");
        print_array(C, k + 1);
    }
	#endif

    for (int i = 1; i <= k; ++i) { /// C[i] contiene il numero di elementi <= i
        C[i] += C[i - 1];
        ct_read += 2;
    }

	#ifdef VERBOSE_ALGORITHMS
    if (details) {
        printf("array con conteggi accumulati\n");
        print_array(C, k + 1);
    }
	#endif

    for (int j = n - 1; j >= 0; --j) { /// per ogni elemento originale in A ->
        /// mi chiedo nel conteggio C quanti sono gli elementi minori o uguali:
        /// questo corrisponde alla posizione dell'elemento in B
		
		#ifdef VERBOSE_ALGORITHMS
        if (details)
            printf("A[%d]=%d, C[A[%d]]=%d --> scrivo B[%d-1]=%d\n", j, A[j], j, C[A[j]], C[A[j]], A[j]);
		#endif

        B[C[A[j]] - 1] = A[j];
        ct_read += 3;
        C[A[j]] = C[A[j]] - 1;
        ct_read += 2;
    }

	#ifdef VERBOSE_ALGORITHMS
    if (details) {
        printf("array con conteggi accumulati dopo il decremento\n");
        print_array(C, k + 1);
    }
	#endif
}

int parse_cmd(int argc, char** argv)
{

    /// parsing argomento
    max_dim = 743;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i][1] == 't')
                ntests = atoi(argv[i] + 3);
            if (argv[i][1] == 'v')
                details = 1;
            if (argv[i][1] == 'a') {
                algorithm = atoi(argv[i] + 3);
            }
        }
    }

    return 0;
}

int main(int argc, char** argv)
{

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    int* A = malloc(sizeof(int) * max_dim);

    n = max_dim;

    FILE* input_data = fopen("data.txt", "r");

    int read_min = -1;
    int read_max = -1;
    long read_avg = 0;

	int* lowvals = malloc(sizeof(int) * max_dim);
	int* highvals = malloc(sizeof(int) * (max_dim));

	int* merge_left = NULL;
	int* merge_right = NULL;

	if (algorithm == 0) {
		merge_left = malloc(sizeof(int) * (max_dim));
		merge_right = malloc(sizeof(int) * (max_dim));
	}

    //// lancio ntests volte per coprire diversi casi di input random
    for (int test = 0; test < ntests; ++test) {

        /// array initialization
        for (int i = 0; i < n; ++i) {
            fscanf(input_data, "%d,", &A[i]);
        }

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_read = 0;

        if (algorithm >= 0 && algorithm < 3) {
            int lowvals_size = 0;
            int highvals_size = 0;
			//Based on data analysis
            int negvals[20];
            int negvals_size = 0;

			/// Partitions A in 3 sections
            for (int it = 0; it < n; ++it) {
                ++ct_read;
                int val = A[it];
                if (val > LOW_HIGH_BOUND) {
                    // Put value in highvalues array and its address in the original array
                    highvals[highvals_size] = val;
                    ++highvals_size;
                } else if (val >= 0) {
                    // Put value in lowvalues array and its address in the original array offset by 1000
                    lowvals[lowvals_size] = val;
                    ++lowvals_size;
                } else {
                    negvals[negvals_size] = val;
                    ++negvals_size;
                    assert(negvals_size <= 50);
                }
            }

			#ifdef VERBOSE_ALGORITHMS
			if (details) {
				puts("negvals");
				print_array(negvals, negvals_size);
				puts("lowvals");
				print_array(lowvals, lowvals_size);
				puts("highvals");
				print_array(highvals, highvals_size);
			}
			#endif

            assert(highvals_size > 0);
            assert(lowvals_size > 0);

			//Sort Negative Values and load them back into A
			insertion_sort(negvals, negvals_size);
			int re_size = 0;
            int iter = 0;
            while (iter < negvals_size) {
                ++ct_read;
                A[re_size++] = negvals[iter];
                ++iter;
            }
            
			/// Create increments array to be used as input in counting_sort (we know lowvals have a max value of \ref LOW_HIGH_BOUND)
			int increments[LOW_HIGH_BOUND+1];
			//Passing a pointer to the first cell after negative values as output for the counting sort
            counting_sort(lowvals, A + negvals_size, increments, lowvals_size, LOW_HIGH_BOUND);
			//No need to load lowvals back in A since counting_sort already takes care of that
			re_size += lowvals_size;

			//Sort high values with
			if (algorithm == 0) {
				merge_sort(highvals, 0, highvals_size, merge_left, merge_right);
			}
			else if (algorithm == 1) {
				shellsort(highvals, highvals_size);
			}
			else if (algorithm == 2) {
				quick_sort(highvals, 0, highvals_size);
			}
			iter = 0;
            while (iter < highvals_size) {
                ++ct_read;
                A[re_size++] = highvals[iter];
                ++iter;
            }

			#ifdef VERBOSE_ALGORITHMS
			if (details) {
				puts("negvals post-processing:");
				print_array(negvals, negvals_size);
				puts("lowvals post-processing:");
				print_array(lowvals, lowvals_size);
				puts("highvals post-processing:");
				print_array(highvals, highvals_size);
			}
			#endif
			
        } else if (algorithm == 3) {
            shellsort(A, n);
        }
		else if (algorithm == 4) {
			quick_sort(A, 0, n-1);
		}

        if (details) {
            printf("Output:\n");
            print_array(A, n);
        }

        /// statistics
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);
    }

    printf("%d,%d,%.1f,%d\n",
        ntests,
        read_min, ((double) read_avg) / ntests, read_max);

	free(highvals);
	free(lowvals);
    free(A);

    return 0;
}