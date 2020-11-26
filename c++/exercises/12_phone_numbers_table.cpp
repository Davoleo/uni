#include <iostream>
#include <cstring>

struct Contact {
    char name[50];
    char phoneNumber[50];
};

int loadInputs(Contact[]);
void printCString(char[]);

int main() {

    std::cout << "========================" << std::endl;
    std::cout << "|| Phone Number Table ||" << std::endl;
    std::cout << "========================" << std::endl << std::endl;

    Contact contactsTable[100];

    int contactCount = loadInputs(contactsTable);

    std::cout << "Dati inseriti correttamente!" << std::endl << std::endl;

    std::cout << "Scegli un'operazione:" << std::endl;
    std::cout << "1. ricerca il numero di telefono" << std::endl;
    std::cout << "2. ricerca il nome" << std::endl;
    std::cout << "3. stampa l'intera rubrica" << std::endl;
    std::cout << "4. Esci" << std::endl << std::endl;

    int choice = 0;

    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();   
        }

        std::cout << "Operazione? ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Inserisci il nome: ";
            char name[50];
            std::cin.ignore();
            std::cin.getline(name, 50, '\n');
            for (int i = 0; i < contactCount; i++) {
                if (strcmp(contactsTable[i].name, name) == 0)
                    std::cout << "Il numero di telefono di " << name << " e': " << contactsTable[i].phoneNumber << std::endl;
            }
            break;
        
        case 2:
            std::cout << "Inserisci il numero di telefono: ";
            char numb[50];
            std::cin.ignore();
            std::cin.getline(numb, 50, '\n');
            for (int i = 0; i < contactCount; i++) {
                if (strcmp(contactsTable[i].phoneNumber, numb) == 0)
                    std::cout << "Il numero " << numb << " e' di " << contactsTable[i].name << std::endl;
            }
            break;
            
        case 3:
            std::cout << "------------------------" << std::endl;
            for (int i = 0; i < contactCount; i++)
                std::cout << "| " << contactsTable[i].name << " | " << contactsTable[i].phoneNumber << " |" << std::endl;
            std::cout << "------------------------" << std::endl;
            break;
        case 4:
            std::cout << "Breaking the looops..." << std::endl;
            break;
        default:
            std::cout << "Scelta non valida!" << std::endl;
            break;
        }

    } while (choice != 4);

}

int loadInputs(Contact contacts[]) {

    int n = 0;

    while(n < 100) {

        char name[50];
        char number[50];

        std::cout << "Inserisci il nome: ";
        std::cin.getline(name, 50, '\n');

        if (strcmp(name, "stop") == 0)
            return n;

        std::cout << "Inserisci il numero di telefono relativo al contatto: ";
        std::cin.getline(number, 50, '\n');

        Contact contact;
        strcpy(contact.name, name);
        strcpy(contact.phoneNumber, number);
        contacts[n] = contact;
        n++;
    }

    return n;
}