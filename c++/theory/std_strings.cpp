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

    return 0;
}