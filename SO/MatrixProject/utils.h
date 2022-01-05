#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

//Maximum Matrix Size constant (can be modified) [used to initialize arrays at the beginning of programs execution]
#define MATRIX_SIZE 32

/**
 * \brief Prints a matrix to the standard output (debug purposes)
 * \param matrix the matrix to print
 * \param x_limit the horizontal length of the matrix
 * \param y_limit the vertical length of the matrix
 */
void print_matrix(long matrix[MATRIX_SIZE][MATRIX_SIZE], int x_limit, int y_limit) {
	for(int y=0; y < y_limit; y++)
	{
		for(int x=0; x < x_limit; x++)
		{
			printf("%ld ", matrix[x][y]);
		}
		printf("\n");
	}
}

/**
 * \brief Loads a matrix from a text file
 * The Matrix in the text file is written in rows with each cell horizontally 
 * separated by a non-numerical character (not a '\n') from others in the same row
 * \param out_matrix the matrix that is loaded from the text file
 * \param x used as a column counter inside of this function (equals the actual horizontal matrix length at the end of the function)
 * \param y used as a row counter inside of this function (equals the actual vertical matrix length at the end of the function)
 * \param filename the name of the file containing the matrix
 */
void load_matrix(long out_matrix[MATRIX_SIZE][MATRIX_SIZE], int* x, int* y, const char* filename) {
	int matrix_fd = open(filename, O_RDONLY);
	
	//char_buff contains the current char read from the text file
	char char_buff;
	*x = 0;
	*y = 0;

	while(read(matrix_fd, &char_buff, 1) != 0) {

		//char is a digit
		if(char_buff >= '0' && char_buff <= '9') {
			//Add it to the output matrix while offsetting it by the ASCII value of '0'
			out_matrix[*x][*y] = char_buff - 48;
			//Increment column counter
			(*x)++;
		}
		else if(char_buff == '\n')
		{
			//Char is a new line -> next matrix row:
			//reset column counter and increment row counter
			(*y)++;
			(*x) = 0;
		}

		//Every other character is ignored
	}
	//Increment row counter by 1 at the end as there are no new lines at the end.
	(*y)++;

	//Close matrix file descriptor
	close(matrix_fd);
}

/**
 * \brief Prints an error message and exits execution with an "error" status code
 **/
void error(const char* message) {
	printf("ERROR! %s\n", message);
	exit(-1);
}

#endif