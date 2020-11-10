#include <iostream>
#include <cstring>

int main() {

    //str = CString da injectare
    //num = numero di caratteri da estrarre da cin
    //delim = carattere delimitatore di default '\n'
    //std::cin.getline(str, num, delim);

    char stringa[10] = "ciao";
    std::cout << strlen(stringa); //4
    char clone[10];
    strcpy(clone, stringa);

    //strcat(string1, string2);
    //strcmp(string1, string2); //int

    return 0;
}