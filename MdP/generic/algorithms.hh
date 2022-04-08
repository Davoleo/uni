#include <string>
#include <iostream>

namespace algo {
	///Scorre gli elementi della sequenza e ritorna la posizione dell'elemento se lo trova altrimenti ritorna last 
	template<typename ITER, typename T>
	ITER find(ITER first, ITER last, const T& elem) {
		while (first != last) {
			if (*first == elem)
				return true;
			++first;
		}
		return last;
	}

	//Predicato
	template<typename ITER, typename UPRED>
	ITER find_if(ITER first, ITER last, UPRED predicate) {
		while (first != last) {
			if(predicate(*first))
				++first;
		}
		return last;
	}

	template<typename ITER, typename T>
	unsigned long count(ITER first, ITER last, const T& elem) {
		unsigned long num = 0;
		while (first != last) {
			if (*first == elem)
				++num;
			++first;
		}
		return num;
	}

	template<typename ITER, typename UPRED>
	unsigned long count_if(ITER first, ITER last, UPRED predicate) {
		unsigned long num = 0;
		while (first != last) {
			if (predicate(*first))
				++num;
			++first;
		}
		return num;
	}

	template<typename ITER, typename UPRED>
	bool all_of(ITER first, ITER last, UPRED predicate) {
		while (first != last) {
			if (!predicate(*first))
				return false;
			++first;
		}
		return true;
	}

	template<typename ITER, typename UPRED>
	bool any_of(ITER first, ITER last, UPRED predicate) {
		while (first != last) {
			if (predicate(*first))
				return true;
			++first;
		}
		return false;
	}

	//replace all occurrences
	template<typename ITER, typename T>
	void replace(ITER first, ITER last, const T& x, const T& y) {
		while (first != last) {
			if (*first == x)
				*first = y;
			++first;
		}
	}

	//replace if predicates evaluates to true
	template<typename ITER, typename UPRED, typename T>
	void replace(ITER first, ITER last, UPRED predicate, const T& y) {
		while (first != last) {
			if (predicate(*first))
				*first = y;
			++first;
		}
	}

	//copy
	template<typename ITER, typename OUTITER>
	OUTITER copy(ITER first, ITER last, OUTITER out) {
		while (first != last) {
			*out = *first;
			++first;
			++out;
		}
		return out;
	}

	template<typename ITER, typename UPRED, typename OUTITER>
	OUTITER copy_if(ITER first, ITER last, UPRED predicate, OUTITER out) {
		while (first != last) {
			if (predicate(*first)) {
				*out = *first;
				++out;
			}
			++first;
		}
		return out;
	}

	//calls a function for each of the elements inside a sequence
	template<typename ITER, typename UFUNC>
	void for_each(ITER first, ITER last, UFUNC fun) {
		while(first != last) {
			fun(*first);
			++first;
		}
	}

	//Whether a sequence is sorted (using operator<)
	template<typename ITER>
	bool is_sorted(ITER first, ITER last) {
		if (first == last)
			return true;

		ITER next = first;
		++next;

		while(next != last) {
			if (*next < *first)
				return false;
			++first;
			++next;
		}
		return true;
	}

	//Whether a sequence is sorted (using operator<)
	template<typename ITER, typename COMP>
	bool is_sorted(ITER first, ITER last, COMP comparator) {
		if (first == last)
			return true;

		ITER next = first;
		++next;

		while(next != last) {
			if (comparator(*next, *first))
				return false;
			++first;
			++next;
		}
		return true;
	}

	template<typename ITER, typename OUTITER>
	OUTITER set_union(ITER first1, ITER last1, ITER first2, ITER last2, OUTITER out);

	///Sequenza1 dove si cerca | Sequenza2 cosa si cerca
	template<typename ITER1, typename ITER2>
	ITER1 find_first_of(ITER1 first1, ITER1 last1, ITER2 first2, ITER2 last2) {
		while(first1 != last1) {
			//Need to copy second iterator because it needs to back to the first posision after one outer cycle is complete
			for (ITER2 inner = first2; inner != last2; ++inner) {
				if (*first1 == *inner)
					return first1
			}
			++first1;
		}
		return last1;
	}

}

bool is_vocal(char c);

void test(const std::string& s) {
	auto k_pos1 = algo::find(s.begin(), s.end(), 'k');
	if (k_pos1 == s.end())
		std::cout << "No Ks";
	else
		std::cout << "There are Ks";
	
	auto k_pos2 = algo::find(std::begin(s), std::end(s), 'k');

	auto vocal_pos2 = algo::find_if(std::begin(s), std::end(s), is_vocal);
}