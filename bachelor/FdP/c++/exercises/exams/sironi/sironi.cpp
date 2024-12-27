#include <iostream>
#include <cstring>
#include <fstream>

int sottoseq(int array[], int length) {
    
    int maxLength = 0;
    int counter = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] < 0) {
            counter++;
            if (maxLength < counter)
                maxLength = counter;
        }
        else 
            counter = 0;
    }

    return maxLength;
}

int main() {

    char year[4];
    std::cout << "Inserire un anno: ";
    std::cin >> year;

    char month[10];
    std::cout << "Inserire un mese: ";
    std::cin >> month;

    char filename[4 + 10 + 5];
    strcpy(filename, month);
    strcat(filename, year);
    strcat(filename, ".dat");

    std::ifstream finput;
    finput.open(filename);

    if (finput.fail()) {
        std::cout << "Errore: Il file " << filename << " non e' stato trovato!" << std::endl;
        return EXIT_FAILURE;
    }

    int dati[10000];
    int dataCount = 0;
    while (!finput.eof()) {
        int dat;
        finput >> dat;
        dati[dataCount] = dat;
        dataCount++;
    }
    std::cout << "Letto " << dataCount << " numeri dal file " << filename << std::endl;

    int longest = sottoseq(dati, dataCount);
    std::cout << "La sottosequenza di num negativi di lunghezza massima e' di: " << longest << std::endl;

    return EXIT_SUCCESS;
}