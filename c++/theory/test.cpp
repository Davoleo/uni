#include <iostream>

using namespace std;

void customGetline(char string[], int max, char delim) {
    int i = 0;
    do {
        char next = cin.get();
        if (next == delim)
            string[i] = '\0';
        string[i] = next;
        next++;
    } 
    while (i < max);
}

bool calcola(int n, int m, int& ris) {
    bool nondivBy0 = (n - m) != 0;

    if (nondivBy0) {
        ris = n / (n - m);
    }

    return nondivBy0;
}

int main() {

    char string[10];

    customGetline(string, 10, '\n');
    return 0;
}