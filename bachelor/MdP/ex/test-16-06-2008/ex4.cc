/**
 * last è un input iterator
 * first è un random access iterator
 * \return a random access iterator at the max element position
 * predicate è un predicato binario
 **/
template<typename RIT, typename IIT, typename BIPRED>
RIT max_element(RIT first, IIT last, BIPRED predicate) {

	RIT max_iter = first;
	
	int counter = 0;
	int max_counter = 0;
	int max = *first;
	while (++first != last) {
		if (predicate(max, *first)) {
			max = *first;
			max_iter = first;
		}
	}

	return max_iter;
}