#include <iostream>
#include <fstream>

struct Data {
    //Corrispondono ai campi per giorno mese e anno della data
    int day;
    int month;
    int year;
};

//Ricerca lineare, se tutti i campi della struct corrispondono a quelle della chiave ritorna true
bool search(Data* array[], int length, Data key) {
    for (int i = 0; i < length; i++) {
        Data* current = array[i];
        if (key.day == current->day && key.month == current->month && key.year == current->year) 
            return true;
    }

    return false;
}

int main() {
    char filename[150];

    //Primo ciclo di lettura (nessun fallimento)
    std::cout << "Inserisci il nome del file di input: ";
    std::cin.getline(filename, 150, '\n');

    //Setup della file input stream
    std::ifstream inputStream;
    inputStream.open(filename);

    //Controllo se lo stream è in stato di failure (ciclo di lettura dopo il primo fallimento)
    while (inputStream.fail()) {
        std::cout << "Nome del file non valido!" << std::endl;

        std::cout << "Inserisci il nome del file di input: ";
        std::cin.getline(filename, 150, '\n');

        //Apro il file
        inputStream.open(filename);
    }

    //Inizializzo un array di puntatori a struct
    Data** dates = new Data*[1000];
    int dateCount = 0;

    //Finché non si raggiunge la END OF FILE
    while (!inputStream.eof()) {

        //Utilizzo l'input tipato per ottenere i dati della struct
        int day, month, year;
        inputStream >> day;
        inputStream >> month;
        inputStream >> year;

        //Controllo se la data non è valida e in caso stampo un messaggio di errore 
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
            std::cout << "La data " << day << '/' << month << '/' << year << " non e' valida!" << std::endl;
            //continua al prossimo passaggio del loop senza inserire la data nell'array
            continue;
        }

        //Inizializzo un oggetto dinamico con 
        Data* date = new Data();
        date->day = day;
        date->month = month;
        date->year = year;

        //Assegna l'oggetto all'ultimo valore del count che poi viene incrementato per side-effect
        dates[dateCount++] = date;
    }

    //Creo l'oggetto chiave da ricercare
    Data key = {15, 8, 1989};
    bool found = search(dates, dateCount, key);

    if (found)
        std::cout << "La data richiesta e' stata trovata!" << std::endl;
    else 
        std::cout << "La data richiesta non e' stata trovata!" << std::endl;

    //Ripulisco la memoria heap precedentemente allocata sia per le struct che per i puntatori
    for (int i = 0; i < dateCount; i++)
        delete dates[i];

    delete[] dates;

    inputStream.close();

    return 0;
}