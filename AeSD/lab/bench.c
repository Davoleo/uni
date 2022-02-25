#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


// compilazione: gcc insertion_sort_bench.c -o insertion_sort_bench 
//
// Obiettivo: creazione di un benchmark su 100 array di dimensioni diverse, con contenuto random. Ogni test ripetuto 1000 volte
// viene misurato il caso migliore, peggiore e medio in termini di swap e confronti

// Avvio con
// > ./insertion_sort_bench 100

// usare i risultati per plottare dei grafici ed osservare l'andamento rispetto a quello del caso peggiore atteso

typedef void (*sort_func)(int*, int);

int n_ripetizioni_tests=1000;
int compare_ct = 0;
int swap_ct = 0;


int benchmark(int* arr, sort_func func) {
	int length;
	int max_array_dim = 100;


	printf("Dim_array,n_ripetizioni_test,min_swap,avg_swap,max_swap,expected_worst_case_swap,min_cmp,avg_cmp,max_cmp,expected_worst_case_cmp\n");

	//// inizio il ciclo per calcolare 100 dimensioni di array crescenti
	for (length = max_array_dim/100; length <= max_array_dim; length += max_array_dim/100) {
		int swap_min=-1;
		int swap_max=-1;
		long swap_avg=-1;

		int cmp_min=-1;
		int cmp_max=-1;
		long cmp_avg=-1;

		//// lancio n_ripetizioni_tests volte per coprire diversi casi di input random
		for (int test = 0; test < n_ripetizioni_tests; test++) {

			/// inizializzazione array: numeri random con range dimensione array
			for (int i=0; i < length; i++) {
				arr[i]= rand() % length;
			}

		swap_ct = 0;
		compare_ct = 0;

		(*func)(arr, length);

		/// statistiche
		swap_avg+= swap_ct;
		if (swap_min < 0 || swap_min > swap_ct)
			swap_min = swap_ct;
		if (swap_max < 0 || swap_max < swap_ct) 
			swap_max = swap_ct;
		
		cmp_avg+= compare_ct;
		
		if (cmp_min < 0 || cmp_min > compare_ct) 
			cmp_min = compare_ct;
		if (cmp_max < 0 || cmp_max < compare_ct) 
			cmp_max = compare_ct;
	}

	printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
		length, n_ripetizioni_tests,
		swap_min, round((0.0+swap_avg)/n_ripetizioni_tests), swap_max, length * (length-1)/2,
		cmp_min, round((0.0+cmp_avg)/n_ripetizioni_tests), cmp_max, length * (length-1)/2);
	}
	return 0;
}
