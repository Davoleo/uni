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

    //condizione tra le istruzioni
    //La condizionedeve essere specificata 2 volte ergo meno ottimizzato
    //a meno che non si usi lo statement di salto chiamato break che permette di uscire dal loop prima
    do {
        cin >> x;
        if (x < 0 || x > 10) {
            cout << "Numero non valido" << endl;
        }
        else break;
    } while(true);

    do {
        //se cin è in stato failed
        if (cin.fail())
        {
            cout << "Errore, ripeti l'input" << endl;
            //Resetta lo stato a non failed (il dato errato rimane)
            cin.clear();
            cin.ignore(256, '\n');
        } else break;
    } while (true);

    // Risolvi espressioni //

    int num1, num2;
    char op;
    bool error;
    float result;

    cout << "Inserisci un operazione algebrica (senza spazi): ";
    cin >> num1 >> op >> num2;

   /* switch(op) {
        case '+':
        case '-':
        case '*':
        case 'x':
        case '/':
        case ':':
    }*/

    //in questo caso si può anche evitare la specifica del numero di slot
    char vocali[5] = {'a', 'e', 'i', 'o', 'u'};

    float fl = 1;
    double db = 1;

    for (int i = 0; i < 10; i++) {
        fl -= 0.1;
        db -= 0.1;
    }

    cout << "Float: " << fl << endl << "Double: " << db << endl;

    system("pause");

    return 0;

    
}