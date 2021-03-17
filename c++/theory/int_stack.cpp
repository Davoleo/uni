#include <string>
#include <iostream>

class int_stack {
private:
    //Pointer to the head of the stack array
    int* array;
    //Current max Size of the array
    int maxSize;
    //Index of the element at the head
    int head;

    void expand() {
        //Pointer to the new dynamic array
        int* temp = new int[maxSize + 10];

        for (int i = 0; i < maxSize; i++)
            temp[i] = array[i];

        delete[] array;
        array = temp;
        maxSize += 10;
    }

public:
    int_stack() {
        //Empty Stack
        array = nullptr;
        maxSize = 0;
        head = 0;
    }

    //Costruttore con un parametro in cui l'utente può specificare una size iniziale
    explicit int_stack(int count) {
        array = new int[count];
        maxSize = count;
        head = 0;
    }

    ~int_stack() {
        delete[] array;
    }

    void push(int value) {
        if (head == maxSize)
            this->expand();
        array[head] = value;
        head++;
    }

    bool is_empty() const {
        return head == 0;
    }

    int pop() {
        if(is_empty()) {
            throw std::string("Pop chiamato su una pila vuota");
        }
        return array[--head];
    }

    int size() const {
        return head;
    }

};


int main() {


    int_stack stack;
    stack.push(3);
    stack.push(5);
    stack.push(21);

    try {
        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl;
    }
    catch(std::string e) {
        std::cout << "ECCEZIONE: " << e << std::endl;
    }

    return 0;
}