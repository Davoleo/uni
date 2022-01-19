#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "utils.h"


/**
 * \brief matrix multiplication without any parallel computations
 */
void multiply_matrices(
                        long result_matrix[MATRIX_SIZE][MATRIX_SIZE], 
                        long matrix1[MATRIX_SIZE][MATRIX_SIZE],
                        long matrix2[MATRIX_SIZE][MATRIX_SIZE], 
                        int x_limit,
                        int y_limit
                    ) {

    for (int x=0; x < x_limit; x++)
        for (int y=0; y < y_limit; y++)
            for (int i=0; i < y_limit; i++)
                result_matrix[x][i] += matrix1[x][y] * matrix2[y][i];
                
}


int main() {

    long matrix1[MATRIX_SIZE][MATRIX_SIZE];
    long matrix2[MATRIX_SIZE][MATRIX_SIZE];

    int matrix_length = 0;

    //Mastrix (CIT. Zambo 28/12/2021 10:57)
    load_matrix(matrix1, &matrix_length, "matrice100-1.txt");
    load_matrix(matrix2, &matrix_length, "matrice100-2.txt");
    
    //print_matrix(matrix1, matrix1_x, matrix1_y);
    //print_matrix(matrix2, matrix2_x, matrix2_y);

    long result[MATRIX_SIZE][MATRIX_SIZE];

    BENCHMARK(multiply_matrices(result, matrix1, matrix2, matrix_length, matrix_length))

    print_matrix(result, matrix_length, matrix_length);

    return 0;
}
