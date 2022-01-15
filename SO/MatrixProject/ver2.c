#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

typedef struct _cell_result {
	int x;
	int y;
	long value;
} cell_struct;

static int matrix_length = 0;

void compute_cell(int x, int y, int horizontal_pipe[2], int vertical_pipe[2], int parent_pipe[2]) {

	long cell_result = 0;

	//For each row value we read 3 column values from the second matrix (sent via pipe) 
	for(int i=0; i < matrix_length; i++) {

		long hvalue;
		long vvalue;

		while(read(horizontal_pipe[0], hvalue, sizeof(long)) <= 0) {
			//Wait until we read the input matrix value that scrolls horizontally 
		}
		while(read(vertical_pipe[0], vvalue, sizeof(long)) <= 0) {
			//Wait until we read the input matrix value that scrolls vertically
		}

		//Multiplication and add to the value buffer
		cell_result += (hvalue * vvalue);

		//Pass values to the next process through the pipes
		write(horizontal_pipe[1], hvalue, sizeof(long));
		write(vertical_pipe[1], vvalue, sizeof(long));
	}

	//Once calculations are complete pass the result to the parent through the parent_pipe
	//Coordinates of the cell the result belongs to are also passed
	cell_struct result_obj = { x, y, cell_result };
	write(parent_pipe[1], &result_obj, sizeof(cell_struct));
}

int main() {
	
	///Arrays Storing the two matrices
	long matrix1[MATRIX_SIZE][MATRIX_SIZE];
	long matrix2[MATRIX_SIZE][MATRIX_SIZE];


	load_matrix(matrix1, &matrix_length, "matrice3-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice3-2.txt");

	printf("MATRIX length %d\n", matrix_length);

	//Debug Prints
	//print_matrix(matrix1, matrix_length, matrix_length);
	//print_matrix(matrix2, matrix_length, matrix_length);
	
	int parent_pipe[2];
	pipe(parent_pipe);

	// Allocate and initialize pipes
	int hori_pipes[matrix_length][matrix_length][2];
	int vert_pipes[matrix_length][matrix_length][2];
	for(int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
			pipe(hori_pipes[i][j]);
			pipe(vert_pipes[i][j]);
		}
	}


	clock_t bench_begin = clock();

	// Process id array
	int proc_ids[matrix_length][matrix_length];
	
	
	
	for(int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
			proc_ids[i][j] = fork();

			if (proc_ids[i][j] == -1) {
				error("Errore durante la creazione del processo");
				return EXIT_FAILURE;
			}
			else if (proc_ids[i][j] == 0) {
				//weird Hybrid index used for the columns of the first matrix and rows of the second matrix
				int hyb = i + j % matrix_length;
				long initial_rowvalue = matrix1[i][hyb];
				long initial_colvalue = matrix2[hyb][j];

				//Link horizontal rotation pipes
				int nexthpipe = j == 0 ? matrix_length : j - 1;
				dup2(hori_pipes[i][nexthpipe][1], hori_pipes[i][j][1]);
				//pass initial values into the pipe
				write(hori_pipes[i][j][1], initial_rowvalue, sizeof(long));

				//Link vertical rotation pipes
				int nextvpipe = i == 0 ? matrix_length : i - 1;
				dup2(vert_pipes[nextvpipe][j][1], vert_pipes[i][j][1]);
				//pass initial values into the pipe
				write(vert_pipes[i][j][1], initial_colvalue, sizeof(long));


				compute_cell(i, j, hori_pipes[i], vert_pipes[i], parent_pipe);

			}


		}
	}

	//---- Code here below still needs to be adapted to the new version ----//

	//wait for every child process
	for(int i=0; i < matrix_length * matrix_length; i++)
		wait(NULL);

	clock_t bench_end = clock();
	printf("Execution time: %lf milliseconds\n", (double)(bench_end - bench_begin) * 1000 / CLOCKS_PER_SEC);

	long result_matrix[matrix_length][matrix_length];
	cell_struct result;

	//CLOSE EVERY FILE DESCRIPTOR
	for (int i=0; i < matrix_length; i++) {
		for (int j=0; i < matrix_length; j++) {
			close(hori_pipes[i][j][0]);
			close(hori_pipes[i][j][1]);
			close(vert_pipes[i][j][0]);
			close(vert_pipes[i][j][1]);
		}
	}


	puts("Result: ");
	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {	
			printf("%ld ", result_matrix[x][y]);
		}	
		puts("");
	}
}
