#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

// compilazione: g++ tree_dot.c -o tree
//

// Al contrario degli alberi la lista suppone un ordinamento totale sugli elementi
// per l'operatore next
// 
// Proprietà di un Albero:
// - Non avere puntatori che puntano ad oggetti posizionati più in alto nella gerarchia
//   - Non punta mai ai padri
// - Non contiene cicli di puntatori che fanno ritornare nello stesso nodo
// - Numero esponenziale di nodi per ogni livello aggiunto

// Alberi binari
// - n nodi -> log_2(n) livelli -> Algoritmo Ricerca O(log(n))

// Obiettivo:
// 1) struttura dati, allocazione nodo, inserimento manuale nodi
// 2) creazione albero random

// 3) visita inorder
// 4) implementare visita preorder, postorder
// 5) delete albero
// 6) euler tour: stampa e ricostruzione albero da lista nodi
// 	 	Stampato in pre, in e post ordine contemporaneamente (meccanismo anche utilizzato per le parentesi)

// 7) flip albero

// 8) height - depth
// 9) isBalanced

//Concetti Visite alberi binari:
	//Pre-ordine: Prima stampo il nodo stesso e poi chiamo ricorsivamente
		//Primo nodo stampato: Radice
		//Priorità: Stampare il nodo stesso > Scendere a sinistra > Scendere a destra
	//Post-ordine: Prima faccio tutte le chiamate ricorsive e poi prima di ritornare stampo il nodo
		//Il primo nodo stampato è quello più a sinistra (espanso prima) senza figli (e.g. quello che ritorna prima)
		//L'ultimo nodo stampato è la radice
		//Priorità: Scendere a sinistra > Scendere a destra > Stampare il nodo stesso
	//In-Ordine:
		//Primo nodo stampato: primo nodo a sinistra senza figli a sinistra
		//Priorità: Scendere a sinistra > Stampare il nodo stesso > Scendere a destra
		//Collegato al parsing della notazione infissa
		//Ambiguita insita perdita di informazione sulla posizione dei sottoalberi

int ct_swap = 0;
int ct_cmp = 0;
int ct_op = 0; /// operazioni per la ricerca

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

ofstream output_visit;
ifstream input_visit;

//////////////////////////////////////////////////
/// Definizione della struttura dati tree
//////////////////////////////////////////////////

/// struct per il nodo dell'albero
typedef struct node {
    int val;
    struct node* L;
    struct node* R;
} node_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati tree
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

node_t* global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void* node)
{
    if (node == NULL)
        return 0;
    return (int)((long)node - (long)global_ptr_ref);
}

/// stampa il codice del nodo per dot
void print_node_code(node_t* n)
{
    output_graph << "node_" << get_address(n) << "_" << n_operazione;
}

void node_print_graph(node_t* n)
{

    print_node_code(n);
    output_graph << "\n[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n<TR> <TD CELLPADDING=\"3\" BORDER=\"0\"  ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
    output_graph << get_address(n) << "</TD> </TR><TR>\n<TD PORT=\"val\" bgcolor=\"#a0FFa0\">";
    output_graph << n->val << "</TD>\n <TD PORT=\"L\" ";
    if (n->L == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->L);
    output_graph << "</TD>\n <TD PORT=\"R\" ";
    if (n->R == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->R);
    output_graph << "</TD>\n</TR></TABLE>>];\n";

    /// visualizzazione figli sullo stesso piano
    if (n->L != NULL && n->R != NULL) {
        output_graph << "rank = same; ";
        print_node_code(n);
        output_graph << ";";
        print_node_code(n->L);
        output_graph << ";\n";
    }

    // mostro archi uscenti

    if (n->L != NULL) { /// disegno arco left
        print_node_code(n);
        output_graph << ":L:c -> ";
        print_node_code(n->L);
        output_graph << ":id ;\n";
    }

    if (n->R != NULL) { /// disegno arco R
        print_node_code(n);
        output_graph << ":R:c -> ";
        print_node_code(n->R);
        output_graph << ":id ;\n";
    }
}

void tree_print_rec_graph(node_t* n)
{
    if (n != NULL) {
        node_print_graph(n);
        tree_print_rec_graph(n->L);
        tree_print_rec_graph(n->R);
    }
}

void tree_print_graph(node_t* n)
{
    /// stampa ricorsiva del noto
    tree_print_rec_graph(n);
    n_operazione++;
}

void node_print(node_t* n)
{
    if (n == NULL)
        printf("Puntatore vuoto\n");
    else
        printf("allocato in %d [Val: %d, L: %d, R: %d]\n",
            get_address(n),
            n->val,
            get_address(n->R),
            get_address(n->L));
}

node_t* node_new(int elem)
{ /// crea nuovo nodo
    node_t* t = new node_t;
    if (details) {
        printf("nodo creato\n");
    }

    t->val = elem;
    t->L = NULL;
    t->R = NULL;
    if (details) {
        printf("Imposto a NULL children\n");
    }

    return t;
}

void tree_insert_child_L(node_t* n, int elem)
{
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Left del nodo n

    /// creo nodo
    n->L = node_new(elem);
}

void tree_insert_child_R(node_t* n, int elem)
{
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Right del nodo n
    n->R = node_new(elem);
}

int max_nodes = 8;
int n_nodes = 0;

void insert_random_rec(node_t* n)
{
    //// inserisce in modo random un nodo L e R e prosegue ricorsivamente
    /// limito i nodi interni totali, in modo da evitare alberi troppo grandi

    printf("inserisco %d\n", n_nodes);

    if (n_nodes++ >= max_nodes) /// limito il numero di nodi
        return;
    printf("inserisco %d\n", n_nodes);

    float probabilita = 0.5; /// tra 0 e 1

    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        tree_insert_child_R(n, rand() % 100);
    }
    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso
        tree_insert_child_L(n, rand() % 100);
    }
    if (n->L != NULL)
        insert_random_rec(n->L);
    if (n->R != NULL)
        insert_random_rec(n->R);
}

int ct_visit = 0;

void inOrder(node_t* n)
{

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        inOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        inOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }
}

void preOrder(node_t* n)
{

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        preOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        preOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }
}

void postOrder(node_t* n)
{

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        postOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        postOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }
}

void EulerOrder(node_t* n)
{

    if (details)
        printf("%d ", n->val);

    output_visit << n->val << "\n";

    if (graph) {
        node_print_graph(n);
    }

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        EulerOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        EulerOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";
}
///////
/// crea una copia dell'albero in input, scambiando i sottoalberi L e R
///////
node_t* flip(node_t* origin)
{
	if (origin == nullptr)
		return nullptr;

    node_t* flipped = node_new(origin->val);
	flipped->L = flip(origin->R);
	flipped->R = flip(origin->L);

    return flipped;
}

//////
/// costruzione albero in base ai valori stampati dalla visita di eulero
/// la funzione restituisce il puntatore alla radice dell'albero
/// Es. input: 32 74 74 64 76 76 44 44 44 76 64 64 74 32 85 85 2 36 36 36 2 85 85 85 2 85 32
//////
node_t* build_euler(int val1)
{
	//The three values from the euler notation
	int val2, val3;
	node_t* new_node = node_new(val1);
	
	input_visit >> val2;

	//There's a subtree on the left
    if (val1 != val2) {
        new_node->L = build_euler(val2);
		//returning from inner recursive call (we can skip the next node in the visit)
		//As the next val2 is going to be == val1
		input_visit >> val2;
		assert(val1 == val2);
    }

	input_visit >> val3;

	//There's a subtree on the right
    if (val2 != val3) {
        new_node->R = build_euler(val3);
		//returning from inner recursive call (we can skip the next node in the visit)
		//As the next val2 is going to be == val3
		input_visit >> val3;
		assert(val2 == val3);
    }

    return new_node;
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
    if (parse_cmd(argc, argv))
        return 1;

    // init random
    srand((unsigned)time(NULL));

    if (graph) {
        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"TB\"" << endl;
        ;
        output_graph << "edge[tailclip=false,arrowtail=dot];" << endl;
    }

	//* UNCOMMENT HERE TO TEST FLIPPED TREE COPY
    node_t* root = node_new(5);
    global_ptr_ref = root;

    tree_insert_child_L(root, 7);
    tree_insert_child_R(root, 4);
    tree_insert_child_L(root->L, 8);
    tree_insert_child_R(root->L, 2);
    tree_insert_child_L(root->R, 1);
    tree_insert_child_R(root->R, 3);
	tree_insert_child_R(root->L->R, 10);
    tree_print_graph(root);

	node_t* flipped_tree = flip(root);
	tree_print_graph(flipped_tree);

    // creo albero random
    /*
    insert_random_rec(root);
    tree_print_graph(root);
    */

    // stampa visita di eulero
    /*
    output_visit.open("visit.txt");
    EulerOrder(root);
    output_visit.close();
    printf("\n");
    */

    // stampa albero
    //tree_print_graph(root);
    n_operazione++;

    //* UNCOMMENT HERE TO TEST EULER TREE BUILD
    // input_visit.open("visit.txt");
	// int root_val;
	// input_visit >> root_val;
    // node_t* root = build_euler(root_val);
	// preOrder(root);
	// global_ptr_ref=root;
    // input_visit.close();
    // tree_print_graph(root);

    /*
      node_t* root1=flip(root);
      tree_print_graph(root);
    */

    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        cout << " File graph.dot scritto" << endl
             << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << endl;
    }

    return 0;
}
