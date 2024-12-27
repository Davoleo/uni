//word frequency: parole dallo standard input e contare il numero di occorrenze di ogni parola
#include <map>
#include <string>
#include <iostream>
#include <iterator>

using map = std::map<std::string, unsigned long>;

using multimap = std::multimap<unsigned long, std::string, std::greater<unsigned long>>;

int main() {

	std::istream_iterator<std::string> it_begin(std::cin);
	std::istream_iterator<std::string> it_end;
	//^ il costruttore di default lo costruisce alla fine dell'input

	map word_freq;

	//Operatore di input di stringa legge fino allo spazio bianco (divisore di parole)
	for (auto iter = it_begin; iter != it_end; ++iter) {

		//Fa la stessa cosa alla fine ma è molto più compresso -> complicato da capire
		++word_freq[*iter];
		
		// auto match = word_freq.find(word);
		// if (match != word_freq.end())
		// 	++(match->second);
		// else
		// 	word_freq.insert(map::value_type(word, 1));
	}

	multimap freq_word;
	for (const auto& pair : word_freq)
		freq_word.insert(multimap::value_type(pair.second, pair.first));

	for (const auto& pair : freq_word) 
		std::cout << "La parola " << pair.second << " occorre numero " << pair.first << " volte/a\n";

	//Print reverse order
	// for (auto it = freq_word.rbegin(), it_end = freq_word.rend(); it != it_end; ++it) {
	// 	const auto& pair = *it;
	// 	std::cout << "La parola " << pair.second << " occorre numero " << pair.first << " volte/a\n";
	// }

	return 0;
}