#include <stdlib.h>
#include <stdio.h>

int main() {

    static const int INVALID_SEQUENCE = -3;

    //Initial value
    int input = -2;
    int prevInput = -2;

    do {    
        int readVars = scanf("%d", &input);
        if (readVars != 1) {
            printf("Input non valido, ripetere.\n");
            continue;
        }

        if (input < -1 || input > 3 || input == 0) {
            printf("Input non valido, ripetere\n");
            continue;
        }

        if (input > prevInput) {
            input = INVALID_SEQUENCE;
            break;
        }

        switch (input) {
            case 1:
                prevInput = 1;
                printf("Stato 3: è stato inserito un 1\n");
                break;
            case 2:
                prevInput = 2;
                printf("Stato 2: è stato inserito un 2\n");
                break;
            case 3:
                prevInput = 3;
                printf("Stato 3: è stato inserito un 3\n");
                break;
        }
    } 
    while(input != -1);

    if (input == -1)
        printf("Stato 4 -> FINE - Sequenza Accettata\n");
    else
        printf("Stato 4 -> FINE - Sequenza non accettata\n");

    return EXIT_SUCCESS;
    
}