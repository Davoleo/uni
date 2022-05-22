#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

// compilazione: g++ -Wall -Wextra graph_dijkstra.cc -o graph_dijkstra.out
//
// Obiettivo:
// 1) grafo con archi pesati
// 2) implementazione shortest path

#define INFTY 1000000

int details = 0;
int graph = 0;

/// file di output per grafo
std::ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

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
    node* head;
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
float* V_dist; // distanza da sorgente

list_t** E; /// array di puntatori a le liste di adiacenza per ogni nodo
int n_nodi;

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

void node_print(int n)
{

    /// calcolo massima distanza (eccetto infinito)
    float max_d = 0;
    for (int i = 0; i < n_nodi; i++)
        if (max_d < V_dist[i] && V_dist[i] < INFTY)
            max_d = V_dist[i];

    output_graph << "node_" << n << "_" << n_operazione << std::endl;
    output_graph << "[ shape = oval; ";

    if (V_visitato[n] == 1)
        output_graph << "penwidth = 4; ";

    float col = V_dist[n] / max_d; /// distanza in scala 0..1
    output_graph << "fillcolor = \"0.0 0.0 " << col / 2 + 0.5 << "\"; style=filled; ";
    if (V_dist[n] < INFTY)
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: " << V_dist[n] << "\" ];\n";
    else
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: INF\" ];\n";

    node_t* elem = E[n]->head;
    while (elem != NULL) { /// disegno arco
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione << " [ label=\"" << elem->w << "\", len=" << elem->w / 100 * 10 << " ]\n";
        elem = elem->next;
    }

    if (V_prev[n] != -1) { // se c'e' un nodo precedente visitato -> disegno arco

		//Cerco arco che va V_prev[n] -> V[n]
		float len = 0;
		node_t* elem = E[V_prev[n]]->head;
		while (elem != NULL) {
			if (elem->val == V[n]) {
				len = elem->w;
			}
			elem = elem->next;
		}

        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << V_prev[n] << "_" << n_operazione << " [ color=blue, penwidth=5 len=" << len << "]\n";
    }
}

void graph_print()
{
    for (int i = 0; i < n_nodi; i++)
        node_print(i);
    n_operazione++;
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
    list_t* l = new list;
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
    node_t* new_node = new node_t;
    new_node->next = NULL;

    new_node->val = elem;
    new_node->w = w;

    new_node->next = l->head;

    l->head = new_node;
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
	V_dist[n] = 0;

	//Contatore degli elementi in coda (V_visitato)
	int q_size = n_nodi; 

	while (q_size != 0)
	{
		///Trova il minimo in coda
		float best_dist = INFTY;
		int best_index = -1;
		for (int i = 0; i < n_nodi; i++) {
			//Il nodo è in coda (non ancora visitato) ed è migliore del nodo corrente
			if (V_visitato[i] == 0 && V_dist[i] < best_dist) {
				best_dist = V_dist[i];
				best_index = i;
			}
		}
		
		if (best_index >= 0) {
			///Estrae dalla coda
			V_visitato[best_index] = 1;
			q_size--;

			//Esploro la lista di adiacenza
			node_t* elem = E[best_index]->head;
			while(elem != NULL) {
				//Se il nodo della lista (elem->val) non è ancora stato visitato -> possiamo procedere
				if (V_visitato[elem->val] == 0) {
					//Costo/distanza per arrivare al nuovo nodo passando per best_index
					float alt = V_dist[best_index] + elem->w; 
					//Il percorso alternativo che passa per best_index migliora il percorso attuale che va direttamente a elem->val
					if (alt < V_dist[elem->val]) {
						V_dist[elem->val] = alt;
						V_prev[elem->val] = best_index;
					}
				}

				elem = elem->next;
			}
		}
		else {
			//Coda non vuota => nodi irragiungibili -> FINE [annullo la coda]
			q_size = 0;
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
	using std::endl;

    // init random
    srand((unsigned)time(NULL));

    if (parse_cmd(argc, argv))
        return 1;

    if (graph) {
        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"LR\"" << endl;
        ;
        //    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;
    }

	int matrix_size = 5;
    n_nodi = matrix_size*matrix_size;

    //// init nodi
    V = new int[n_nodi];
    V_visitato = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];

    //// init archi
    E = new list_t*[n_nodi]; //(list_t**)malloc(n_nodi*sizeof(list_t*));

    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato
        V_prev[i] = -1; // non c'e' precedente
        V_dist[i] = INFTY; // infinito

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

    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        std::cout << " File graph.dot scritto" << endl
             << "****** Creare il grafo con: neato graph.dot -Tpdf -o graph.pdf" << endl;
    }

    return 0;
}
