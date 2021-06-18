#include <iostream>

struct ArrayLengths {
    int negativeArrLen;
    int positiveArrLen;
};

ArrayLengths separate(int[], int, int[], int[]);

int main() {

    std::cout << "+----------------------------+" << std::endl;
    std::cout << "| Separa Positivi e Negativi |" << std::endl;
    std::cout << "+----------------------------+" << std::endl << std::endl;

    int oriLength;
    std::cout << "Quanti numero vuoi inserire? ";
    std::cin >> oriLength;
    std::cout << std::endl;

    int array[oriLength];

    std::cout << "Inserisci i numeri separati da spazio:" << std::endl;
    
    for (int i = 0; i < oriLength; i++) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(128, '\n');
            std::cout << "Uno dei dati era corrotto! Ripetere l'input: " << std::endl;
            i = 0;
        }

        std::cin >> array[i];
    }

    int negativeNums[oriLength];
    int positiveNums[oriLength];

    ArrayLengths lengths = separate(array, oriLength, negativeNums, positiveNums);

    std::cout << "Numeri negativi: ";
    for (int i = 0; i < lengths.negativeArrLen; i++)
        std::cout << negativeNums[i] << " ";

    std::cout << "\nNumeri positivi: ";
    for (int i = 0; i < lengths.positiveArrLen; i++)
        std::cout << positiveNums[i] << " ";


    std::cout << std::endl;
    system("pause");

    return 0;
}

ArrayLengths separate(int original[], int length, int negativeNums[], int positiveNums[]) {

    int negLen = 0;
    int posLen = 0;

    for (int i = 0; i < length; i++) {
        if (original[i] > 0) {
            positiveNums[posLen++] = original[i];
        }
        else if (original[i] < 0) {
            negativeNums[negLen++] = original[i];
        }
    }

    return {
        negLen,
        posLen
    };
}