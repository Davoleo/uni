#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "../graph.hh"
#include "../cmd.h"

// compilazione: g++ merge_sort_dot.cc -o merge_sort_dot
//
// Obiettivo: disegnare la sequenza di ordinamenti effettuata e la struttura delle chiamate ricorsive
//   --> 1 Creazione nodi e numerazione univoca per tracciare la ricorsione
//   --> 2 Preparazione disegno con Graphviz dot
//   --> 3 Nodo che descrive il sotto-array corrente (in verde conto l'ordine in cui e' chiamata la attività)

// esecuzioni (per osservare struttura ricorsiva)
// ./a.out 15 -graph; dot graph.dot -Tpdf -o graph.pdf
// ./a.out 16 -graph; dot graph.dot -Tpdf -o graph.pdf
// ./a.out 17 -graph; dot graph.dot -Tpdf -o graph.pdf

// prove con array ordinato crescente, decrescente o random --> come cambia la struttura ricorsiva?

int ct_swap = 0;
int ct_cmp = 0;

int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int* A, int dim)
{
	for (int j = 0; j < dim; j++)
	{
		printf("%d ", A[j]);
	}
	printf("\n");
}

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
	/// aggiorno contatore globale di swap
	ct_swap++;
}

void merge(int* A, int p, int q, int r, int* L, int* R)
{

	/// copia valori delle due meta p..q e q+1..r
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < q - p + 1; i++)
		L[i] = A[p + i];
	L[i] = 1000000; /// un numero grande

	for (i = 0; i < r - q; i++)
		R[i] = A[q + 1 + i];
	R[i] = 1000000; /// un numero grande

	//// dettagli
	if (details)
	{
		printf("Array L (%d .. %d): ", p, q);
		print_array(L, q - p + 1);
		printf("Array R (%d .. %d): ", q + 1, r);
		print_array(R, r - q);
	}

	i = 0; /// usato per gestire array L
	j = 0; /// usato per gestire array R

	for (k = p; k <= r; k++)
	{
		ct_cmp++;
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
}

void merge_sort(int* A, int p, int r, int* L, int* R)
{
	/// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
	if (p < r)
	{
		int q = (p + r) / 2;

		if (graph)
		{
			graph_write_array(A, p, q, "node_before");
			graph_write_array(A, q + 1, r, "node_before");

			/// disegna arco p_r -> p_q
			graph_write_arch(p, r, p, q, "node_before");

			/// disegna arco p_r -> q+1_r
			graph_write_arch(p, r, q+1, r, "node_before");
		}

		merge_sort(A, p, q, L, R);
		merge_sort(A, q + 1, r, L, R);

		if (graph)
		{
			graph_write_array(A, p, q, "node_after");
			graph_write_array(A, q + 1, r, "node_after");

			/// disegna arco p_q -> p_r
			graph_write_arch(p, q, p, r, "node_after");
			
			/// disegna arco q+1_r -> p_r
			graph_write_arch(q+1, r, p, r, "node_after");
		}

		merge(A, p, q, r, L, R);
		if (details)
			print_array(A, n);
	}
	else
	{
		/// disegno archi nodi singoli
		graph_write_arch(p, r, p, r, "node_before", "node_after");
	}
}

int main(int argc, char** argv)
{
	int *A;
	int *L; /// usato come buffer di appoggio
	int *R; /// usato come buffer di appoggio

	args_t args;
	if (parse_cmd(argc, argv, &args) < 0)
		return 1;

	/// allocazione array
	A = new int[args.max_dim];
	L = new int[args.max_dim];
	R = new int[args.max_dim];

	// init random
	srand((unsigned)time(NULL));

	if (graph) 
		graph_open("graph.dot");

	if (args.div_n > 1)
		printf("Dim_array,N_test,min_swap,avg_swap,max_swap,worst_case_swap,min_cmp,avg_cmp,max_cmp,worst_case_cmp\n");

	// printf("Parametri: max-dim %d, d %d, t %d, verbose %d\n",max_dim,ndiv,ntests,details);

	//// inizio ciclo per calcolare 100 dimensioni di array crescenti
	for (n = args.max_dim / args.div_n; n <= args.max_dim; n += args.max_dim / args.div_n)
	{
		int swap_min = -1;
		int swap_max = -1;
		long swap_avg = 0;

		int cmp_min = -1;
		int cmp_max = -1;
		long cmp_avg = 0;

		//// lancio ntests volte per coprire diversi casi di input random
		for (int test = 0; test < args.test_n; test++)
		{

			/// inizializzazione array: numeri random con range dimensione array
			for (int i = 0; i < n; i++)
			{
				// if (graph)
				// A[i]= n - i;
				// A[i]= i;
				// else
				A[i] = rand() % (3 * n);
			}

			if (details)
			{
				printf("creato array di dimensione %d\n", n);
				print_array(A, n);
			}

			ct_swap = 0;
			ct_cmp = 0;

			/// algoritmo di sorting
			if (graph)
				graph_write_array(A, 0, n - 1, "node_before");

			merge_sort(A, 0, n, L, R);

			if (graph)
				graph_write_array(A, 0, n - 1, "node_after");

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
		}

		if (args.div_n > 1)
			printf("%d,%d,%d,%.1f,%d,%.1f,%d,%.1f,%d,%.1f\n",
			       n, args.test_n,
			       swap_min, (0.0 + swap_avg) / args.test_n, swap_max, 0.0,
			       cmp_min, (0.0 + cmp_avg) / args.test_n, cmp_max, n * log(n) / log(2));
	}

	if (graph) 
		graph_close();

	delete[] A;
	delete[] L;
	delete[] R;

	return 0;
}
