#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 2048

int main() {

    int testFd = open("test.txt", O_RDWR);

    if (testFd == -1) {
        puts("Error while opening file text.txt");
        return -1;
    }

    char testContent[LENGTH] = {};
    int count = read(testFd, testContent, LENGTH);

    if (count == -1) {
        puts("error while reading file");
        return -1;
    }

    printf("%s", testContent);

    int wordCount = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (testContent[i] == ' ' || testContent[i] == '\n')
            wordCount++;
    }

    char wordCountLine[32];
    sprintf(wordCountLine, "\nWord Count: %d", wordCount);
    write(testFd, wordCountLine, strlen(wordCountLine));

    close(testFd);

    return 0;
}