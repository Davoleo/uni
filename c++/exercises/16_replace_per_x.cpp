#include <iostream>
#include <fstream>
#include <cstring>

int main() {
    std::cout << "+----------------------+" << std::endl;
    std::cout << "| Replace 'per' -> 'x' |" << std::endl;
    std::cout << "+----------------------+" << std::endl << std::endl;

    std::ifstream inputStream;
    std::cout << "Inserisci il nome del file di input (max 50 caratteri): ";

    char filename[50];
    std::cin.getline(filename, 50);

    inputStream.open(filename);

    if (inputStream.fail()) {
        inputStream.clear();
        inputStream.open(strcat(filename, ".txt"));
    }

    if (inputStream.fail()) {
        std::cout << "Il file specificato non esiste, riavviare il programma e riprovare." << std::endl;
        system("pause");
        return 1;
    }

    std::ofstream outStream;

    char prefixed[strlen(filename) + 7] = "nuovo_";
    strcat(prefixed, filename);
    outStream.open(prefixed);

    int count = 0;

    while (!inputStream.eof()) {
        char readChar = inputStream.get();
        char banane = '\t';
        char mandorle = '\t';

        if (readChar == 'p') {
            banane = inputStream.get();
            if (banane == 'e') {
                mandorle = inputStream.get();
                if (mandorle == 'r') {
                    readChar = 'x';
                    banane = mandorle = '\t';
                    count++;
                }
            }
        }

        outStream.put(readChar);

        if (banane != '\t')
            outStream.put(banane);
        if (mandorle != '\t')
            outStream.put(mandorle);
    }

    std::cout << "\"per\" e' stato sostituito con \"x\" " << count << " volte" << std::endl;
    system("pause");
    return 1;
    
}