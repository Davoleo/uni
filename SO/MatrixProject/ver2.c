#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * \param pipe The pipe through which column values are sent and received
 * \param row The row of the first matrix this process is working on
 * \param row_i The index of the first element of the row the process is working on
 * \param result_row The row of the resulting matrix
 */
void compute_row(int pipe[2], long row[MATRIX_SIZE], int row_i, long result_row[MATRIX_SIZE]) {

	long col_vals[3];
	
	for(int i=0; i < MATRIX_SIZE; i++)
	{
		printf("yo boi eccomi %d\n", getpid());

		while(read(pipe[0], col_vals, 3 * sizeof(long)) <= 0) {
			// Read wait
		}
	
		printf("column values: %ld %ld %ld\n", col_vals[0], col_vals[1], col_vals[2]);

	}

}

int main() {
	
	long matrix1[MATRIX_SIZE][MATRIX_SIZE];
	long matrix2[MATRIX_SIZE][MATRIX_SIZE];
	long result[MATRIX_SIZE][MATRIX_SIZE];

	int matrix1_x = 0;
	int matrix1_y = 0;
	int matrix2_x = 0;
	int matrix2_y = 0;


	load_matrix(matrix1, &matrix1_x, &matrix1_y, "matrice1.txt");
	load_matrix(matrix2, &matrix2_x, &matrix2_y, "matrice2.txt");

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

		compute_row(pipe1, matrix1[0], 0, result[0]);

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
			
			for(int i=0; i < MATRIX_SIZE; i++) {
				int status = write(pipe1[1], arr, 3 * sizeof(long));
				printf("write status %d\n", status);
			}

			puts("End of Child 2");
		}
		else { // THE PARENT
			
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
		}
		// ----- 2nd process if finished -----
	}
}
