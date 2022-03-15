#ifndef NUMBERS_FRACTION_GUARD
#define NUMBERS_FRACTION_GUARD 1

#include <iostream>
#include <cassert>

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

		//delegating constructors (delegate the construction of the object to another constructor)
		explicit fraction(int num) : fraction(num, 1) {}

		//* Proprietà invariante di classe: che è sempre vera quando la frazione è ben formata
		//* implementazione che assicura la canonicità
		// se una funzione viene implementata dentro all'interfaccia inline viene apposto automaticamente
		/*explicit*/ fraction(const integer& num = 0, const integer& den = 1);

		//Getters
		inline const integer& num() const {
			assert(this->check_inv());
			return num_;
		}
		inline const integer& den() const {
			assert(this->check_inv());
			return den_;
		}

		//Overloaded Operators
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
		//fraction operator++(int);
		//fraction operator--(int);

		bool operator==(const fraction& other) const;
		bool operator<(const fraction& other) const;

	private:
		// I nomi con __ sono riservati per l'implementazione
		// Alcuni nomi che iniziano con _ potebbero essere riservati (se si è nel namespace globale)
		integer num_;
		integer den_;

		//Controlla se l'invariante è rispettata sull'oggetto
		bool check_inv() const;
	};

	std::istream& operator>>(std::istream& istream, fraction& frac);
	std::ostream& operator<<(std::ostream& ostream, const fraction& frac);

	//I const sono buona norma perché non si modificano né this né other
	//const correctness : Qualificazione di const ogni volta che ci sono le possibilità
	//Binary Operators
	fraction operator+(const fraction& x, const fraction& y);
	fraction operator-(const fraction& x, const fraction& y);
	fraction operator*(const fraction& x, const fraction& y);
	fraction operator/(const fraction& x, const fraction& y);
	//Si potrebbero spostare fuori dalla classe visto che l'implementazione usa solo
	//Metodi di interfaccia della frazione
	
	//TODO Gli altri possono anche essere estratti dalla classe
	inline bool operator!=(const fraction& x, const fraction& y) {
		return not (x == y);
	}
	inline bool operator>(const fraction& x, const fraction& y) {
		return y < x;
	}
	inline bool operator>=(const fraction& x, const fraction& y) {
		return x > y || x == y;
	}
	inline bool operator<=(const fraction& x, const fraction& y) {
		return x < y || x == y;
	}

} //namespace numbers

#endif
