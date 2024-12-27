#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator> //Contiene ad esempio ostream_iterator

//Esercizio 5
//stampa in ordine lessicografico tutte le stringhe in vs che iniziano con il carattere c
//+ Versione alternativa dove si inverte l'ordine di stampa

//oggetti di funzione
struct Starts_With_Char {
private:
	char c_;
public:
	explicit Starts_With_Char(char c) : c_(c) {}

	bool operator()(const std::string& str) const {
		return !str.empty() && str[0] == c_;
	}
};

//Funzioni classiche
bool starts_with_char(const std::string& str) {
	return !str.empty() && str[0] == 'c';
}

//lambda-expression
void f(const std::vector<std::string>& vs, const char c, bool reverse) {
	std::vector<std::string> temp;

	//* Temporary inefficient solution to allocating vector space
	temp.resize(vs.size());

	//Tipi di inserter
	//- back_inserter(): inserisce sempre in fondo
	//- front_inserter(): inserisce sempre all'inizio (se permesso dalla struttura dati ofc)
	//- insert_iterator(): inserisce in una posizione custom
	copy_if(vs.begin(), vs.end(), [c](const std::string& str) -> bool { return !str.empty() && str[0] == c; }, temp.begin());
	std::sort(temp.begin(), temp.end());

	std::ostream_iterator<std::string> cout_iter(std::cout, "\n");
	if (!reverse)
		copy(temp.begin(), temp.end(), cout_iter);
	else
		copy(temp.rbegin(), temp.rend(), cout_iter);
}

/**
 * Esercizio 6:
 * Requisiti dei 6 Parametri:
 * Iteratore è almeno un FORWARD ITERATOR
 * L'importante del tipo T è che possa essere confontato con i valori della sequenza e che possa essere assegnato
 * x e y non hanno requisiti speciali
 * first e last devono far parte della stessa sequenza e first deve essere <= di last
 **/
template<typename FWDITER, typename T>
void replace(FWDITER first, FWDITER last, const T& x, const T& y) {
	while (first != last) {
		if (*first == x)
			*first = y;
		++first;
	}
}

int main() {
	std::vector<std::string> vec = {"cane", "gatto", "canarino"};
	f(vec, 'c', true);
	f(vec, 'c', false);
	return 0;
}