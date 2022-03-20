#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cmd.h"

typedef void (*sort_func)(int* arr, int length);
typedef void (*array_initializer)(int* arr, int length);

int compare_ct = 0;
int swap_ct = 0;
int read_ct = 0;
int op_ct = 0;

int benchmark(int* arr, sort_func func, args_t* args, array_initializer array_init) 
{
	// init random
	srand((unsigned)time(NULL));

	int length;

	printf("Dim_array,n_ripetizioni_test,min_swap,avg_swap,max_swap,expected_worst_case_swap,min_cmp,avg_cmp,max_cmp,expected_worst_case_cmp,min_cmp,avg_cmp,max_cmp\n");

	//// inizio il ciclo per calcolare 100 dimensioni di array crescenti
	for (length = (args->max_dim)/(args->div_n); length <= (args->max_dim); length += (args->max_dim/args->div_n)) 
	{
		int swap_min=-1;
		int swap_max=-1;
		double swap_avg=-1;

		int cmp_min=-1;
		int cmp_max=-1;
		double cmp_avg=-1;

		int read_min=-1;
		int read_max=-1;
		double read_avg=-1;

		//// lancio n_ripetizioni_tests volte per coprire diversi casi di input random
		for (int test = 0; test < args->test_n; test++) 
		{
			/// inizializzazione array: numeri random con range dimensione array
			(*array_init)(arr, length);

			swap_ct = 0;
			compare_ct = 0;
			read_ct = 0;

			(*func)(arr, length);

			/// statistiche
			printf("swap_ct: %d\n", swap_ct);
			swap_avg+= swap_ct;
			if (swap_min < 0 || swap_min > swap_ct)
				swap_min = swap_ct;
			if (swap_max < 0 || swap_max < swap_ct) 
				swap_max = swap_ct;
			
			printf("swap_max %d\n", swap_max);

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

		printf("SWAP_MAX %d\n", swap_max);

		swap_avg = round((double) swap_avg / args->test_n);
		cmp_avg = round((double) cmp_avg / args->test_n);
		read_avg = round((double) read_avg / args->test_n);

		printf("%d,%d,%d,%.2f,%d,%d,%d,%.2f,%d,%d,%d,%.2f,%d\n",    // %d = 13
			length, args->test_n,
			swap_min, swap_avg, swap_max, length * (length-1)/2,
			cmp_min, cmp_avg, cmp_max, length * (length-1)/2,
			read_min, read_avg, read_max);
	
		// printf("length: %d | n_test: %d\nswap_min: %d | swap_avg: %d | swap_max: %d | %d\ncmp_min: %d | cmp_avg: %d | cmp_max: %d | %d\nread_min: %d | read_avg: %d | read_max: %d | %d\n",
		// 	length, args->test_n,
		// 	swap_min, round((0.0+swap_avg)/args->test_n), swap_max, length * (length-1)/2,
		// 	cmp_min, round((0.0+cmp_avg)/args->test_n), cmp_max, length * (length-1)/2,
		// 	read_min, round((0.0+read_avg)/args->test_n), read_max);
	}


	return 0;
}
