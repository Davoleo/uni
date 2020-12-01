#include <iostream>

void loadNumber(int&);
int squared(int);
int sum(int);
int factorial(int);

int main() {

    std::cout << "+--------------------+" << std::endl;
    std::cout << "| Menu Operazioni V2 |" << std::endl;
    std::cout << "+--------------------+" << std::endl << std::endl;


    std::cout << "Scegli una delle seguenti operazioni:" << std::endl;
    std::cout << "1. Leggi un numero intero n" << std::endl;
    std::cout << "2. Calcola il quadrato di n" << std::endl;
    std::cout << "3. Calcola la sommatoria da 1 a n (n >= 1)" << std::endl;
    std::cout << "4. Calcola il fattoriale di n (n >= 0)" << std::endl;
    std::cout << "5. Esci" << std::endl;

    int choice = -1;

    int numberWasInput = false;
    int number = 0;

    do {

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }

        std::cout << "Scelta? ";
        std::cin >> choice;

        if (!numberWasInput && (choice > 1 && choice < 5)) {
            std::cout << "Prima devi usare l'operazione 1 per inserire un numero n" << std::endl;
            continue;
        }

        switch (choice) {
            case 1: {
                numberWasInput = true;
                loadNumber(number);
                break;
            }

            case 2: {
                std::cout << "Il quadrato di " << number << " e' " << squared(number) << std::endl;
                break;
            }

            case 3: {
                if (number < 1)
                    std::cout << "Il numero deve essere maggiore o uguale a 1 per poter calcolare la sommatoria" << std::endl;
                else 
                    std::cout << "La sommatoria da 1 a " << number << " e' pari a " << sum(number) << std::endl;
                break;
            }

            case 4: {
                if (number < 0)
                    std::cout << "Il numero deve essere maggiore o uguale a 0 per poter calcolare il fattoriale" << std::endl;
                else 
                    std::cout << "Il fattoriale di " << number << " e' pari a " << factorial(number) << std::endl;
                break;
            }

            case 5: {
                std::cout << "Chiusura in corso . . . " << std::endl;
                break;
            }

            default:
                std::cout << "Scelta non valida!" << std::endl;
        }
    } while (choice != 5);

    return 0;
}

void loadNumber(int& number) {
    std::cout << "Inserisci un numero intero: ";
    std::cin >> number;
}

int squared(int number) {
    return number * number;
}

///Sums numbers from 1 to limit
int sum(int limit) {
    int sum = 0;
    for (int i = 1; i <= limit; i++) {
        sum += i;
    }

    return sum;
}

int factorial(int limit) {
    int fac = 1;
    for (int i = 1; i <= limit; i++) {
        fac *= i;
    }

    return fac;
}