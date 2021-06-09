#ifndef _AVL_H_
#define _AVL_H_ 

#include <stdlib.h>
#include <stdbool.h>

typedef struct _tree_node_avl {
    int key;
    int height;

    struct _tree_node_avl* left;
    struct _tree_node_avl* right;
} avl_tree_node;

typedef struct {
    avl_tree_node* root;
} avl_tree;


extern avl_tree* create_tree_avl(void);
extern bool delete_tree_avl(avl_tree* tree);

extern bool insert_tree_avl(avl_tree* tree, int key);
extern bool remove_tree_avl(avl_tree* tree, int key);

extern bool fill_tree_avl(avl_tree* tree, int data[], int length);

extern bool print_tree_avl(avl_tree* tree);

extern bool search_tree_avl(avl_tree* tree);

#endif