#include <iostream>

const int DAYS_IN_A_YEAR = 365;
const int RECORDS_IN_A_DAY = 4;

int loadInputTemperatures(float matrix[][RECORDS_IN_A_DAY]) {
    int days = 0;

    do {
        std::cout << "Inserisci le temperature per il giorno " << days + 1 << " (separate da spazio)" << std::endl;

        for (int rec = 0; rec < RECORDS_IN_A_DAY; rec++) {
            std::cin >> matrix[days][rec];

            if (matrix[days][rec] >= 100)  
                return days;
        }
        days++;
    }
    while (days <= 365);
    return 365;
}

int main() {

    std::cout << "=================================" << std::endl;
    std::cout << "|| Subzero Temperatures Matrix ||" << std::endl;
    std::cout << "=================================" << std::endl << std::endl;

    bool exit = false;

    float tempMatrix[DAYS_IN_A_YEAR][RECORDS_IN_A_DAY] = {};

    const int days = loadInputTemperatures(tempMatrix);

    int subZero = 0;
    float minTemp = tempMatrix[0][0];
    float minTempDay = 0;
    float tempSum = 0;

    for (int day = 0; day < days; day++) {

        bool anySubZero = false;

        for (int n = 0; n < RECORDS_IN_A_DAY; n++) {
            
            if (tempMatrix[day][n] < 0 && !anySubZero) {
                anySubZero = true;
                subZero++;
            }

            if (tempMatrix[day][n] < minTemp) {
                minTemp = tempMatrix[day][n];
                minTempDay = (day + 1);
            }
        }

        tempSum += tempMatrix[day][0];
        std::cout << tempSum << std::endl;
    }

    std::cout << tempMatrix[0][0] << std::endl;
    float average = tempSum / days;

    std::cout << "La temperatura e' scesa sotto zero in " << subZero << " giorni" << std::endl;
    std::cout << "La temperatura minima e' stata di " << minTemp << " il giorno " << minTempDay << std::endl;
    std::cout << "La temperatura media per la prima registrazione di ogni giornata e' di: " << average << " gradi" << std::endl;

    system("pause");
    return 0;
}