#include <iostream>
#include <string>

using namespace std;

#include "stack_vec_impl.cpp"

const int dim = 2;

//%%%%%%%%%%%%%%%%%%%%%%% main di prova

int main() {
  try {
  pila<float> P1(dim);   // test costruttore con un parametro

  cout << "Numero elementi in P1 = " << P1.getNElem() << endl;  // test getNElem
  P1.push(1.5);          // test push
  P1.push(2);   
  P1.push(2.3);
  cout << "Numero elementi in P1 = " << P1.getNElem() << endl << endl;
  cout << "pila P1: " << P1 << endl << endl;                    // test operatore <<

  while (!P1.empty())             // test empty
      cout << P1.pop() << endl;   // test pop
  cout << endl;  
  P1.pop();
  }
  catch(string str) {
      cout << "Eccezione: " << str << endl << endl;
  }

  try { 
  pila<int> P2(10);   
  for(int i=0;i<10;i++)
      P2.push(i);
  P2.push(10);
  cout << "Numero elementi in P2 = " << P2.getNElem() << endl;
  cout << "pila P2: " << P2 << endl << endl;                    // test operatore <<
  }
  catch(string str) {
      cout << "Eccezione: " << str << endl << endl;
  }

  return 0;
}

/* Traccia output

Numero elementi in P1 = 0
Numero elementi in P1 = 3

pila P1: 1.5 2 2.3

2.3
2
1.5

Eccezione: Empty stack

Numero elementi in P2 = 11
pila P2: 0 1 2 3 4 5 6 7 8 9 10


*/
