#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cmd.h"

typedef void (*sort_func)(int*);

int n_ripetizioni_tests=1000;
int compare_ct = 0;
int swap_ct = 0;
int read_ct = 0;
int op_ct = 0;


int max_dim = 100;


int benchmark(int* arr, sort_func func) {
	int length;


	printf("Dim_array,n_ripetizioni_test,min_swap,avg_swap,max_swap,expected_worst_case_swap,min_cmp,avg_cmp,max_cmp,expected_worst_case_cmp,min_cmp,avg_cmp,max_cmp\n");

	//// inizio il ciclo per calcolare 100 dimensioni di array crescenti
	for (length = max_dim/100; length <= max_dim; length += max_dim/100) {
		int swap_min=-1;
		int swap_max=-1;
		long swap_avg=-1;

		int cmp_min=-1;
		int cmp_max=-1;
		long cmp_avg=-1;

		int read_min=-1;
		int read_max=-1;
		int read_avg=-1;

		//// lancio n_ripetizioni_tests volte per coprire diversi casi di input random
		for (int test = 0; test < n_ripetizioni_tests; test++) {

			/// inizializzazione array: numeri random con range dimensione array
			for (int i=0; i < length; i++) {
				arr[i]= rand() % length;
			}

			swap_ct = 0;
			compare_ct = 0;
			read_ct = 0;

			(*func)(arr);

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

			read_avg+= read_ct;
			if (read_min < 0 || read_min > read_ct) 
				read_min = read_ct;
			if (read_max < 0 || read_max < read_ct) 
				read_max = read_ct;
		}

		printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			length, n_ripetizioni_tests,
			swap_min, round((0.0+swap_avg)/n_ripetizioni_tests), swap_max, length * (length-1)/2,
			cmp_min, round((0.0+cmp_avg)/n_ripetizioni_tests), cmp_max, length * (length-1)/2,
			read_min, round((0.0+read_avg)/n_ripetizioni_tests), read_max);
	}


	return 0;
}
