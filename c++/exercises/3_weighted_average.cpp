#include <iostream>

int main() {

    std::cout << "====================" << std::endl;
    std::cout << "| Weighted Average |" << std::endl;
    std::cout << "====================" << std::endl << std::endl;

    int mark = 0;
    int cfu = 0;

    int markCount = 0;
    int markXCfuSum = 0;
    int cfuSum = 0;

    while (mark >= 0) 
    {
        std::cout << "Inserisci un voto (negativo per terminare l'esecuzione): ";
        std::cin >> mark;
        
        if (mark >= 18 && mark <= 30) 
        {
            std::cout << "Inserisci i CFU del corso: ";
            std::cin >> cfu;

            //Handle sums and counters incrementation
            markCount++;
            markXCfuSum += (mark * cfu);
            cfuSum += cfu;
        } 
        else if (mark > 0) //The mark is greater than 0 but not valid since not in the range: [18, 30]
            std::cout << "Il voto deve essere compreso tra 18 e 30" << std::endl;
    }

    float average = markXCfuSum / (float) cfuSum;

    std::cout << "Hai inserito " << markCount << " voti" << std::endl;
    std::cout << "La media pesata dei tuoi voti e': " << average << std::endl;

    system("pause");
    return 0;
}