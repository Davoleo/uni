#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../graphviz.h"

// compilazione: gcc -Wall -Wextra graph_dijkstra_heap.c -o graph_dijkstra.out -lm
//
// Obiettivo:
// 1) grafo con archi pesati
// 2) implementazione shortest path

#define INFTY 1000000

int details = 0;
int graph = 0;

int ct_visit = 0; // contatore durante visita

int n_operazione = 0;

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int val; /// prossimo nodo
    float w; ///* peso dell'arco
    struct node* next;
} node_t;

/// struct per la lista
typedef struct list {
    node_t* head;
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////

//////////////////////////////////////////////////
/// Definizione della struttura dati HEAP
//////////////////////////////////////////////////
typedef struct _heap_elem {
    int node_index;
    float weight;
} heap_elem;

heap_elem* qheap; // "Priority Queue"
int qheap_capacity;
int qheap_size;

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int* V; // elenco dei nodi del grafo
int* V_prev; // nodo precedente dalla visita
float* V_dist; // distanza da sorgente

list_t** E; /// array di puntatori a le liste di adiacenza per ogni nodo
int n_nodi;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati grafo
//////////////////////////////////////////////////

/////////// Utility /////////////

void swap(heap_elem* a, heap_elem* b)
{
    heap_elem tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(int* A, int dim)
{
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

list_t* global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void* node)
{
    return (int)((long)node - (long)global_ptr_ref);
}

list_t* list_new(void)
{
    list_t* l = malloc(sizeof(list_t));
    if (details) {
        printf("Lista creata\n");
    }

    l->head = NULL; //// perche' non e' l.head ?
    if (details) {
        printf("Imposto a NULL head\n");
    }

    return l;
}

void list_insert_front(list_t* l, int elem, float w)
{
    /// inserisce un elemento all'inizio della lista
    node_t* new_node = malloc(sizeof(node_t));
    new_node->next = NULL;

    new_node->val = elem;
    new_node->w = w;

    new_node->next = l->head;

    l->head = new_node;
}

void list_print(list_t* l)
{
    printf("Stampa lista\n");

    if (l->head == NULL) {
        printf("Lista vuota\n");
    } else {
        node_t* current = l->head;

        while (current != NULL) {
            if (!details)
                printf("%d w:%f, ", current->val, current->w);
            else { /// stampa completa
                if (current->next == NULL)
                    printf("allocato in %d [Val: %d, W: %f, Next: NULL]\n",
                        get_address(current),
                        current->val,
                        current->w);
                else
                    printf("allocato in %d [Val: %d, W: %f, Next: %d]\n",
                        get_address(current),
                        current->val,
                        current->w,
                        get_address(current->next));
            }
            current = current->next;
        }
        printf("\n");
    }
}

void node_print(int n)
{
    /// calcolo massima distanza (eccetto infinito)
    float max_d = 0;
    for (int i = 0; i < n_nodi; i++) {
        if (max_d < V_dist[i] && V_dist[i] < INFTY)
            max_d = V_dist[i];
    }

    fprintf(output_graph, "node_%d_%d\n[ shape = oval; ", n, n_operazione);

    bool present = false;
    for (int i = 0; i < qheap_size; i++) {
        if (qheap[i].node_index == n) {
            present = true;
            return;
        }
    }
    if (present)
        fprintf(output_graph, "penwidth = 4; ");

    float col = V_dist[n] / max_d; /// distanza in scala 0..1
    fprintf(output_graph, "fillcolor = \"0.0 0.0 %.1f\"; style=filled; ", col / 2 + 0.5);
    if (V_dist[n] < INFTY)
        fprintf(output_graph, "label = \"Idx: %d, dist: %.1f\" ];\n", n, V_dist[n]);
    else
        fprintf(output_graph, "label = \"Idx: %d, dist: INF\" ];\n", n);

    node_t* elem = E[n]->head;
    while (elem != NULL) {
        /// disegno arco
        dot_write_arch(n, n_operazione, elem->val, n_operazione, "node_", "node_");
        fprintf(output_graph, " [ label=\"%.1f\", len=%.1f ]\n", elem->w, elem->w / 100 * 10);
        elem = elem->next;
    }

    if (V_prev[n] != -1) { // se c'e' un nodo precedente visitato -> disegno arco

        // Cerco arco che va V_prev[n] -> V[n]
        float len = 0;
        node_t* elem = E[V_prev[n]]->head;

        while (elem != NULL) {
            if (elem->val == V[n]) {
                len = elem->w;
            }
            elem = elem->next;
        }

        dot_write_arch(n, n_operazione, V_prev[n], n_operazione, "node_", "node_");
        fprintf(output_graph, " [ color=blue, penwidth=5 len=%f]\n", len / 10);
    }
}

void graph_print()
{
	if (!graph)
		return;
    for (int i = 0; i < n_nodi; i++)
        node_print(i);
    n_operazione++;
}

void heap_allocate(int size)
{
    qheap_capacity = size;
    qheap = malloc(size * sizeof(heap_elem));
}

/// uso -1 per indicare un indice non esistente
int parent_index(int i)
{
    if (i == 0)
        return -1;
    return (i - 1) / 2;
}

int lchild_index(int i)
{
    if (2 * i + 1 >= qheap_size)
        return -1;
    return 2 * i + 1;
}

int rchild_index(int i)
{
    if (2 * i + 2 >= qheap_size)
        return -1;
    return 2 * i + 2;
}

/// restituisce 0 se il nodo in posizione n e' un nodo interno (almeno un figlio)
/// restituisce 1 se il nodo non ha figli
bool is_leaf(int n)
{
    return lchild_index(n) == -1;
    // non c'e' bisogno di controllare il figlio R
    // Perché non può avere un figlio destro se non ha il sinistro
}

void heap_insert(heap_elem elem)
{
    /// inserisco il nuovo nodo con contenuto elem
    /// nell'ultima posizione dell'array
    /// ovvero continuo a completare il livello corrente

    if (details)
        printf("Inserisco elemento %f in posizione %d\n", elem.weight, qheap_size);

    if (qheap_size < qheap_capacity) {
        int current = qheap_size;
        qheap_size++;

        qheap[current] = elem;

        //// Si sistema la relazione con i parent (la struttura potrebbe non essere più un heap)
        int parent = parent_index(current);

        while (parent >= 0 && qheap[current].weight < qheap[parent].weight) {
            // Valid Parent && Il genitore è più grande -> Swap
            swap(qheap + current, qheap + parent);

            /// Preparo per la prossima iterazione spostando indietro entrambi gli indici
            current = parent;
            parent = parent_index(parent);
        }

    } else
        printf("Heap pieno!\n");
}

void heap_change_key(int node_index, float new_weight)
{
    int work_index = -1;

    for (int i = 0; i < qheap_size; i++) {
        if (node_index == qheap[i].node_index) {
            qheap[i].weight = new_weight;
            work_index = i;
        }
    }

    if (work_index == -1)
        return;

    //// Si sistema la relazione con i parent (la struttura potrebbe non essere più un heap)
    int parent = parent_index(work_index);

    while (parent >= 0 && qheap[work_index].weight < qheap[parent].weight) {
        // Valid Parent && Il genitore è più grande -> Swap
        swap(qheap + work_index, qheap + parent);

        /// Preparo per la prossima iterazione spostando indietro entrambi gli indici
        work_index = parent;
        parent = parent_index(parent);
    }
}

heap_elem heap_remove_min()
{
    if (qheap_size <= 0) { /// heap vuoto!
        printf("Errore: heap vuoto\n");
        heap_elem undefined = { -1, 0.0F };
        return undefined;
    }

    heap_elem minimum = qheap[0];

    if (details)
        printf("Minimo identificato %f\n", minimum.weight);

    /// scambio la radice con l'ultima foglia a destra
    /// il minimum e' stato spostato in fondo --> pronto per l'eliminazione
    swap(qheap, qheap + qheap_size - 1);

    // elimino il minimum (ora in fondo all'array)
    qheap_size--;

    /// nella radice c'e' un valore piccolo (minimo?)
    /// -> non è il minimo perché non ci sono relazioni tra nodi foglia fratelli (quindi potrebbe esserci un fratello più piccolo)
    int i = 0; // indice di lavoro (parto dalla root)

    /// garantisco di fermarmi alla foglia
    while (i >= 0 && !is_leaf(i)) {

        if (details)
            printf("Lavoro con il nodo in posizione i = %d, peso %f\n", i, qheap[i].weight);

        int swap_with = -1; /// -1 ==> Non mi scambio

        int l_child = lchild_index(i);
        int r_child = rchild_index(i);
        // This must exists since the current node is not a leaf (while condition)
        float current_val = qheap[i].weight;
        float l_child_val = qheap[l_child].weight;

        // index <- min(L, R)
        if (l_child_val < current_val) {
            swap_with = l_child;
        }

        // If right child exists
        //  & right child is < than left child
        //  & right child is < than the parent
        float r_child_val = qheap[r_child].weight;
        if (r_child >= 0 && r_child_val < l_child_val && r_child_val < current_val) {
            swap_with = r_child;
        }

        if (swap_with >= 0) {
            /// swap tra i e swap_with
            swap(qheap + i, qheap + swap_with);
        }

        // New index to iterate with
        i = swap_with;
    }

    return minimum;
}

void shortest_path(int n)
{
    // Nodo da cui si parte -> Distanza 0
    V_dist[n] = 0;

    heap_allocate(n_nodi);

    for (int i = 0; i < n_nodi; i++) {
        if (i != n) {
            V_prev[i] = -1; // non c'e' precedente
            V_dist[i] = INFTY; // infinito
        }
        heap_elem elem = { i, V_dist[i] };
        heap_insert(elem);
    }

    while (qheap_size != 0) {
        // Estrazione del minimo (qheapsize è diminuito)
        heap_elem minimum = heap_remove_min();

        int min_index = minimum.node_index;

        if (min_index >= 0) {
            // Esploro la lista di adiacenza
            node_t* elem = E[min_index]->head;
            while (elem != NULL) {
                // Costo/distanza per arrivare al nuovo nodo passando per best_index
                float alt = V_dist[min_index] + elem->w;
                // Il percorso alternativo che passa per best_index migliora il percorso attuale che va direttamente a elem->val
                if (alt < V_dist[elem->val]) {
                    V_dist[elem->val] = alt;
                    V_prev[elem->val] = min_index;
                    heap_change_key(elem->val, alt);
                }

                elem = elem->next;
            }
        }
    }

    graph_print();
}

int parse_cmd(int argc, char** argv)
{
    /// controllo argomenti
    int ok_parse = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][1] == 'v') {
            details = 1;
            ok_parse = 1;
        }
        if (argv[i][1] == 'g') {
            graph = 1;
            ok_parse = 1;
        }
    }

    if (argc > 1 && !ok_parse) {
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
    // init random
    srand((unsigned)time(NULL));

    if (parse_cmd(argc, argv)) {
        return 1;
    }

    if (graph)
        dot_open("dijkstra.dot");

    int matrix_size = 4;
    n_nodi = matrix_size * matrix_size;

    //// init nodi
    V = malloc(sizeof(int) * n_nodi);
    V_prev = malloc(sizeof(int) * n_nodi);
    V_dist = malloc(sizeof(float) * n_nodi);

    //// init archi
    E = malloc(sizeof(list_t*) * n_nodi);

    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = i;
        E[i] = list_new();

        if (i == 0)
            global_ptr_ref = E[i];

        int x = i % matrix_size;
        int y = i / matrix_size;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // Limito gli archi ai vicini con 1 variazioneassoluta sulle cordinate
                if (abs(dx) + abs(dy) == 1) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < matrix_size && ny >= 0 && ny < matrix_size) {
                        int new_index = nx + matrix_size * ny;
                        list_insert_front(E[i], new_index, 15 * sqrt(abs(dx) + abs(dy)));
                    }
                }
            }
        }
    }

    // Small Shortcut Example
    // list_insert_front(E[0], 1, 50);
    // list_insert_front(E[0], 2, 10);
    // list_insert_front(E[2], 3, 10);
    // list_insert_front(E[3], 1, 10);
    // list_insert_front(E[1], 4, 20);

    graph_print();

    for (int i = 0; i < n_nodi; i++) {
        printf("Sono il nodo di indice %d nell'array\n", i);
        printf("Il valore del nodo e' %d\n", V[i]);
        printf("La lista di adiacenza e'\n");
        list_print(E[i]);
    }

    shortest_path(0);

    if (graph)
        dot_close();

    return 0;
}
