#include <string>

template <typename T>
class linked_list {

private:
    struct elem {
        int info;
        elem* next;
    };

    elem* list;

public:
    linked_list() {
        list = nullptr;
    }

    void insert_head(T value) {
        elem* newElem = new elem;
        newElem->info = value;
        newElem->next = list;
        list = newElem;
    }

    void print(ostream& dest) const {
        elem* temp = list;
        while (temp != nullptr)
        {
            dest << temp->info << ", ";
            temp = temp->next;
        }
    }

    int size() const {
        int len = 0;
        elem temp* = list;
        while (t != nullptr) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    int recursiveSize() const {
        if (list == nullptr)
            return 0
        else {
            linked_list smallerList;
            smallerList.list = list->next;
            return smallerList.recursiveSize() + 1;
        }
    }

    T extract_head() {
        if (list == nullptr)
            throw std::string("Empty list")
        
        int value = list->info;
        elem* oldHead = list;
        list = list->next;
        delete oldHead;
        return value;
    }

    T last() const {
        if (list == nullptr)
            throw std::string("Empty list")

        elem* temp = list;
        while (temp->next != nullptr)
            temp = temp->next;
        return temp->info;
    }

    bool is_empty() const {
        return list == nullptr;
    }

    T get(int index) const {
        if (index < 0 || index >= this->size)
            throw std::string("Index Out of Bounds!");
        elem* temp = list;
        for (int j = 0; j < index; j++)
            temp = temp->next;

        return temp->info;
    }

    //Confronto tra liste
    bool operator==(const linked_list& other) const {
        if (list == nullptr && other.list == nullptr)
            return true
        else if (list == nullptr || other.list == nullptr)
            return false

        elem* list1 = list;
        elem* list2 = other;
        while (list1 != nullptr && list2 != nullptr && list1->info == list2->info) {
            list1 = list1->next;
            list2 = list2->next;
        }

        if (list1 == nullptr && list2 == nullptr)
            return true
        else 
            return false;

        //If they're both empty it means all their items are equals
        return list1 == nullptr && list2 == nullptr;
    }

};