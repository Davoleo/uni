#include "fraction.hh"

#include <iostream>

void test01() {
	using numbers::fraction;

	fraction frac; 			//Default Constructor

	fraction frac1(frac); 		//Copy Constructor
	fraction frac2 = frac;		//Copy Constructor
	fraction frac3 {frac};		//Copy Constructor (C++11)
	fraction frac4 = {frac};	//Copy Constructor (C++11)

	fraction frac5(1,2); 	//Direct Construction
	fraction frac6 {1,2};	//Direct Construction (C++11)
	fraction frac7(1);		//Direct Construction
	fraction frac8{1};		//Direct Construction (C++11)
	//fraction frac9 = 1234 //Implicit Construction (to avoid!)

	frac = frac1;			//copy assignment 
	//(frac perde il suo valore venendo sovrascritto da una copia di frac1)

	//frac = fraction(1);		//move assignment
	frac2 = frac1 = frac;	//Concatenated assignments (avoid?)

	//Binary Arithmentic Operators
	frac1 = frac + frac;
	frac1 = frac - frac;
	frac1 = frac * frac;
	frac1 = frac / frac;

	//Unary Arithmentic Operators
	frac1 = -frac;
	frac1 = +frac;

	//Assignments with Arithmentic Operators
	frac += frac;
	frac -= frac;
	frac *= frac;
	frac /= frac;

	//Increment & Decrement
	//Le versioni postfisse (eccetto i tipi built-in) sono sempre meno efficienti delle versioni prefisse
	++frac;
	--frac;
	frac++; //avoid?
	frac--;

	//Relational Operators
	bool rel_res;
	rel_res = (frac == frac);
	rel_res = (frac != frac);
	rel_res = (frac < frac);
	rel_res = (frac <= frac);
	rel_res = (frac > frac);
	rel_res = (frac >= frac);

	//stream I/O
	std::cin >> frac;
	std::cin >> frac >> frac1;
	std::cout << frac :: std::endl
	std::cout << frac << " + " << frac1 << " = " << frac + frac1 << std::endl; 

	//Invocazione Implicita dei Distruttori

}

int main() {
	test01();
	return 0;
}
