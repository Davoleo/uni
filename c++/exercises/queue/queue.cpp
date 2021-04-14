template<typename T>
class coda {
private:
    struct elem {
        T info;
        elem* next;
    };

    elem* listTop;
    elem* listEnd;
    int elemCount;
public:
    coda() {
        listTop = nullptr;
        listEnd = nullptr;
        elemCount = 0;
    }

    coda(coda<T>& other) {
        this->listTop = nullptr;
        this->listEnd = nullptr;
        this->elemCount = 0;

        if (other.elemCount != 0) {
            this->listTop = new elem;
            listEnd = listTop;
            elem* workList = other.listTop;
            while (workList != nullptr) {
                this->enqueue(workList->info);
                workList = workList->next;
            }
        }
    }

    ~coda() {
        while (listTop != nullptr) {
            elem* oldElem = listTop;
            listTop = listTop->next;
            delete oldElem;
        }
    }

    void enqueue(T x) {
        if (this->isEmpty()) {
            elem* firstElem = new elem;
            firstElem->info = x;
            firstElem->next = nullptr;
            listEnd = firstElem;
            listTop = firstElem;
        }
        else {
            listEnd->next = new elem;
            listEnd = listEnd->next;
            listEnd->info = x;
            listEnd->next = nullptr;
        }
        elemCount++;
    }

    T dequeue() {
        if (listTop == nullptr)
            throw std::string("empty queue");
        
        elemCount--;
        T dequeued = listTop->info;
        elem* oldElem = listTop;
        listTop = listTop->next;
        delete oldElem;
        return dequeued;
    }

    bool isEmpty() const {
        return elemCount == 0;
    }

    int size() const {
        return elemCount;
    }
    
    void print(std::ostream& stream) const {
        if (elemCount == 0)
            return;
        
        elem* workList = listTop;
        while (workList != nullptr) {
            stream << workList->info;
            if (workList->next != nullptr)
                stream << ' ';
            workList = workList->next;
        }
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const coda<T>& queue) {
    out << '[';
    queue.print(out);
    out << ']';
    return out;
}