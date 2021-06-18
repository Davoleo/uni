#include "avl.h"

#include <stdio.h>

static inline void delete_node_avl(avl_tree_node* node) {
    if (node == NULL)
        return;

    delete_node_avl(node->left);
    delete_node_avl(node->right);

    //TODO Finish
}

bool delete_tree_avl(avl_tree* tree) {
    if (tree == NULL)
        return false;

    //TODO Finish
}

static inline int node_tree_height_avl(avl_tree_node* root) {
    if (root == NULL)
        return -1;

    return root->height;
}

static inline void update_node_tree_height_avl(avl_tree_node* root) {
    if (root == NULL)
        return;

    int leftHeight = node_tree_height_avl(root->left);

    int rightHeight = node_tree_height_avl(root->right);

    int highest = leftHeight > rightHeight ? leftHeight : rightHeight;

    root->height = 1 + highest;
}

static inline avl_tree_node* rotate_right_avl(avl_tree_node* node) {
    avl_tree_node* leftBranch = node->left;
    avl_tree_node* rightBranch = node->right;

    leftBranch->right = node;
    node->left = rightBranch;

    update_node_tree_height_avl(node);
    update_node_tree_height_avl(leftBranch);

    return leftBranch;
}

static inline balance_avl(avl_tree_node* root) {
    update_node_tree_height_avl(root);

    //Factor
    int b;

    if (root == NULL)
        b = 0;
    else {
        b = node_tree_height_avl(root->right) - node_tree_height_avl(root->left);
    }

    if (b > 1) {
        if (node_tree_height_avl(root->left->right) > node_tree_height_avl(root->right->left))
            root = rotate_left_avl(root);
        else {
            root->right = rotate_right_avl(root->right);
            root = rotate_left_avl(root);
        }
    }
    else if (b < -1) {
        if (node_tree_height_avl(root->left->left) > node_tree_height_avl(root->left->right))
            root = rotate_right_avl(root);
        else {
            root->left = rotate_left_avl(root->left);
            root = rotate_right_avl(root);
        }
    }

    return root;
}

static inline avl_tree_node* insert_node_avl(avl_tree_node* node, int key) {
    if (node == NULL) {
        //TODO
    }
}

bool insert_tree_avl(avl_tree* tree, int key) {
    if (tree == NULL)
        return false;

    avl_tree_node* root = insert_node_avl(tree->root, key);

    if (root == NULL)
        return false;

    tree->root = root;
    return true;
}

static inline avl_tree_node* remove_node_avl(avl_tree_node* node, int key, bool* edited) {
    if (node == NULL)
        return NULL;

    //TODO    
}

bool remove_node_avl(avl_tree* tree, int key) {
    if (tree == NULL || tree->root == NULL)
        return false;

    bool edited = false;
    tree->root = remove_node_avl(tree->root, key, &edited);
    return edited;
}