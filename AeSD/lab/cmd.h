#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct args {
	bool details;
	bool graph;
} args_t;

int parse_cmd(int argc, char** argv, args_t* out)
{
	//va be fallo te
	//*out = {false, false};

	/// controllo argomenti
	bool ok_parse = false;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-') {
			ok_parse = false;
			break;
		}

		if (argv[i][1] == 'v')
		{
			out->details = true;
			ok_parse = true;
		}	
		if (argv[i][1] == 'g')
		{
			out->graph = true;
			ok_parse = true;
		}
	}

	if (!ok_parse)
	{
		printf("Usage: %s [Options]\n", argv[0]);
		printf("Options:\n");
		printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
		printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
		return 1;
	}

	return 0;
}