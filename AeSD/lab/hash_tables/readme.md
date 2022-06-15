# HASH TABLE
- INSERT (...)
- FIND (...)
- DELETE

### Decisione Struttura dati 
Operazioni di INSERT FIND e DELETE nelle varie strutture dati
- LISTA -> O(1) O(n) O(n)
- HEAP -> O(logn) O(n)
- BST -> O(logn) O(logn)
- TABELLA -> O(1) O(1)

## Tabella
- Memorizzare informazioni in un array, ma trovando un sistema di passare da una chiave all'indice dell'array underlying
- Questo sistema è la funzione di hash che si usa per convertire da chiave a indice array
- Problema di Collisions
  - Collisione: 2 chiavi diverse producono lo stesso indice nella funzione di hash
  - Dipendono dalla funzione, dal numero di chiavi e dalla dimensione della tabella
  - Risoluzione: 
    a. O si trova un metodo di tenere più record nella stessa chiave
	  - Address Chaining: l'array in realtà contiene dei puntatori ad una lista a cui vengono attaccati i nuovi records in collisione
	  - Si cerca di mantenere la lunghezza della lista comunque bassa
	  - `E[number of elements hashed to the same location as x] = ∑all elements y Pr[y is hashed to the same location as x] = n * (1/m) = n/m.`
	b. spostare uno dei records in un altro luogo
	  - Open Addressing: Quando si va in conflitto si scende nell'array finché non si trova un buco libero (cercando di scendere il meno possibile)
	    - Funziona bene solo quando la tabella è abbastanza vuota (altrimenti tende molto velocemente a O(n))

## Funzioni di HASH
- Esempio Semplice:
```
  F(string s) {
	int H = 0;
	for i -> len(s) {
		H+= (H + S+[i]) %N
	}
  }
```
  - Tante collisioni quando scambi l'ordine di caratteri nella stringa, quando si aggiungono più di un carattere.
- **Metodo di Divisione**
  - Prendo la stringa e il resto della divisione mod m (grandezza della tabella)
  - Con certi m sfortunati la funzione crea tanti collisioni
  - I numeri primi (grandi) hanno una probabilità molto più bassa di creare collisioni in questo metodo
```c
/* treat strings as base-256 integers
   with digits in the range 1:255 */
#define BASE (256)

unsigned long hash(const char* s, unsigned long m) {
	unsigned long h;
	unsigned const char* us;

	//Cast s to unsigned const char
	//this ensures that elements of s will be treated as having values >= 0
	us = (unsigned const char*) s;

	h = 0;
	while(*us != '\0') {
		h = (h * BASE + *us) % m;
		us++;
	} 

	return h;
}
```
- **Metodo di Moltiplicazione**
  - Moltiplicando per un numero primo piccolo (37, 31, 91)
```c
#define MULTIPLIER (37)

unsigned long hash(const char* s) {
	unsigned long h;
	unsigned const char* us;

	//Cast s to unsigned const char
	//this ensures that elements of s will be treated as having values >= 0
	us = (unsigned const char*) s;

	h = 0;
	while(*us != '\0') {
		//L'overflow è IGNORATO
		h = h * MULTIPLIER + *us;
		us++;
	} 

	return h;
}
```
- **UNIVERSAL HASHING**
  - Utilizzare un set di funzioni di hash invece che una sola, e scegliere una funzione di hash con una certa probabilità
  - Per diminuire la possibilità di collisioni e di brute force dell'algoritmo
  - (ambito di sicurezza)
```c
/* implmenets universal hashing using random bit-vectors in x */
/* assumes number of elements in x is at least BITS_PER_CHAR * MAX_STRING_SIZE */

#define BITS_PER_CHAR (8) // not true on all machines!
#define MAX_STRING_SIZE (128)  //we'll stop hashing after this many
#define MAX_BITS (BITS_PER_CHAR * MAX_STRING_SIZE)

unsigned long hash(const char* s, unsigned long x[]) {
	unsigned long h;
	unsigned const char* us;
	int i;
	unsigned char c;
	int shift;

	//Cast s to unsigned const char
	//this ensures that elements of s will be treated as having values >= 0
	us = (unsigned const char*) s;

	h = 0;
	for (i = 0; *us != 0 && i < MAX_BITS; us++) {
		for (shift = 0; shift < BITS_PER_CHAR; shift++,i++) {
			// low bit of c set?
			if(c & 0x1) {
				h ^= x[i];
			}

			// shift c to get new bit in lowest position
			c >>= 1;
		}
	}

	return h;
}
```


## Resources: 
- https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29