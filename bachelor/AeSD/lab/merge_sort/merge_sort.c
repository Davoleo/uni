#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../cmd.h"
#include "../bench.h"
#include "../utils.h"

/*
Compilazione: gcc .\merge_sort.c -o merge_sort

Opzioni:
   max-dim: specifica la massima dimensione n del problema
   -d=<int>: Specifica quanti test lanciare, ciascuno con dimensione diversa [default: 1]
			 la dimensione di ciascun array n e' calcolata: n = k * max-dim / d, k=1..d
   -t=<int>: Specifica quante volte viene lanciato l'algoritmo per una specifica dimensione [default: 1]
			 Utile nel caso in cui l'input viene inizializzato in modo random per calcolare i valori medi
   -verbose: Abilita stampe durante l'esecuzione dell'algoritmo
*/

// esecuzioni
// osservare i vari passaggi
// ./a.out 10 -verbose

// osservare la progressione n log (n)
// ./a.out 100 -d=10

// come cambiano i confronti al variare della dimensione dell'array: divisione ricorsiva a volte chiede piu' confronti (rispetto al caso con albero bilanciato)
// ./a.out 128 -d=128 -t=1

// il numero dei confronti non cambia con diversi input (min=avg=max)
// ./a.out 100 -d=10 -t=100

int ct_swap = 0;
int ct_cmp = 0;

int details = 0;

int n = 0; /// dimensione dell'array

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

void merge(int *A, int p, int q, int r, int *L, int *R)
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

void merge_sort(int *arr, int left_id, int right_id, int *left, int *right)
{
	/// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
	if (right_id < left_id)
	{
		int mid_id = (left_id + right_id) / 2;
		merge_sort(arr, left_id, mid_id, left, right);
		merge_sort(arr, mid_id + 1, right_id, left, right);
		merge(arr, left_id, mid_id, right_id, left, right);
		if (details)
			print_array(arr, n);
	}
}

void run_merge_sort(int* arr, int length)
{
	merge_sort(arr, 0, length)
}

int main(int argc, char** argv)
{

	int* arr;
	int* left;	/// usato come buffer di appoggio
	int* right; /// usato come buffer di appoggio

	args_t args;
	argc = parse_cmd(argc, argv, &args);

	//We need at least 1 argument
	if (argc < 2)
		return 1;

	/// allocazione array
	arr = malloc(sizeof(int) * args.max_dim);
	left = malloc(sizeof(int) * (args.max_dim + 1));
	right = malloc(sizeof(int) * (args.max_dim + 1));

	if (args.div_n > 1)
		printf("Dim_array,N_test,min_swap,avg_swap,max_swap,worst_case_swap,min_cmp,avg_cmp,max_cmp,worst_case_cmp\n");

	// printf("Parametri: max-dim %d, d %d, t %d, verbose %d\n",max_dim,ndiv,ntests,details);

	/// inizializzazione array: numeri random con range dimensione array
	benchmark(arr, run_merge_sort, &args, init_array_normal);

	free(arr);
	free(left);
	free(right);
	return 0;
}
