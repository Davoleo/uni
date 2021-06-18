#include <iostream>
#include <cstring>

struct Element {
    char name[50];
    int count;
};

void edit(Element[], int&, char[]);

int main() {

    std::cout << "+-----------------+" << std::endl;
    std::cout << "| Update Function |" << std::endl;
    std::cout << "+-----------------+" << std::endl << std::endl;

    std::cout << "Inserisci una frase terminata da invio (max 100 parole): " << std::endl;

    Element elems[100];

    int length = 0;
    
    while (std::cin.peek() != '\n' && length <= 100) {
        char word[50];
        std::cin >> word;
        edit(elems, length, word);
    }

    std::cout << "\nNumero di occorenze di ogni parola nel testo" << std::endl;

    for (int i = 0; i < length; i++)
        std::cout << elems[i].name << ": " << elems[i].count << " volte" << std::endl;

    system("pause");
    return 0;
}

void edit(Element elements[], int& lastIndex, char name[]) {
    for (int i = 0; i < lastIndex; i++) {
        if (strcmp(elements[i].name, name) == 0) {
            elements[i].count++;
            return;
        }
    }

    if (lastIndex < 100) {
        strcpy(elements[lastIndex].name, name);
        elements[lastIndex].count = 1;
        lastIndex++;
    }
}