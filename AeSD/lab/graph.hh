#pragma once

#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

int global_count_recursion = 0;
std::ofstream output_graph;


void graph_open(string&& filename)
{
	output_graph.open(filename);
	/// preparo header
	output_graph << "digraph g" << endl;
	output_graph << "{ " << endl;
	output_graph << "node [shape=plaintext]" << endl;
}


void graph_close()
{
	output_graph << "}" << endl;
	output_graph.close();
	cout << " File graph.dot scritto" << endl
		<< "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << endl;
}


void graph_write_array(int* A, int a, int b, string c, bool enable = false)
{
	/// prepara il disegno dell'array A ed il suo contenuto dall'indice a all'indice b inclusi

	if(enable)
	{
		output_graph << c << a << "_" << b << " [label=<"<<endl<<
		"<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">"<<endl;
		output_graph << "<TR><TD bgcolor=\"#80f0b0\">"<<global_count_recursion++<<"</TD></TR><TR>";
		for (int j=a; j<=b; j++) {
		output_graph << "<TD>" << A[j] << "</TD>"<<endl;
		}
		output_graph << "</TR> </TABLE>>];"<<endl;
	}
}

/* Create an arch form a_b to c_d with their separate strings */
void graph_write_arch(int a, int b, int c, int d, string str, string str2 = "")
{
	if(str2.empty())
		str2.append(str);

	output_graph << str << a << "_" << b << " -> ";
	output_graph << str2 << c << "_" << d << "\n";
}