#include <iostream>
#include <string>

template <typename T>
class vec {
private:
    T* array;
    int size;

public:
    vec() {
        array = NULL;
        size = 0;
    }

    vec(int capacity) {
        if (capacity < 0)
            throw std::string("Invalid Capacity Argument!");
        array = new T[capacity];
        this->size = capacity;
    }

    vec(int capacity, T defaultVal) {
        if (capacity < 0)
            throw std::string("Invalid Capacity Argument!")
        array = new T[capacity];
        this->size = capacity;
        for (int i = 0; i < n; i++)
            array[i] = defaultVal;
    }

    //Copy Constructor
    vec(vec<T>& wector) {
        array = new T[wector.size];
        this->size = wector.size
        for (int i = 0; i < maxSize; i++)
            array[i] = w.array[i];
    }

    ~vec() {
        delete[] array;
    }

    //Ridefinire operatore [] di selezione i-esimo elemento
    //NB: usa reference return
    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw std::string("index out of bounds!")
        return array[index]
    }

    //Uguaglianza tra vettori ==
    bool operator==(const vec<T>& other) {
        if (this->size != other.size)
            return false;
        for (int i = 0; i < size; i++) {
            if (array[i] != other.array[i])
                return false;
        }
        return false;
    }

    vec<T>& operator=(const vec<T> other) {
        delete[] array;
        array = new T[other.size];
        this->size = other.size;
        for (int i = 0; i < size; i++)
            array[i] = other.array[i];

        return *this;
    }
};

int main() {
    vec<int> v1(10);
    vec<int> v2(100);
    vec<char> v3(32);

    int size;
    std::cin >> size;
    vec<float> v4(size);
    vec<int> w(5, -1);
    return 0;
}