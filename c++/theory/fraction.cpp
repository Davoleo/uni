#include <iostream>

//Example ADT
class fraction {
private:
    //numerator
    int n;
    //denominator
    int d;

public:
    void print() {
        std::cout << n << '/' << d;
    }

    //TODO WIP
    void read() {
        char separator;

        std::cout << "Inserisci una frazione (formato: n/d):";
        std::cin >> n;
        std::cin >> separator;
        std::cin >> d;

        if (d == 0) {
            std::cout << "ERROR: Denominatore Nullo!" << std::endl;
            d = 1;
        }

        if (separator != '/')
            std::cout << "WARNING: Separatore Invalido!" << std::endl;
    }

    fraction sum(fraction other) {
        fraction result;
        
        //Compute the minimum common denominator
        int mcd = d * other.d;
        result.d = mcd;
        result.n = n * other.d + other.n * d;

        return result;        
    }

};

using namespace std;

int main() {
    fraction a;
    a.read();
    a.print();
}