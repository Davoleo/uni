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

// template (di tipi o funzioni)

//namespace