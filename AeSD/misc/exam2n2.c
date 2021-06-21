#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    char val;
    struct _node* next;
} node;

bool list_insert_head(node** list, int key) {
    if (*list == NULL)
        return false;

    node* elem = (node*) malloc(sizeof(node));

    if (elem == NULL)
        return false;
    
    elem->val = key;
    elem->next = *list;
    *list = elem;

    return true;
}

/**
 * Automa a Stati finiti
 * S = {S_i, S_o, S_ot, S_otn, S_otno, S_otnot}
 * Ogni stato corrisponde a quando l'automa ha ricevuto la sequenza scritta a pedice del nome dello stato
 * mentre S_i è lo stato iniziale quando nessuna sequenza è stata ancora inserita
 * Funzioni di Stato e di Uscita dell'automa nella seguente sintassi (S_input, lettera_in) -> (S_output, lettera_out)
 * coppie in input unite da || significa che hanno lo stesso output
 * F_s = {
 *   (S_i, o) -> (S_o, n)
 *   (S_i, t) || (S_i, n) || (S_i, a) || (S_i, b) -> (S_i, n)
 *   (S_o, t) -> (S_ot, n)
 *   (S_o, o) || (S_o, n) || (S_o, a) || (S_o, b) -> (S_i, n)
 *   (S_ot, n) -> (S_otn, n)
 *   (S_ot, o) || (S_ot, t) || (S_ot, a) || (S_ot, b) -> (S_i, n)
 *   (S_otn, o) -> (S_otno, n)
 *   (S_otn, n) || (S_otn, t) || (S_otn, a) || (S_otn, b) -> (S_i, n)
 *   (S_otno, t) -> (S_otnot, t)
 *   (S_otno, n) || (S_otno, o) || (S_otno, a) || (S_otno, b) -> (S_i, n)
 * }
 **/
int main() {

    char lett;
    node* char_list = malloc(sizeof(node));

    if (char_list == NULL)
        return EXIT_FAILURE;

    do {
        scanf("%c", &lett);

        if (lett == '$')
            break;

        if (lett != 'o' && lett != 't' && lett != 'n' && lett != 'a' && lett != 'b' && lett != '$') 
            return EXIT_FAILURE;

        list_insert_head(&char_list, lett);
    }
    while (true);

    node* clist = char_list;
    int seqCount = 0;
    while (clist != NULL) {
        if (clist->val == 'o' && (seqCount == 0 || seqCount == 3)) {
            seqCount++;
        }
        
        if (clist->val == 't' && (seqCount == 1 || seqCount == 4)) {
            seqCount++;
        }

        if (clist->val == 'n' && seqCount == 2) {
            seqCount++;
        }

        if (seqCount == 5) {
            printf("Uscita automa: t");
        }
        else {
            printf("Uscita automa: n");
        }

        clist = clist->next;
    }

    return EXIT_SUCCESS;
}