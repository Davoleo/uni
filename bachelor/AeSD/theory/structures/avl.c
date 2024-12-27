#include "avl.h"

#include <stdio.h>

avl_tree *create_tree_avl() {
    avl_tree* tree = (avl_tree*) malloc(sizeof(avl_tree));

    if (tree == NULL)
        return NULL;

    tree->root = NULL;

    return tree;
}

static inline void delete_node_avl(avl_tree_node* node) {
    if (node == NULL)
        return;

    delete_node_avl(node->left);
    delete_node_avl(node->right);

    free(node);
}

bool delete_tree_avl(avl_tree* tree) {
    if (tree == NULL)
        return false;

    avl_tree_node* root = tree->root;

    delete_node_avl(root);

    free(tree);
    return true;
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

/**
 *          O               
 *        /   \             
 *       X     Y      -->   
 *      / \   / \           
 *     Z1  Z2 Z3 Z4         
 **/
static inline avl_tree_node* rotate_right_avl(avl_tree_node* node) {
    avl_tree_node* leftBranch = node->left;
    avl_tree_node* rightBranch = node->right;

    leftBranch->right = node;
    node->left = rightBranch;

    update_node_tree_height_avl(node);
    update_node_tree_height_avl(leftBranch);

    return leftBranch;
}

static inline avl_tree_node* rotate_right_avl(avl_tree_node* node) {
    avl_tree_node* leftBranch = node->left;
    avl_tree_node* rightBranch = node->right;

    rightBranch->left = node;
    node->right = leftBranch;

    update_node_tree_height_avl(node);
    update_node_tree_height_avl(rightBranch);
}

static inline avl_tree_node* balance_avl(avl_tree_node* root) {
    update_node_tree_height_avl(root);

    //Factor
    int beta;

    if (root == NULL)
        beta = 0;
    else {
        beta = node_tree_height_avl(root->right) - node_tree_height_avl(root->left);
    }

    //Se il fattore è sbilanciato di oltre 1 livello da uno dei due lati bilancio l'albero in 2 modi opposti e diversi
    if (beta > 1) {
        if (node_tree_height_avl(root->left->right) > node_tree_height_avl(root->right->left))
            root = rotate_left_avl(root);
        else {
            root->right = rotate_right_avl(root->right);
            root = rotate_left_avl(root);
        }
    }
    else if (beta < -1) {
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
    //if there's Empty space for the new node
    if (node == NULL) {
        avl_tree_node* node = (avl_tree_node*) malloc(sizeof(avl_tree_node));

        if (node == NULL)
            return NULL;

        node->key = key;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }

    //If the value is already there no need to add it and we return the node with the same value
    if (key == node->key)
        return node;

    //Recursive branch sorted insert
    if (key < node->key) {
        avl_tree_node* modifiedLeftBranch = insert_node_avl(node->left, key);

        if (modifiedLeftBranch == NULL)
            return NULL;
        
        node->left = modifiedLeftBranch;
    }
    else {
        avl_tree_node* modifiedRightBranch = insert_node_avl(node->right, key);

        if (modifiedRightBranch == NULL)
            return NULL;
        
        node->right = modifiedRightBranch;
    }
    
}

bool insert_tree_avl(avl_tree* tree, int key) {
    if (tree == NULL)
        return false;

    avl_tree_node* root = insert_node_avl(tree->root, key);

    //If something fails return false and don't reassign the new tree 
    if (root == NULL)
        return false;

    //Reassign the root
    tree->root = root;
    return true;
}

/**
 * returns the node on the farthest left of the tree (which is the minimum)
 **/
static inline avl_tree_node* min_node_avl(avl_tree_node* root) {
    if (root == NULL)
        return NULL;

    avl_tree_node* current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

static inline avl_tree_node* remove_node_avl(avl_tree_node* node, int key, bool* edited) {
    if (node == NULL)
        return NULL;

    if (key < node->key)
        node->left = remove_node_avl(node->left, key, edited);
    else if (key > node->key)
        node->left = remove_node_avl(node->left, key, edited);
    else {
        if (node->left == NULL) {
            node = node->right;
            *edited = true;
        }
        else if (node->right == NULL) {
            node = node->left;
            *edited = true;
        }
        else {
            //Minimum of the right branch
            avl_tree_node* min = min_node_avl(node->right);
            node->key = min->key;
            node->right = remove_node_avl(node->right, min->key, edited);
        }
    }

    if (node != NULL)
        node = balance_avl(node);

    return node;
}

bool remove_tree_avl(avl_tree* tree, int key) {
    if (tree == NULL || tree->root == NULL)
        return false;

    bool edited = false;
    tree->root = remove_node_avl(tree->root, key, &edited);
    return edited;
}

bool fill_avl_tree(avl_tree* tree, int data[], int length) {
    if (tree == NULL || data == NULL || length < 1)
        return false;

    for (int i = 0; i < length; i++) {
        bool failed = !insert_tree_avl(tree, data[i]);
        if (failed)
            return false;
    }

    return true;
}

static inline void print_indent(int level) {
    if (level <= 0)
        return;
    for (int i = 0; i < level - 1; i++) {
        printf("| ");
    }
    printf("|-");
}

static inline bool print_avl_tree_nodes_with_indent(avl_tree_node* node, int level) {
    if (node == NULL || level < 0)
        return false;

    print_indent(level);
    printf("%d\n", node->key);

    avl_tree_node* leftBranch = node->left;
    avl_tree_node* rightBranch = node->right;

    //We've reached the end of the tree (leaf) on both branches
    if (leftBranch == NULL && rightBranch == NULL)
        return true;

    if (leftBranch != NULL)
        print_avl_tree_nodes_with_indent(leftBranch, level + 1);
    else {
        print_indent(level + 1);
        printf("*\n");
    }

    if (rightBranch != NULL)
        print_avl_tree_nodes_with_indent(rightBranch, level + 1);
    else {
        print_indent(level + 1);
        printf("*\n");
    }

    return true;
}

bool print_avl_tree(avl_tree* tree) {
    if (tree == NULL)
        return false;

    avl_tree_node* root = tree->root;
    if (root == NULL)
        return false;

    return print_avl_tree_nodes_with_indent(root, 0);
}

//Dichotomic search
bool search_avl_tree(avl_tree* tree, int key) {
    if (tree == NULL || tree->root == NULL)
        return false;

    avl_tree_node* current = tree->root;

    while (current != NULL) {
        if (key == current->key)
            return true;

        if (key > current->key)
            current = current->right;
        else
            current = current->left;
    }

    return false;
}