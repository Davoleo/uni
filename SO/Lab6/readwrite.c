#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdbool.h>

/* This is terrible yes, I know :sadmelon: */

pthread_mutex_t write_lock;

int array[10];
bool writefinished = false;
sem_t semaphore;

void twrite() {
    for(int i = 0; i < 10; i++) {        
        int semvalue;
        sem_getvalue(&semaphore, &semvalue);

        pthread_mutex_lock(&write_lock);
        array[semvalue] = i + 10;
        pthread_mutex_unlock(&write_lock);

        puts("before sempost");
        //+1 on the semaphore
        sem_post(&semaphore);

        sleep(5);
    }

    writefinished = true;
    
    puts("Writer Thread Exiting...");
    pthread_exit(0);
}

void tread(unsigned int* interval) {
    unsigned int thread_num = (*interval / 2) - 2;
    int semvalue;
    sem_getvalue(&semaphore, &semvalue);

    while (semvalue >= 0) {
        sem_wait(&semaphore);
        printf("T%d Number: %d\n", thread_num, array[semvalue]);

        sleep(*interval);
    }

    printf("Reader Thread %d Exiting...\n", thread_num);
    pthread_exit(0);
}

int main() {

    pthread_t writer;
    pthread_t reader1, reader2;
    unsigned int interval1 = 6;
    unsigned int interval2 = 8;

    pthread_mutex_init(&write_lock, NULL);
    sem_init(&semaphore, 0, 0);

    if (pthread_create(&writer, NULL, (void*) twrite, NULL) != 0) {
        puts("Errore nella creazione del thread writer, exiting now...");
        exit(1);
    }

    if (pthread_create(&reader1, NULL, (void*) tread, (void*) &interval1) != 0) {
        puts("Errore nella creazione del thread reader1, exiting now...");
        exit(1);
    }
    if (pthread_create(&reader2, NULL, (void*) tread, (void*) &interval2) != 0) {
        puts("Errore nella creazione del thread reader2, exiting now...");
        exit(1);
    }

    pthread_join(writer, NULL);

    //unlock any thread that might have been blocked
    sem_post(&semaphore);

    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);

    return 0;
}