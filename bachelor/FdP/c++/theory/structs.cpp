#include "iostream"
#include <cstring>

int main() {

    const int tableDim = 100;
    const int titleDim = 100;

    struct {
        char name[32];
        char cognome[32];
        //..
        int eta;
    } structureName = {"mario", "verdi", 24};


    struct Person {
        char name[32];
        char surname[32];
        int age;
    };

    Person person = {"Test", "test", 213};

    struct Date {
        int day;
        int month;
        int year;
    };

    struct ExamData {
        char subject[titleDim];
        int mark;
        bool praise;
        Date examDate;
    };

    ExamData exams[100];
    int i = 0;
    do {
        char title[titleDim];
        std::cout << "Dai nome esame (stop per smettere): ";
        std::cin.getline(title, titleDim);
        if (strcmp(title, "stop") == 0)
            break;
        else
            strcpy(exams[i].subject, title);
        
        int mark;
        std::cout << "Inserisci un voto: ";
        do {
            std::cin >> mark;
        } while (mark < 0 || mark > 30);

        exams[i].mark = mark;

        char praise;

        if (exams[i].mark == 30) {
            std::cout << "Lode? (s/n)";
            do {
                std::cin >> praise;
            } while(praise != 'n' && praise != 's');

            exams[i].praise = praise == 's';
        }

        Date examDate;
        std::cout << "Day data esame (g m a)";
        std::cin >> examDate.day >> examDate.month >> examDate.year;
        //examDate Validation

        exams[i].examDate = examDate;
        i++;
        std::cin.ignore(256, '\n');

    }while(i < tableDim);

    //stampa tabella
    //voto max
    int max = 0;
    for (int j = 0; j < i; j++) {
        if (exams[j].mark > max) {
            max = exams[j].mark;
        }
    }

    std::cout << "Il voto maggiore è " << max << std::endl;

    system("pause");
    return 0;
}