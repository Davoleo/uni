#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _node {
    int data;
    struct _node* next;
} node;

typedef struct {
    int length;
    node* head;
} llist;

bool add(llist* list, int elem) {

    if (list->head == NULL) {
        list->head = malloc(sizeof(node));
        if (list->head == NULL || elem % 2 == 0)
            return false;
        else {
            list->head->data = elem;
            list->head->next = NULL;
            return true;
        }
    }
    else {
        node* newNode = malloc(sizeof(node));
        if (newNode == NULL || elem % 2 == 0)
            return false;
        else {
            newNode->next = list->head;
            newNode->data = elem;
            list->head = newNode;
            return true;
        }
    }
}

float average(llist* list) {
    int total = 0;
    int count = 0;

    node* head = list->head;

    while (head != NULL) {
        total += head->data;
        head = head->next;
        count++;
    }

    return total / (float) count;
}

int main() {

    llist* linked_list = malloc(sizeof(llist));
    linked_list->length = 0;
    linked_list->head = NULL;

    int value;
    do {
        scanf("%d", &value);
        if (value == -1)
            break;

        add(linked_list, value);
    } while(true);

    node* to_print = linked_list->head;
    while (to_print != NULL) {
        printf("%d ", to_print->data);
        to_print = to_print->next;
    }

    printf("\n");
    printf("La media e': %f", average(linked_list));

    return EXIT_SUCCESS;
}