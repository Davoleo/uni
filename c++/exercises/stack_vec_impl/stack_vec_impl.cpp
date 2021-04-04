#include <vector>
#include <cstring>

template<typename T>
class pila {

private:
    vector<T> vec;

public:
    pila() {}

    explicit pila(int initialSize) {
        vec.reserve(initialSize);
    }

    void push(T item) {
        vec.push_back(item);
    }

    T pop() {
        if (vec.empty()) {
            throw string("empty stack");
        }
        T item = vec.back();
        vec.pop_back();
        return item;
    }

    bool empty() {
        return vec.empty();
    }

    int getNElem() {
        return vec.size();
    }

    ostream& print(ostream& stream) const {
        for (int i = 0; i < vec.size(); i++) {
            stream << vec[i] << ' ';
        }
        return stream;
    }
};

template<typename T>
ostream& operator<<(ostream& outStream, const pila<T> stack) {
    return stack.print(outStream);
}