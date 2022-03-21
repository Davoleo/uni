#pragma once

#include <stdio.h>
#include <stdlib.h>

void print_array(int* arr, int length) {
	putchar('[');
	for (int i = 0; i < length; ++i) {
		if (i > 0)
			printf(", ");
		printf("%d", i);
	}
	puts("]");
}

void init_array_wide(int* arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i]= rand() % (length * 10);
}

void init_array_normal(int* arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i]= rand() % length;
}

void init_array_wdups(int* arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i] = rand() % (length / 3);
}

void init_array_ordered(int* arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i]= i;
}
void init_array_reverse_ordered(int* arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i]= length - i;
}