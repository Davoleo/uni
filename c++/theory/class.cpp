#include <iostream>

class date {

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

    bool equals(date other) {
        return year == other.year && month == other.month && day == other.day;
    }
};

bool operator==(date date1, date date2) {
    return date1.equals(date2);
}

int main() {

    date dat;
    dat.read();
    dat.print();

    date dat2;
    dat2.read();
    dat2.print();
    //std::cin è di tipo std::istream ed è più generico di std::ifstream
    
    return 0;
}