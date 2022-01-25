#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

pthread_mutex_t** matrix_res_lock;

/* Matrix */
long matrix1[MATRIX_SIZE][MATRIX_SIZE];
long matrix2[MATRIX_SIZE][MATRIX_SIZE];
long matrix_res[MATRIX_SIZE][MATRIX_SIZE];

pthread_t thread_arr[MATRIX_SIZE];

int matrix_length;
int cords_arr[MATRIX_SIZE * MATRIX_SIZE][2];
int matrix_length = 0;


void compute_cell(int cords[2])
{
        /* Set x and y from parameter array */
        int x = cords[0];
        int y = cords[1];
        /* Index used for array shifting */
        int array_shift_idx;
        /*
        if(y == 0)
        {
                for(int i=1; i < matrix_length; i++)
                {
                        array_shift_idx = x * matrix_length;
                        cords_arr[array_shift_idx+i][0] = x;
                        cords_arr[array_shift_idx+i][1] = i;
                        
                        if(pthread_create(&thread_arr[i], NULL, (void *)compute_cell, (void *)cords_arr[array_shift_idx+i]) != 0)
                        {
                                puts("Thread creation failed");
                                fflush(stdout);
                                i--;
                        }
                        else 
                        {
                                printf("Thraed %d%d created!\n", x, i);
                                fflush(stdout);
                        }
                }
                puts("END");
        }
        */
        long value1, value2, result;
        /* Set value1 from the first matrix */
        value1 = matrix1[x][y];

        for(int i=0; i < matrix_length; i++)
        {
                /* Shift fhe second matrix row based on the column value */
                array_shift_idx = (i+y) % matrix_length;
                /* Set value2 from properly shifted matrix2 */
                value2 = matrix2[y][array_shift_idx];
                /* Calculate the result */
                result = value1 * value2;

                /* Get access to the result cell and add the result */
                pthread_mutex_lock(&matrix_res_lock[x][array_shift_idx]);
                matrix_res[x][array_shift_idx] += result;
                pthread_mutex_unlock(&matrix_res_lock[x][array_shift_idx]);
        }

        /*
        if(y == 0)
        {
                for(int i=1; i < matrix_length; i++)
                        while(pthread_join(thread_arr[i], NULL) != 0) {}
        }
        */
        
        printf("Thraed %d stopped!\n", x);
        fflush(stdout);

        /* Exit from thread */
        pthread_exit(NULL);
} 


int main() {

        /* Setup global mutex array */
        matrix_res_lock = malloc(sizeof(pthread_mutex_t) * matrix_length);
        for(int x=0; x < matrix_length; x++)
        {
                matrix_res_lock[x] = malloc(sizeof(pthread_mutex_t) * matrix_length);

                for(int y=0; y < matrix_length; y++)
                        pthread_mutex_init(&matrix_res_lock[x][y], NULL);
        }

	load_matrix(matrix1, &matrix_length, "matrice3-1.txt");
	load_matrix(matrix2, &matrix_length, "matrice3-2.txt");

	printf("MATRIX length %d\n", matrix_length);

        int pid;

        for(int x=0; x < matrix_length; x++)
        {
                pid = fork();
                if(pid == -1)
                {
                        puts("Process creation failed!");
                        return EXIT_FAILURE;
                }
                if(pid == 0) /* Child process */
                {

                        printf("Process %d Created!\n", x);
                        fflush(stdout);

                        cords_arr[x*matrix_length][0] = x;
                        cords_arr[x*matrix_length][1] = 0;

                        if(pthread_create(&thread_arr[0], NULL, (void *)compute_cell, (void *)cords_arr[x*matrix_length]) != 0)
                        {
                                puts("Thread creation failed!");
                                fflush(stdout);
                                return EXIT_FAILURE;
                        }                   
                        
                        while(pthread_join(thread_arr[0], NULL) != 0) {}
                        
                        printf("Process and thread%d stopped!\n", x);
                        fflush(stdout);

                        return EXIT_SUCCESS;
                }
        }
        
        for(int i=0; i < matrix_length; i++)
                wait(NULL);
       
        /* Print result matrix */
        print_matrix(matrix_res, matrix_length, matrix_length);

        return EXIT_SUCCESS;
}
