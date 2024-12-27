#include <iostream>
#include <string>
#include <vector>

template<typename ITER, typename UPRED>
int count_if(ITER begin, ITER end, UPRED predicate) {
	int count = 0;
	while (begin != end) {
		if (predicate(*begin))
			++count;
		++begin;
	}

	return count;
}

bool length_greater_than10(const std::string& string) {
	return string.size() > 10;
}

int main() {

	std::cout << "Inserisci stringhe terminate da a capo (stringa che inizia con ^ per terminare)" << std::endl;
	std::vector<std::string> vec_in(10);
	do {
		char charray_in[100];
		std::cin.getline(charray_in, 100);
		vec_in.push_back(charray_in);
	}
	while (vec_in.back()[0] != '^');

	//Remove last placeholder string
	vec_in.pop_back();

	int num = ::count_if(vec_in.begin(), vec_in.end(), length_greater_than10);

	std::cout << "Numero di stringe di lunghezza > 10: " << num << std::endl;

}