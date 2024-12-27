#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

// compilazione: g++ -Wall -Wextra graph_transition_matrix.cc -o graph_matrix.out
//
// Obiettivo - Consegna 4:
// - Implementare la rappresentazione del grafo tramite matrice di adiacenza.
// - Adattare la creazione del grafo e la visita Dfs per lavorare con le matrici.

int details = 0;
int graph = 0;

/// file di output per grafo
std::ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

int ct_visit = 0; // contatore durante visita

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int* V; // elenco dei nodi del grafo
int* V_visitato; // nodo visitato?

int** E; 
int n_nodi;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati grafo
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

void node_print(int n)
{

    output_graph << "node_" << n << "_" << n_operazione << std::endl;
    output_graph << "[ shape = oval; ";
    if (V_visitato[n])
        output_graph << "fillcolor = red; style=filled; ";
    output_graph << "label = "
                 << "\"Idx: " << n << ", val: " << V[n] << "\" ];\n";

    int* current_row = E[n];
	for (int i = 0; i < n_nodi; i++) {
		if (current_row[i]) {
			output_graph << "node_" << n << "_" << n_operazione << " -> ";
        	output_graph << "node_" << i << "_" << n_operazione << " [  color=gray ]\n";
		}
	}
}

void graph_print()
{
    for (int i = 0; i < n_nodi; i++)
        node_print(i);
    n_operazione++;
}

void print_array_graph(int* A, int n, std::string c, int a, int l, int m, int r)
{
    /// prepara il disegno dell'array A ed il suo contenuto (n celle)
    /// a e' il codice del nodo e c la stringa
    /// l,m,r i tre indici della bisezione

    // return ;

	using std::endl;

    output_graph << c << a << " [label=<" << endl;

    /// tabella con contenuto array
    output_graph << "<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\" > " << endl;
    /// indici
    output_graph << "<TR  >";
    for (int j = 0; j < n; j++) {
        output_graph << "<TD ";
        output_graph << ">" << j << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "<TR>";
    // contenuto
    for (int j = 0; j < n; j++) {
        output_graph << "<TD BORDER=\"1\"";
        if (j == m)
            output_graph << " bgcolor=\"#00a000\""; /// valore testato
        else if (j >= l && j <= r)
            output_graph << " bgcolor=\"#80ff80\""; /// range di competenza
        output_graph << ">" << A[j] << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "</TABLE> " << endl;

    output_graph << ">];" << endl;
}

void DFS(int n)
{

    graph_print();

    if (details)
        printf("DFS: lavoro sul nodo %d (visitato %d)\n", n, V_visitato[n]);

    if (V_visitato[n])
        return;

    V_visitato[n] = 1; // prima volta che incontro questo nodo

    if (details)
        printf("Visito il nodo %d (val %d)\n", n, V[n]);

    int* current_row = E[n];
	for (int i = 0; i < n_nodi; i++)
	{
		if (current_row[i]) {
			output_graph << "dfs_" << n << " -> dfs_" << i;
			if (V_visitato[i])
				output_graph << "[color=gray, label = \"" << ct_visit++ << "\"]";
			else
				output_graph << "[color=red, label = \"" << ct_visit++ << "\"]";
			output_graph << std::endl;

			DFS(i);
		}
	}
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
		using std::endl;

        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"LR\"" << endl;
        ;
        //    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;
    }

    n_nodi = 5;
    V = new int[n_nodi];
    V_visitato = new int[n_nodi]; 

    E = new int*[n_nodi];

    // inizializzazione
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato

        E[i] = new int[n_nodi];
		memset(E[i], 0, n_nodi * sizeof(int));

        for (int j = 0; j < n_nodi; j++) {
			if (rand()%2==0)
            	E[i][j] = 1;
        }
    }

    graph_print();

    for (int i = 0; i < n_nodi; i++) {

        printf("Sono il nodo di indice %d nell'array\n", i);
        printf("Il valore del nodo e' %d\n", V[i]);
        printf("La riga della matrice di adiacenza e': ");
        for (int cell = 0; cell < n_nodi; cell++) {
			printf("%d,", E[i][cell]);
		}
		puts("");
    }

    DFS(1);

    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << std::endl;
        output_graph.close();
        std::cout << " File graph.dot scritto" << std::endl
             << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << std::endl;
    }

    return 0;
}
