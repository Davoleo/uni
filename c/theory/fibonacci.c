#include <stdio.h>
#include <math.h>

//Algoritmo Ricorsivo
//è molto meno efficiente ed efficacie ma è precisa
int fibonacci1(int n) {
    if (n <= 0)
        return -1;

    if (n < 3)
        return 1;

    return fibonacci1(n - 1) + fibonacci1(n - 2);
}

//Con sezione aurea
//è molto più efficiente ed efficacie ma è imprecisa
double fibonacci2(int n) {
    double f;

    if (n <= 0)
        return 0;

    f = sqrt(5);

    return (pow((1 + f) / 2, n) - pow((1 - f) / 2, n)) / f;
}

//Algoritmo Iterativo con array (numero di celle di memoria lineari)
int fibonacci3(int n) {
    if (n <= 0)
        return 0;

    if (n <= 2)
        return 1;

    //Puoi solo farlo con compilatori C recenti
    int fib[n];

    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    return fib[n - 1];
}

//Algoritmo Iterativo (numero di celle di memoria K costante)
int fibonacci4(int n) {
    if (n <= 0)
        return 0;

    if (n <= 2)
        return 1;

    int base1 = 1;
    int base2 = 1;
    int fib;

    for (int i = 2; i < n; i++)
    {
        fib = base1 + base2;
        base1 = base2;
        base2 = fib;
    }

    return base2;
}

int fibonacci5(int n) {
    if (n <= 0)
        return 0;

    if (n <= 2)
        return 1;

    int mat[2][2];

    mat[0][0] = mat[0][1] = mat[1][0] = 1;

    //TODO

    return mat[0][0];
}

int fibonacci6(int n) {
    //TODO
}

int main() {
    const int n = 40;

    printf("Fibonacci con Ricorsione      | n=%d: %d\n", n, fibonacci1(n));
    printf("Fibonacci con Sezione Aurea   | n=%d: %f\n", n, fibonacci2(n));
    printf("Fibonacci iterativo con array | n=%d: %d\n", n, fibonacci3(n));
    printf("Fibonacci iterativo           | n=%d: %d\n", n, fibonacci4(n));
    return 0;
}