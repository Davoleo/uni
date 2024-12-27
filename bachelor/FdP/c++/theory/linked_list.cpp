#include <iostream>
#include <string>

struct elem {
    int info;
    elem* next;
};

elem* firstEven(elem* lst) {
	while (lst != nullptr) {
		if (lst->info % 2 == 0) {
			return lst;
		}
		lst = lst->next;
	}
}

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
	std::cout << "[ ";
	while(list != nullptr) {
		std::cout << list->info << " -> ";
		list = list->next;
	}
	std::cout << " ]\n";
}

void removeHead(elem*& list) {
	elem* elemToRemove = list;
	list = list->next;
	delete elemToRemove;
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

void removeTail(elem*& list) {

	elem* current = list;
	while (current->next->next != nullptr) {
		current = current->next;
	}

	elem* elemToRemove = current->next;
	delete elemToRemove;
	current->next = nullptr;
}

void insertTail(elem*& list, int newVal) {

	if (list == nullptr)
		insertHead(list, newVal);
	else {
		elem* newElem = new elem;
		newElem->info = newVal;
		newElem->next = nullptr;

		elem* current = list;
		while(current->next != nullptr) {
			current = current->next;
		}

		current->next = newElem;
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
        return 1+recursiveLength(list->next);
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

	elem* list = new elem;
	list->info = 5;
	elem* newElem = new elem;
	newElem->info = 6;
	list->next = newElem;
	elem* newElem2 = new elem;
	newElem2->info = 7;
	newElem->next = newElem2;

	printList(list);
	removeTail(list);
	printList(list);

	std::ifstream input;
	input.open("prova.txt");
	char string[250];
	input.getline(string, 100, '\n');
	std::cout << string << std::endl;
	input.getline(string, 100, '\n');
	std::cout << string  << std::endl;
	input.getline(string, 100, '\n');
	std::cout << string  << std::endl;
	input.close();


	
	//Array: [][][][][]
	//Random Access
	//List: [1]->[2]->[3]->[4]->[5]->[6]
	//Sequetianl Access
	
	//	int x = 10;
	//	int y[10];
	//	TestStruct str;
	//	str.c1 = 12;

	//Modificatori di tipo
	//int
	//int*
	//int& -

	//Operatori su variabile
	//&a -> Indirizzo di memoria che punta ad a -> int*
	//*p -> Ottieni il valore di a partendo dall puntatore p

    return 0;
}

struct dl_elem {
    int info;
    dl_elem* prev;
    dl_elem* next;
};