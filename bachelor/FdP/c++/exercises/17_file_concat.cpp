#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_FILENAME_LENGTH = 50;

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

void copyContent(std::ifstream& input, std::ofstream& output) {

    char ch = input.get();

    while (!input.eof()) {
        output.put(ch);
        ch = input.get();
    }

    input.close();
}

int main() {

    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Concatenate Files Content |" << std::endl;
    std::cout << "+---------------------------+" << std::endl << std::endl;

    std::ifstream file1;
    std::ifstream file2;

    char filename1[MAX_FILENAME_LENGTH];
    char filename2[MAX_FILENAME_LENGTH];

    loadFile(file1, filename1);
    loadFile(file2, filename2);

    //filename1 now contains the result filename
    strcat(filename1, "_");
    strcat(filename1, filename2);

    std::ofstream osvaldo;
    osvaldo.open(filename1, std::ios::app);

    copyContent(file1, osvaldo);
    copyContent(file2, osvaldo);

    osvaldo.close();
    std::cout << "File Contatenati successfully" << std::endl;

    system("pause");
    return 0;
}