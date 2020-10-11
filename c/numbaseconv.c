#include <stdio.h>
#include <string.h>

const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int charToValueShift = 54;
const int numToValueshift = 48;

int customToDecimal(const char* number, int base);
const char* decimalToCustom(int decimal, int base);

int main() {

    int base1;
    int base2;
    const char* number;

    puts("=========================");
    puts("| Number Base Converter |");
    puts("=========================");
    puts("");

    printf("Please input the first base: ");
    scanf("%i", base1);
    printf("Base: %i\n", base1);
    
    if (base1 < 2 || base1 > 37) 
    {
        puts("Base can't be smaller than binary or bigger than 37, the program will terminate now");
        getchar();
        return 0;
    }
    
    if (base1 <= 10)
        printf("You can use digits from 0 to %i to describe your number", base1 - 1);
    else
        printf("You can use digits from 0 to 9 and letters from A to %c to describe your number", alpha[base1 - 11]);
    
    scanf("%s", number);

    printf("Please insert the base you want to convert your nunber to [2, 37]: ");
    scanf("%s", &base2);

    int decimalNumber = customToDecimal(number, base1);

    const char* finalNumber = decimalToCustom(decimalNumber, base2);

    printf("The final converted number is: %s", finalNumber);

    return 0;
}

int customToDecimal(const char* number, int base) 
{
    int decimalSum = 0;

    for (int i = 0; strlen(number); i++) {
        if (number[i] <= 57) //the char is a normal digit
        {
            int converted = (number[i] - numToValueshift) * base;
            decimalSum += converted;
        }

        if (number[i] >= 65)
        {
            int converted = (number[i] - charToValueShift) * base;
            decimalSum += converted;
        }
    }

    return decimalSum;
}

const char* decimalToCustom(int decimal, int base)
{
    char* converted = "";

    while (decimal != 0) {
        int result = decimal % base;

        if (result > 9)
            strcat(converted, alpha[result - 10]);
        else
            strcat(converted, result);

        decimal /= base;
    }

    return converted;
}