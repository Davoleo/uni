#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

#include "utils.h"

typedef struct _cell_result {
	int x;
	int y;
	long value;
} cell_struct;

static int matrix_length = 0;

void compute_cell(int x, int y, int initial_rowvalue, int initial_colvalue, int horizontal_pipe[2], int vertical_pipe[2], int parent_pipe[2]) {

	long cell_result = 0;

	//For each row value we read 3 column values from the second matrix (sent via pipe) 
	for(int i=0; i < matrix_length; i++) {

		long hvalue = 0;
		long vvalue = 0;

		if (i == 0) {
			hvalue = initial_rowvalue;
			vvalue = initial_colvalue;
		}
		else {
			while(read(horizontal_pipe[0], &hvalue, sizeof(long)) <= 0) {
				//puts("Waiting in horizontal read");
				//Wait until we read the input matrix value that scrolls horizontally 
			}
			while(read(vertical_pipe[0], &vvalue, sizeof(long)) <= 0) {
				//puts("Waiting in vertical read");
				//Wait until we read the input matrix value that scrolls vertically
			}
		}

		//Multiplication and add to the value buffer
		cell_result += (hvalue * vvalue);
		//if (i == 0)
		printf("%d | Multiplying cell %d %d: %ld * %ld = %ld\n", i, x, y, hvalue, vvalue, cell_result);
		//printf("iteration %d\n", i);

		//Pass values to the next process through the pipes
		//puts("before hori write");
		int hwstatus = write(horizontal_pipe[1], &hvalue, sizeof(long));
		//puts("before vert write");
		int vwstatus = write(vertical_pipe[1], &vvalue, sizeof(long));
		if (hwstatus <= 0 || vwstatus <= 0) 
			error("Error while passing values to the next process in pipes");
	}

	//Once calculations are complete pass the result to the parent through the parent_pipe
	//Coordinates of the cell the result belongs to are also passed
	cell_struct result_obj = { x, y, cell_result };
	if (write(parent_pipe[1], &result_obj, sizeof(cell_struct)) <= 0) {
		error("Error while passing values to parent process.");
	}
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
	if (pipe(parent_pipe) == -1) 
		error("Error while creating parent pipe");

	//allocate and initialize pipes
	int hori_pipes[matrix_length][matrix_length][2];
	int vert_pipes[matrix_length][matrix_length][2];
	for(int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
			int pipecreate = 0;
			pipecreate += pipe(hori_pipes[i][j]);
			pipecreate += pipe(vert_pipes[i][j]);

			if (pipecreate < 0) 
				error("Error while creating pipe matrices");
		}
	}

	for (int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
			//Link horizontal rotation pipes
			int nextcell = j == 0 ? matrix_length - 1 : j - 1;
			dup2(hori_pipes[i][nextcell][1], hori_pipes[i][j][1]);
			//Link vertical rotation pipes
			dup2(vert_pipes[i][nextcell][1], vert_pipes[i][j][1]);
		}
	}

	puts("----- Matrix Multiplication Begins NOW -----");
	clock_t bench_begin = clock();

	// Process id array
	int proc_ids[matrix_length][matrix_length];
	
	for(int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
			proc_ids[i][j] = fork();

			if (proc_ids[i][j] == -1) {
				error("Errore while creating process.");
				return EXIT_FAILURE;
			}
			else if (proc_ids[i][j] == 0) { //in child processes
				
				//weird Hybrid index used for the columns of the first matrix and rows of the second matrix
				int hyb = (i + j) % matrix_length;
				long initial_rowvalue = matrix1[i][hyb];
				long initial_colvalue = matrix2[hyb][j];

				//printf("initial indexes i = %d, j = %d, hyb = %d\n", i, j, hyb);
				//printf("initial values row = %ld, column = %ld\n",  initial_rowvalue, initial_colvalue);


				//pass initial values into the pipe
				//if (write(hori_pipes[i][j][1], &initial_rowvalue, sizeof(long)) <= 0) {
				//	error("Error while writing initial rowvalues as first values for the pipes");
				//}
				//pass initial values into the pipe
				//if (write(vert_pipes[i][j][1], &initial_colvalue, sizeof(long)) <= 0) {
				//	error("Error while writing initial colvalues as first values for the pipes");
				//}

				compute_cell(i, j, initial_rowvalue, initial_colvalue, hori_pipes[i][j], vert_pipes[i][j], parent_pipe);
				return EXIT_SUCCESS;
			}


		}
	}

	//wait for every child process
	for(int i=0; i < matrix_length * matrix_length; i++)
		wait(NULL);

	clock_t bench_end = clock();
	puts("----- Matrix Multiplication ENDED -----");
	printf("Execution time: %lf milliseconds\n", (double)(bench_end - bench_begin) * 1000 / CLOCKS_PER_SEC);

	long result_matrix[matrix_length][matrix_length];

	for (int i=0; i < matrix_length * matrix_length; i++) {
		cell_struct result;
		while (read(parent_pipe[0], &result, sizeof(cell_struct)) <= 0) {
			//Keep trying to read result until we actually read more than 0 bytes
		}
		result_matrix[result.x][result.y] = result.value;
	}

	//CLOSE EVERY FILE DESCRIPTOR
	for (int i=0; i < matrix_length; i++) {
		for (int j=0; j < matrix_length; j++) {
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
