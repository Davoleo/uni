#include <stdio.h>
#include <string.h>

const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int charToValueShift = 54;
const int numToValueshift = 48;

int customToDecimal(const char number[], int base);
void decimalToCustom(int decimal, int base, char* converted[]);

int main() {

    int base1;
    char number[256];

    puts("=========================");
    puts("| Number Base Converter |");
    puts("=========================");
    puts("");

    printf("Please input the first base: ");
    scanf("%d", &base1);
    printf("Base: %d \n", base1);

    if (base1 < 2 || base1 > 37) 
    {
        puts("Base can't be smaller than binary or bigger than 37, the program will terminate now");
        system("pause");
        return 0;
    }
    
    if (base1 <= 10)
        printf("You can use digits from 0 to %d to describe your number: ", base1 - 1);
    else
        printf("You can use digits from 0 to 9 and letters from A to %c to describe your number: ", alpha[base1 - 11]);
    
    scanf("%s", number);

    int base2;
    printf("Please insert the base you want to convert your nunber to [2, 37]: ");
    scanf("%d", &base2);

    int decimalNumber = customToDecimal(number, base1);

    printf("Decimal number is: %d", decimalNumber);

    char finalNumber[256] = "";

    decimalToCustom(decimalNumber, base2, &finalNumber);

    printf("The final converted number is: %s", *finalNumber);

    return 0;
}

int customToDecimal(const char number[], int base) 
{
    int decimalSum = 0;

    for (int i = 0; i < strlen(number); i++) 
    {
        if (number[i] <= 57) //the char is a normal digit
        {
            int converted = (number[i] - numToValueshift) * base;
            decimalSum += converted;
        }

        if (number[i] >= 65) //The char is an extended digit from the alpha array
        {
            int converted = (number[i] - charToValueShift) * base;
            decimalSum += converted;
        }
    }

    return decimalSum;
}

void decimalToCustom(int decimal, int base, char* converted[])
{
    puts("se non printo io mi ammazzo");
    int i = 0;

    while(decimal != 0) {

        puts("Appena entrato nella balena");

        int result = decimal % base;

        puts("Dopo aver preso il resto");
        
        if (result > 9) {
            puts("if");
            *converted[i] = alpha[result - 10];
        }
        else {
            puts("else");
            printf("%s", *converted);
            system("pause");
            //*converted[i] = result + numToValueshift;
        }

        puts("Dopo l'if");

        i++;
        decimal /= base;

        puts("I mean, se stampa questo, io sono felice");
    }
}