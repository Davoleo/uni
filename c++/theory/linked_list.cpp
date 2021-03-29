struct elem {
    int info;
    elem* next;
};

int main() {
    //Empty linked list
    elem* llist = NULL;

    //List of one element
    llist = new elem;
    llist->info = 5;
    llist->next = NULL;


    elem* temp;
    temp = new elem;
    temp->info = 7;
    temp->next = llist;
    llist = temp;

    return 0;
}