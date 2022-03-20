#pragma once

#include <stdio.h>

void print_array(int* arr, int length) {
	putchar('[');
	for (int i = 0; i < length; ++i) {
		printf("%d, ", i);
	}
	putchar(']');
}