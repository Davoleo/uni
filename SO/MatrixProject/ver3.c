#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

pthread_mutex_t** matrix_res_lock;
pthread_mutex_t cords_lock = PTHREAD_MUTEX_INITIALIZER;

/* Matrix */
long matrix1[MATRIX_SIZE][MATRIX_SIZE];
long matrix2[MATRIX_SIZE][MATRIX_SIZE];
long matrix_res[MATRIX_SIZE][MATRIX_SIZE];

int matrix_length;
int* cords;
int* cords_read_ptr;


void compute_cell()
{
	int x = *(cords_read_ptr++);
	int y = *(cords_read_ptr++);

	//puts("sending signal");
	//pthread_cond_signal(&cond);

	long val1, val2, result;
	int idx;
	val1 = matrix1[x][y];

	for(int i=0; i < matrix_length; i++)
	{
		idx = (i+y) % matrix_length;

		val2 = matrix2[y][idx];
		result = val1 * val2;

		pthread_mutex_lock(&matrix_res_lock[x][idx]);
		matrix_res[x][idx] += result;
		pthread_mutex_unlock(&matrix_res_lock[x][idx]);
	}
}


int main()
{	
	/* Load matrices */
	load_matrix(matrix1, &matrix_length, "matrice100-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice100-2.txt");

	/* Setup mutex */
	matrix_res_lock = malloc(sizeof(pthread_mutex_t) * matrix_length);
	for(int x=0; x < matrix_length; x++)
	{
		matrix_res_lock[x] = malloc(sizeof(pthread_mutex_t) * matrix_length);
		for(int y=0; y < matrix_length; y++)
		{
			pthread_mutex_init(&matrix_res_lock[x][y], NULL);
		}
	}

	//printf("Matrix length: %d\n", matrix_length);

	/* Initalize result matrix with zeroes */
	for(int i=0; i < matrix_length; i++)
		memset(matrix_res[i], 0, matrix_length * sizeof(long));

	/* Allocate threads array */
	pthread_t thread_arr[matrix_length][matrix_length];

	/* Allocate global cords */
	cords = malloc(sizeof(int) * matrix_length * matrix_length * 2);
	cords_read_ptr = cords;
	int* cords_write_ptr = cords;

	clock_t bench_begin = clock();

	/* Start threads */
	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
		{	
			pthread_mutex_lock(&cords_lock);
			*(cords_write_ptr++) = x;
			*(cords_write_ptr++) = y;
			pthread_mutex_unlock(&cords_lock);

			if(pthread_create(&thread_arr[x][y], NULL, (void*)compute_cell, (void*)cords) != 0)
				return EXIT_FAILURE;
		}
	}

	/* Wait for evey thread to join */
	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
		{	
			while(pthread_join(thread_arr[x][y], NULL) != 0) {}
		}
	}

	clock_t bench_end = clock();

	/* Print result matrix */
	print_matrix(matrix_res, matrix_length, matrix_length);
	
	/* Print execution time */
	printf("Execution time: %lf milliseconds\n", (double)(bench_end - bench_begin) * 1000 / CLOCKS_PER_SEC);

	/* Destroy mutex */
	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
		{
			pthread_mutex_destroy(&matrix_res_lock[x][y]);
		}
		free(matrix_res_lock[x]);
	}
	free(matrix_res_lock);


	return EXIT_SUCCESS;
}
