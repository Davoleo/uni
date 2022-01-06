#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "utils.h"

/**
 * TODO Document
 */
void multiply_matrices(
                        long result_matrix[MATRIX_SIZE][MATRIX_SIZE], 
                        long matrix1[MATRIX_SIZE][MATRIX_SIZE],
                        long matrix2[MATRIX_SIZE][MATRIX_SIZE], 
                        int x_limit,
                        int y_limit
                    ) {
    
    long res_val;

    /* For con y lenta */
    for(int y1=0; y1 < y_limit; y1++) {
        /* For con y veloce */
        for (int y=0; y < y_limit; y++) {
            res_val = 0;
            /* For con x veloce */
            for (int x=0; x < x_limit; x++) {
                //freesult Zambo 28/12/2021 11:13
                res_val += (matrix1[x][y1] * matrix2[y][x]);
            }

            result_matrix[y][y1] = res_val;
        }
    }
}

void multiply_matrices_procs() {
    
}


int main() {

    long matrix1[MATRIX_SIZE][MATRIX_SIZE];
    long matrix2[MATRIX_SIZE][MATRIX_SIZE];

    int matrix1_x = 0;
    int matrix1_y = 0;
    int matrix2_x = 0;
    int matrix2_y = 0;


    //Mastrix (CIT. Zambo 28/12/2021 10:57)
    load_matrix(matrix1, &matrix1_x, &matrix1_y, "matrice1.txt");
    load_matrix(matrix2, &matrix2_x, &matrix2_y, "matrice2.txt");

    //At this point matrix*_x and matrix*_y are the length of the matrices
    
    //print_matrix(matrix1, matrix1_x, matrix1_y);
    //print_matrix(matrix2, matrix2_x, matrix2_y);

    long result[MATRIX_SIZE][MATRIX_SIZE];

    BENCHMARK(multiply_matrices(result, matrix1, matrix2, matrix1_x, matrix1_y))

    //print_matrix(result, matrix1_x, matrix1_y);

    return 0;
}
