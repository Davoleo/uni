#include <iostream>
#include <cstring>
#include <fstream>

void trim_blanks(char string[]) {
    int length = strlen(string);

    for (int i = 0; i < length; i++) {
        if (string[i] == ' ') {
            //Minore e uguale così sposto anche il terminatore di stringhe
            for (int j = i + 1; j <= length; j++) {
                string[j - 1] = string[j];
            }
        }
    }
}

int main() {

    char filename[64];

    //Primo ciclo di lettura (nessun fallimento)
    std::cout << "Inserisci il nome del file di input: ";
    std::cin.getline(filename, 64, '\n');

    //Setup della file input stream
    std::ifstream inputStream;
    inputStream.open(filename);

    std::ofstream outputStream;
    char newFile[17 + strlen(filename) + 1] = "copia_ridotta_di_";
    outputStream.open(strcat(newFile, filename));

    //Controllo se lo stream è in stato di failure (ciclo di lettura dopo il primo fallimento)
    while (inputStream.fail()) {
        std::cout << "Nome del file non valido!" << std::endl;

        std::cout << "Inserisci il nome del file di input: ";
        std::cin.getline(filename, 64, '\n');

        //Apro il file
        inputStream.open(filename);
    }

    while (!inputStream.eof()) {
        char line[100];
        inputStream.getline(line, 100, '\n');

        std::cout << "Vuoi salvare la stringa " << line << " in un nuovo file? (s/n)" << std::endl;

        char answer;
        do {
            if (std::cin.fail()) {
                std::cout << "Carattere invalido, ridare input." << std::endl;
                std::cin.clear();
            }

            answer = std::cin.get();
            //std::cout << "the answer: " << answer << std::endl;
        } while (answer != 's' && answer != 'n');

        if (answer == 's') {
            trim_blanks(line);
            outputStream << line << std::endl;
        }
        else if (answer == 'n') {
            continue;
        }
        
    }

    inputStream.close();
    outputStream.close();
    
    return EXIT_SUCCESS;
}