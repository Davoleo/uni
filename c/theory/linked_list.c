#include <stdlib.h>
#include <stdio.h>

//Private name _list_node while the struct is not finished
typedef struct _list_node {
    int key;
    struct _list_node* next;
} list_node;
//Public name list_node when the node is ready

void print_list(list_node* head) {
    for (list_node* e = head; e != NULL; e = e->next) {
        printf("%d ", e->key);
    }
    puts("");
}

void delete_list(list_node* head) {
    list_node* list = head;

    while (list != NULL) {
        list_node* temp = list;
        list = list->next;
        free(temp);
    }
}

list_node* read_list(void) {
    list_node* current = NULL;
    list_node* head = NULL;
    int value;

    do {
        int read_nums = scanf("%d", &value);

        if (read_nums != 1) {
            delete_list(head);
            return NULL;
        }

        if (value >= 0) {
            list_node* new = (list_node*) malloc(sizeof(list_node));

            if (new == NULL) {
                delete_list(head);
                return NULL;
            }

            new->key = value;
            new->next = NULL;

            if (current != NULL)
                current->next = new;


            if (head == NULL)
                head = new;

            //Increase the current node
            current = new;
        }
    } while (value >= 0);

    return head;
}

int main(void) {
    list_node* head = read_list();

    if (head == NULL) {
        printf("Impossibile leggere tutta la lista\n");
        return EXIT_FAILURE;
    }

    print_list(head);

    delete_list(head);

    return EXIT_SUCCESS;
}