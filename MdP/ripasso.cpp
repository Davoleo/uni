#include <iostream>

//int è un tipo built-in, non c'è bisogno di importare niente per utilizzarlo
// i tipi unsigned vengono modulati in automatico quando in overflow
// i tipi signed hanno undefined behaviour

//
//- comportamento definito dallo standard
//- comportamento non specificato (definito dall'implementazione)
//- comportamento che dipende dal locale (eg. ordinamento alfabetico)
//- comportamento non definito

// ------- variabili ----------
// dichiarazione di un integer
int a;
// dichiarazione pura di un integer definito e dichiarato esternamente
// in molti casi possono anche essere ripetute
extern int b;
// definizione di b
int b = 1;

//funzioni
//dichiarazione
int test(double d);
int test(double); //si possono omettere i nomi dei param nelle dichiarazioni
//short int test(double); // errore: overload di funzione non valido 
//[per identificare una funzione nome qualificato (con namespace) e il numero e il tipo di argomenti]
short int test(float); // overload valido
// extern inutile
extern int test(double d);

//definizione
int test(double d) {
    return d;
}

// tipi
// Dichiarazione di tipo
struct SampleStruct;

// Definizione di tipo
struct SampleStruct {
	int a;
	char ch;
	//3 byte di padding
	int b;
};

//non è possibile se SampleStruct è dichiarata ma non è definita
SampleStruct sample;
// possibile anche se SampleStruct è solo dichiarata
SampleStruct* sample;

//solo uno dei due dati può essere immagazzinato
union aut
{
	int a;
	char* s;
};

//non è possibile fare dichiarazioni pure di enumerazioni
enum Semaforo; 
//Se non è specificato il tipo nascosto che viene usato per rappresentare i valori dell'enumerazioni
//Dentro header
enum Semaforo : int;

// gli indici di default iniziano da 0 a meno che il 
//primo non sia specificato, quel caso parte da quel numero
//File implementazione
enum Semaforo {
	ROSSO,
	GIALLO,
	VERDE
};

// template (di tipi o funzioni)
// Modelli generatori

//Dichiarazione pura di modello (template) di funzione
template <typename T>
T sum(const T& a, const T& b);

//Definizione
template <typename T>
T sum(const T& a, const T& b) {
	return a + b;
}

//Definizione di template di classe
template <typename T, typename U>
struct Pair {
	T t;
	U u;
};

//alias per i tipi
typedef int intero;
//oppure anche meglio (C++11)
using intero = int;

//namespace
namespace CoolProject {

}	//namespace CoolProject
    // ^ Convenzione per specificare che si sta chiudendo il namespace con quel nome

//alias per namespace
namespace cp = CoolProject;

//using directives
// Sempre meglio usarlo all'interno di scope, e tenere controllato il raggio in cui viene disabilitato
// il namespace
using namespace cp;

//Using declaration
//Viene creato alias senza namespace solo per il membro specificato
using std::cout;

//etichette
int funzione_molto_lunga(int a) {
	if (true)
		goto uscita;

	//more code

	uscita:
	return a;
}