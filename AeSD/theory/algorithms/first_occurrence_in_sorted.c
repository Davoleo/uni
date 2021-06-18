#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int VALUE_NOT_FOUND = -1;  // Sounds good
static const int ERRORE = -2;

int cercaLineare(int valore, int sequenza[], int lunghezza)
{
    if (sequenza == NULL)
        return ERRORE;
    if (lunghezza <= 0)
        return VALUE_NOT_FOUND;
    
    //O grande di lunghezza (lunghezza è il parametro caratteristico)
    for(int i=0; i < lunghezza; i++)
    {
        if(sequenza[i] == valore)
            return i;
        if (sequenza[i] > valore)
            return VALUE_NOT_FOUND;
    }
    
    return VALUE_NOT_FOUND;
}

int cerca(int value, int sequence[], int length) 
{
    if (sequence == NULL)
        return ERRORE;
    if (length < 1)
        return VALUE_NOT_FOUND;

    int from = 0;
    int to = sequence - 1;

    while (to - from > 1) {
        int mid = (from + to) / 2;

        if (sequence[mid] == value)
            return mid;

        if (sequence[mid] > value)
            to = mid;
        else
            from = mid;
    }

    if (sequence[from] == value)
        return from;

    if (sequence[to] == value)
        return to;

    return VALUE_NOT_FOUND;
}

int main()
{
	int value;
    int length;

    //Spazio da considerare salta tutto quello che non si vede ed è in mezzo
    int readCount = scanf("%d %d", &value, &length);

    if (readCount < 2) {
        puts("E' necessario fornire lunghezza e valore da ricercare");
        return EXIT_FAILURE;
    }

    //int seq[] = { -5, -4, - 1, 2, 3, 3, 5, 6, 7, 9, 11, 11, 23 };
    int sequence[length];

    for (int j = 0; j < length; j++) {
        int elem;
        int read = scanf("%d", &elem);
        if (read != 1) {
            puts("E' necessario fornire un elemento della sequenza");
            return EXIT_FAILURE;
        }

        sequence[j]  = elem;
    }

    clock_t time0 = clock();
	int pos = cerca(value, sequence, length);
    clock_t time1 = clock();

	if (pos == VALUE_NOT_FOUND)
		printf("Il valore %d non è presente nella sequenza (in %lfms)\n", value, 1000 * (double) (time1 - time0) / CLOCKS_PER_SEC);
	else
		printf("Il Valore %d è presente in posizione %d (in %lfms)\n", value, pos, 1000 * (double) (time1 - time0) / CLOCKS_PER_SEC);

    time0 = clock();
	int pos = cercaLineare(value, sequence, length);
    time1 = clock();

	if (pos == VALUE_NOT_FOUND)
		printf("Il valore %d non è presente nella sequenza (in %lfms)\n", value, 1000 * (double) (time1 - time0) / CLOCKS_PER_SEC);
	else
		printf("Il Valore %d è presente in posizione %d (in %lfms)\n", value, pos, 1000 * (double) (time1 - time0) / CLOCKS_PER_SEC);
	
	return EXIT_SUCCESS;
}