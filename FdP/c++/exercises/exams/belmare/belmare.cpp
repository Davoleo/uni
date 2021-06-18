#include <iostream>
#include <cstring>
#include <fstream>

void dividi(char str1[], char str2[]) {
    int length = strlen(str1);

    int length2 = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (str1[i] == '.') {
            //Tagliamo la stringa all'altezza del punto tramite il carattere terminatore
            str1[i] = '\0';
            for (int j = i+1; j < length; j++) {
                str2[length2] = str1[j];
                length2++;
            }
            str2[length2] = '\0';
        }
    }
}

int main() {
    char filename1[100];
    char filename2[100];

    std::cout << "Inserisci i nomi di 2 file separati da 'a capo': " << std::endl;

    std::ifstream finput1;
    std::ifstream finput2;

    do
    {
        std::cin.getline(filename1, 100, '\n');
        fflush(stdout);
        finput1.open(filename1);
    }
    while(finput1.fail());
    
    do
    {
        std::cin.getline(filename2, 100, '\n');
        fflush(stdout);
        finput2.open(filename2);
    }
    while(finput2.fail());

    char ext1[10];
    dividi(filename1, ext1);
    char ext2[10];
    dividi(filename2, ext2);
    
    //std::cout << "Ext1: " << ext1 << " Ext2: " << ext2;
    if (strcmp(ext1, ext2) != 0) {
        std::cout << "Errore: Le estensioni dei 2 file sono diverse";
        return EXIT_FAILURE;
    }

    char output[150];
    strcpy(output, filename1);
    strcat(output, "_");
    strcat(output, filename2);
    strcat(output, ".");
    strcat(output, ext1);

    std::ofstream foutput;
    foutput.open(output);

    char ch = finput1.get();
    while (!finput1.eof()) {
        foutput.put(ch);
        ch = finput1.get();
    }

    ch = finput2.get();
    while (!finput2.eof()) {
        foutput.put(ch);
        ch = finput2.get();
    }

    finput1.close();
    finput2.close();
    foutput.close();

    return EXIT_SUCCESS;
}