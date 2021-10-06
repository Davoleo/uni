#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    //Fork Child Process
    pid = fork();

    //Error
    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) {
        //Child process
        //
        execlp("/bin/ls", "ls", NULL);
    }
    else {
        //Parent process
        wait(NULL);
        printf("Child Complete");
    }
    return 0;
}