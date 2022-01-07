#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"

static int matrix_length = 0;

/**
 * \param pipe The pipe through which column values are sent and received
 * \param row The row of the first matrix this process is working on
 * \param row_id Index of the process
 * //\param result_row The row of the resulting matrix
 */
void compute_row(int pipe[2], int parent_pipe[2], long row[matrix_length], int row_id) {

	///Storage array for column values read from the pipe
	long col_vals[matrix_length];
	
	///Result Row Array -> Will contain the result values of the row this process is working on
	long res_row[matrix_length];
	memset(res_row, 0, matrix_length * sizeof(long));

	//For each row value we read 3 column values from the second matrix (sent via pipe) 
	for(int i=0; i < matrix_length; i++) {

		while(read(pipe[0], col_vals, matrix_length * sizeof(long)) <= 0) {
			//Wait until 3 values have been read from the pipe
		}

		// Multiply RowCell from Matrix 1 and ColumnCell from Matrix 2 -> increment results in res_row
		for(int j = 0; j < matrix_length; j++)
		{
			int idx = ((matrix_length - i) + j) % matrix_length;
			res_row[j] += row[idx] * col_vals[idx];
		}
		write(pipe[1], col_vals, matrix_length * sizeof(long));
	}
	
	long arr_arr[matrix_length+1];

	for(int i=0; i < matrix_length; i++)
		arr_arr[i] = res_row[i];
	
	arr_arr[matrix_length] = row_id;

	write(parent_pipe[1], arr_arr, (matrix_length+1) * sizeof(long));
}

int main() {
	
	///Arrays Storing the two matrices
	long matrix1[MATRIX_SIZE][MATRIX_SIZE];
	long matrix2[MATRIX_SIZE][MATRIX_SIZE];


	load_matrix(matrix1, &matrix_length, "matrice100-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice100-2.txt");

	printf("MATRIX length %d\n", matrix_length);

	//Debug Prints
	//print_matrix(matrix1, matrix_length, matrix_length);
	//print_matrix(matrix2, matrix_length, matrix_length);
	


	int parent_pipe[2];
	pipe(parent_pipe);

	// Allocate and initialize pipes
	int pipe_arr[matrix_length][2];
	for(int i=0; i < matrix_length; i++)
	{
		pipe(pipe_arr[i]);
	}

	clock_t bench_begin = clock();

	// Process id array
	int proc_id[matrix_length];
	
	for(int i=matrix_length-1; i >= 0; i--) {
		// ----- creating the 1st child process -----
		proc_id[i] = fork();
		if (proc_id[i] == -1) {
			error("ERROR: while forking the first process");
			return EXIT_FAILURE;
		}
		else if(proc_id[i] == 0) {	
			
			printf("Process %d started!\n",i, getpid());
			
			long initial_values[matrix_length];

			for(int j=0; j < matrix_length; j++) {     
				//i goes from 3 to 0 -> we reverse it so that it goes from 0 to 3
				//we offset i by j
				//modulo matrix length to keep it in the range of matrix slots
				int idx = ((matrix_length - 1 - i) + j) % matrix_length; 
				initial_values[j] = matrix2[idx][j];
			}
		       
			if((i+1) == matrix_length)
				dup2(pipe_arr[0][1], pipe_arr[i][1]);
			else
				dup2(pipe_arr[i+1][1], pipe_arr[i][1]);
			
			write(pipe_arr[i][1], initial_values, matrix_length * sizeof(long));
			
			for(int j=0; j < matrix_length; j++)
				initial_values[j] = matrix1[j][i];
			
			compute_row(pipe_arr[i], parent_pipe, initial_values, i);

			printf("Process %d ended!\n", i);
			
			close(pipe_arr[i][0]);
			close(pipe_arr[i][1]);

			return EXIT_SUCCESS;
		}
	}

	for(int i=0; i < matrix_length; i++)
		wait(NULL);

	clock_t bench_end = clock();
	printf("Execution time: %lf milliseconds\n", (double)(bench_end - bench_begin) * 1000 / CLOCKS_PER_SEC);

	long result_matrix[matrix_length][matrix_length];
	long res_row[matrix_length+1];
	long row_id;

	for(int x=0; x < matrix_length; x++) {
		while(read(parent_pipe[0], res_row, (matrix_length+1) * sizeof(long)) <= 0) {}
		row_id = res_row[matrix_length];

		for(int y=0; y < matrix_length; y++) {
			int shift_val = (y + row_id) % matrix_length;
			result_matrix[row_id][y] = res_row[shift_val];
		}
	}

	for(int i=0; i < matrix_length; i++) {
		close(pipe_arr[i][0]);
		close(pipe_arr[i][1]);
	}


	puts("Result: ");
	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {	
			printf("%ld ", result_matrix[x][y]);
		}	
		puts("");
	}
}
