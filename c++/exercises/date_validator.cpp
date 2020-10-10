#include <iostream>

int main() 
{
    int day;
    int month;
    int year;

    std::cout << "==================" << std::endl;
    std::cout << "| Date Validator |" << std::endl;
    std::cout << "==================" << std::endl << std::endl;

    std::cout << "Inserisci una data in formato \"GG MM AAAA\": ";
    std::cin >> day >> month >> year;

    bool valid = false;

    //Year must be greater than 0
    //Month must be in the range [1, 12]
    //Day must be in the range [1, 31]
    if (year < 0 || month > 12 || month < 1 || day < 1 || day > 31)
    {
        std::cout << "Data Errata\n";
        system("pause");
        return 0;
    }
    
    //February
    if (month == 2) 
    {
        //Leap Year (February has 29 days)
        if (year % 4 == 0 || year % 400 == 0)
        {
            if (day > 0 && day <= 29)
                valid = true;
        } 
        else {
            if (day > 0 && day <= 28)
                valid = true;   
        }
    }//September | November | April | June
    else if (month == 11 || month == 4 || month == 6 || month == 9)
    {
        if (day > 0 && day <= 30)
            valid = true;
    }//All the other months
    else {
        if (day > 0 && day <= 31)
            valid = true;
    }
    
    if (valid)
        std::cout << "Data Corretta" << std::endl;
    else
        std::cout << "Data Errata" << std::endl;

    system("pause");
    return 0;
}