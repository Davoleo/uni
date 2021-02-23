#include <iostream>

class Date {

private:
    int day;
    int month;
    int year;

    bool validate() {
        //Code...
    }

    void nextDay() {
        //Code...
    }

public:
    bool read() {
        std::cin >> day >> month >> year;
        if (validate()) {
            return true;
        }
        else {
            day = month = year = 0;
            return false;
        }
        
    }

    void print() {
        std::cout << day << '/' << month << '/' << year << std::endl;
    }

    bool compare(Date other) {
        //Code...
    }
};

int main() {

    Date date;
    date.read();
    date.print();

    Date date2;
    date2.read();
    date2.print();

    
    return 0;
}