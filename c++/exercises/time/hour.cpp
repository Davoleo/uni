#include <iostream>

class Orario {
private:
    int hours;
    int minutes;
    int seconds;

// TODO 
bool validate() {
    if (hours >= 0 && hours < 24) {

    }


    if (minutes >= 0 && minutes < 60) {

    }

    if (seconds >= 0 && seconds < 60) {

    }
}

public:
    Orario() {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
    }

    Orario(int h, int m, int s) {
        this->hours = h;
        this->minutes = m;
        this->seconds = s;

        if (!validate()) {
            std::cout << ""
        }
    }

    Orario(int seconds) {
        this->hours = seconds / 3600;
        seconds %= 3600;
        this->minutes = seconds / 60;
        seconds %= 60;
        this->seconds = seconds;
    }

    int get_ora() {
        return hours;
    }

    int get_minuti() {
        return minutes;
    }

    int get_secondi() {
        return seconds;
    }

    int to_seconds() {
        int hToS = this->hours * 60 * 60;
        int mToS = this->minutes * 60;
        return hToS + mToS + seconds;
    }

    //Operators
    bool operator==(Orario other) {
        return this->hours == other.hours && this->minutes == other.minutes && this->seconds == other.seconds;
    }

    Orario operator+(Orario other) {
        return Orario(this->hours + other.hours, this->minutes + other.minutes, this->seconds + other.seconds);
    }

    Orario operator+(int secondsToAdd) {
        Orario other = Orario(secondsToAdd);
        return *this + other;
    }
}