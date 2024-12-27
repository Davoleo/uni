#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    //Fork Child Process
    //This pid is useful to manage the child process but it's not the actual pid of the process in the OS
    pid = fork();

    //Error
    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) {
        //Child process
        //execlp executes a command you give it
        //Arguments: location where the command is executed, command (argument?), should be NULL
        execlp("/bin/ls", "ls", NULL);
        //System call getpid() returns the actual pid of the childprocess here
        pid_t childPID = getpid();
        printf("Child PIDs: %d | %d", pid, childPID);
    }
    else {
        //Parent process
        wait(NULL);
        printf("Child Complete");
    }
    return 0;
}