#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "utils.h"

int matrix_length = 0;

/**
 * \brief matrix multiplication without any parallel computation
 */
void multiply_matrices(
			long result_matrix[MATRIX_SIZE][MATRIX_SIZE],
			long matrix1[MATRIX_SIZE][MATRIX_SIZE],
			long matrix2[MATRIX_SIZE][MATRIX_SIZE]
		    ) {

    	for (int x=0; x < matrix_length; x++) {
		for (int y=0; y < matrix_length; y++) {
			for (int i=0; i < matrix_length; i++) {
				result_matrix[x][i] += matrix1[x][y] * matrix2[y][i];
			}
		}
	}
}

int main(int argc, char* argv[]) {

	long matrix1[MATRIX_SIZE][MATRIX_SIZE];
	long matrix2[MATRIX_SIZE][MATRIX_SIZE];

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
		//Mastrix (CIT. Zambo 28/12/2021 10:57)
		int status = 0;
		status += load_matrix(matrix1, &matrix_length, argv[2]);
		status += load_matrix(matrix2, &matrix_length, argv[3]);
		if (status < 0)
			error("Error while loading matrices from files!");
	}
	else
		return EXIT_FAILURE;

	printf("MATRIX length %d\n", matrix_length);

	long result[MATRIX_SIZE][MATRIX_SIZE];

	BENCHMARK_BEGIN()

	multiply_matrices(result, matrix1, matrix2);

	BENCHMARK_END(print_matrix(result, matrix_length))

	return EXIT_SUCCESS;
}
