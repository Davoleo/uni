#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./bench.c"


// compilazione: gcc insertion_sort.c -o insertion_sort
//
// Obiettivo:

// Lanciare con
// > ./insertion_sort 10
// > ./insertion_sort 100

// > time ./insertion_sort 1000

int do_bench = 0;
int details = 0;

/**
 * \brief Swaps two integer values given their pointers to variables
 */
void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
	swap_ct++;
}

/**
 * \brief sorts arr using an insertion algorithm approach
 */
void insertion_sort(int* arr, int length) {
	for (int i=1; i < length; i++) {
		for (int j=i-1; j>=0; j--) {
			if (arr[j]>arr[j+1]) {
				compare_ct++;
				swap (&arr[j],&arr[j+1]);
			} else {
				break;
			}
		}

		/// prints algorithm steps
		if (details) {
			printf("passo %d:\n",i);
			for (int j=0; j < length; j++) {
				printf("%d ",arr[j]);
			}
			printf("\n");
		}
	}
}


int main(int argc, char** argv) {

	/// controllo argomenti
	if (argc < 2) {
		printf("Usage: %s dim-array [details=0/1] [benchmark=0/1]\n",argv[0]);
		return 1;
	}

	/// parsing argomento
	int length = atoi(argv[1]);
	if (argc >= 3)
		details = atoi(argv[2]);

	if (argc == 4) 
		do_bench = atoi(argv[3]);
		

	// init random
	srand((unsigned) time(NULL));

	/// allocazione array
	int* arr = malloc(length * sizeof(int));

	/// inizializzazione array
	for (int i=0; i<length; i++) {
		arr[i]=length-i;
	}

	if (do_bench) {
		benchmark(arr, &insertion_sort);
		free(arr);
		return 0;
	}

	/// input
	if (details) {
		printf("L'input e':\n");
		for (int i=0; i<length; i++) {
			printf("%d ",arr[i]);
		}
		printf("\n");
	}

	/// sort
	insertion_sort(arr, length);

	/// output
	if (details) {
		printf("L'output e':\n");
		for (int i=0; i<length; i++) {
			printf("%d ",arr[i]);
		}
		printf("\n");
	}

	printf("Totale swap = %d\n", swap_ct);

	free(arr);
	return 0;
}
