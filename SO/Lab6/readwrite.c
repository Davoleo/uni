#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_mutex_t read_index_lock;

sem_t queue;
int readcount = 0;
int array[10] = {};

void twrite() {

    for(int i = 0; i < 10; i++) {        

        array[i] = i + 10;

        puts("new value in the queue - POG");
        //+1 on the semaphore as a new element can be read by reader threads
        sem_post(&queue);

        sleep(2);
    }
    
    puts("Writer Thread Exiting...");
    pthread_exit(0);
}

void tread(unsigned int* interval) {
    unsigned int thread_num = (*interval / 2) - 2;
    //int semvalue;
    //sem_getvalue(&semaphore, &semvalue);

    while (readcount < 10) {
        //acquire one of the resources of the semaphore (OR WAIT IF THERE ARE NONE)
        sem_wait(&queue);

        pthread_mutex_lock(&read_index_lock);
        printf("T%d Number: %d\n", thread_num, array[readcount++]);
        pthread_mutex_unlock(&read_index_lock);

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

    pthread_mutex_init(&read_index_lock, NULL);

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

    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);

    return 0;
}