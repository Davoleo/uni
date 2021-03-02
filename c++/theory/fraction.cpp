#include <iostream>

//Example ADT
class fraction {
private:
    //numerator
    int n;
    //denominator
    int d;

public:
    fraction() {
        n = 0;
        d = 1;
    }

    //explicit
    fraction(int n) {
        this->n = n;
        d = 1;
    }

    fraction(int n, int d) {
        this->n = n;

        if(d == 0) {
            std::cout << "ERROR: Denominatore Nullo!" << std::endl;
            this->d = 1;
        }
        else
            this->d = d;
    }

    void print() {
        std::cout << n << '/' << d;
    }

    //TODO WIP
    void read(std::istream& src) {
        char separator;

        std::cout << "Inserisci una frazione (formato: n/d):";
        src >> n;
        src >> separator;
        src >> d;

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

    fraction operator+ (fraction other) {
        return sum(other);
    }

    fraction operator+(int other) {
        return sum(fraction(other));
    }

    bool operator>(fraction other) {
        return this->n * other.d > this->d * other.n;
    }
};

using namespace std;

int main() {
    fraction a = fraction(2, 3);
    a.read(cin);
    a.print();

    fraction* frac = new fraction(2, 3);
    frac->print();

    //Chained Calls and anonymous object initialization
    fraction(1000, 3920).sum(fraction(100, 328)).print();
    return 0;
}