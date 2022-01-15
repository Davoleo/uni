#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

pthread_mutex_t* matrix_res_lock;
pthread_mutex_t cords_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* Matrix */
long matrix1[MATRIX_SIZE][MATRIX_SIZE];
long matrix2[MATRIX_SIZE][MATRIX_SIZE];
long matrix_res[MATRIX_SIZE][MATRIX_SIZE];

int matrix_length;
int** cords;

void compute_cell()
{
	pthread_mutex_lock(&cords_lock);
	int x = *((*cords)++);
	int y = *((*cords)++);
	int idx = *((*cords)++);
	pthread_mutex_unlock(&cords_lock);

	//puts("sending signal");
	//pthread_cond_signal(&cond);

	long val1, val2, result;

	val1 = matrix1[x][y];

	for(int i=0; i < matrix_length; i++)
	{
		val2 = matrix2[y][i];
		result = val1 * val2;

		pthread_mutex_lock(&matrix_res_lock[idx]);
		matrix_res[x][i] += result;
		pthread_mutex_unlock(&matrix_res_lock[idx]);
	}
}


int main()
{	
	/* Load matrices */
	load_matrix(matrix1, &matrix_length, "matrice100-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice100-2.txt");

	matrix_res_lock = malloc(sizeof(pthread_mutex_t) * matrix_length * matrix_length);

	/* Setup mutex */
	for(int x=0; x < matrix_length; x++)
		pthread_mutex_init(&matrix_res_lock[x], NULL);

	//printf("Matrix length: %d\n", matrix_length);

	/* Initalize result matrix with zeroes */
	for(int i=0; i < matrix_length; i++)
		memset(matrix_res[i], 0, matrix_length * sizeof(long));

	/* Allocate threads array */
	pthread_t thread_arr[matrix_length][matrix_length];

	cords = malloc(sizeof(int*));
	*cords = malloc(sizeof(int) * matrix_length * matrix_length * 3);
	int mutex_idx = 0;
	int* cords_ptr = *cords;

	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
		{	
			pthread_mutex_lock(&cords_lock);
			*(cords_ptr++) = x;
			*(cords_ptr++) = y;
			*(cords_ptr++) = mutex_idx;
			pthread_mutex_unlock(&cords_lock);

			if(pthread_create(&thread_arr[x][y], NULL, (void*)compute_cell, (void*)cords) != 0)
				return EXIT_FAILURE;
			//printf("thread %d %d started\n", x, y);

			//pthread_cond_wait(&cond, &cords_lock);
			mutex_idx++;
		}
	}

	for(int x=0; x < matrix_length; x++)
	{
		for(int y=0; y < matrix_length; y++)
		{
			while(pthread_join(thread_arr[x][y], NULL) != 0) {}
		}
	}

	print_matrix(matrix_res, matrix_length, matrix_length);

	free(matrix_res_lock);

	return EXIT_SUCCESS;
}