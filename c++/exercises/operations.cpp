#include <iostream>

int main() {

    std::cout << "+-----------------+" << std::endl;
    std::cout << "| Menu Operazioni |" << std::endl;
    std::cout << "+-----------------+" << std::endl << std::endl;

    std::cout << "Scegli una delle seguenti operazioni dal menu: "  << std::endl;
    std::cout << "\t1) Valore Assoluto" << std::endl;
    std::cout << "\t2) Quadrato" << std::endl;
    std::cout << "\t3) Sommatoria" << std::endl;
    std::cout << "\t4) Fattoriale" << std::endl;
    std::cout << "\t5) Esci" << std::endl;

    int choice;

    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }

        std::cout << "La tua scelta: ";
        std::cin >> choice;

        int input;
        int sum = 0;
        int fact = 1;

        switch(choice) {
            case 1:
                std::cout << "Inserisci un numero intero: ";
                std::cin >> input;
                std::cout << "Il valore assoluto di " << input << " e' " << (input < 0 ? -input : input) << std::endl;
                break;
            case 2:
                std::cout << "Inserisci un numero intero: ";
                std::cin >> input;
                std::cout << "Il quadrato di " << input << " e' " << (input * input) << std::endl;
                break;
            case 3:
                std::cout << "Inserisci un numero intero: ";
                std::cin >> input;
                for (int i = 1; i <= input; i++)
                    sum += i;
                std::cout << "La sommatoria da 1 a " << input << " e' uguale a " << sum << std::endl;
                break;
            case 4:
                std::cout << "Inserisci un numero intero: ";
                std::cin >> input;
                for (int i = 1; i <= input; i++)
                    fact *= i;
                std::cout << "Il fattoriale di " << input << " e' " << fact << std::endl;
                break;
            case 5:
                std::cout << "The software will exit now" << std::endl;
                break;
            default:
                std::cout << "Scelta non valida! - Riprova" << std::endl;
        }

    } while(choice != 5);

    system("pause");
    return 0;
}