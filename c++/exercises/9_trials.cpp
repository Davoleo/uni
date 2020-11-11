#include <iostream>

int main() {
    
    std::cout << "+--------------------+" << std::endl;
    std::cout << "| Competitors Trials |" << std::endl;
    std::cout << "+--------------------+" << std::endl << std::endl;

    int competitors;
    
    std::cout << "Inserisci il numero di concorrenti: ";
    std::cin >> competitors;
    
    while (competitors < 2 || std::cin.fail())
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(128, '\n');
        }
        
        std::cout << "Errore nel dato di input! Riprova: ";
        std::cin >> competitors;
    }

    float firstTrial[competitors];
    float secondTrial[competitors];

    std::cout << "\nPrima Prova: " << std::endl;
    for (int i = 1; i <= competitors; i++) {
        std::cout << "Punteggio concorrente n" << i << ": ";
        std::cin >> firstTrial[i-1];
        while (firstTrial[i-1] > 10 || firstTrial[i-1] < 1 || std::cin.fail()) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(128, '\n');
            }

            std::cout << "Errore nell'input! Riprova l'inserimento: ";
            std::cin >> firstTrial[i-1];
        }
    }

    std::cout << "\nSeconda Prova: " << std::endl;
    for (int i = 1; i <= competitors; i++) {
        std::cout << "Punteggio concorrente n" << i << ": ";
        std::cin >> secondTrial[i-1];
        while (secondTrial[i-1] > 10 || secondTrial[i-1] < 1 || std::cin.fail()) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(128, '\n');
            }

            std::cout << "Errore nell'input! Riprova l'inserimento: ";
            std::cin >> secondTrial[i-1];
        }
    }

    float averageArr[competitors];
    for (int i = 0; i < competitors; i++)
        averageArr[i] = (firstTrial[i] + secondTrial[i]) / 2;

    int winnerIndex = 0;

    //Skipping the first loop directly
    for (int i = 1; i < competitors; i++) {
        if (averageArr[winnerIndex] < averageArr[i]) {
            winnerIndex = i;
        }
    }

    std::cout << "\nIl vincitore e' il concorrente n" << (winnerIndex + 1) << "\nMedia del vincitore: " << averageArr[winnerIndex] << std::endl;
    system("pause");
    return 0;
}