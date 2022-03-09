#ifndef NUMBERS_FRACTION_GUARD
#define NUMBERS_FRACTION_GUARD 1

namespace numbers {

	class fraction
	{
	public:
		using Integer = long;

		//Una convenzione è quella di specificare anche se 
		//si usano operatori o costruttori definiti di defualt dal compilatore
		fraction() = default;
		fraction(const fraction&) = default;
		//Per fare in modo che l'assegnamento concatenato non funzioni
		//Se si vuole bloccare questo behaviour bisogna anche dare l'implementazione
		//(non ci si può basare su quella di default)
		//const fraction& operator=(const fraction&);
		fraction& operator=(const fraction&) = default;
		fraction& operator=(fraction&&) = default;
		~fraction() = default;

	private:
		Integer num_;
		Integer den_;
	};
	
} //namespace numbers

#endif
