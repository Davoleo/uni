#include <array>
#include <iostream>
#include <string>


template<typename IIT, typename BINARY_FUNC, typename OIT>
OIT transform(IIT first1, IIT last1, IIT first2, OIT out, BINARY_FUNC func) {
	while (first1 != last1) {
		*out = func(*first1, *first2);
		++first1;
		++first2;
		++out;
	}
	return out;
}

int main() {
	std::array<double,5> arr1 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	std::array<double,5> arr2 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	std::array<double,5> out;

	transform(arr1.begin(), arr1.end(), arr2.begin(), out.begin(), [](double a, double b){
		return (a + b) / 2;
	});

	std::cout << "[";
	for (double d : out) {
		std::cout << d << ",";
	}
	std::cout << "]\n";

	return 0;
}