#include <stdio.h>
#include <stdlib.h>

typedef struct _binary_tree_node {
    int key;
    struct _binary_tree_node* left;
    struct _binary_tree_node* right;
} bt_node;

bt_node* binary_tree_search(bt_node* source, int key) {
    if (source == NULL)
        return NULL;

    if (source->key == key)
        return source;

    bt_node* leftNode = binary_tree_search(source->left, key);

    if (leftNode != NULL)
        return leftNode;

    bt_node* rightNode = binary_tree_search(source->right, key);

    if (rightNode != NULL)
        return rightNode;

    return NULL;

}

void binary_tree_print_indented(bt_node* source, int level) {
    if (source == NULL || level < 0)
        return;

    if (level > 0) {
        for (int i = 0; i < level - 1; i++) {
            printf("| ");
        }
        printf("|-");
    }

    printf("%d\n", source->key);

    binary_tree_print_indented(source->left, level + 1);

    binary_tree_print_indented(source->right, level + 1);
}

void binary_tree_print(bt_node* source) {
    binary_tree_print_indented(source, 0);
}

void binary_tree_delete(bt_node* source) {
    if (source == NULL)
        return;

    binary_tree_delete(source->left);
    binary_tree_delete(source->right);

    free(source);
}

bt_node* binary_tree_read(void) {
    int key, children;

    int readValues = scanf("%d %d", &key, &children);

    if (readValues != 2 || readValues < 0 || readValues > 2)
        return NULL;

    bt_node* source = (bt_node*) malloc(sizeof(bt_node));

    if (source == NULL) 
        return NULL;

    int right, left;

    if (children == 0)
        left = right = NULL;
    else if (children == 1) {
        left = binary_tree_read();
        
        if (left == NULL) {
            free(source);
            return NULL;
        }
    }
    else if (children == 2) {
        left = binary_tree_read();
        
        if (left == NULL) {
            free(source);
            return NULL;
        }

        right = binary_tree_read();

        if (right == NULL) {
            free(source);
        }
    }

    source->left = left;
    source->right = right;
    return source;
}

int main(void) {
    bt_node* source = binary_tree_read();

    if (source == NULL) {
        puts("Impossibile leggere tutto l'albero");
        return EXIT_FAILURE;
    }

    binary_tree_print(source);

    puts("");

    bt_node* subTreeSource = binary_tree_search(source, 2);

    if (subTreeSource == NULL)
        printf("Il valore della chiave non è presente nell'albero\n");
    else
        binary_tree_print(subTreeSource);

}