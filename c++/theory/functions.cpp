#include <iostream>

//num1, num2 e num3 sono parametri della funzione
//l'int prima dell'identificatore della funzione è il tipo del  risultato
int max(int num1, int num2, int num3) {
    //Variabile locale nella funzione
    int temp;

    if (num1 > num2)
        temp = num1;
    else
        temp = num2;

    if (temp > num3)
        return temp;
    else
        return num3;
}


void increment(int* num) {
    (*num)++;
}

int main() {

    //Chiamata di funzione
    max(4, 6, 2);

    int example = 1;
    int* dynamicVar = new int(1);
    increment(&example);
    increment(dynamicVar);

    std::cout << example << " | " << *dynamicVar << std::endl;  // 2 | 2
    delete dynamicVar;

    int test = int(2);

    system("pause");
    return 0;
}

int fatt(int x) {
    if (x == 0)
        return 1;
    else {
        return fatt(x - 1) * x;
    }
}