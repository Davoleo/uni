#include <iostream>

//Yeah it's really bad practice I know
using namespace std;

int main() {
    
    //Calcolo del valore assoluto
    int x;
    cin >> x;
    if (x < 0) {
        cout << "Il numero dato è negativo" << endl;
        x = -x;
    }
    cout << "Il valore assoluto è: " << x << endl;
    
    //Massimo tra 2 numeri
    int y, max;
    cin >> x;
    cin >> y;
    if (x >= y)
        max = x;
    else
        max = y;
    
    cout << max << endl;

    //Voto 2 Giudizio
    float mark;
    cout << "Scrivi un voto numerico (tra 0 e 10): ";
    cin >> mark;

    if  (mark < 0 || mark > 10)
        cout << "Voto non Valido" << endl;
    else if (mark <= 5)
        cout << "Insufficiente" << endl;
    else if (mark <= 6.5)
        cout << "Sufficiente" << endl;
    else if (mark <= 7.5)
        cout << "Buono" << endl;
    else 
        cout << "Ottimo" << endl;

    
    //While Example
    int i = 1;
    while (i <= 10) {
        cout << i * i << endl;
        i++;
    }

    char c;
    char vocalCount = 0;
    cout << "Inserisci una sequenza di caratteri terminata da '.'" << endl;
    
    cin >> c;
    while(c != '.') {
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            vocalCount++;
        cin >> c;
    }

    cout << "La sequenza contiene " << vocalCount << " vocali" << endl;
    system("pause");

    return 0;
}