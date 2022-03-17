#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// compilazione: gcc list.c -o list
//
// Obiettivo:
// 1) analisi allocazioni
// ./a.out -verbose

// 2) implementa print reverse (ricorsivo)

// 3) implementa delete list (con rimozione esplicita di tutti elementi)

// 4) implementa double linked list e inserimento in testa

int ct_swap = 0;
int ct_cmp = 0;
int ct_op = 0; /// operazioni per la ricerca

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node
{
  int val;
  struct node* next;
} node_t;

/// struct per la lista
typedef struct list
{
  node_t* head;
  // node* tail;
  /// per lista doubly linked
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////

list_t* global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata


/**
* \brief Prints the offset of the node to the first global ptr
 */
int get_address(void* node)
{
  return (int)((long)node - (long)global_ptr_ref);
}

void list_print(list_t* l)
{
  printf("Stampa lista\n");

  if (l->head == NULL)
  {
    printf("Lista vuota\n");
  }
  else
  {
    printf("Head in address %d\n", get_address(l->head));

    node_t* current = l->head;

    while (current != NULL)
    {
      if (!details)
        printf("%d, ", current->val);
      else
      { /// stampa completa
        if (current->next == NULL)
          printf("allocato in %d [Val: %d, Next: NULL]\n",
                 get_address(current),
                 current->val);
        else
          printf("allocato in %d [Val: %d, Next: %d]\n",
                 get_address(current),
                 current->val,
                 get_address(current->next));
      }
      current = current->next;
    }
    printf("\n");
  }
}

void list_print_reversed(list_t* list) {
  if (list->head == NULL) {
    puts("Lista Vuota!");
  }
  else {
    node_print_recursive(list->head);
  }
}

void node_print_recursive(node_t* node) {
  puts("Printing linked list in reverse order");

  if (node->next == NULL) {
    puts("Last Node:");
  }
  else {
    node_print_recursive(node->next);
  }
  
  printf("Node: %d", node->val);
}

list_t* list_new(void)
{
  list_t* l = malloc(sizeof(list_t));
  if (details)
  {
    printf("Lista creata\n");
  }

  l->head = NULL; //// perche' non e' l.head ?
  if (details)
  {
    printf("Imposto a NULL head\n");
  }

  return l;
}

void list_delete_iter(list_t* list) {
  while(list->head != NULL);
    list_delete_front(list);
}

void node_delete_recur(node_t* node) {
  if (node->next == NULL)
    puts("Ultimo nodo");
  else {
    node_delete_recur(node->next);
  }

  free(node);
}

void list_delete(list_t* list)
{
  if (list->head != NULL) {
    node_delete_recur(list->head);
  }
  else {
    puts("Lista Vuota!");
  }

  list->head = NULL;

  //// implementare rimozione dal fondo della lista
  //// deallocazione struct list
}

/**
 * Inserts an element before the old head of the list
 * Complessità: O(1)
 */
void list_insert_front(list_t* l, int elem)
{
  /// inserisce un elemento all'inizio della lista
  node_t* new_node = malloc(sizeof(node_t));
  new_node->next = NULL;

  new_node->val = elem;

  new_node->next = l->head;

  l->head = new_node;
}


/**
 * Inserts a new element after the old tail
 * Complessità: O(n) 
 */
void list_insert_tail(list_t* l, int elem)
{
  /// inserisce un elemento alla fine della lista
  /// dato che non c'e' puntatore a last in list_t (possibile miglioramento)
  /// bisogna scorrere tutta la lista!

  node_t* new_node = malloc(sizeof(node_t));
  new_node->next = NULL;

  new_node->val = elem;

  node_t* last_node = l->head;

  if (last_node == NULL)
  { // aggancio direttamente al nodo creato
    l->head = new_node;
  }
  else
  {
    // cerca ultimo nodo
    while (last_node != NULL && last_node->next != NULL)
      last_node = last_node->next;

    last_node->next = new_node;
  }
}

/**
 * Inserisce un elemento dopo un certo elemento ricercato
 * Complessità: O(n)
 */
void list_insert_after(list_t* l, int elem, int search_elem)
{
  /// inserisco il nuovo nodo con contenuto elem
  /// dopo il primo nodo con contenuto search_elem

  node_t* found_node = l->head;
  if (found_node != NULL)
  { /// comincio la ricerca
    // continua a cercare se il nodo non ha il valore richiesto e c'e' ancora un nodo next
    while (found_node->val != search_elem && found_node->next != NULL)
      found_node = found_node->next;

    if (found_node->val == search_elem)
    { // se il nodo ha il valore richiesto -> inserisci nuovo nodo

      /// creo nodo
      node_t* new_node = malloc(sizeof(node_t));
      new_node->next = NULL;
      new_node->val = elem;

      new_node->next = found_node->next;

      found_node->next = new_node;
    }
  }
}

/**
 * Deletes the head of the list
 * Complessità: O(1)
 */
void list_delete_front(list_t *l)
{
  /// elimina il primo elemento della lista
  node_t* node = l->head; // il nodo da eliminare

  if (node == NULL) // lista vuota
    return;

  l->head = node->next;

  node->next = NULL;

  free(node);
}

/**
 * Delete the last element in the list
 * Complessità: O(n)
 */
void list_delete_tail(list_t* l)
{
  /// elimina l'ultimo elemento della lista
  /// dato che non c'e' puntatore a last in list_t (possibile miglioramento)
  /// bisogna scorrere tutta la lista
  /// Siamo sicuri che mantenere un puntatore a last element della lista risolva il problema?

  node_t* but_last_node = l->head; /// cerco penultimo elemento

  if (but_last_node == NULL)
  { // lista vuota
    return;
  }

  if (but_last_node->next == NULL)
  { // lista con un elemento

    l->head = NULL;

    free(but_last_node);

    return;
  }

  /// caso generale
  else
  {
    // cerca penultimo nodo
    while (but_last_node->next->next != NULL) /// se il next del next e' nullo mi fermo -> il next e' l'ultimo!
      but_last_node = but_last_node->next;

    node_t* node_del = but_last_node->next; /// nodo da cancellare

    but_last_node->next = NULL; // sgancio ultimo nodo

    free(node_del);
  }
}

/**
 * Delete an element from the list given the key
 * Complessità: O(n)
 */
void list_delete_node(list_t* l, int search_elem)
{
  /// elimina il primo nodo che contiene search_elem
  node_t* current_node = l->head; /// cerco nodo precedente al nodo che contiene search_elem (devo cambiare il suo next!)

  // casi speciali
  if (current_node == NULL)
  { // lista vuota
    return;
  }

  if (current_node->val == search_elem)
  { // lista con primo elemento da cancellare
    list_delete_front(l);
    return;
  }

  /// caso generale
  else
  {

    // cerca penultimo nodo
    while (current_node->next->next != NULL && current_node->next->val != search_elem) /// se il next del next e' nullo mi fermo -> il next e' l'ultimo! oppure current->next->val == search elem (trovato!)
      current_node = current_node->next;

    if (current_node->next->val == search_elem)
    { /// se il nodo next e' il nodo che cerco, lo cancello

      node_t* node_del = current_node->next; /// nodo da cancellare

      current_node->next = node_del->next; // bypass del nodo

      node_del->next = NULL;

      free(node_del);
    }
  }
}

void print_array(int* A, int dim)
{
  for (int j = 0; j < dim; j++)
  {
    printf("%d ", A[j]);
  }
  printf("\n");
}

void swap(int* a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
  /// aggiorno contatore globale di swap
  ct_swap++;
}

int parse_cmd(int argc, char** argv)
{
  /// controllo argomenti
  int ok_parse = 0;
  for (int i = 1; i < argc; i++)
  {
    if (argv[i][1] == 'v')
    {
      details = 1;
      ok_parse = 1;
    }
    if (argv[i][1] == 'g')
    {
      graph = 1;
      ok_parse = 1;
    }
  }

  if (argc > 1 && !ok_parse)
  {
    printf("Usage: %s [Options]\n", argv[0]);
    printf("Options:\n");
    printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
    printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
    return 1;
  }

  return 0;
}

int main(int argc, char** argv)
{
  int i, test;

  if (parse_cmd(argc, argv))
    return 1;

  list_t* list = list_new();
  global_ptr_ref = list;

  list_insert_front(list, 3);
  list_insert_front(list, 1);
  list_insert_front(list, 2);
  //  list_insert_tail(list,5);

  // list_insert_after(list, 7, 1);
  // list_delete_front(list);
  // list_delete_node(list,3);

  list_print(list);

  // init random
  srand((unsigned)time(NULL));

  return 0;
}
