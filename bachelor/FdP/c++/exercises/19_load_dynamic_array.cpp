#include <iostream>
#include <fstream>

void loadFile(std::ifstream& stream, char filename[64]) {
    do {
        if (stream.fail()) {
            std::cout << "Errore nell'apertura del file! riprovare" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        
        stream.clear();

        std::cout << "Nome del File: ";

        std::cin.getline(filename, 64, '\n');
        stream.open(filename);
    } while (stream.fail() || std::cin.fail());
}

///Extends the array making it double the old length and returns the new length of the array
int extendArray(int*& array, int oldLength) {
    int* temp = new int[oldLength * 2];
    for (int i = 0; i < oldLength; i++)
        temp[i] = array[i];
    delete[] array;
    array = temp;
    return oldLength * 2;
}


int main() {

    std::cout << "+----------------------+" << std::endl;
    std::cout << "| Dynamic Array Loader |" << std::endl;
    std::cout << "+----------------------+" << std::endl << std::endl;

    char filename[64];
    std::ifstream inputStream;

    loadFile(inputStream, filename);
    int maxLength = 4;
    int counter = 0;
    int* array = new int[maxLength];

    while(!inputStream.fail()) {
        if (counter > maxLength)
            maxLength = extendArray(array, maxLength);
        
        inputStream >> array[counter++];
    }

    if (!inputStream.eof()) {
        std::cout << "I contenuti del file sono corrotti!" << std::endl;
        std::cout << "Riprovare dopo aver aggiustato il file" << std::endl;
        system("pause");
        return 0;
    }

    int maxValue = array[0];
    for (int i = 1; i < counter; i++) {
        if (array[i] > maxValue) {
            maxValue = array[i];
        }
    }

    std::cout << "Il valore massimo tra i numeri caricati nell'array e': " << maxValue << std::endl;

    system("pause");
    return 0;
}

