#include <iostream>
#include <string>

int main() {
    //Creates an empty string implicitly calling the constructor with no params
    std::string string;
    //Implicitly Invoking the one param constructor
    std::string hello = "Hello";
    std::cout << hello.size() << std::endl;

    std::string newString = hello;

    //hello == newString, hello < newString, hello > newString

    std::string s = hello;
    s += ", Worldo";
    s += '!';
    std::cout << s; //--> Hello, Worldo!

    std::cout << s[8];

    //Takes the substring that is 3 chars long starting from index 2
    s = s.substr(2, 3);

    //Cerca una sottostringa "ll" all'interno di s a partire dalla posizione di indice zero
    //Ritorna la posizione indice della prima occurance della stringa oppure un valore speciale "std::string::npos" (costante static classe string)
    s.find("ll", 0);

    //Funzione esterna
    std::getline(std::cin, s, '\n');
    //Funzione propria di cin può essere usata solo con le cstring
    //std::cin.getline(s, 100, '\n');

    return 0;
}