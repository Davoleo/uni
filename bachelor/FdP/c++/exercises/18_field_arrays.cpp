#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_FILENAME_LENGTH = 50;

struct Data {
    int f1;
    float f2;
};

void loadFile(std::ifstream& stream, char filename[MAX_FILENAME_LENGTH]) {
    do {
        if (stream.fail()) {
            std::cout << "Errore nell'apertura del file! riprovare" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        
        stream.clear();

        std::cout << "Nome del File: ";

        std::cin.getline(filename, MAX_FILENAME_LENGTH, '\n');
        stream.open(filename);
    } while (stream.fail() || std::cin.fail());
}

void printFieldArray(Data datarray[1000], const int length, std::ofstream& outStream, int field, char filename[50]) {
    
    //Build the output filename
    char outName[100];
    std::sprintf(outName, "campi%d", field);
    strcat(outName, "_di_");
    strcat(outName, filename);

    outStream.open(outName);

    for (int i = 0; i < length; i++) {
        Data entry = datarray[i];

        if (field == 1) {
            outStream << entry.f1 << std::endl;
        }
        else if (field == 2) {
            outStream << entry.f2 << std::endl;
        }
    }

    outStream.close();
}

int main() {

    std::cout << "+----------------------+" << std::endl;
    std::cout << "| Fields Array Printer |" << std::endl;
    std::cout << "+----------------------+" << std::endl << std::endl;

    std::ifstream input;
    char filename[MAX_FILENAME_LENGTH];
    
    loadFile(input, filename);

    Data datarray[1000];
    int count = 0;
    while (!input.eof()) {
        int f1;
        input >> f1;
        float f2;
        input >> f2;

        datarray[count] = { f1, f2 };
        count++;
    }

    std::ofstream outputStream;

    printFieldArray(datarray, count, outputStream, 1, filename);
    printFieldArray(datarray, count, outputStream, 2, filename);

    system("pause");
    return 0;
}