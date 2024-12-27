#include <string>

typedef std::string Chiamata;

///////////////////////////////////////////////////

// File: Scheda_Prepagata.hh

class Scheda_Prepagata {
public:
    virtual std::string tipo_scheda() const = 0;
    virtual void addebita_chiamata(const Chiamata& call) = 0;
    // ...

	virtual ~Scheda_Prepagata() {}
};

///////////////////////////////////////////////////

// File: Paga_la_mamma.cc
class Paga_la_mamma : public Scheda_Prepagata {
public:
	void addebita_chiamata(const Chiamata& call) override {
		fai_la_cosa_giusta_3(call);
	}
	std::string tipo_scheda() const {
		return "PAGA_LA_MAMMA";
	}
private:
	void fai_la_cosa_giusta_3(const Chiamata& call) {
		//...
	}
};

// File: Costo_Random.cc
class Costo_Random : public Scheda_Prepagata {
public:
	void addebita_chiamata(const Chiamata& call) override {
		fai_la_cosa_giusta_2(call);
	}
	std::string tipo_scheda() const {
		return "COSTO_RANDOM";
	}
private:
	void fai_la_cosa_giusta_2(const Chiamata& call) {
		//...
	}
};

// File: Paga_di_piu.cc
class Paga_di_piu : public Scheda_Prepagata {
public:
	void addebita_chiamata(const Chiamata& call) override {
		fai_la_cosa_giusta_1(call);
	}
	std::string tipo_scheda() const {
		return "PAGA_DI_PIU";
	}
private:
	void fai_la_cosa_giusta_1(const Chiamata& call) {
		//...
	}
};