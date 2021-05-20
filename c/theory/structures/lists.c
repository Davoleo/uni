#include <stdlib.h>
#include <stdbool.h>

#include "lists.h"

typedef struct _list_node {
    int key;
    struct _list_node* next;
    struct _list_node* prev;
} node;

typedef struct {
    int length;
    node* head;
    node* tail;
} list;

list *create_list(void) {
    list* read = (list*) malloc(sizeof(list));

    if (read == NULL)
        return NULL;
    
    read->length = 0;
    read->head = NULL;
    read->tail = NULL;
}

bool delete_list(list* list) {
    if (list == NULL)
        return false;

    node* elem = list->head;

    while (elem != NULL) {
        node* nod = elem;
        elem = elem->next;
        free(nod);
    }

    free(list);
    return true;
}

bool list_insert_head(list* list, int key) {
    if (list == NULL)
        return false;

    node* elem = (node*) malloc(sizeof(node));

    if (elem == NULL)
        return false;
    
    elem->key = key;

    elem->next = list->head;
    elem->prev = NULL;

    if (list->head != NULL)
        list->head->prev = elem;

    list->head = elem;

    if (list->tail = NULL)
        list->tail = elem;

    list->length++;
}

//Same thing as before with swapped head and tail
bool list_insert_tail(list* list, int key) {
    if (list == NULL)
        return false;

    node* elem = (node*) malloc(sizeof(node));

    if (elem == NULL)
        return false;
    
    elem->key = key;

    elem->next = NULL;
    elem->prev = list->tail;

    if (list->tail != NULL)
        list->tail->prev = elem;

    list->tail = elem;

    if (list->head = NULL)
        list->head = elem;

    list->length++;
}

bool list_remove_tail(list* list) {
    if (list == NULL || list->length <= 0 || list->tail == NULL)
        return false;

    node* n = list->tail;

    list->tail = n->prev;

    free(n);

    list->length--;

    //TODO
}

bool list_remove_tail(list* list) {
    if (list == NULL || list->length <= 0 || list->head == NULL)
        return false;

    node* n = list->tail;

    list->head = n->next;

    free(n);

    list->length--;

    if (list->length == 0)
        list->tail = NULL;

    return true;
}

bool fill_list(list* list, int data[], int length) {
    if(data == NULL)
        return false;

    if (length < 1)
        return false;

    for (int i = 0; i < length; i++)
        list_insert_tail(list, data[i]);

    return true;
}

bool fill_list_reverse(list* list, int data[], int length) {
    //TODO
}

bool list_search(list* list, int key_to_find) {
    if (list == NULL || list->length <= 0 || list->head == NULL)
        return false;

    for (node* el = list->head; el != NULL; el = el->next) {
        if (el->key == key_to_find) {
            return true;
        }
    }

    return false;
}

bool list_visit(list* list, list_visitor fun, void* data) {
    if (list == NULL || list->length <= 0 || list->head == NULL)
        return false;

    for (node* elem = list->head; elem != NULL; elem = elem->next) {
        bool should_stop = (*fun)(elem->key, data);

        if (should_stop)
            return true;
    }

    return false;
}

bool list_visit_reverse(list* list, list_visitor fun, void* data) {
    if (list == NULL || list->length <= 0 || list->head == NULL)
        return false;

    for (node* elem = list->tail; elem != NULL; elem = elem->prev) {
        bool should_stop = (*fun)(elem->key, data);

        if (should_stop)
            return true;
    }

    return false;
}

bool list_remove_if(list* list, list_visitor fun, void* data) {
    if (list == NULL || list->length <= 0 || list->head == NULL)
        return false;

    node* elem = list->head;

    while (elem != NULL) {
        bool should_remove = fun(elem, data);

        //TODO
        if (!should_remove) {
            elem = elem->next;
        }
        else {

        }
    }

    //TODO
    return NULL;
}

bool list_delete_iterator(list_iterator* iter) {
    if (iter == NULL)
        return NULL;

    free(iter);
    return true;
}


static const int INVALID_VALUE = -1;
//TODO
bool list_iterator_valid(list_iterator* iter);

int list_iterator_next(list_iterator* iter) {
    if (iter == NULL)
        return INVALID_VALUE;

    node* current = iter->current;

    if (current == NULL)
        return INVALID_VALUE;

    int res = current->key;
    iter->current = current->next;
}