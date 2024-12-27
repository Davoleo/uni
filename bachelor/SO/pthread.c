#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Dati condivisi tra i thread
int sum;
void* runner(void* param); //I thread chiamano questa funzione

int main(int argc, char* argv[]) {
    pthread_t tid;
    pthread_attr_t attr;

    //Aggiunta degli attributi del thread
    pthread_attr_init(&attr);
    //creazione di un thread (argv è il parametro passato nella funzione runner)
    pthread_create(&tid, &attr, runner, argv[1])
    //thread principale aspetta che finisca il thread secondario
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
    return 0;
}

//funzione eseguita nel thread
void* runner(void* param) {
    int i;
    int upper = atoi(param);

    for (for int i = 1; i <= upper; i++)
        sum+=i;

    pthread_exit(0);
}