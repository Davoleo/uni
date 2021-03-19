#include <iostream>

//Example ADT
class fraction {
private:
    //numerator
    int n;
    //denominator
    int d;
    
    bool validate();

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
            throw 1;
        }
        else
            this->d = d;
    }

    //Copy constructor - Default behaviour per la classe fraction
    fraction(const fraction& original) {
        this->n = original.n;
        this->d = original.d;
    }

    ~fraction() {
        std::cout << "una frazione sta morendo..." << std::endl;
    }

    void print(std::ostream& out) const {
        out << n << '/' << d;
    }

    //TODO WIP
    void read(std::istream& src) {
        char separator;

        std::cout << "Inserisci una frazione (formato: n/d):";
        src >> n;
        src >> separator;
        src >> d;

        if (src.fail())
            throw -1;

        if (d == 0)
            throw 1;
        
        if (separator != '/')
            throw 0;
    }

    fraction sum(fraction other) const {
        fraction result;
        
        //Compute the minimum common denominator
        int mcd = d * other.d;
        result.d = mcd;
        result.n = n * other.d + other.n * d;

        return result;        
    }

    fraction operator+ (fraction other) const {
        return sum(other);
    }

    fraction operator+(int other) const {
        return sum(fraction(other));
    }

    bool operator>(fraction other) {
        return this->n * other.d > this->d * other.n;
    }

    int get_num() {
        return this->n;
    }

    int get_den() {
        return this->d;
    }

    void set_num(int num) {
        this->n = num;
        return;
    }

    void set_den(int den) {
        if (den == 0) {
            throw 1;
        }
        else 
            this->d = den;
        return;
    }

    // Comportamento di default dell'operatore per la classe fraction
    //fraction& operator=(const fraction& other) {   
    //    this->n = other.n;
    //    this->d = other.d;
    //    return *this;
    //}

    //Dichiarate nella classe ma definite fuori (permettono di non usare i getter e i setter)
    friend ostream& operator<<(ostream&, fraction);
    friend istream& operator>>(istream&, fraction);
};

using namespace std;

ostream& operator<<(ostream& out, const fraction fraction) {
    fraction.print(out);
    return out;
}

istream& operator>>(istream& in, fraction& fraction) {
    fraction.read(in);
    return in;
}

bool fraction::validate() {
    return true;
}

int main() {
    fraction a = fraction(2, 3);
    a.read(cin);
    a.print(cout);

    fraction* frac = new fraction(2, 3);
    frac->print(cout);

    //Chained Calls and anonymous object initialization
    fraction(1000, 3920).sum(fraction(100, 328)).print(cout);

    try {
        fraction exc = fraction(1, 0);
    }
    catch (int x) {
        if (x == 1)
            std::cout << "ERROR: Denominatore Nullo!" << std::endl;
        else if (x == 0) {
            std::cout << "ERROR: Separatore Invalido!" << std::endl;
        }
        else {
            std::cout << "ERROR: Codice errore imprevisto!" << std::endl;
        }
    }
    //Will catch any exception
    catch (...) {
        std::cout << "Eccezione non prevista" << std::endl;
    }
    return 0;
}