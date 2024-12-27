#ifndef __INTELLISENSE__

// File FaxModem_AS.hh
class FaxModem_AllStars {
private:
    // ...
public:
    void fax_function_1();
    void fax_function_2(const char*);
    void fax_function_3(int);
    // ...
    void modem_function_1(const char*);
    void modem_function_2();
    void modem_function_3(unsigned int);
    // ...
};

//////////////////////////////////////////////////////////////
// Fax.hh

class Fax {
public:
    virtual void fax_function_1() = 0;
    virtual void fax_function_2(const char*) = 0;
    virtual void fax_function_3(int) = 0;
    virtual ~Fax() { }
};

//////////////////////////////////////////////////////////////

class Modem {
public:
    virtual void modem_function_1(const char*) = 0;
    virtual void modem_function_2() = 0;
    virtual void modem_function_3(unsigned int) = 0;
    virtual ~Modem() { }
};

//////////////////////////////////////////////////////////////

// File User.cc
#include "Fax.hh"
#include "Modem.hh"

void user_function_1(Fax& f)
{
    f.fax_function_1();
    // ...
    f.fax_function_3(12);
}

void user_function_2(Modem& m, const char* command)
{
	m.modem_function_1(command);
	// ...
	m.modem_function_3(1024);
}

void user_function_3(Fax& f, Modem& m)
{
	f.fax_function_2("+390521906950");
	// ...
	m.modem_function_2();
}

//////////////////////////////////////////////////////////////

// File FaxModem_AS_Adapter.hh
#include "Fax.hh"
#include "Modem.hh"
#include "FaxModem_AS.hh"

class FaxModem_AllStars_Adapter : public Fax, public Modem {
private:
	FaxModem_AllStars fax_modem;
public:
    void fax_function_1() override {
		fax_modem.fax_function_1();
	}
    void fax_function_2(const char* s) override {
		fax_modem.fax_function_2(s);
	}
    void fax_function_3(int i) override {
		fax_modem.fax_function_3(i);
	}
    
	// ...

    void modem_function_1(const char* s) override {
		fax_modem.modem_function_1(s);
	}
    void modem_function_2() override {
		fax_modem.modem_function_2();
	}
    void modem_function_3(unsigned int i) override {
		fax_modem.modem_function_3(i);
	}
    // ...
};

//////////////////////////////////////////////////////////////

//Modem_USRobotics_Adapter.hh
#include "Modem.hh"
#include "Modem_USRobotics.hh"

class Modem_USRobotics_Adapter : public Modem {

private:
	Modem_USRobotics musr;

public:
	void modem_function_1(const char* s) override {
		musr.modem_function_1(s);
	}
    void modem_function_2() override {
		musr.modem_function_2();
	}
    void modem_function_3(unsigned int i) override {
		musr.modem_function_3(i);
	}
    // ...
};

#endif