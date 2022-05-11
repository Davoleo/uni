#ifndef __INTELLISENSE__
//Esercizio teorico (il codice non compila)

// Biblio.hh
class Biblio {
	public:
	virtual void b1() = 0;
	virtual void b2(const Biblio& y, int n) = 0;
	virtual void b3(int n) = 0;
	virtual ~Biblio() {}
};

//----------------------------------------------
//user_code.cc

void f(Biblio& x, const Biblio& y, int n) {
	if (n > 0)
		x.b3(n);
	else {
		x.b1();
		n = 5;
	}
	//...

	x.b2(y, n);
	//...
}

//----------------------------------------------
//Implementazione di Biblio che usa BSoft
//BSoft_Adapter.hh

#include "BSoft.hh"

class BSoft_Adapter : public Biblio {
private: 
	BSoft bsoft;
public:
	BSoft_Adapter(const BSoft& bsoft) : bsoft(bsoft) {}
	void b1() override {
		bs.s1();
	}

	void b2(const Biblio& y, int n) override {
		const auto& yAdapter = dynamic_cast<const BSoft_Adapter&>(y);
		bs.s2(yAdapter.bsoft, n);
	}

	void b3(int n) override {
		bs.s3(n);
	}
}

//----------------------------------------------
//Implementazione di Biblio che usa BWare
//BWare_Adapter.hh

#include "BWare.hh"

class BWare_Adapter : public Biblio {
private: 
	BWare bware;
public:
	BWare_Adapter(const BWare& bware) : bware(bware) {}
	void b1() override {
		bware.w1();
	}

	void b2(const Biblio& y, int n) override {
		const auto& yAdapter = dynamic_cast<const BWare_Adapter&>(y);
		bware.w2(yAdapter.bware, n);
	}

	void b3(int n) override {
		bware.w3(n);
	}
}

#endif