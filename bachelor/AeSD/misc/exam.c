#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* next;
} node;

typedef struct {
    int length;
    node* head;
} llist;

bool set_push(llist* list, int key) {
    if (list == NULL)
        return false;

    node* newElem = (node*) malloc(sizeof(node));

    if (newElem == NULL)
        return false;
    
    newElem->data = key;
    newElem->next = NULL;

    node* cycleNode = list->head;
    while (cycleNode != NULL) {
        if (cycleNode->next->data == key)
            return false;

        cycleNode = cycleNode->next;

        printf("Elem: %d\n", cycleNode->data);
    }

    if (list->head == NULL)
        list->head = newElem;

    list->length++;
    return true;
}

/**
 * Funzione che trova una sottosequenza con queste proprietà:
 * - Non contiene numeri duplicati (se 2 indici della sottoseuqenza sono diversi anche i numero corrispondenti sono diversi)
 * - Per ogni elemento nella sottosequenza deve esistere almeno un indice nella seuqenza principale tale che i valori corrispondenti sono uguali
 * - Per ogni indice dispari vale la regola che il valore corrispondente l'indice pari successivo è la metà del precendente
 * 
 * Complessità Temporale dell'algoritmo:
 * - Nel caso peggiore dato che l'algoritmo tenta di aggiungere tutti i valori dell'array alla sottosequenza quindi avremo una complessità asintotica 
 * di O(n^2) visto che l'inserimento ordinato nella lista senza duplicati è a complessità temporale asintotica lineare.
 * - La complessità spaziale asintotica dell'algoritmo è di O(n) nel caso peggiore in quanto tutto l'array viene aggiunto alla lista
 * */
bool find_sub_sequence(int main[], int main_length, llist* subseq) {

    int lastEvenIndex = -1;

    for (int i = 0; i < main_length; i++) {

        //Indici dispari & non è l'ultimo index
        if (i % 2 != 0 && i < main_length - 1) {
            if (main[i] * 2 == main[i+1]) {
                puts("Pusho 2 valori");
                set_push(subseq, main[i]);
                set_push(subseq, main[i+1]);
            }
        }

        //Numero pari
        if (main[i] % 2 == 0) {
            lastEvenIndex = i;
        }
    }

    if (lastEvenIndex != -1) {
        puts("Pusho m");
        set_push(subseq, main[lastEvenIndex]);
        return true;
    }
    else 
        return false;

}

int main() {

    int length;

    printf("Inserire la lunghezza dell'array:");
    scanf("%d", &length);

    if (length <= 0)
        return EXIT_FAILURE;

    int array[length];
    
    for (int i = 0; i < length; i++) {
        int value;
        printf("Elemento %d: ", i);
        scanf("%d", &value);
        array[i] = value;
    }

    llist* subseq = malloc(sizeof(llist));
    subseq->head = NULL;
    subseq->length = 0;

    if (subseq == NULL)
        return EXIT_FAILURE;

    find_sub_sequence(array, length, subseq);

    node* cycle_node = subseq->head;
    while (cycle_node != NULL) {
        printf("%d ", cycle_node->data);
        //free(cycle_node);
        cycle_node = cycle_node->next;
    }

    //free(subseq);

    return EXIT_SUCCESS;

}