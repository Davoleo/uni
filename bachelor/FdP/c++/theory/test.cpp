#include <iostream>

#include <algorithm>
#include <vector>
#include <string>

#include <limits>
#include <cmath>
#include <stdint.h>

using namespace std;

struct TestStruct {
    int c1;
    char c2;
};

struct LLUnit {
    char* ptr;
    char info;
};

void customGetline(char string[], int max, char delim) {
    int i = 0;
    do {
        char next = cin.get();
        if (next == delim)
            string[i] = '\0';
        string[i] = next;
        next++;
    } 
    while (i < max);
}

bool calcola(int n, int m, int& ris) {
    bool nondivBy0 = (n - m) != 0;

    if (nondivBy0) {
        ris = n / (n - m);
    }

    return nondivBy0;
}

template <typename T>
void swapCustom(T& x, T& y) {
    T z(x); //Costruttore di copia di T
    x = y;
    y = z;
}

int main() {

#ifdef __SIZEOF_INT128__
    cout << "Max of unsigned long long: " <<  sizeof(__int128_t) << endl;
#endif

    cout << sizeof(__uint128_t) << endl;

    unsigned long long int test = ULLONG_MAX + 1;
    cout << "Max of unsigned long long: " <<  test << " | " << log2(ULLONG_MAX) << endl;

    int x = 5, y = 7;
    swap(x, y);

    vector<int> v1;
    cout << " v1.size(): " << v1.size() << endl;
    cout << " v1.capacity(): " << v1.capacity() << endl;

    vector<char> v2(5, '*');
    cout << " v2.size(): " << v2.size() << endl;
    cout << " v2.capacity(): " << v2.capacity() << endl;

    vector<string> v3(7, "empty");
    cout << " v3.size(): " << v3.size() << endl;
    cout << " v3.capacity(): " << v3.capacity() << endl;

    v3.reserve(30);
    cout << " v3.size(): " << v3.size() << endl;
    cout << " v3.capacity(): " << v3.capacity() << endl;

    cout << "v2[3]: " << v2[3] << endl;
    cout << "v2[10]: " << v2[10] << endl;
    v2[3] = 'a';
    cout << "v2[3]: " << v2[3] << endl;

    v2.push_back('c');
    //Returns a reference to the last element in the array
    v2.back();
    //Pops the last element
    v2.pop_back();

    TestStruct* pointer;
    pointer = new TestStruct;
    (*pointer).c1;
    pointer->c2;

    //char kek[10];
    //customGetline(kek, 10, '\n');

    return 0;
}