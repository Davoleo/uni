#include "utilfunctions.h"

static inline short isBaseValid(int base) 
{
    if (base < 2 || base > 37) 
    {
        puts("Base can't be smaller than binary or bigger than 37, the program will terminate now");
        return 0;
    }

    return 1;
}

int main() {

    int base1;
    char number[256];

    puts("+-----------------------+");
    puts("| Number Base Converter |");
    puts("+-----------------------+");
    puts("");

    printf("Please input the first base: ");
    scanf("%d", &base1);
    printf("Base: %d \n", base1);

    if (!isBaseValid(base1))
    {
        system("pause");
        return 0;
    }
    
    if (base1 <= 10)
        printf("You can use digits from 0 to %d to describe your number: ", base1 - 1);
    else
        printf("You can use digits from 0 to 9 and letters from A to %c to describe your number: ", alpha[base1 - 11]);

    scanf("%s", number);

    if (base1 <= 10) {
        for (int i = 0; i < strlen(number); i++) {
            if (isalpha(number[i])) {
                puts("Illegal characters are present in the number literal, the program will terminate now");
                system("pause");
                return 0;
            }
        }
    }

    int base2;
    printf("Please insert the base you want to convert your number to [2, 37]: ");
    scanf("%d", &base2);
    
    if (!isBaseValid(base2))
    {
        system("pause");
        return 0;
    }

    if (base1 == base2) {
        printf("The final number is: %s\n", number);
        system("pause");
        return 0;
    }
    double decimalNumber;
    
    if (base1 != 10) {
        if(strstr(number, ".") == NULL)
            decimalNumber = halfCustomToDecimal(number, base1, 1);
        else
            decimalNumber = floatCustomToDecimal(number, base1);
    }
    else {
        decimalNumber = atof(number);
    }

    printf("Decimal number is: %f\n", decimalNumber);

    if (base2 != 10)
    {
        char finalNumber[128] = "";

        const int intPartLength = decimalToCustom((int) decimalNumber, base2, &finalNumber);
        finalNumber[intPartLength] = '.';
        const int floatingPartLength = floatDecimalToCustom(decimalNumber - (int) decimalNumber, base2, &finalNumber, intPartLength + 1);
        
        //Reverse the int part
        for(int r = 0; r < (intPartLength / 2); r++) 
        {
            char temp = finalNumber[r];
            finalNumber[r] = finalNumber[intPartLength - r - 1];
            finalNumber[intPartLength - r - 1] = temp;
        }

        char truncatedFinalNumber[128];
        memcpy(truncatedFinalNumber, &finalNumber[0], intPartLength + 7);
        truncatedFinalNumber[intPartLength + 7] = '\0';

        printf("The final converted number is: %s\n", truncatedFinalNumber);
    }

    system("pause");

    return 0;
}