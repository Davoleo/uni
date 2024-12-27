#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

pthread_mutex_t** matrix_res_lock;

/* Matrix */
long matrix1[MATRIX_SIZE][MATRIX_SIZE];
long matrix2[MATRIX_SIZE][MATRIX_SIZE];
long matrix_res[MATRIX_SIZE][MATRIX_SIZE];

pthread_t thread_arr[MATRIX_SIZE][MATRIX_SIZE];

int matrix_length;
int cords_arr[MATRIX_SIZE * MATRIX_SIZE][2];


/** 
 * Creates threads from children threads and makes the actual computation between input values
 * \param cords an array with two numbers, x and y of the cell to be computed
 **/
void compute_cell(int cords[2])
{	
	/* Set x and y from parameter array */
	int x = cords[0];
	int y = cords[1];
	/* Index for already joined threads */
	int thread_join_idx = 1;
	/* Index used for array shifting */
	int array_shift_idx;

	/* If the cell is the first of the row, create row_len-1 threads */
	if(y == 0)
	{
		for(int i=1; i < matrix_length; i++)
		{	
			/* Use the global array for cods as a matrix shifting the x value by row_len */
			array_shift_idx = x * matrix_length;
			/* Set value of the global array for thread */
			cords_arr[array_shift_idx+i][0] = x;
			cords_arr[array_shift_idx+i][1] = i;

			/* Try to create a thread, if it fails decrement i */
			if(pthread_create(&thread_arr[x][i], NULL, (void *)compute_cell, (void *)cords_arr[array_shift_idx+i]) != 0)
				i--;
			
			/* Try to join a thread to make space for a new one */
			if(pthread_join(thread_arr[x][thread_join_idx], NULL) == 0)
				thread_join_idx++;
		}
	}

	long value1, value2, result;
	/* Set value1 from the first matrix */
	value1 = matrix1[x][y];

	for(int i=0; i < matrix_length; i++)
	{
		/* Shift fhe second matrix row based on the column value */
		array_shift_idx = (i+y) % matrix_length;
		/* Set value2 from properly shifted matrix2 */
		value2 = matrix2[y][array_shift_idx];
		/* Calculate the result */
		result = value1 * value2;

		/* Get access to the result cell and add the result */
		pthread_mutex_lock(&matrix_res_lock[x][array_shift_idx]);
		matrix_res[x][array_shift_idx] += result;
		pthread_mutex_unlock(&matrix_res_lock[x][array_shift_idx]);
	}
	
	/* If the cell is the first of the row, join row_len-1 threads */
	if(y == 0)
	{
		for(int i=thread_join_idx; i < matrix_length; i++)
			while(pthread_join(thread_arr[x][i], NULL) != 0) {}
	}
		
	/* Exit from thread */
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{	
	int fun = parse_flags(argc, argv);

	if(fun == 0)
		return EXIT_SUCCESS;
	else if(fun == 1)
	{	
		matrix_length = atoi(argv[2]);
		generate_matrix(matrix1, matrix_length);
		generate_matrix(matrix2, matrix_length);
	}
	else if(fun == 2)
	{
		int status = 0;
		status += load_matrix(matrix1, &matrix_length, argv[2]);
		status += load_matrix(matrix2, &matrix_length, argv[3]);
		if (status < 0)
			error("Error while loading matrices from files!");
	}
	else
		return EXIT_FAILURE;	

	/* Setup global mutex array */
	matrix_res_lock = malloc(sizeof(pthread_mutex_t) * matrix_length);
	for(int x=0; x < matrix_length; x++)
	{
		matrix_res_lock[x] = malloc(sizeof(pthread_mutex_t) * matrix_length);

		for(int y=0; y < matrix_length; y++)
			pthread_mutex_init(&matrix_res_lock[x][y], NULL);
	}

	BENCHMARK_BEGIN()
	
	/* Start threads */
	for(int x=0; x < matrix_length; x++)
	{
		cords_arr[x*matrix_length][0] = x;

		if(pthread_create(&thread_arr[x][0], NULL, (void *)compute_cell, (void *)cords_arr[x*matrix_length]) != 0)
		{	
			puts("Thread creation failed!");
			return EXIT_FAILURE;
		}
	}

	/* Wait for evey thread to join */
	for(int x=0; x < matrix_length; x++)
	{
		while(pthread_join(thread_arr[x][0], NULL) != 0) {}
	}

	BENCHMARK_END(print_matrix(matrix_res, matrix_length))

	/* Destroy mutexes */
	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
			pthread_mutex_destroy(&matrix_res_lock[x][y]);

		free(matrix_res_lock[x]);
	}
	free(matrix_res_lock);


	return EXIT_SUCCESS;
}
