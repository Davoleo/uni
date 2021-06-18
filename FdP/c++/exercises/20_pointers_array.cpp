#include <iostream>

int main() {

    std::cout << "+----------------+" << std::endl;
    std::cout << "| Pointers Array |" << std::endl;
    std::cout << "+----------------+" << std::endl << std::endl;

    std::cout << "Inserisci una sequenza di numeri positivi (negativo per terminare):" << std::endl;
    int* array[1000] = {};
    int num;
    int allocated = 0;
    int counter = 0;
    
    std::cin >> num;

    while(num >= 0) {
        bool found = false;
        for (int i = 0; i < counter; i++) {
            //If the deferenced value in the array is equal to the input number
            if (*array[i] == num) {
                //Assign the old address to the new array cell
                array[counter] = array[i];
                counter++;
                found = true;
                break;
            }
        }

        if (!found) {
            array[counter++] = new int(num);
            allocated++;
        }

        std::cin >> num;
    }

    std::cout << "Numero di variabili allocate: " << allocated << std::endl;
    std::cout << "Sequenza Memorizzata: ";
    for (int i = 0; i < counter; i++)
        std::cout << *array[i] << " ";
    std::cout << std::endl;

    system("pause");
    return 0;
}