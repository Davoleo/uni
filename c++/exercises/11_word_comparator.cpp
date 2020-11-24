#include <iostream>
#include <cstring>
#include <cmath>

void printIsPrefix(char[], char[]);

int main() {

    std::cout << "=======================" << std::endl;
    std::cout << "|| String Comparator ||" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;

    while (true) {
        
        char firstWord[100];
        char secondWord[100];

        std::cout << "Inserisci la prima parola: ";
        std::cin.getline(firstWord, 100, '\n');

        if (strcmp(firstWord, "$$$")) {
            std::cout << "Terminato!" << std::endl;
            break;
        }

        std::cout << "Inserisci la seconda parola: ";
        std::cin.getline(secondWord, 100, '\n');

        int result = strcmp(firstWord, secondWord);

        if (result < 0)
            std::cout << "La parola " << firstWord << " precede la parola " << secondWord << std::endl;
        else if (result == 0)
            std::cout << "Le due parole sono uguali" << std::endl;
        else
            std::cout << "La parola " << secondWord << " precede la parola " << firstWord << std::endl;

        int smolLength = std::min(strlen(firstWord) + 1, strlen(secondWord) + 1);
        
        if (strlen(firstWord) < strlen(secondWord))
            printIsPrefix(firstWord, secondWord);
        else 
            printIsPrefix(secondWord, firstWord);
    }

    system("pause");
}

void printIsPrefix(char possiblePrefix[], char containingWord[]) {
    bool isPrefix = true;

    for (int i = 0; i < strlen(possiblePrefix); i++) {
        if (possiblePrefix[i] != containingWord[i]) {
            isPrefix = false;
        }
    }

    if (isPrefix) {
        std::cout << possiblePrefix << " e' un prefisso di " << containingWord << std::endl;
    }
}