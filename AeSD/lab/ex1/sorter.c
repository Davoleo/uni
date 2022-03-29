#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

//#include "../bench.h"
//#include "../cmd.h"
//#include "../utils.h"
//#include "../bench.h"

/**
 * Windows: .\sort.exe -m=743 -t=107
 * UNIX: ./sort -m=743 -t=107
 **/

int ct_swap = 0;
int ct_cmp = 0;
int ct_read = 0;

int max_dim = 0;
int ntests = 107;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int* A, int dim)
{
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    /// aggiorno contatore globale di swap
    ct_swap++;
}

int partition(int* A, int p, int r)
{

    /// copia valori delle due meta p..q e q+1..r
    ct_read++;
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        ct_cmp++;
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

void shellsort(int arr[], int num)
{
	for (int i = num/2; i > 0; i = i/2)
	{
		for (int j = i; j < num; ++j)
		{
			for(int k = j - i; k >= 0; k = k - i)
			{
				++ct_read;
				++ct_read;
				if (arr[k+i] >= arr[k])
					break;
				else
				{
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
void insertion_sort(int* arr, int length) {
	for (int i=1; i < length; ++i) {
		for (int j=i-1; j>=0; --j) {
			ct_read += 2;
			if (arr[j]>arr[j+1]) {
				ct_read += 2;
				swap(arr + j, arr + j + 1);
			} else {
				break;
			}
		}

		/// prints algorithm steps
		if (details) {
			printf("passo %d:\n",i);
			for (int j=0; j < length; ++j) {
				printf("%d ",arr[j]);
			}
			printf("\n");
		}
	}
}

void counting_sort(int *A, int *B, int *C, int n, int k)
{
  /// A: array in input 0..n-1
  /// B: array in output 0..n-1
  /// C: array per conteggi 0..k
  /// n: elementi da ordinare
  /// k: valore massimo contenuto in A

  for (int i = 0; i <= k; ++i)
  { /// reset array conteggi
    C[i] = 0;
    //ct_opw++;
  }

  for (int j = 0; j < n; ++j)
  { /// conteggio istogramma
    C[A[j]]++;
    ct_read += 2;
  }

  if (details)
  {
    printf("array conteggi\n");
    print_array(C, k + 1);
  }
  for (int i = 1; i <= k; ++i)
  { /// C[i] contiene il numero di elementi <= i
    C[i] += C[i - 1];
    ct_read += 2;
  }

  if (details)
  {
    printf("array con conteggi accumulati\n");
    print_array(C, k + 1);
  }

  for (int j = n - 1; j >= 0; --j)
  { /// per ogni elemento originale in A ->
    /// mi chiedo nel conteggio C quanti sono gli elementi minori o uguali:
    /// questo corrisponde alla posizione dell'elemento in B
    if (details)
      printf("A[%d]=%d, C[A[%d]]=%d --> scrivo B[%d-1]=%d\n", j, A[j], j, C[A[j]], C[A[j]], A[j]);

    B[C[A[j]] - 1] = A[j];
    ct_read += 3;
    C[A[j]] = C[A[j]] - 1;
    ct_read += 2;
  }

  if (details)
  {
    printf("array con conteggi accumulati dopo il decremento\n");
    print_array(C, k + 1);
  }
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
            if (argv[i][1] == 'g') {
                graph = 1;
                ntests = 1;
            }
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
	const int LOWS_OFFSET = 1000;
	const int NEGS_OFFSET = 2000;

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    int* A = malloc(sizeof(int) * max_dim);

    n = max_dim;

    FILE* input_data = fopen("data.txt", "r");

    int read_min = -1;
    int read_max = -1;
    long read_avg = 0;

    //// lancio ntests volte per coprire diversi casi di input random
    for (int test = 0; test < ntests; ++test) {

        /// inizializzazione array: numeri random con range dimensione array
        for (int i = 0; i < n; ++i) {
            char comma;
            fscanf(input_data, "%d,", &A[i]);
        }

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_swap = 0;
        ct_cmp = 0;
        ct_read = 0;

		int* lowvals = malloc(sizeof(int) * max_dim);
		int lowvals_size = 0;
		int* highvals = malloc(sizeof(int) * (max_dim));
		int highvals_size = 0;
		int negvals[50];
		int negvals_size = 0;

		for (int it = 0; it < n; ++it) {
			++ct_read;
			int val = A[it];
			if (val > 131) {
				//Put value in highvalues array and its address in the original array
				highvals[highvals_size] = val;
				//A[it] = highvals_size;
				++highvals_size;
			}
			else if (val >= 0) {
				//Put value in lowvalues array and its address in the original array offset by 1000
				lowvals[lowvals_size] = val;
				//A[it] = LOWS_OFFSET + lowvals_size;
				++lowvals_size;
			}
			else {
				negvals[negvals_size] = val;
				//A[it] = NEGS_OFFSET + negvals_size;
				++negvals_size;
				assert(negvals_size <= 50);
			}
		}

        /// algoritmo di sorting
        //quick_sort(A, 0, n - 1);
		//insertion_sort(A, n);
		
		assert(highvals_size > 0);
		assert(lowvals_size > 0);

		int increments[132];
		int* lowvals_copy = malloc(max_dim * sizeof(int));
		memcpy(lowvals_copy, lowvals, sizeof(int));
		ct_read += lowvals_size;
		//Create increments array and lowvals copy to be used as input in counting_sort

		counting_sort(lowvals_copy, lowvals, increments, lowvals_size, 132);
		free(lowvals_copy);
		puts("Sono arrivato qui quante volte?");

		shellsort(highvals, highvals_size);
		insertion_sort(negvals, negvals_size);

		int re_size = 0;
		int iter = 0;
		while (iter < negvals_size) {
			++ct_read;
			A[re_size++] = negvals[iter];
			++iter;
		}
		iter = 0;
		while(iter < lowvals_size) {
			++ct_read;
			A[re_size++] = lowvals[iter];
			++iter;
		}
		while(iter < highvals_size) {
			++ct_read;
			A[re_size++] = highvals[iter];
			++iter;
		}

        if (details) {
            printf("Output:\n");
            print_array(A, n);
        }

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);

		free(highvals);
		free(lowvals);
    }

    printf("%d,%d,%.1f,%d\n",
        ntests,
        read_min, (0.0 + read_avg) / ntests, read_max);

    free(A);

    return 0;
}