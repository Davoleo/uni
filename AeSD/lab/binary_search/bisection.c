#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../bench.h"
#include "../utils.h"
#include "../cmd.h"

// compilazione: gcc bisection.c
//
// Ricerca semplice:
// - Caso Pessimo: O(n)
// - Caso Medio: O(n/2) | (assumendo distribuzione uniforme)
// - Caso Ottimo: O(1)
// Ciclo for semplice da 1 a k volte
// 1 Ricerca O(1) + O(n) -> O(n)
// k Ricerche O(1) + kO(n) -> O(kn)

// Alternativa: Preprocessing
//  Sorting: Assumiamo algoritmo generico in: O(nlogn)
//  Binary Search: O(logn)
//  Binary Search da 1 a k volte
//  1 Ricerca: O(nlogn) + O(logn) = O(nlogn)
//  k Ricerche: O(nlogn) + kO(logn) = O(nlogn) + O(klogn)

// Il preprocessing e binary search non conviene mai nel caso di una sola ricerca
// se n = k
// Linear: O(n^2)
// Bisection: O(nlogn)

// Obiettivo:

// ricerca per bisezione su array ordinato
// completare il codice

int details;
int n = 0; /// dimensione dell'array

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	/// aggiorno contatore globale di swap
	swap_ct++;
}

int partition(int *A, int p, int r)
{

	/// copia valori delle due meta p..q e q+1..r
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		compare_ct++;
		if (A[j] <= x)
		{
			i++;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i + 1], &A[r]);

	return i + 1;
}

void quick_sort(int *A, int p, int r)
{
	/// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
	if (p < r)
	{
		int q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}

int bisection(int *A, int n, int t)
{
	int l = 0;
	int r = n - 1;
	while (l <= r)
	{
		op_ct++;
		int m = (l + r) / 2;
		if (details)
			printf("[%d .. %d .. %d]\n", l, m, r);
		if (A[m] < t)
			l = m + 1;
		else
		{
			if (A[m] > t)
				r = m - 1;
			else
				return m; /// trovato
		}
	}
	return -1; // non trovato
}

void call_quicksort(int *arr, int length)
{
	quick_sort(arr, 0, length - 1);
}

int main(int argc, char **argv)
{
	int i, test;
	int *A;
	int *B; /// buffer per visualizzazione algoritmo

	args_t args;
	if (parse_cmd(argc, argv, &args) < 0)
		return 1;

	/// allocazione array
	A = malloc(sizeof(int) * args.max_dim);

	details = args.details;

	// printf("Parametri: max-dim %d, d %d, t %d, verbose %d\n",max_dim,ndiv,ntests,details);

	benchmark(A, &call_quicksort, &args, &init_array_wide);

	free(A);

	return 0;
}
