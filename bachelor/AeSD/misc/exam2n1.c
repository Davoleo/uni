#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _binary_tree_node {
    float key;
    struct _binary_tree_node* left;
    struct _binary_tree_node* right;
} bt_node;

/**
 * Il costo temporale asintotico della creazione dell'albero e lineare con l'aumento di profondità dell'albero O(h) il che significa che 
 * in riferimento al numero di nodi dell'albero il costo temporale asintotico è O(log(n))
 * Il costo spaziale asintotico della creazione dell'albero e O(1) costante poiché non si usa nessuna struttura di appoggio intermedia 
 * in cui i dati vengono mantenuti prima di essere aggiunti
 */
void readTreeChildren(bt_node** root, int depth, int maxDepth) {

    if (depth == maxDepth)
        return;

    bt_node* copy = *root;
    float parent = copy->key;
    float lkey = parent * 6 * (pow(-1, depth));
    float rkey = 2 * parent + 3 * lkey;
    
    copy->left = malloc(sizeof(bt_node));
    if (copy->left != NULL) {
        copy->left->key = lkey;
        copy->left->left = NULL;
        copy->left->right = NULL;
    }

    copy->right = malloc(sizeof(bt_node));
    if (copy->right != NULL) {
        copy->right->key = rkey;
        copy->right->left = NULL;
        copy->right->right = NULL;
    }

    readTreeChildren(&(copy->left), depth + 1, maxDepth);
    readTreeChildren(&(copy->right), depth + 1, maxDepth);   
}

void print(bt_node** root)
{
    bt_node* c = *root;
    if(*root != NULL)
    {
        print(&c->left);
        print(&c->right);
        printf("%f ", c->key);
    }
}

int main() {

    int n = 0;
    float rVal;

    scanf("%d", &n);
    scanf("%f", &rVal);

    if (n == 0)
        return EXIT_FAILURE;

    bt_node* root = malloc(sizeof(bt_node));

    if (root == NULL)
        return EXIT_FAILURE;

    root->key = rVal;
    root->left = NULL;
    root->right = NULL;

    readTreeChildren(&root, 1, n - 1);

    print(&root);
    
    
    return EXIT_SUCCESS;
}

