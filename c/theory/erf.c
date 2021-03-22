#include <math.h>
#include <stdlib.h>

double gaussian (double x) {
    return exp(-x * x);
}

double erf(double x) {
    double n = 1E7 * x * x;
    //TODO non ho visto dove fosse rectangles e gaussian sicuro non aveva questi parametri attuali qua
    return M_2_SQRTPI * rectangles(gaussian(0, x, n));
}

int main(void) {
    for (double x = 0; x <= 1; x+= 0.1)
        printf("erf(%f) = %f\n", x, erf(x));

    return EXIT_SUCCESS;
}