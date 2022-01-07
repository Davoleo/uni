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


void compute_row(int cords[2]) {
	int x = cords[0];
	int y = cords[1];

	for(int i=0; i < matrix_length; i++) {
		printf("x: %d, y: %d, i: %d\n", x, y, i);

		pthread_mutex_lock(&result_matrix_lock);
		matrix_res[x][i] += matrix1[x][y] * matrix2[x][i];
		pthread_mutex_unlock(&result_matrix_lock);
	}

}


int main() {
	
	///Arrays Storing the two matrice

	load_matrix(matrix1, &matrix_length, "matrice3-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice3-2.txt");

	for(int x=0; x < matrix_length; x++) {
		memset(matrix_res[x], 0, matrix_length);
	}

	printf("MATRIX length %d\n", matrix_length);

	pthread_t thread_arr[matrix_length][matrix_length];

	int cords[2];


	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {
			cords[0] = x;
			cords[1] = y;
			pthread_create(&thread_arr[x][y], NULL, (void*)compute_row, (void*)cords);
		}
	}

	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {
			while(pthread_join(thread_arr[x][y], NULL) != 0) {}
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
