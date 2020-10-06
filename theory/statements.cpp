#include <iostream>

//Yeah it's really bad practice I know
using namespace std;

int main() {
    
    //Calcolo del valore assoluto
    int x;
    cin >> x;
    if (x < 0)
        x = -x;
    cout << "Il valore assoluto è" << x << endl;
    return 0;

    //Massimo tra 2 numeri
    int y, max;
    cin >> x;
    cin >> y;
    if (x >= y)
        max = x;
    else
        max = y;
    
    cout << max << endl;
        
}