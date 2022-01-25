#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//Benchmarking
#include <time.h>

/**
 * \brief Maximum Matrix Size constant (can be modified) [used to initialize arrays at the beginning of programs execution]
 **/ 
#define MATRIX_SIZE 500

/**
 * \brief If this is defined result matrices will be printed to the console output after the program is run
 **/ 
#define PRINT_MATRICES

/**
 * \brief Prints an error message and exits execution with an "error" status code
 **/
void error(const char* message) {
	printf("ERROR! %s\n", message);
	exit(-1);
}

/**
 * \brief Prints a matrix to the standard output (debug purposes)
 * \param matrix the matrix to print
 * \param matrix_length the horizontal length of the matrix
 */
void print_matrix(long matrix[MATRIX_SIZE][MATRIX_SIZE], int matrix_length) {
	#ifdef PRINT_MATRICES
	for(int x=0; x < matrix_length; x++) {
		for(int y=0; y < matrix_length; y++) {
			printf("%ld ", matrix[x][y]);
		}
		printf("\n");
	}
	#endif
}

/**
 * \brief Loads a matrix from a text file (super inefficient as we're loading it char by char)
 * The Matrix in the text file is written in rows with each cell horizontally 
 * separated by a non-numerical character (not a '\n') from others in the same row
 * \param out_matrix the matrix that is loaded from the text file
 * \param x used as a column counter inside of this function (equals the actual horizontal matrix length at the end of the function)
 * \param y used as a row counter inside of this function (equals the actual vertical matrix length at the end of the function)
 * \param filename the name of the file containing the matrix
 */
void load_matrix(long out_matrix[MATRIX_SIZE][MATRIX_SIZE], int* length, const char* filename) {
	
	FILE* matrix_file = fopen(filename, "r");
	char row_buff[MATRIX_SIZE * 3];

	*length = 0;

	//fgets default delim is \n of course
	while(fgets(row_buff, MATRIX_SIZE * 3, matrix_file) != NULL) {
		
		int y = 0;
		char* token = strtok(row_buff, " ");
		while (token != NULL) {
			out_matrix[*length][y] = strtol(token, NULL, 10);
			token = strtok(NULL, " ");
			y++;
		}
		(*length)++;
	}

	//Close matrix file
	fclose(matrix_file);
}

void generate_matrix(long out_matrix[MATRIX_SIZE][MATRIX_SIZE], int size) {
	#ifndef RAND_SEED
	#define RAND_SEED
	srand(time(NULL));
	#endif

	if (size >= MATRIX_SIZE)
		error("Random matrix size can't be greater than 500");

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			out_matrix[x][y] = rand() % 25;
		}
	}
}

/**
 * \brief Macro with the code to benchmark as parameter
 **/
#define BENCHMARK_OLD(code) clock_t bench_begin = clock(); \
code; \
clock_t bench_end = clock(); \
printf("Execution time: %lf milliseconds\n", (double)(bench_end - bench_begin) * 1000 / CLOCKS_PER_SEC);

/**
 * \brief Sets up structures and begin benchmark timepoint
 * \note should always be used before \ref BENCHMARK_END
 **/
#define BENCHMARK_BEGIN() \
	/* Create structs for time benchmark */\
	struct timespec start, end;\
	/* Get wall time before */\
	clock_gettime(CLOCK_REALTIME, &start);

/**
 * \brief registers benchmark finished timepoint and prints the execution time between the two timepoints
 * \note it also runs result printer as code to print the actual result of calculations (e.g. result matrix) before the execution time
 **/
#define BENCHMARK_END(result_printer)  \
	/* Get wall time after execution */ \
	clock_gettime(CLOCK_REALTIME, &end); \
	/* Print result matrix */ \
	result_printer; \
	/* Print execution time */ \
	printf("Execution time: %0.3f sec\n", (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec));

#endif


int parse_flags(int argc, char* argv[])
{
	if(argc == 1)
	{
		puts("No flags provided!\nUse -h for help");
		return -1;
	}
	else if(strcmp(argv[1], "-h") == 0)
	{
		puts(
			"-h		List commands\n"
			"-r n		Generate two random matrices n x n\n"
			"-f f1 f2	Use two files as input"
		);

		return 0;
	}
	else if(strcmp(argv[1], "-r") == 0)
	{	
		if(argc < 3)
		{
			puts("No size provided!");
			return -1;
		}

		return 1;
	}
	else if(strcmp(argv[1], "-f") == 0)
	{
		if(argc < 4)
		{
			puts("No files provided!");
			return -1;
		}	
		
		return 2;
	}

	puts("Invalid flags!");
	return -1;
}