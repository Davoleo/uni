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

    //---------------------

    const int maxLength = 1000;
    char sentence[maxLength];
    std::cout << "Inserisci una frase (terminata da punto - max 1000 caratteri)...";

    int i = 0;
    char c;

    while (i < maxLength) {
        c = std::cin.get();
        if (c == '.')
            break;
        sentence[i] = c;
    }

    for (int j = i - 1; j >= 0; j--) {
        std::cout.put(sentence[j]);
    }


    const int DAYS = 7;
    const int HOURS = 24;

    float tempMatrix[DAYS][HOURS];

    //Lettura e caricamento della matrice
    for (int day = 0; day < DAYS; i++) 
    {
        for (int hour = 0; hour < HOURS; hour++)
        {
            std::cout << "Inserire un valore di temperatura per il giorno " << day << " all'ora " << hour << ": ";
            std::cin >> tempMatrix[day][hour];
        }
    }

    int subZero = 0;
    for (int day = 0; day < DAYS; i++) 
    {
        for (int hour = 0; hour < HOURS; hour++)
        {
            if (tempMatrix[day][hour] < 0)
            {
                subZero++;
                //Esci dal ciclo più interno
                break;
            }
        }
    }
    cout << "La temperatura è scesa sotto zero in " << subZero << " giorni." << std::endl;


    char nome[32];
    cin >> nome;
}