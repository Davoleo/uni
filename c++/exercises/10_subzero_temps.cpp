#include <iostream>

int main() {

    std::cout << "=================================" << std::endl;
    std::cout << "|| Subzero Temperatures Matrix ||" << std::endl;
    std::cout << "=================================" << std::endl << std::endl;

    const int DAYS_IN_A_YEAR = 365;
    const int RECORDS_IN_A_DAY = 4;
    int days = 0;
    bool exit = false;

    float tempMatrix[DAYS_IN_A_YEAR][RECORDS_IN_A_DAY];

    do {
        std::cout << "Inserisci le temperature per il giorno " << days + 1 << " (separate da spazio)" << std::endl;
        std::cin >> tempMatrix[days][0] >> tempMatrix[days][1] >> tempMatrix[days][2] >> tempMatrix[days][3];
        days++;
    } 
    while (days <= 365 && tempMatrix[days][0] < 100);

    int subZero = 0;
    float minTemp = tempMatrix[0][0];
    float minTempDay = 0;
    float tempSum = 0;

    for (int day = 0; day < days; day++) {
        for (int n = 0; n < RECORDS_IN_A_DAY; n++) {
            if (tempMatrix[day][n] < 0)
                subZero++;
            
            if (tempMatrix[day][n] < minTemp) {
                minTemp = tempMatrix[day][n];
                minTempDay = (day + 1);
            }
        }

        tempSum += tempMatrix[day][0];
    }

    float average = tempSum / (days + 1);

    std::cout << "La temperatura e' scesa sotto zero in " << subZero << " giorni" << std::endl;
    std::cout << "La temperatura minima e' stata di " << minTemp << " il giorno " << minTempDay << std::endl;
    std::cout << "La temperatura media per la prima registrazione di ogni giornata e' di: " << average << " gradi" << std::endl;

    system("pause");
}