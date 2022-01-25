#include <stdio.h>
#include <stdlib.h>

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

	print_matrix(matrix2, matrix_length);

    for (int x=0; x < matrix_length; x++) {
		for (int y=0; y < matrix_length; y++) {
			for (int i=0; i < matrix_length; i++) {
				result_matrix[x][i] += matrix1[x][y] * matrix2[y][i];
			}
		}
	}


	print_matrix(result_matrix, matrix_length);
}

int main() {

    long matrix1[MATRIX_SIZE][MATRIX_SIZE];
    long matrix2[MATRIX_SIZE][MATRIX_SIZE];

    //Mastrix (CIT. Zambo 28/12/2021 10:57)
    load_matrix(matrix1, &matrix_length, "matrice3-1.txt");
    load_matrix(matrix2, &matrix_length, "matrice3-2.txt");

	printf("MATRIX length %d\n", matrix_length);

    long result[MATRIX_SIZE][MATRIX_SIZE];
	//for(int i = 0; i < matrix_length; i++) {
	//	memset(result[i], 0, matrix_length * sizeof(long));
	//}

    BENCHMARK_OLD(multiply_matrices(result, matrix1, matrix2))

    print_matrix(result, matrix_length);

    return EXIT_SUCCESS;
}
