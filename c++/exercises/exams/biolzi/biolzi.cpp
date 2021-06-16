#include <iostream>
#include <string>

class collezione {

private:
    int capacity;

protected:
    std::string* arr;
    int size;

public:
    explicit collezione(int capacity) {
        arr = new std::string[capacity];
        size = 0;
        this->capacity = capacity;
    }

    collezione(const collezione& ref) {
        this->arr = new std::string[ref.capacity];
        
        for (int i = 0; i < ref.size; i++) {
            this->arr[i] = ref.arr[i];
        }

        this->size = ref.size;
        this->capacity = ref.capacity;
    }

    ~collezione() {
        delete[] arr;
    }
    
    void aggiungi(std::string elem) {
        if (size >= capacity) {
            throw "spazio non sufficiente";
        }
        arr[size] = elem;
        size++;
    }

    bool contiene(std::string elem) const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == elem) {
                return true;
            }
        }
        return false;
    }

    void stampa(std::ostream& osvaldo, char sepastiano) const {
        for (int i = 0; i < size; i++) {
            osvaldo << arr[i];
            if (i < size - 1) {
                osvaldo << sepastiano;
            }
        }
    }
};

class insieme : public collezione {

public:
    explicit insieme(int capacity) : collezione(capacity) {

    }

    bool sottoinsieme(insieme set) {
        for (int i = 0; i < size; i++) {
            if (!set.contiene(this->arr[i])) {
                return false;
            }
        }
        return true;
    }

    std::ostream& stampa(std::ostream& osvaldo) const {
        osvaldo << '{';
        this->collezione::stampa(osvaldo, ',');
        osvaldo << '}';
        return osvaldo;
    }
};

std::ostream& operator<<(std::ostream& stream, const insieme& set) {
    return set.stampa(stream);
}

int main() {
    insieme set1 = insieme(10);
    
    try {
        set1.aggiungi("aaa");
        set1.aggiungi("ccc");

        std::cout << set1 << std::endl;

        char string[100];
        std::cin.getline(string, 100, '\n');
        std::string coolString = string;
        if (set1.contiene(coolString)) {
            std::cout << "La stringa e' contenuta nel set" << std::endl;
        }
        else {
            std::cout << "La stringa non e' contenuta nel set" << std::endl;
        }

        insieme sibis(set1);
        sibis.aggiungi("bbb");

        if (set1.sottoinsieme(sibis)) {
            std::cout << "Set 1 e' un sottoinsieme di SIBIS" << std::endl;
        }
    }
    catch(const char ex) {
        std::cout << "Eccezione: " << ex << std::endl;
    }

}