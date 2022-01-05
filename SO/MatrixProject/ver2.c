#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

///The Actual Matrix length (only 1 value because exercise is simplified to square matrices)
static int matrix_length = 0;

/**
 * \param pipe The pipe through which column values are sent and received
 * \param row The row of the first matrix this process is working on
 * //\param row_i The index of the first element of the row the process is working on
 * //\param result_row The row of the resulting matrix
 */
void compute_row(int pipe[2], long row[matrix_length]) {

	///Storage array for column values read from the pipe
	long col_vals[matrix_length];
	
	///Result Row Array -> Will contain the result values of the row this process is working on
	long res_row[matrix_length];
	memset(res_row, 0, matrix_length * sizeof(long));

	printf("Process %d begins computing row\n", getpid());

	//For each row value we read 3 column values from the second matrix (sent via pipe) 
	for(int i=0; i < matrix_length; i++) {

		while(read(pipe[0], col_vals, matrix_length * sizeof(long)) <= 0) {
			//Wait until 3 values have been read from the pipe
		}
		
		printf("column values: %ld %ld %ld\n", col_vals[0], col_vals[1], col_vals[2]);
	
		// Multiply RowCell from Matrix 1 and ColumnCell from Matrix 2 -> increment results in res_row
		for(int j=0; j < matrix_length; j++)
			res_row[j] += row[j] * col_vals[j];

		//TODO output values
		//write(pipeout)
		
	}

}

int main() {
	
	///Arrays Storing the two matrices
	long matrix1[MATRIX_SIZE][MATRIX_SIZE];
	long matrix2[MATRIX_SIZE][MATRIX_SIZE];

	int matrix1_x = 0;
	int matrix1_y = 0;
	int matrix2_x = 0;
	int matrix2_y = 0;

	load_matrix(matrix1, &matrix1_x, &matrix1_y, "matrice1.txt");
	load_matrix(matrix2, &matrix2_x, &matrix2_y, "matrice2.txt");
	

	matrix_length = matrix1_x;

	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	
	//Pipe creation (pipes are created globally so that everyone has knoweledge of their descriptors)
	pipe(pipe1);
	pipe(pipe2);
	pipe(pipe3);
	
	/*
	//Pipe Linkining	
	//reading end of pipe 1 to writing end of pipe 2
	dup2(pipe2[1], pipe1[0]);
	//reading end of pipe 3 to writing end of pipe 1
	dup2(pipe1[1], pipe3[0]);
	//reading end of pipe 2 to writing end of pipe 3
	dup2(pipe3[1], pipe2[0]);
	*/

	int pid1 = fork();
	if (pid1 == -1) {
		error("ERROR: while forking the first process");
	}
	else if(pid1 == 0) {	
		//1st Child Process
		printf("child 1 : %d\n", getpid());

		compute_row(pipe1, matrix1[0]);

		puts("end of child 1");
	}
	else {	// THE PARENT
		
		// ----- creating the 2nd process -----
		int pid2 = fork();
		if (pid2 == -1) {
			error("ERROR: while forking the first process");
		}
		if(pid2 == 0) {
			// child 2
			printf("child 2 : %d\n", getpid());

			long arr[] = {1, 2, 3};
			
			for(int i=0; i < matrix_length; i++) {
				int status = write(pipe1[1], arr, 3 * sizeof(long));
				printf("write status %d\n", status);
			}

			puts("End of Child 2");
		}
		else { // THE PARENT

			// ----- creating the 3rd process -----
			int pid3 = fork();
			if (pid3 == -1) {
				error("ERROR: while forking the first process");
			}
			if(pid3 == 0) {
				
				//child 3
				printf("child 3 : %d\n", getpid());
				
				puts("End of child 3");
			}
			else {
				wait(NULL);
				wait(NULL);
				wait(NULL);
				puts("PADRE KEK");
			}
			// ----- 3rd process if finished -----
		}
		// ----- 2nd process if finished -----
	}
}
