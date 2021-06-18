#include <iostream>
#include <cstring>

struct bundle {
    char c[100];
    double r;
};

void compress(bundle array[], int length, const char* aux, bundle arrayB[], int& bLength) {

    bLength = 0;
    for (int i = 0; i < length; i++) {
        if (aux[i] == '1') {
            arrayB[bLength] = array[i];
            bLength++;
        }
    }
}

int main() {

    const char* c = "101011000101000111111000111010";

    bundle v1[30];
    int arraySize = 0;

    std::cout << "Inserire coppie di stringhe e numeri reali separati da uno spazio ($$$ 0 per terminare)" << std::endl;

    bundle readVal;
    do {
        std::cin >> readVal.c >> readVal.r;

        if (strcmp(readVal.c, "$$$") == 0 && readVal.r == 0.0)
            break;

        v1[arraySize] = readVal;
        arraySize++;
    }
    while (arraySize < 30);

    bundle compressed[30];
    int newLength;
    compress(v1, arraySize, c, compressed, newLength);

    for (int i = 0; i < newLength; i++) {
        std::cout << "Bundle << " << i << ": string -> " << compressed[i].c << " num -> " << compressed[i].r << std::endl;
    }

    return EXIT_SUCCESS;
}