#include <iostream>
#include <cstring>
#include <cmath>

void printIsPrefix(char[], char[]);
void printIsSuffix(char[], char[]);

int main() {

    std::cout << "=======================" << std::endl;
    std::cout << "|| String Comparator ||" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;

    while (true) {
        
        char firstWord[100];
        char secondWord[100];

        std::cout << "Inserisci la prima parola: ";
        std::cin.getline(firstWord, 100, '\n');

        if (strcmp(firstWord, "$$$") == 0) {
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

        const int FIRST_LENGTH = strlen(firstWord);
        const int SECOND_LENGTH = strlen(secondWord);

        if (FIRST_LENGTH < SECOND_LENGTH) {
            printIsPrefix(firstWord, secondWord);
            printIsSuffix(firstWord, secondWord);
        }
        else if (FIRST_LENGTH > SECOND_LENGTH) {
            printIsPrefix(secondWord, firstWord);
            printIsSuffix(secondWord, firstWord);
        }

        std::cout << "--------------------------------------------" << std::endl;
    }

    system("pause");
}

void printIsPrefix(char possiblePrefix[], char containingWord[]) {
    for (int i = 0; i < strlen(possiblePrefix); i++) {
        if (possiblePrefix[i] != containingWord[i])
            return;
    }

    std::cout << possiblePrefix << " e' un prefisso di " << containingWord << std::endl;
}

void printIsSuffix(char possibleSuffix[], char containingWord[]) {

    for (int i = 0; i < strlen(possibleSuffix); i++) {
        if (containingWord[strlen(containingWord) -1 -i] != possibleSuffix[strlen(possibleSuffix) -1 -i]) {
            return;
        }
    }

    std::cout << possibleSuffix << " e' un suffisso di " << containingWord << std::endl;
}