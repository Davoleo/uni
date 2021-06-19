#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

struct node
{
    int value;
    struct node* left;
    struct node* right;
};


struct node* create_node(int value)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


void add_child_nodes(struct node** root, int height, int k)
{
    if(*root == NULL)
        *root = create_node(height);

    struct node* copy = *root;

    if(height < k)
    {   
        add_child_nodes(&copy->left, height+1, k);
        add_child_nodes(&copy->right, height+1, k);
    }

    return;
}

void add_leaves(struct node** root, int arr[], int* idP, int len)
{
    //printf("Inizio Id: %d - Val: %d\n", *idx, arr[*idx]);
    struct node* copy = *root;

    if(copy->left == NULL && copy->right == NULL)
    {
        copy->left = create_node(arr[*idP]);
        (*idP)++;
        copy->right = create_node(arr[(*idP)]);
        (*idP)++;
    }
    else {
        add_leaves(&copy->left, arr, idP, len);
        add_leaves(&copy->right, arr, idP, len);
    }

    return;
}

void print(struct node** root)
{
    struct node* c = *root;
    if(*root != NULL)
    {
        print(&c->left);
        printf("%d ", c->value);
        print(&c->right);
    }
}


int main()
{
    struct node* root = create_node(0);

    int k;
    int status = scanf("%d", &k);
    if (status != 1)
        return EXIT_FAILURE;

    int leaves = pow(2, k);
    int arr[leaves];

    for(int i=0; i< leaves; i++)
        scanf("%d", &arr[i]);

    printf("\n---\nTotal Leaves: %d\n---\n", leaves);

    add_child_nodes(&root, 0, k - 1);
    puts("alfkjklsfjkslafjlkf");
    int current_level = 0;
    add_leaves(&root, arr, &current_level, leaves);
    print(&root);

    return EXIT_SUCCESS;
}