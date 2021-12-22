#include <unistd.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

#define SLEEP_TIME 5

int procs_arr[5];
char procs_status[5];

void eat() {
    printf("Philosofo with ID %d is eating...\n", getpid());
    sleep(SLEEP_TIME);
}

void think() {
    printf("Philosofo with ID %d is thinking...\n", getpid());
    sleep(SLEEP_TIME);
}

void hungry() {
    printf("Philosofo with ID %d is hungry...\n", getpid());
    sleep(SLEEP_TIME);
}

void checkStatus(int i) {
    
    int prev = (i == 0) ? 4 : (i - 1);
    
    if(procs_status[i] == 'M')
    {
        procs_status[i] = 'P';
        think();
    }
    else if(procs_status[prev] == 'P') {
        procs_status[i] = 'M';
        eat();
    }
    else if(procs_status[i] == 'P') {
        procs_status[i] = 'F';
        hungry();
    }
}

int main() {

    for (int i = 0; i < 5; i++) {
        int status = fork();

        if (status == -1)
        {
            perror("Perry l'ornitorinco s'e' rotto");
            exit(666);
        }
        else if (status == 0) {
            if (i == 0 || i == 2)
            {
                procs_status[i] = 'M';
                eat();
            }
            else if (i == 1 || i == 3)
            {
                procs_status[i] = 'P';
                think();
            }
            else {
                procs_status[i] = 'F';
                hungry();
            }

            checkStatus(i);
            
        }
        else {
            //assign new process id to procs_arr slot
            procs_arr[i] = status;
        }
        
    }
    
    return 0;
}



/*

array[5] -> status processi {AFFAMATO, mangia, pensa non al cibo}
0 < check counter < 5

check_status(index)
    quali processi stanno mangiando

processo:
    check_status(index)e

    sleep(1);

*/