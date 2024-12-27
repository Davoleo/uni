#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Tipo funzione che prende un double e ritorna un double
typedef double (*double_function)(double);

double bisection(double_function fun, double a, double b, double epsilon) {
    if (epsilon <= 0)
        return -1;

    if (a >= b)
        return -1;

    if (fun == NULL)
        return -1;

    double xm = (a+b)/2;
    double ym = g(xm);

    while (fabs(ym) >= epsilon) {
        if (ym * fun(a) < 0) {
            b = xm;
        }
        else
            a = xm;

        xm = (a+b)/2;
        ym = g(xm);
    }
        
}

double f(double x) {
    return pow(3, x);
}

int main(void) {


    //1 * 10 ^ -9
    double x = bisection(f, 0, 2, 1E-9);


    return EXIT_SUCCESS;
}