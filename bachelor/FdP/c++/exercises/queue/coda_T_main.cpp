#include <iostream>
#include <string>

using namespace std;

#include "queue.cpp"

//%%%%%%%%%%%%%%%%%%%%%%% main di prova

template <class T>
void stampa_primo(coda<T> c) {
    cout << c.dequeue() << endl;
}

int main() {
   try {
      coda<int> q1;            					// test costruttore
      cout << "q1 iniziale: " << q1 << endl;   	// test operator>>
      for (int i=0; i<10; i++) 
             q1.enqueue(i);            			// test enqueue       
      cout << "q1: " << q1 << endl;       		// test operator>>
      cout << "q1 contiene " << q1.size() << " elementi" << endl;
 
	  coda<int> q2(q1);							// test costruttore di copia
      cout << "q2: " << q2 << endl;       		// test operator>>

	  cout << "primo elemento di q1: ";
	  stampa_primo(q1); 	                    // test costruttore di copia	

	  cout << "elementi tolti da q1: ";
	  while (!q1.isEmpty())           			// test empty
          cout << q1.dequeue() << " ";   		// test dequeue
      cout << endl;
      cout << "q1 finale: " << q1 << endl;       		
      cout << "q2 finale: " << q2 << endl;    
	            
      coda<string> q3; 
      q3.enqueue("aaa");    
      q3.enqueue("bbb");    
      cout << "\nq3: " << q3 << endl;              
	  cout << "primo elemento di q3: ";
	  stampa_primo(q3); 	                    // test costruttore di copia	
      cout << "q3 invariata: " << q3 << endl;
      
      q3.dequeue(); q3.dequeue(); q3.dequeue(); // test eccezione  
   }
   catch(string str) {
      cout << "Eccezione: " << str << endl << endl;
   }   
     
   return 0;
}

/* Traccia esecuzione

q1 iniziale: []
q1: [0  1  2  3  4  5  6  7  8  9]
q1 contiene 10 elementi
q2: [0  1  2  3  4  5  6  7  8  9]
primo elemento di q1: 0
elementi tolti da q1: 0 1 2 3 4 5 6 7 8 9
q1 finale: []
q2 finale: [0  1  2  3  4  5  6  7  8  9]

q3: [aaa  bbb]
primo elemento di q3: aaa
q3 invariata: [aaa  bbb]
Eccezione: empty queue


*/
