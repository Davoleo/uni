typedef struct _list_node {
    int data;
    _list_node* next;
    _list_node* prev;
} node;

typedef struct {
    int length;
    node* head;
    node* tail;
} list;

typedef struct {
    node* current;
} list_iterator;

typedef bool(*list_visitor) (int key, void* data);

extern list* create_list(void);

extern bool delete_list(list* l);

extern bool fill_list(list* l, int data[], int length);

extern bool list_insert_head(list* l, int key);
extern bool list_insert_tail(list* l, int key);

extern bool list_remove_head(list* l);
extern bool list_remove_tail(list* l);

extern bool print_list(list* l);
extern bool print_list_reverse(list* l);

extern bool list_search(list* l, int k);

//Returns false when the iteration should be terminated before the end
extern bool list_visit(list* list, list_visitor iterFun, void* data);
extern bool list_visit_reverse(list* list, list_visitor iterFun, void* data);

extern bool list_remove_if(list* list, list_visitor predFun, void* data);

extern list_iterator* list_create_iterator(list* list);
extern bool list_delete_iterator(list_iterator* iter);
