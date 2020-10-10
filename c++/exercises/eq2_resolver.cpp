#include <iostream>
#include <cmath>

int main() {

    float a, b, c;

    std::cout << "=====================" << std::endl;
    std::cout << "| Equation Resolver |" << std::endl;
    std::cout << "=====================" << std::endl << std::endl;

    std::cout << "Risoluzione dell'equazione di II grado a x^2 + b x + c = 0" << std::endl;
    std::cout << "Inserisci i valori dei coefficienti a, b e c: ";

    std::cin >> a >> b >> c;

    float delta = pow(b, 2) - (4 * a * c);

    if (delta < 0)
    {
        std::cout << "Discriminante Negativa!" << std::endl;
        system("pause");
        return 0;
    }
    

    float x1 = (-b + sqrt(delta)) / (2 * a);
    float x2 = (-b - sqrt(delta)) / (2 * a);

    if (delta == 0)
    {
        std::cout << "x_1 = x_2 = " << x1 << std::endl;
    }
    else {
        std::cout << "x_1 = " << x1 << std::endl;
        std::cout << "x_2 = " << x2 << std::endl;
    }

    system("pause");
    return 0;
}