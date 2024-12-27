#include <iostream>
#include <string>

using namespace std;

#include "stringset.cpp"

int main() {
  StringSet S1;
  cout << "S1: " << S1 << endl;
  cout << "Cardinalita' di S1: " << S1.size() << endl << endl;
  
  string frase[] = {"il","gatto","e","il","topo"};
  StringSet S2(frase,5);
  cout << "S2: " << S2 << endl;
  cout << "Cardinalita' di S2: " << S2.size() << endl << endl;
  
  const StringSet empty;          //attenzione: empty � un oggetto const ...
  cout << "Insieme vuoto: " << empty << endl;        
  cout << "Cardinalita' di insieme vuoto: " << empty.size() << endl;
  cout << "Unione di insieme vuoto e S2: " << empty + S2 << endl << endl;

  try {
	S1.add("topo");
  	S1.add("gatto");
  	S1.add("il");
  	S1.add("e");
    cout << "Cardinalita' di S1: " << S1.size() << endl;
  
  	if (S1.contains("gatto"))
      	cout << S1 << " contiene la stringa 'gatto'" << endl << endl;
  	else
      	cout << S1 << " non contiene la stringa 'gatto'" << endl << endl;
      
  	if (S1 < S2 && S2 < S1)
      	cout << "I due insiemi sono uguali" << endl << endl;
  	else
      	cout << " I due insiemi sono diversi" << endl << endl;

  	StringSet S3;
  	S3.add("e");
  	S3.add("il");
  	S3.add("cane");
  	cout << "S3: " << S3 << endl;
  	S3 = S1 + S3;	
  	cout << "Unione di S1 e S3: " << S3 << endl << endl;
  	
	string aux;
	for (int i=0; i<100; i++)
    	{aux = aux + '*';
  	     S3.add(aux);     // test gestione eccezioni
		}  	     
  }
  catch(string e) {
	 cout << "Eccezione: " << e << endl << endl;
  }   

  return 0;
}

/* Output:

S1: {}
Cardinalita' di S1: 0

S2: {il, gatto, e, topo}
Cardinalita' di S2: 4

Insieme vuoto: {}
Cardinalita' di insieme vuoto: 0
Unione di insieme vuoto e S2: {il, gatto, e, topo}

Cardinalita' di S1: 4
{topo, gatto, il, e} contiene la stringa 'gatto'

I due insiemi sono uguali

S3: {e, il, cane}
Unione di S1 e S3: {e, il, cane, topo, gatto}

Eccezione: spazio non sufficiente

Premere un tasto per continuare . . .
*/
