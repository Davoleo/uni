#include "./fraction.cpp"

template <typename T>
class stack {

private:
    T* array;
    int head;
    int maxSize;

    void expand() {
        //Pointer to the new dynamic array
        T* temp = new T[maxSize + 10];

        for (int i = 0; i < maxSize; i++)
            temp[i] = array[i];

        delete[] array;
        array = temp;
        maxSize += 10;
    }

public:
    stack() {
        array = NULL;
        head = 0;
        maxSize = 0;
    }

    //Costruttore con un parametro in cui l'utente può specificare una size iniziale
    explicit stack(int count) {
        array = new T[count];
        maxSize = count;
        head = 0;
    }

    ~stack() {
        delete[] array;
    }

    void push(T value);

    stack(const stack<T>& source) {
        array = new int[source.maxSize];
        for (int i = 0; i < source.head; i++) {
            this->array[i] = source.array[i];
        }

        this->maxSize = source.maxSize;
        this->head = source.head;
    }

    T pop();

    void clear() {
        this->head = 0;
    }

    int size() const {
        return head;
    }

    bool is_empty() const {
        return head == 0;
    }


    stack& operator=(const stack<T>& other) {
        
        this->clear();
        for (int i = 0; i < other.head; i++)
            push(other.array[i]);

        this->maxSize = other.maxSize;
        this->head = other.head;
        return *this;
    }
};

template <typename T> 
void stack<T>::push(T value) {
    if (head == maxSize)
        this->expand();
    array[head] = value;
    head++;
}

template <typename T>
T stack<T>::pop() {
    if(is_empty()) {
        throw std::string("Pop chiamato su una pila vuota");
    }
    return array[--head];
}

template <typename T>
T max(T array[], int count) {
    T max = array[0];
    for (int i = 1; i < count; i++) {
        if (max < array[i]) {
            max = array[i]
        }
    }

    return max;
}

template <typename T>
T* test(int x);

int main() {

    stack<int> a; //oggetto di nome a e tipo stack<int>
    a.push(3);
    stack<char> b;
    b.push('a');
    b.push('*');
    stack<fraction> r;
    r.push(fraction(2, 3));
    stack<float>* p = new stack<float>();
    delete p;

    int* bruh;
    bruh = test<int>(3);

    return 0;
}