#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int charToValueShift = 54;
const int numToValueshift = 48;

static inline short isBaseValid(int base) 
{
    if (base < 2 || base > 37) 
    {
        puts("Base can't be smaller than binary or bigger than 37, the program will terminate now");
        return 0;
    }

    return 1;
}

int customToDecimal(const char number[], int base);
void decimalToCustom(int decimal, int base, char (*converted)[]);

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

    int decimalNumber;

    if (base1 != 10) {
        decimalNumber = customToDecimal(number, base1);
    }
    else {
        decimalNumber = atoi(number);
    }

    printf("Decimal number is: %d\n", decimalNumber);

    if (base2 != 10)
    {
        char finalNumber[256] = "";

        decimalToCustom(decimalNumber, base2, &finalNumber);
        printf("The final converted number is: %s\n", finalNumber);
    }

    system("pause");

    return 0;
}

int customToDecimal(const char number[], int base) 
{
    int decimalSum = 0;

    short length = strlen(number);

    for (int i = 0; i < length; i++) 
    {
        if (number[i] <= 57) //the char is a normal digit
        {
            int converted = (number[i] - numToValueshift) * pow(base, length - i - 1);
            decimalSum += converted;
        }

        if (number[i] >= 65) //The char is an extended digit from the alpha array
        {
            int converted = (number[i] - charToValueShift) * pow(base, length - i - 1);
            decimalSum += converted;
        }
    }

    return decimalSum;
}

void decimalToCustom(int decimal, int base, char (*converted)[])
{
    int i = 0;

    while(decimal != 0) {

        int result = decimal % base;
        printf("Resto: %d\n", result);
        
        if (result > 9) {
            (*converted)[i] = alpha[result - 10];
        }
        else {
            (*converted)[i] = result + numToValueshift;
        }

        i++;
        decimal /= base;
        printf("Nuovo quoziente: %d\n", decimal);
        system("pause");
    }
}
