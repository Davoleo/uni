#include <stdio.h>

//TODO Fix
double pow1(double base, int exp) {
    if (exp < 0)
        return 0;

    if (exp == 0)
        return 1;
    
    if (exp == 1)
        return base;

    double pow = exp;
    for (int i = 2; i < exp; i++)
        pow *= base;
    
    return pow;
}

double pow2(double base, int exp) {
    if (exp < 0)
        return 0;

    if (exp == 0)
        return 1;

    if (exp == 1)
        return base;

    double pow = pow2(base * base, exp / 2);

    if (exp % 2 == 1)
        pow *= base;

    return pow;   
}

int main() {
    const int exp = 19;

    //.3 -> 3 cifre significative dopo la virgola
    double p1 = pow1(3, exp);
    printf("Algoritmo 1: %f.3\n", p1);
    double p2 = pow2(3, exp);
    printf("Algoritmo 2: %f.3\n", p2);

    return 0;
}