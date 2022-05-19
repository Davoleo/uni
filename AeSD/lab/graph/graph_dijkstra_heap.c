#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// compilazione: g++ -Wall -Wextra graph_dijkstra.cc -o graph_dijkstra.out
//
// Obiettivo:
// 1) grafo con archi pesati
// 2) implementazione shortest path

#define INFTY 1000000

int details = 0;
int graph = 0;

int ct_visit = 0; // contatore durante visita

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
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int* V; // elenco dei nodi del grafo
int* V_visitato; // nodo visitato?  (Sono nella coda / non sono nella coda)
int* V_prev; // nodo precedente dalla visita

list_t** E; /// array di puntatori a le liste di adiacenza per ogni nodo
int n_nodi;

///////// Min Heap Structure ///////////
int max_heap_size;
float* dist_heap;
int heap_size = 0; /// dimensione attuale dell'heap

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati grafo
//////////////////////////////////////////////////

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

void swap(int* a, int* b) {
	int temp = *b;
	*a = *b;
	*b = temp;
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

/////////////////// Heap Functions /////////////////////////

void heap_allocate(int size)
{
	max_heap_size = size;
	dist_heap = malloc(size * sizeof(float));
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
	if (2 * i + 1 >= heap_size)
		return -1;
	return 2 * i + 1;
}

int rchild_index(int i)
{
	if (2 * i + 2 >= heap_size)
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

void heap_insert(int elem)
{
	/// inserisco il nuovo nodo con contenuto elem
	/// nell'ultima posizione dell'array
	/// ovvero continuo a completare il livello corrente

	if (details)
		printf("Inserisco elemento %d in posizione %d\n", elem, heap_size);

	if (heap_size < max_heap_size) {
		int current = heap_size;
		heap_size++;

		dist_heap[current] = elem;

		//// Si sistema la relazione con i parent (la struttura potrebbe non essere più un heap)
		int parent = parent_index(current);

		while (parent >= 0 && dist_heap[current] < dist_heap[parent]) {
			// Valid Parent && Il genitore è più grande -> Swap
			swap(dist_heap + current, dist_heap + parent);

			/// Preparo per la prossima iterazione spostando indietro entrambi gli indici
			current = parent;
			parent = parent_index(parent);
		}

	} else
		printf("Heap pieno!\n");
}

float heap_get_min() {
	if (heap_size <= 0) {
		puts("Errore: heap vuoto");
		return -1;
	}

	return dist_heap[0];
}

float heap_remove_min() {

	if (heap_size <= 0) { /// heap vuoto!
		printf("Errore: heap vuoto\n");
		return -1;
	}

	int minimum = dist_heap[0];

	if (details)
		printf("Minimo identificato %d\n", minimum);

	/// scambio la radice con l'ultima foglia a destra
	/// il minimum e' stato spostato in fondo --> pronto per l'eliminazione
	swap(dist_heap, dist_heap + heap_size - 1);

	// elimino il minimum (ora in fondo all'array)
	heap_size--;

	/// nella radice c'e' un valore piccolo (minimo?)
	/// -> non è il minimo perché non ci sono relazioni tra nodi foglia fratelli (quindi potrebbe esserci un fratello più piccolo)
	int i = 0; // indice di lavoro (parto dalla root)

	/// garantisco di fermarmi alla foglia
	while (i >= 0 && !is_leaf(i)) {

		if (details)
			printf("Lavoro con il nodo in posizione i = %d, valore %d\n", i, dist_heap[i]);

		int swap_with = -1; /// -1 ==> Non mi scambio

		int l_child = lchild_index(i);
		int r_child = rchild_index(i);
		// This must exists since the current node is not a leaf (while condition)
		int current_val = dist_heap[i];
		int l_child_val = dist_heap[l_child];

		// index <- min(L, R)
		if (l_child_val < current_val) {
			swap_with = l_child;
		}

		// If right child exists
		//  & right child is < than left child
		//  & right child is < than the parent
		int r_child_val = dist_heap[r_child];
		if (r_child >= 0 && r_child_val < l_child_val && r_child_val < current_val) {
			swap_with = r_child;
		}

		if (swap_with >= 0) {
			/// swap tra i e swap_with
			swap(dist_heap + i, dist_heap + swap_with);
		}

		// New index to iterate with
		i = swap_with;
	}

	return minimum;
}

void print_array(int* A, int dim)
{
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

void shortest_path(int n)
{

	heap_insert(0);
	dist_heap[n] = 0;


	while (heap_size != 0)
	{
		///Trova il minimo in coda
		float best_dist = heap_get_min();
		
		///Estrae dalla coda
		V_visitato[best_index] = 1;

		//Esploro la lista di adiacenza
		node_t* elem = E[best_index]->head;
		while(elem != NULL) {
			//Se il nodo della lista (elem->val) non è ancora stato visitato -> possiamo procedere
			if (V_visitato[elem->val] == 0) {
				//Costo/distanza per arrivare al nuovo nodo passando per best_index
				float alt = dist_heap[best_index] + elem->w; 
				//Il percorso alternativo che passa per best_index migliora il percorso attuale che va direttamente a elem->val
				if (alt < dist_heap[elem->val]) {
					dist_heap[elem->val] = alt;
					V_prev[elem->val] = best_index;
				}
			}

			elem = elem->next;
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

    if (parse_cmd(argc, argv))
        return 1;

	int matrix_size = 5;
    n_nodi = matrix_size*matrix_size;

    //// init nodi
    V = malloc(sizeof(int) * n_nodi);
    V_visitato = malloc(sizeof(int) * n_nodi);
    V_prev = malloc(sizeof(int) * n_nodi);
    heap_allocate(n_nodi);

    //// init archi
    E = malloc(sizeof(node_t*) * n_nodi); //(list_t**)malloc(n_nodi*sizeof(list_t*));

    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato
        V_prev[i] = -1; // non c'e' precedente
        dist_heap[i] = INFTY; // infinito

        E[i] = list_new();

        if (i == 0)
            global_ptr_ref = E[i];


		int x = i%matrix_size;
		int y = i/matrix_size;
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				//Limito gli archi ai vicini con 1 variazioneassoluta sulle cordinate
				if (abs(dx) + abs(dy) >= 1) {
					int nx = x+dx;
					int ny = y+dy;
					if (nx >= 0 && nx < matrix_size && ny >= 0 && ny < matrix_size) {
						int new_index = nx + matrix_size * ny;
						list_insert_front(E[i], new_index, 15 * sqrt(abs(dx) + abs(dy)));
					}
				}
			}
		}

		/*
        for (int j = 0; j < n_nodi; j++) {
            // if (rand()%2==0)
            if (i < j)
                list_insert_front(E[i], j, 10 * (3 + j + i));

			//Grafo forma matrice di quadratini
        }
		*/
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

	puts("test");

    shortest_path(0);

    return 0;
}
