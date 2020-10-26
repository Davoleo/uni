#include <iostream>

//Si può usare arrayLength al posto di 10 ovunque
//Concettualmente molto diverso dalle costanti con nome
#define arrayLength 10;

int main() {

    int array[100];

    for (int i = 0; i < 100; i++) {
        //Adds spaces before every input
        std::cout.width(4);
        std::cout << array[i];
    }

    //---------
    //Esercizio: leggi due sequenze di 10 numeri interi e controlla se sono simmetriche

    //Crea una costante di nome length e di valore 10
    const int length = 10;

    int arrayA[length];
    int arrayB[length];

    std::cout << "Scrivi la prima sequenza di 10 numeri: " << std::endl;
    for(int i = 0; i < length; i++)
        std::cin >> arrayA[i];

    std::cout << "Scrivi la seconda sequenza di 10 numeri: " << std::endl;
    for(int i = 0; i < length; i++)
        std::cin >> arrayB[i];
    
    int index = 0;

    while(index < length && arrayA[index] == arrayB[length - 1 - index]) {
        index++;
    }

    if (index == length)
       std::cout << "Sequenze simmetriche" << std::endl;
    else
        std::cout << "Sequenze non simmetriche" << std::endl;

    return 0;

    //---------
    int n;
    std::cout << "Grandezza CArray? ";
    std::cin >> n;
    int semiDynamicCArray[n];

}