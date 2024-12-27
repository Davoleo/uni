#include <stdio.h>
#include <stdbool.h>

bool primo(int n) {
    if (n <= 1)
        return false;

    if (n == 2) {
        return true;
    }

    if (n % 2 == 0)
        return false;

    for (int i = 3; i*i < n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

int main(void) {
    int n = 10;

    bool b = primo(n);

    if (b)
        printf("%d e' un numero primo!", n);
    else
        printf("%d non e' un numero primo!", n);

    return 0;
}