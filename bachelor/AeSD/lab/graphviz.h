#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>
#include <string.h>

int global_count_recursion = 0;
FILE* output_graph;


void dot_open(const char* filename)
{
	output_graph = fopen(filename, "w");
	/// preparo header
	fputs("digraph g", output_graph);
	fputs("{ ", output_graph);
	fputs("node [shape=plaintext]", output_graph);
}


void dot_close()
{
	fputs("}", output_graph);
	fclose(output_graph);
	
	puts("File di graphvix '.dot' scritto");
}


void dot_write_array(int* A, int a, int b, const char* c, bool enable)
{
	/// prepara il disegno dell'array A ed il suo contenuto dall'indice a all'indice b inclusi

	if(enable)
	{
		fprintf(output_graph, "%s%d_%d [label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n", c, a, b);
		fprintf(output_graph, "<TR><TD bgcolor=\"#80f0b0\">%d</TD></TR><TR>", global_count_recursion++);
		for (int j=a; j<=b; j++) {
			fprintf(output_graph, "<TD>%d</TD>\n", A[j]);
		}
		fputs("</TR> </TABLE>>];", output_graph);
	}
}

/* Create an arch form a_b to c_d with their separate strings */
void dot_write_arch(int a, int b, int c, int d, const char* str, const char* str2)
{
	fprintf(output_graph, "%s%d_%d -> ", str, a, b);
	fprintf(output_graph, "%s%d_%d\n", str2, c, d);
}

#endif