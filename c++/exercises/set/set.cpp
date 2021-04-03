template<typename T>
class Insieme {
private:
    T* array;
    int m_size;
    int max_capacity;

    void expand() {
        T* narray = new T[max_capacity + 10];

        for (int i = 0; i < max_capacity; i++) {
            narray[i] = this->array[i];
        }

        delete[] this->array;
        this->array = narray;
        this->max_capacity += 10;
    }

public:
    Insieme() {
        array = nullptr;
        max_capacity = 0;
        m_size = 0;
    }

    explicit Insieme(int capacity) {
        array = new T[capacity];
        m_size = 0;
        max_capacity = capacity;
    }

    Insieme(const T elems[], const int count) {
        array = new T[count];
        m_size = 0;
        max_capacity = 0;

        for (int i = 0; i < count; i++)
            this->add(elems[i]);
    }

    Insieme(const Insieme<T>& otherSet) {
        array = new T[otherSet.max_capacity];

        for (int i = 0; i < otherSet.m_size; i++) {
            this->array[i] = otherSet.array[i];
        }

        this->m_size = otherSet.m_size;
        this->max_capacity = otherSet.max_capacity;
    }

    ~Insieme() {
        delete[] array;
    }

    void add(T value) {

        if (m_size >= max_capacity) {
            //std::cout << "before Expand Called| Capacity: " << max_capacity << " Size: " << m_size << std::endl;
            this->expand();
            //std::cout << "after Expand Called| Capacity: " << max_capacity << " Size: " << m_size << std::endl;
        }

        this->array[m_size] = value;
        m_size++;
    }

    void remove(T item) {
        int iToRemove = -1;

        for (int i = 0; i < m_size; i++) {
            if (this->array[i] == item) {
                iToRemove = i;
            }
        }

        if (iToRemove == -1) {
            throw std::string("elemento non presente");
        }
        else {
            for (int j = iToRemove; j < m_size-1; j++) {
                array[j] = array[j+1];
            }

            this->m_size--;
        }
    }

    bool contains(T value) const {
        int i = 0;
        while (i < this->m_size) {
            if (value == this->array[i])
                return true;

            i++;
        }

        return false;
    }

    int size() const {
        return this->m_size;
    }

    std::string join(bool enclosed, char separator) const {
        std::string repr;
        if (enclosed)
            repr += '{';

        for (int i = 0; i < m_size; i++) {
            repr += array[i];
            if (i + 1 < m_size) { //If it's not the last element
                repr += separator;
            }
        }
 
        if (enclosed)
            repr += '}';

        return repr;
    }

    bool operator<(const Insieme<T>& other) {
        for (int i = 0; i < m_size; i++) {
            if (!other.contains(array[i])) {
                return false;
            }
        }

        return true;
    }

    Insieme<T> operator+(const Insieme<T>& other) const {

        Insieme<T> set = Insieme(array, m_size);

        for (int i = 0; i < other.m_size; i++) {
            if (!set.contains(other.array[i]))
                set.add(other.array[i]);
        }

        return set;
    }

    Insieme<T> operator=(const Insieme<T>& other) {

        this->m_size = 0;
        for (int i = 0; i < other.m_size; i++)
            this->add(other.array[i]);
        
        this->max_capacity = other.max_capacity;
        return *this;
    }
};

template <typename T>
ostream& operator<<(ostream& out, Insieme<T> set) {
    std::string repr = set.join(true, ',');
    return out << repr.c_str();
}