#include <iostream>
#include <string>

struct elem {
    int info;
    elem* next;
};

//The pointer must be passed as a reference because the function acts by side-effect and by changing the value of list
void insertHead(elem*& list, int value) {
    elem* newElem = new elem;
    newElem->info = value;
    //Link the new element to the old first pointer
    newElem->next = list;
    //Make the list first pointer to point ot the new first element
    list = newElem;
}

void print(elem* list) {
    while(list != nullptr) {
        std::cout << list->info << "  ";
        list = list->next;
    }
}

int extractHead(elem*& list) {
    if (list == nullptr)
        throw std::string("empty list");
    int x = list->info;
    elem* old = list;
    list = list->next;
    delete old;
    return x;
}

void insertEnd(elem*& list, int value) {
    if (list == nullptr)
        insertHead(list, value);
    else {
        elem* newElem = new elem;
        newElem->info = value;
        newElem->next = nullptr;
        elem* oldLast = list;
        while (oldLast->next != nullptr)
            oldLast = oldLast->next;
        oldLast->next = newElem;
    }
}

int length(elem* list) {
    int length = 0;
    while (list != nullptr) {
        length++;
        list = list->next;
    }

    return length;
}

int recursiveLength(elem* list) {
    if (list == nullptr)
        return 0;
    else 
        return recursiveLength(list->next);
}

bool contains(elem* list, int value) {
    while (list != nullptr) {
        if (list->info == value)
            return true;
        
        list = list->next;
    }

    return false;
}

bool recursiveContains(elem* list, int value) {
    if (list == nullptr)
        return false;
    else if (list->info == value)
        return true;
    else {
        return recursiveContains(list->next, value);
    }
}

int main() {
    //Empty linked list
    elem* llist = nullptr;

    //List of one element
    llist = new elem;
    llist->info = 5;
    llist->next = nullptr;
    insertHead(llist, 3);
    insertHead(llist, 7);

    return 0;
}