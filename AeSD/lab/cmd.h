#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct args {
	bool details;
	bool graph;
	int max_dim;
	int div_n;
	int test_n;
} args_t;

int parse_cmd(int argc, char** argv, args_t* out)
{
	if (argc < 1)
		return -1;
	if (argc == 1)
	{
		*out = (args_t){false, false, 100, 100, 1};
		return argc;
	}

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
		if (argv[i][1] == 'm')
		{
			out->max_dim = atoi(argv[i] + 3);
			ok_parse = true;
		}
		if (argv[i][1] == 'd')
		{
			out->div_n = atoi(argv[i] + 3);
			ok_parse = true;
		}
		if (argv[i][1] == 't')
		{
			out->test_n = atoi(argv[i] + 3);
			ok_parse = true;
		}
	}

	if (!ok_parse)
	{
		printf("Usage: %s [Options]\n", argv[0]);
		printf("Options:\n");
		printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
		printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
		printf("  -m=<int>: specifica la massima dimensione n del problema\n");
		printf("  -d=<int>: Specifica quali dimensioni n del problema vengono lanciate in sequenza [default: 1] \n");
    	printf("            n = k * max-dim / d, k=1 .. d\n");
    	printf("  -t=<int>: Specifica quanti volte viene lanciato l'algoritmo per una specifica dimensione n [default: 1]\n");
    	printf("            Utile nel caso in cui l'input viene inizializzato in modo random\n");
		return -1;
	}

	return argc;
}