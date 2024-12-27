#include <iostream>
#include <string>

using namespace std;

#include "set.cpp"

void prova(string s, Insieme<string> X){       // test costruttore di copia (automatico)
  X.remove(s);
  X.add("cavallo");
  return;
  }

int main() {		
  Insieme<string> S1;                   // test costruttore senza parametri
  cout << "S1: " << S1 << endl;         // test operator<< per Insieme<T>
  cout << "Cardinalita' di S1: " << S1.size() << endl << endl;  // test funzione size
  
  string frase[] = {"il","gatto","e","il","topo"};
  Insieme<string> S2_0(frase,5);        // test costruttore con due parametri
  Insieme<string> S2_1(S2_0);			// test costruttore di copia (esplicito)
  Insieme<string> S2;
  S2 = S2_1;                            // test operatore di assegnamento
  cout << "S2: " << S2 << endl;
  cout << "Cardinalita' di S2: " << S2.size() << endl << endl;
  
  const Insieme<string> empty;          //attenzione: empty � un oggetto const ...
  cout << "Unione di insieme vuoto e S2: " 
       << empty + S2 << endl << endl;   // test operator+ per Insieme<T>

  try {
	S1.add("topo");                     // test funzione add
  	S1.add("gatto");
  	S1.add("il");
  	S1.add("e");
    cout << "S1: " << S1 << endl;
    cout << "Cardinalita' di S1: " << S1.size() << endl;
        
  	if (S1 < S2 && S2 < S1)              // test operastor<
      	cout << "I due insiemi S1 e S2 sono uguali" << endl << endl;
  	else
      	cout << "I due insiemi S1 e S2 sono diversi" << endl << endl;		

  	Insieme<string> S3;
   	S3.add("e");
  	S3.add("il");
  	S3.add("cane");
  	
  	prova("cane",S3);				// test costruttore di copia per passaggio parametri per valore
  	
  	cout << "S3: " << S3 << endl;
  	S3 = S1 + S3;	
  	cout << "Unione di S1 e S3: " << S3 << endl;
  	S3.remove("il");                // test remove
  	cout << "S3 ridotto: " << S3 << "Size: " << S3.size() << endl << endl;
  	
	string aux = "***";
	for (int i=0; i<100; i++) {
  	     S3.add(aux);               // test crescita dinamica
         std::cout << "Index: " << i << std::endl;
  }
	S3.remove("la");                // test gestione eccezioni
   
  }
  catch(string e) {
	 cout << "Eccezione: " << e << endl << endl;
  }  
  catch(...) {
	 cout << "Eccezione non prevista" << endl << endl;
  }  

  return 0;
}

/* Output:

S1: {}
Cardinalita' di S1: 0

S2: {il, gatto, e, topo}
Cardinalita' di S2: 4

Unione di insieme vuoto e S2: {il, gatto, e, topo}

S1: {topo, gatto, il, e}
Cardinalita' di S1: 4
I due insiemi S1 e S2 sono uguali

S3: {e, il, cane}
Unione di S1 e S3: {e, il, cane, topo, gatto}
S3 ridotto: {e, cane, topo, gatto}

Eccezione: elemento non presente

--------------------------------
Process exited after 0.1211 seconds with return value 0
Premere un tasto per continuare . . .

*/
