#include <iostream>
#include <cstring>
#include <fstream>

struct palla {
    char s[100];
    float m;
};

int somma_campi(palla array_in[], int length_in, palla array_out[]) {

    int length_out = 0;
    for (int i = 0; i < length_in; i++) {

        palla currentPalla = array_in[i];
        int outIndex = -1;
        for (int j = 0; j < length_out; j++) {
            if (strcmp(currentPalla.s, array_out[j].s) == 0) {
                outIndex = j;
            }
        }

        if (outIndex != -1) {
            array_out[outIndex].m += array_in[i].m;
        }
        else {
            palla newPalla;
            newPalla.m = array_in[i].m;
            strcpy(newPalla.s, array_in[i].s);

            array_out[length_out++] = newPalla;
        }
    }

    return length_out;
}

int main() {

    palla couples[1000];
    int pallaCount = 0;

    std::cout << "Inserire coppie di stringhe e numeri reali separati da spazio: " << std::endl;
    do {
        palla zhomasPalla;
        std::cin >> zhomasPalla.s >> zhomasPalla.m;

        if (strcmp(zhomasPalla.s, "$$$") == 0 && zhomasPalla.m == 0) 
            break;
        
        couples[pallaCount] = zhomasPalla;
        pallaCount++;
    }
    while(pallaCount <= 1000);

    palla processedCouples[1000];
    int newPallaCount = somma_campi(couples, pallaCount, processedCouples);

    std::ofstream foutput;
    foutput.open("risultati.txt");

    for (int i = 0; i < newPallaCount; i++) {
        foutput << processedCouples[i].s << ' ' << processedCouples[i].m << std::endl;
    }

    return EXIT_SUCCESS;
}