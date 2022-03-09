#ifndef NUMBERS_FRACTION_GUARD
#define NUMBERS_FRACTION_GUARD 1

#include <iostream>

namespace numbers {

	class fraction
	{
	public:
		using integer = long;

		//Una convenzione è quella di specificare anche se 
		//si usano operatori o costruttori definiti di defualt dal compilatore
		//fraction() = default;
		fraction(const fraction&) = default;
		//Per fare in modo che l'assegnamento concatenato non funzioni
		//Se si vuole bloccare questo behaviour bisogna anche dare l'implementazione
		//(non ci si può basare su quella di default)
		//const fraction& operator=(const fraction&);
		fraction& operator=(const fraction&) = default;
		fraction& operator=(fraction&&) = default;
		~fraction() = default;

		/*explicit*/ fraction(const integer& num = 0, const integer& den = 1);

		//Overloaded Operators
		//I const sono buona norma perché non si modificano né this né other
		//const correctness : Qualificazione di const ogni volta che ci sono le possibilità
		//Binary Operators
		fraction operator+(const fraction& other) const;
		fraction operator-(const fraction& other) const;
		fraction operator*(const fraction& other) const;
		fraction operator/(const fraction& other) const;
		//Unary Operators
		fraction operator+() const;
		fraction operator-() const;

		void operator+=(const fraction& other);
		void operator-=(const fraction& other);
		void operator*=(const fraction& other);
		void operator/=(const fraction& other);

		fraction& operator++();
		fraction& operator--();
		//Argomento fittizio di tipo int per differenziarlo dall'operatore prefisso
		//Non ha nessun utilizzo se non distinguere i 2 overload
		fraction operator++(int);
		fraction operator--(int);

		bool operator==(const fraction& other) const;
		bool operator!=(const fraction& other) const;
		bool operator<(const fraction& other) const;
		bool operator<=(const fraction& other) const;
		bool operator>(const fraction& other) const;
		bool operator>=(const fraction& other) const;

	private:
		integer num_;
		integer den_;
	};

	std::istream& operator>>(std::istream& istream, fraction& frac);
	std::ostream& operator<<(std::ostream& ostream, const fraction& frac);
	
} //namespace numbers

#endif
