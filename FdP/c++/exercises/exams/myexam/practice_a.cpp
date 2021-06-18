#include <iostream>
#include <cstring>
#include <fstream>

/******
 * Author: REDACTED
 * Numero di prova: 21
 ******/


bool Inizio(char str[], int pos) {

    //Se il carattere è in posizione 0 si tratta dell'inizio di una frase
    if (pos == 0) {
        return true;
    }
    //Se il carattere è in posizione 1 non è un inizio di frase
    //Ma non posso nemmeno effettuare il controllo sugli indici perché controllando la presenza della punteggiatura andrei fuori
    //dal range di indici totale della stringa
    else if (pos == 1) {
        return false;
    }
    //Nei restanti casi controllo che nella posizione precedente ci sia una endline o uno spazio e che nella posizione precedente ancora ci sia
    //un segno di punteggiatura tra quelli supportati e nel caso ritorno true altrimenti false
    else if (str[pos - 1] == ' ' || str[pos - 1] == '\n') {
        char punctuation = str[pos - 2];
        if (punctuation == '.' || punctuation == '!' || punctuation == '?') {
            return true;
        }

        return false;
    }

    return false;
}

int main() {

    //nome del file (max 150 caratteri)
    char filename[150];
    std::ifstream finput;

    std::cout << "Inserisci il nome del file: ";
    do
    {
        //Controllo se la stream dei file è in stato di fail e nel caso tolgo la flag di fail e ignoro l'eventuale input rimanente sullo stream
        if (finput.fail()) {
            finput.clear();
            std::cin.ignore(100, '\n');
        }
        //Prendo una linea da std input e provo ad aprire un file con quel nome
        std::cin.getline(filename, 150, '\n');
        finput.open(filename);
    }
    while(finput.fail());

    //Finchè non si raggiunge la End of File
    while (!finput.eof()) {
        //linea del file max 1000 caratteri
        char line[1000];
        finput.getline(line, 1000, '\n');

        int lineLength = strlen(line);
        for (int i = 0; i < lineLength; i++) {

            //Chiamo la funzione Inizio per determinare se l'indice i corrisponde all'inizio di una nuova frase
            if (Inizio(line, i)) {
                //Stampo la posizione dell'inizio della frase in modo che sia basata su index 1 invece che 0
                std::cout << "Inizio frase in pos: " << (i + 1) << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}