#include <iostream>
class Orario {
private:
    int hours;
    int minutes;
    int seconds;

bool validate() {
    if (hours < 0 || hours >= 24) {
        std::cout << "Errore Convalida Orario: Le ore sono fuori dal range consentito" << std::endl;
        this->hours = 0;
    }

    if (minutes < 0 || minutes >= 60) {
        std::cout << "Errore Convalida Orario: I minuti sono fuori dal range consentito" << std::endl;
        this->minutes = 0;
    }

    if (seconds < 0 || seconds >= 60) {
        std::cout << "Errore Convalida Orario: I secondi sono fuori dal range consentito" << std::endl;
        this->seconds = 0;
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

        validate();
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

    int to_second() {
        int hToS = this->hours * 60 * 60;
        int mToS = this->minutes * 60;
        return hToS + mToS + seconds;
    }

    //Operators
    bool operator==(Orario other) {
        return this->hours == other.hours && this->minutes == other.minutes && this->seconds == other.seconds;
    }

    Orario operator+(Orario other) {
        int newSecs = this->seconds + other.seconds;
        int newMins = this->minutes + other.minutes;
        int newHours = this->hours + other.hours;

        if (int deltaSec = (newSecs - 60) >= 0) {
            newSecs = deltaSec;
            newMins++;
        }

        if (int deltaMin = (newMins - 60) >= 0) {
            newMins = deltaMin;
            newHours++;
        }

        if (newHours > 23)
            newHours -= 23;

        return Orario(this->hours + other.hours, this->minutes + other.minutes, this->seconds + other.seconds);
    }

    Orario operator+(int secondsToAdd) {
        Orario other = Orario(secondsToAdd);
        return *this + other;
    }

    bool operator<(Orario other) {
        if(this->hours < other.hours)
            return true;
        else if (this->hours == other.hours) {
            if (this->minutes < other.minutes)
                return true;
        }
        else if (this->minutes == other.minutes) {
            if (this->seconds < other.seconds)
                return true;
        }
        else {
            return false;
        }
    }

    std::istream& read(std::istream& stream) {
        do {
            char separator;
            stream >> hours;
            stream.get();
            stream >> minutes;
            stream.get();
            stream >> seconds;
        }
        while (!validate());
        return stream;
    }

    std::ostream& print(std::ostream& stream) {
        return stream << hours << ':' << minutes << ':' << seconds;
    }
};

std::istream& operator>>(std::istream& stream, Orario& time) {
    return time.read(stream);
}

std::ostream& operator<<(std::ostream& stream, Orario& time) {
    return time.print(stream);
}