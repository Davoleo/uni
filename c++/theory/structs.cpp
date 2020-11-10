#include "iostream"

int main() {

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
    

    system("pause");
    return 0;
}