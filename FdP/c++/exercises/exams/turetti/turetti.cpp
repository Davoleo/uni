#include <iostream>
#include <fstream>

struct llist {
    int dat;
    struct llist* next;
};

int main() {

    llist* arr[50] = {nullptr};

    std::ifstream finput;
    char filename[100];

    std::cout << "Inserisci il nome del file: ";
    do
    {
        std::cin.getline(filename, 100, '\n');
        fflush(stdout);
        finput.open(filename);
    }
    while(finput.fail());

    while (!finput.eof()) {
        int listId;
        int dat;
        finput >> listId >> dat;

        if (finput.fail() || listId > 49 || listId < 0) {
            std::cout << filename << " contiene dati non validi!" << std::endl;
            return EXIT_FAILURE;
        }

        llist* node = arr[listId];
        if (node == nullptr) {
            node = new llist();
            node->dat = dat;
            node->next = nullptr;
            arr[listId] = node;
        }
        else {
            llist* newNode = new llist();
            newNode->dat = dat;
            newNode->next = node;
            arr[listId] = newNode;
        }
    }

    for (int i = 0; i < 50; i++) {
        int count = 0;
        llist* node = arr[i];
        while (node != nullptr) {
            count++;
            node = node->next;
        }

        std::cout << "Lista " << i << ": " << count << std::endl;
    }

    return EXIT_SUCCESS;
}