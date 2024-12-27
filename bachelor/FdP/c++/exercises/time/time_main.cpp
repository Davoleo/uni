
#include <iostream>

using namespace std;

#include <fstream>
#include <cstring>
#include <vector>
#include <string>

#include "hour.cpp"

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

int main() {
    Orario o1(9,42,10);  // crea un oggetto di classe Orario
    Orario o2(5221);   // crea un oggetto di classe Orario
    Orario o3;

    cout << "orario 1: " << o1 << endl;
    cout << "orario 2: " << o2 << endl;
    cout << "orario 3: " << o3 << endl << endl;
    
    cout << "ora di o2: " << o2.get_ora() << endl;
    cout << "minuti di o2: " << o2.get_minuti() << endl;
    cout << "secondi di o2: " << o2.get_secondi() << endl << endl;

    if (o1 < o2) cout << "o1 < o2" << endl;
	else cout << "o2 < o1" << endl;
	if (o1 == o2) cout << "o1 == o2" << endl;
	else cout << "o1 != o2" << endl;
	cout << endl;
	
	int o1_sec = o1.to_second();
	cout << "secondi corrispondenti a o1: " << o1_sec << endl;
	Orario o4(o1_sec);
	if (o4 == o1) cout << "ok" << endl;
	else  cout << "errore"  << endl;
	cout << endl;
		
	o3 = o1 + 5221;	
	cout << "il nuovo orario e: " << o3 << endl << endl;
	
    Orario orario_in;
	cout << "Immetti un orario corretto (h:m:s): ";
    cin >> orario_in;
    cout << "L'orario immesso e' " <<  orario_in << endl << endl;
    
    cout << "Immetti un orario errato (h:m:s): ";
    cin >> orario_in;
    cout << "L'orario immesso e' " <<  orario_in << endl << endl;
    return 0;    
}

/* traccia esecuzione

orario 1: 9:42:10
orario 2: 1:27:1
orario 3: 0:0:0

ora di o2: 1
minuti di o2: 27
secondi di o2: 1

o2 < o1
o1 != o2

secondi corrispondenti a o1: 34930
ok

il nuovo orario e': 11:9:11

Immetti un orario corretto (h:m:s): 12:3:14
L'orario immesso e' 12:3:14

Immetti un orario errato (h:m:s): 12:100:14
Orario errato
L'orario immesso e' 0:0:0


*/
