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


void compute_cell(int cords[2])
{	
	int x = cords[0];
	int y = cords[1];
	long val1, val2, result;
	int idx;

	int thread_join_idx = 1;

	if(y == 0)
	{
		for(int i=1; i < matrix_length; i++)
		{
                        int shift_idx = x * matrix_length;
                        cords_arr[shift_idx+i][0] = x;
                        cords_arr[shift_idx+i][1] = i;
                        
                        if(pthread_create(&thread_arr[x][i], NULL, (void *)compute_cell, (void *)cords_arr[shift_idx+i]) != 0)
				i--;

			if(pthread_join(thread_arr[x][thread_join_idx], NULL) == 0)
				thread_join_idx++;
		}
	}


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
        
        if(y == 0)
        {
                for(int i=thread_join_idx; i < matrix_length; i++)
                        while(pthread_join(thread_arr[x][i], NULL) != 0) {}
        }
        
        pthread_exit(NULL);
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
			pthread_mutex_init(&matrix_res_lock[x][y], NULL);
	}

	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	
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

	clock_gettime(CLOCK_REALTIME, &end);

	/* Print result matrix */
	print_matrix(matrix_res, matrix_length, matrix_length);
	
	/* Print execution time */
	printf("Execution time: %0.3f sec\n", (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec));

	/* Destroy mutex */
	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
			pthread_mutex_destroy(&matrix_res_lock[x][y]);

		free(matrix_res_lock[x]);
	}
	free(matrix_res_lock);


	return EXIT_SUCCESS;
}
