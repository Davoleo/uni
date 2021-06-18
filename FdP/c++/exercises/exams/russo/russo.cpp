#include <iostream>
#include <fstream>
#include <cstring>

float vett_average(int array[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += array[i];
    }

    return (float) sum / length;
}

int main() {

    char filename[100];
    std::ifstream finput;

    std::cout << "Inserisci il nome del file: ";
    do
    {
        std::cin.getline(filename, 100, '\n');
        fflush(stdout);
        finput.open(filename);
    }
    while(finput.fail());

    if (finput.eof()) {
        std::cout << "Errore: Il file è vuoto." << std::endl;
        return EXIT_SUCCESS;
    }


    const char* postfix = "_sopra_la_media";
    int filenameLength = strlen(filename);
    char newFilename[filenameLength + 15];
    bool isBeforeExt = false;

    for (int i = filenameLength - 1; i >= 0; i--) {
        if (!isBeforeExt) {
            newFilename[i + 15] = filename[i];
        }
        else {
            newFilename[i] = filename[i];
        }

        if (filename[i] == '.') {
            isBeforeExt = true;
            for (int j = i, z = 0; z < 15; j++, z++) {
                newFilename[j] = postfix[z];
            }
        }
    }

    int values[1000];
    int count = 0;
    while (!finput.eof()) {
        int readValue;
        finput >> readValue;
        values[count] = readValue;
        count++;
    }

    int average = vett_average(values, count);

    std::ofstream foutput;
    foutput.open(newFilename);

    for (int i = 0; i < count; i++) {
        if (values[i] > average)
            foutput << values[i] << ' ';
    }

    return EXIT_SUCCESS;
}