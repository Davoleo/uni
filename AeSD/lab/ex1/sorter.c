#include <stdio.h>

//#include "../bench.h"
#include "../cmd.h"
#include "../utils.h"
//#include "../quicksort/quicksort.c"

/**
 * .\sort.exe -m=743 -t=107
 **/
int main(int argc, char** argv) {

	args_t args;

	if (parse_cmd(argc, argv, &args) < 0)
		return 1;


	int* arr = malloc(sizeof(int) * args.max_dim);

	init_array_csv(arr, args.max_dim, "data.txt");

	printf("max_dim: %d\n", args.max_dim);

	print_array(arr, args.max_dim);

}