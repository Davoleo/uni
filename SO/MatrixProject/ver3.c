#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

static int matrix_length = 0;
static pthread_mutex_t result_matrix_lock = PTHREAD_MUTEX_INITIALIZER;

long matrix1[MATRIX_SIZE][MATRIX_SIZE];
long matrix2[MATRIX_SIZE][MATRIX_SIZE];
long matrix_res[MATRIX_SIZE][MATRIX_SIZE];


void compute_cell(int cords[2]) {
	int x = cords[0];
	int y = cords[1];

	for(int i=0; i < matrix_length; i++) {

		pthread_mutex_lock(&result_matrix_lock);
		matrix_res[x][i] += matrix1[x][y] * matrix2[y][i];
		if(x == 0)
			printf("y: %d, mult: %ld, res: %ld\n", y, matrix1[x][y] * matrix2[y][i], matrix_res[x][i]);
		pthread_mutex_unlock(&result_matrix_lock);
	}

}


int main() {
	
	///Arrays Storing the two matrices

	load_matrix(matrix1, &matrix_length, "matrice3-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice3-2.txt");

	for(int x=0; x < matrix_length; x++) {
		memset(matrix_res[x], 0, matrix_length);
	}

	printf("MATRIX length %d\n", matrix_length);


	puts("Matrix: ");
	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {	
			printf("%ld ", matrix1[x][y]);
		}	
		puts("");
	}


	pthread_t thread_arr[matrix_length][matrix_length];

	int cords[2];

	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {
			cords[0] = x;
			cords[1] = y;
			int exit_code = pthread_create(&thread_arr[x][y], NULL, (void*)compute_cell, (void*)cords);

			if (x == 0)
				printf("x: %d, y: %d, threadID: %ld\n", x, y, thread_arr[x][y]);
			if (exit_code != 0) {
				char message[32];
				sprintf(message, "Error Code: %d", exit_code);
				error(message);
			}
		}
	}

	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {
			pthread_join(thread_arr[x][y], NULL);
		}
	}

	printf("\nResult --------------------\n");
	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {	
			printf("%ld ", matrix_res[x][y]);
		}	
		puts("");
	}

}
