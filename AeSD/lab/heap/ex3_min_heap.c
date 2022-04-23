#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// compilazione: cc -Wall -Wextra min_heap.c -o heap.out
//

// Test su 10 array di dimensione da 100 a 1000, ripeti 1000 volte con array casuali
// ./heap.out 1000 -d=10 -t=1000

int ct_swap = 0;
int ct_cmp = 0;
int ct_read = 0;

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

/////////// Utility /////////////

void print_array(int* A, int dim)
{
	for (int j = 0; j < dim; j++) {
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

///////// Min Heap Structure ///////////

int max_heap_size;
int* heap;
int heap_size = 0; /// dimensione attuale dell'heap

void heap_allocate(int size)
{
	max_heap_size = size;
	heap = malloc(size * sizeof(int));
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

		heap[current] = elem;
		ct_read++;

		//// Si sistema la relazione con i parent (la struttura potrebbe non essere più un heap)
		int parent = parent_index(current);

		while (parent >= 0 && heap[current] < heap[parent]) {
			ct_read += 2;
			// Valid Parent && Il genitore è più grande -> Swap
			swap(heap + current, heap + parent);

			/// Preparo per la prossima iterazione spostando indietro entrambi gli indici
			current = parent;
			parent = parent_index(parent);
		}

	} else
		printf("Heap pieno!\n");
}

int heap_remove_min()
{
	if (heap_size <= 0) { /// heap vuoto!
		printf("Errore: heap vuoto\n");
		return -1;
	}

	int minimum = heap[0];
	ct_read++;

	if (details)
		printf("Minimo identificato %d\n", minimum);

	/// scambio la radice con l'ultima foglia a destra
	/// il minimum e' stato spostato in fondo --> pronto per l'eliminazione
	ct_read += 2;
	swap(heap, heap + heap_size - 1);

	// elimino il minimum (ora in fondo all'array)
	heap_size--;

	/// nella radice c'e' un valore piccolo (minimo?)
	/// -> non è il minimo perché non ci sono relazioni tra nodi foglia fratelli (quindi potrebbe esserci un fratello più piccolo)
	int i = 0; // indice di lavoro (parto dalla root)

	/// garantisco di fermarmi alla foglia
	while (i >= 0 && !is_leaf(i)) {

		if (details)
			printf("Lavoro con il nodo in posizione i = %d, valore %d\n", i, heap[i]);

		int swap_with = -1; /// -1 ==> Non mi scambio

		int l_child = lchild_index(i);
		int r_child = rchild_index(i);
		// This must exists since the current node is not a leaf (while condition)
		int current_val = heap[i];
		int l_child_val = heap[l_child];
		ct_read += 2;

		// index <- min(L, R)
		ct_cmp++;
		if (l_child_val < current_val) {
			swap_with = l_child;
		}

		// If right child exists
		//  & right child is < than left child
		//  & right child is < than the parent
		ct_read++;
		ct_cmp += 2;
		if (r_child >= 0 && heap[r_child] < l_child_val && heap[r_child] < current_val) {
			swap_with = r_child;
		}

		if (swap_with >= 0) {
			/// swap tra i e swap_with
			ct_read += 2;
			swap(heap + i, heap + swap_with);
		}

		// New index to iterate with
		i = swap_with;
	}

	return minimum;
}

////////////////////////////////////////

int partition(int* A, int p, int r)
{

	/// copia valori delle due meta p..q e q+1..r
	ct_read++;
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++) {
		ct_cmp++;
		ct_read++;
		if (A[j] <= x) {
			i++;
			ct_read++;
			ct_read++;
			swap(A+i, A+j);
		}
	}
	ct_read++;
	ct_read++;
	swap(A+i+1, A+r);

	return i + 1;
}

/**
 * In pre-ordine la funzione partition ritorna un indice su cui dividere l'array e fa in modo
 * che i valori minori o uguali della chiave (pivot) siano nella parte sinistra dell'array
 */
void quick_sort(int* A, int p, int r)
{
	/// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
	if (p < r) {
		int q = partition(A, p, r);
		// Evito di includere il pivot, perché è già al suo posto dopo essere stato scelto da partition
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}

void heap_sort(int* arr, int length)
{
	for (int i = 0; i < length; i++) {
		heap_insert(arr[i]);
		ct_read++;
	}

	for (int i = 0; i < length; i++) {
		arr[i] = heap_remove_min();
	}
}

int parse_cmd(int argc, char** argv)
{
	/// controllo argomenti
	if (argc < 2) {
		printf("Usage: %s max-dim [Options]\n", argv[0]);
		printf("   max-dim: specifica la massima dimensione n del problema\n");
		printf("Options:\n");
		printf("  -d=<int>: Specifica quali dimensioni n del problema vengono lanciate in sequenza [default: 1] \n");
		printf("            n = k * max-dim / d, k=1 .. d\n");
		printf("  -t=<int>: Specifica quanti volte viene lanciato l'algoritmo per una specifica dimensione n [default: 1]\n");
		printf("            Utile nel caso in cui l'input viene inizializzato in modo random\n");
		printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
		printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
		return 1;
	}

	/// parsing argomento
	max_dim = atoi(argv[1]);

	for (int i = 2; i < argc; i++) {
		if (argv[i][1] == 'd')
			ndiv = atoi(argv[i] + 3);
		if (argv[i][1] == 't')
			ntests = atoi(argv[i] + 3);
		if (argv[i][1] == 'v')
			details = 1;
		if (argv[i][1] == 'g') {
			graph = 1;
			ndiv = 1;
			ntests = 1;
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	if (parse_cmd(argc, argv))
		return 1;

	/// allocazione array
	int* A = malloc(sizeof(int) * max_dim);

	/// Allocazione min heap
	heap_allocate(max_dim);

	// init random
	srand((unsigned)time(NULL));

	if (ndiv > 1)
		printf("Dim_array,N_test,min_swap,avg_swap,max_swap,min_cmp,avg_cmp,max_cmp,min_read,avg_read,max_read,n*n,n*log(n)\n");

	// printf("Parametri: max-dim %d, d %d, t %d, verbose %d\n",max_dim,ndiv,ntests,details);

	//// inizio ciclo per calcolare ndiv dimensioni di array crescenti
	for (n = max_dim / ndiv; n <= max_dim; n += max_dim / ndiv) {
		int swap_min = -1;
		int swap_max = -1;
		long swap_avg = 0;

		int cmp_min = -1;
		int cmp_max = -1;
		long cmp_avg = 0;

		int read_min = -1;
		int read_max = -1;
		long read_avg = 0;

		//// lancio ntests volte per coprire diversi casi di input random
		for (int test = 0; test < ntests; test++) {

			/// inizializzazione array: numeri random con range dimensione array
			for (int i = 0; i < n; i++) {
				//A[i] = i;
				//A[i]= n - i;
				A[i]= rand() % (n*10);
			}

			if (details) {
				printf("creato array di dimensione %d\n", n);
				print_array(A, n);
			}

			ct_swap = 0;
			ct_cmp = 0;
			ct_read = 0;

			/// algoritmo di sorting
			quick_sort(A, 0, n - 1);
			//heap_sort(A, n);

			if (details) {
				printf("Output:\n");
				print_array(A, n);
			}

			/// statistiche
			swap_avg += ct_swap;
			if (swap_min < 0 || swap_min > ct_swap)
				swap_min = ct_swap;
			if (swap_max < 0 || swap_max < ct_swap)
				swap_max = ct_swap;
			cmp_avg += ct_cmp;
			if (cmp_min < 0 || cmp_min > ct_cmp)
				cmp_min = ct_cmp;
			if (cmp_max < 0 || cmp_max < ct_cmp)
				cmp_max = ct_cmp;
			read_avg += ct_read;
			if (read_min < 0 || read_min > ct_read)
				read_min = ct_read;
			if (read_max < 0 || read_max < ct_read)
				read_max = ct_read;
		}

		if (ndiv > 1)
			printf("%d,%d,%d,%.1f,%d,%d,%.1f,%d,%d,%.1f,%d,%.1f,%.1f\n",
				n, ntests,
				swap_min, (0.0 + swap_avg) / ntests, swap_max,
				cmp_min, (0.0 + cmp_avg) / ntests, cmp_max,
				read_min, (0.0 + read_avg) / ntests, read_max, 0.0 + n * n, 0.0 + n * log(n) / log(2));
	}

	free(A);

	return 0;
}
