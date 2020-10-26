#include <iostream>

int main() {

    std::cout << "+------------------+" << std::endl;
    std::cout << "| TRYANGLE builder |" << std::endl;
    std::cout << "+------------------+" << std::endl << std::endl;
    
    std::cout << "NOTE: the word triangle is purposefully mispelled because it's KAKKOI" << std::endl << std::endl;

    int side;
    float floatSide;

    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
        
        std::cout << "Insert the length of the cathetus: ";
        std::cin >> floatSide;
        side = (int) floatSide;
        
    } while(std::cin.fail() || side <= 0 || floatSide != side);

    for (int y = 0; y < side; y++) {
        for (int x = 0; x <= y; x++) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }

    system("pause");
    return 0;
}