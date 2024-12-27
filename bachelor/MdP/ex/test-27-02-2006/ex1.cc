void foo(int*); // Funzione #1

template <typename T>
void foo(const T&); // Funzione #2

template <typename T>
void foo(T, T); // Funzione #3

template <typename T, typename U>
void foo(T, U); // Funzione #4

template <typename T>
void foo(const T*, T); // Funzione #5

template <typename T, typename U>
void foo(T*, U); // Funzione #6

namespace A {
	struct Delta {
		Delta(double = 0) {};
	};

	template <typename T>
	void bar(T, double); // Funzione #7

	template <typename T, typename U>
	void bar(T, U); // Funzione #8
} // namespace A

template <typename T>
void bar(T, const A::Delta&); // Funzione #9

int main()
{
    int alfa;
    const int* p_alfa = &alfa;
    double beta;
    long gamma;
    A::Delta delta;

    foo(&alfa, beta); 	// chiamata A	 | 		Cand:	{3,4,5,6}  Util: {4,5,6}	Best: {6}
    foo(&alfa, alfa); 	// chiamata B  | 		Cand:	{3,4,5,6}  Util: {4,5,6}	Best: {5}
    foo(p_alfa, alfa); 	// chiamata C | 		Cand:	{3,4,5,6}  Util: {3,4,5}	Best: {5}
    foo(alfa, p_alfa); 	// chiamata D | 		Cand:	{3,4,5,6}  Util: {4}	Best: {4}
    foo(alfa); 			// chiamata E		 	Cand:	{1,2}	Util: {2}	Best: {2}	
    foo(&alfa); 		// chiamata F			Cand:	{1,2}	Util: {1,2}	Best: {1}	
    foo(p_alfa); 		// chiamata G			Cand:	{1,2}	Util: {}	Best: {}   [ERRORE]
    foo(const_cast<int*>(p_alfa)); //chiamata H Cand:	{1,2}	Util: {1}	Best: {1}
    bar(gamma, gamma); 	// chiamata I			Cand:	{9}		Util: {}	Best: {} 	[ERRORE]
    bar(delta, alfa); 	// chiamata L			Cand:	{7,8,9}	Util: {7,8}	Best: {8}
    bar(delta, beta); 	// chiamata M			Cand:	{7,8,9}	Util: {7,8}	Best: {8}
    A::bar(beta, gamma);// chiamata N			Cand:	{7,8}	Util: {7,8}	Best: {8}
}