#include <iostream>

int main() {

    const float CONVERSION_CONSTANT = 2.54;

    std::cout << "+--------------------------+" << std::endl;
    std::cout << "| Inches <-> cms Converter |" << std::endl;
    std::cout << "+--------------------------+" << std::endl << std::endl;

    int choice;

    do {
        std::cout << "Choose an option: " << std::endl;
        std::cout << "1) Inches --> Centimeters" << std::endl;
        std::cout << "2) Centimeters --> Inches" << std::endl;
        std::cout << "3) Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        float inches;
        float cms;

        switch(choice) {
            case 1:        
                std::cout << "Type the number you want to convert (in inches): ";
                std::cin >> inches;
                cms = inches * CONVERSION_CONSTANT;
                std::cout << inches << "in --> " << cms << "cm" << std::endl;
                break;
            case 2:
                std::cout << "Type the number you want to convert (in centimeters): ";
                std::cin >> cms;
                inches = cms / CONVERSION_CONSTANT;
                std::cout << cms << "cm --> " << inches << "in" << std::endl;
                break;
            case 3: 
                std::cout << "The program will close now" << std::endl;
                break;
            default:
                std::cout << "Invalid Option, please try again" << std::endl;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                }
        }

        std::cout << "============================" << std::endl;

    }while(choice != 3);

    system("pause");

    return 0;
}