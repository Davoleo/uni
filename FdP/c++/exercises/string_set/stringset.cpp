#include <string>

class StringSet {
private:
    std::string array[100];
    int m_size = 0;

public:
    StringSet() {

    }

    StringSet(const std::string elems[], const int count) {
        for (int i = 0; i < count; i++)
            this->add(elems[i]);
    }

    void add(std::string value) {
        if (m_size < 100) {
            this->array[m_size] = value;
            m_size++;
        }
        else
            throw std::string("spazio non sufficiente");
    }

    bool contains(std::string value) const {
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

    bool operator<(const StringSet& other) {
        for (int i = 0; i < m_size; i++) {
            if (!other.contains(array[i])) {
                return false;
            }
        }

        return true;
    }

    StringSet operator+(const StringSet& other) const {

        StringSet set = StringSet(array, m_size);

        for (int i = 0; i < other.m_size; i++) {
            if (!set.contains(other.array[i]))
                set.add(other.array[i]);
        }

        return set;
    }
};

std::ostream& operator<<(std::ostream& stream, const StringSet& set) {
    return stream << set.join(true, ',').c_str();
}

