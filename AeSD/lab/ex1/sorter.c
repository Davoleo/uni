#include <stdio.h>

//#include "../bench.h"
#include "../cmd.h"
#include "../utils.h"
#include "../bench.h"

/**
 * Windows: .\sort.exe -m=743 -t=107
 * UNIX: ./sort -m=743 -t=107
 **/
int main(int argc, char** argv) {

	args_t args;

	//TODO: Refactor this cause it SUCKS
	//Global variable Linked with utils.h
	filename = "data.txt";

	if (parse_cmd(argc, argv, &args) < 0)
		return 1;

	int* arr = malloc(sizeof(int) * args.max_dim);

	init_array_csv(arr, args.max_dim);

	//benchmark(arr, call_quicksort, &args, init_array_csv);

	print_array(arr, args.max_dim);

}