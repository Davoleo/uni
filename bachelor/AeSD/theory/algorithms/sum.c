#include <stdlib.h>
#include <stdio.h>

//Algoritmo 1 : Costo Lineare
int sum1(int n) {
    if (n <= 0)
        return 0;

    int sum = 0;

    for (int i = 1; i <= n; i++)
        sum += i;

    return sum;
}

//Algoritmo 2 : Costo Costante
int sum2(int n) {
    if (n < 0)
        return 0;
    
    return n * (n + 1) / 2;
}

int main() {

    // I simboli tipo '%d' si chiamano tag
    // %d = tipo intero o convertibile ad intero
    // %f = tipo double o convertibile a double

    // In questo caso i computer sono talmente veloci che la differenza non si vede
    // In termini di efficacia sono uguali in termini di efficienza è molto meglio il secondo

    const int n = 100000;
    int s1 = sum1(n);
    printf("Algoritmo 1: %d\n", s1);
    int s2 = sum2(n);
    printf("Algoritmo 2: %d\n", s2);
    getchar();
    return 0;
}