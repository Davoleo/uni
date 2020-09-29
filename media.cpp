//Direttiva di Preprocessing
//Il programma usa funzioni predefinite per l'input e l'output definite nel file iostream.h
#include <iostream>

/*
Commento multilinea

Parole chiave:
using,
namespace,
int,
float,
return,
main
*/

//Commento a linea singola

//Convenzioni per scrittura programmi a mano:
// - Sottolineatura delle parole chiave
// - Indentatura del codice

//Nomi di variabili non riconosciute devono essere cercati nello spazio dei nomi standard
//Standard (= std) - (i.e. cout, cin)
using namespace std;

//Contiene il programma principale - ed è l'entry point del programma
// () -> parentesi vuote -> no parametri
int main() {
    //; = terminatore di dichiarazioni e statement
    //Dichiarazione (dati)
    //+
    //statements (azioni)

    //Dichiarazione di 3 variabili intere di nome n1, n2 ed n3
    int n1, n2, n3;
    //Dichiarazione di 1 variabile reale/razionale di nome average
    float average;

    //cout = nome dello stream di output std
    // << = operatore di output
    // "" = costante di stringa
    // endl = End of Line: Genera una newline
    cout << "Scrivi 3 numeri interi: " << endl;

    //Istruzione di input
    //cin nome stream di input (= tastiera) - può essere concatenato
    //NB: legge da cin valori del tipo delle variabili passate - Legge il primo poi passa al successivo, se non c'è nessun valore presente aspetta
    cin >> x >> y >> z;

    // = operatore di assegnamento
    // a destra c'è un espressione composta
    // dopo averla valutata si assegna ad 'average'
    // / = operatore di divisione (se gli input sono tutti e due interi il risultato della divisione sarà troncato ad intero)
    average = (x + y + z) / 3.0;

    cout << "La media è: " << average << endl;

    //no errori
    return 0;
}