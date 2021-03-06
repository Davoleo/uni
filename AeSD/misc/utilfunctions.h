#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int charToValueShift = 55;
const int numToValueshift = 48;

// Generic function that converts the given int number to the given base
float halfCustomToDecimal(const char number[], int base, short sign) 
{
    float decimalSum = 0;

    short length = strlen(number);    

    for (int i = 0; i < length; i++) 
    {
        int exp;
        if (sign > 0)
            exp = sign * (length - i - 1);
        else
            exp = sign * (i + 1);

        if (number[i] <= 57) //the char is a normal digit
        {
            float converted = (number[i] - numToValueshift) * pow(base, exp);
            //printf("Numero shiftato: %d\n", (number[i] - numToValueshift));
            decimalSum += converted;
        }

        if (number[i] >= 65) //The char is an extended digit from the alpha array
        {
            float converted = (number[i] - charToValueShift) * pow(base,  exp);
            //printf("Numero shiftato: %d\n", (number[i] - charToValueShift));
            decimalSum += converted;
        }
    }

    return decimalSum;
}

// Uses the above halfCustomToDecimal function one time 
// on the integer part and another time on the decimal part of a floating point number
float floatCustomToDecimal(char number[], int base) 
{
    char* token = strtok(number, ".");
    char* intPart = token;
    token = strtok (NULL, ".");
    char* floatingPart = token;

    int convertedInt = halfCustomToDecimal(intPart, base, 1);

    float convertedFloat = halfCustomToDecimal(floatingPart, base, -1);

    return convertedInt + convertedFloat;
}

//Returns the length of the converted number
int decimalToCustom(int decimal, int base, char (*converted)[])
{
    int index = 0;

    while(decimal != 0) {

        int result = decimal % base;
        //printf("Resto: %d |", result);
        
        if (result > 9) {
            (*converted)[index] = alpha[result - 10];
        }
        else {
            (*converted)[index] = result + numToValueshift;
        }

        index++;
        decimal /= base;
        //printf("Nuovo quoziente: %d\n", decimal);
    }

    return index;
}

int floatDecimalToCustom(double decimal, int base, char (*converted)[], int offset) {

    //printf("\nFloat number passato alla funzione: %f\n", decimal);

    int index = 0;

    while(decimal != 0.0) {

        decimal *= base;
        //the integer part of the multiplied number
        int intPart = decimal;
        // the floating part of the multiplied number became the "decimal"
        decimal -= intPart;
        
        //0.30 * 2 = 0.60 < 1 
        //0.30 * 16 = 4.8 --> 4   0.8

        if (intPart > 9) {
            (*converted)[index + offset] = alpha[intPart - 10];
        }
        else {
            (*converted)[index + offset] = intPart + numToValueshift;
        }

        index++;
    }

    return index;
}
