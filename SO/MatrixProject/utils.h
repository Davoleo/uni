#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define MATRIX_SIZE 32

/**
 * TODO Document
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
 * TODO Document
 */
void load_matrix(long matrix[MATRIX_SIZE][MATRIX_SIZE], int* x, int* y, const char* filename) {
	int matrix_fd = open(filename, O_RDONLY);
	
	char char_buff;
	*x = 0;
	
	*y = 0;

	while(read(matrix_fd, &char_buff, 1) != 0) {
		if(char_buff >= '0' && char_buff <= '9') {
			matrix[*x][*y] = char_buff - 48;
			(*x)++;
		}
		else if(char_buff == '\n')
		{
			(*y)++;
			(*x) = 0;
		}
	}
	(*y)++;

	close(matrix_fd);
}

void error(const char* message) {
	printf("%s\n", message);
	exit(-1);
}

#endif