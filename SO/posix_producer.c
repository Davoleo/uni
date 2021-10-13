#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

//Slide 3.58-3.59
int main() {
    //SIZE of the shared memory buffer
    const int SIZE = 4096;
    const char* name = "OS";

    const char* message1 = "Hello";
    const char* message2 = "World!";

    int shm_fd;
    void* ptr;




    return 0;
}