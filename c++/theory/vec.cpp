#include <iostream>

template <typename T>
class vec {
private:
    T* array;
    int maxSize;

public:
    vec() {
        array = NULL;
        maxSize = 0;
    }

    vec(int capacity) {
        if (capacity < 0)
            throw std::string("Invalid Capacity Argument!");
        array = new T[capacity];
        this->maxSize = capacity;
    }

    vec(int capacity, T defaultVal) {
        if (capacity < 0)
            throw std::string("Invalid Capacity Argument!")
        array = new T[capacity];
        this->maxSize = capacity;
        for (int i = 0; i < n; i++)
            array[i] = defaultVal;
    }

    ~vec() {
        delete[] array;
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