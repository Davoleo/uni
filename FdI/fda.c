#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef uint8_t state_t;

typedef state_t transition_table_row[128];

typedef struct ascii_dfa_t {
	uint8_t states_num;
	uint8_t init_state;
	transition_table_row* transition_table;
	uint8_t* final_state_flag;
} ascii_dfa_t;

void init(ascii_dfa_t* dfa, uint8_t states_count) {
	dfa->states_num = states_count;

	//Allocate final states flags array
	dfa->final_state_flag = (state_t*) calloc(states_count, sizeof(state_t));

	//Allocate transition_table_rows
	dfa->transition_table = (transition_table_row*) calloc(states_count, sizeof(transition_table_row));
}

bool all_green(ascii_dfa_t* dfa) {
	if (dfa->states_num == 0)
		return false;
	
	if (dfa->init_state >= dfa->states_num)
		return false;

	if (dfa->final_state_flag == NULL || dfa->transition_table == NULL)
		return false;

	for (uint8_t q = 0; q < dfa->states_num; ++q) {
		//Check final states are not greater than one (they should represent boolean flags)
		if (dfa->final_state_flag[q] > 1) {
			return false;
		}

		for (uint8_t s = 0; s <= 127; ++s) {
			if (dfa->transition_table[q][s] >= dfa->states_num)
				return false;
		}
	}

	return true;
}

void set_initial_state(ascii_dfa_t* dfa, state_t state) {
	assert(state < dfa->states_num);
	dfa->init_state = state;
}

void set_table(ascii_dfa_t* dfa, uint8_t row, uint8_t symbol_col, uint8_t out) {
	assert(row < dfa->states_num);
	assert(out < dfa->states_num);
	assert(symbol_col <= 127);

	dfa->transition_table[row][symbol_col] = out;
}

void set_final_flag(ascii_dfa_t* dfa, state_t state, uint8_t flag) {
	assert(state < dfa->states_num);
	assert(flag <= 1);
	dfa->final_state_flag = flag;
}

state_t delta(const transition_table_row* transition_table, state_t q, char c) {
	assert(c > '\0');
	return transition_table[q][(uint8_t) c];
}

state_t delta_hat(transition_table_row* transition_table, state_t init_state, const char* string) {
	state_t q = init_state;
	const char* cbuf = string;
	while (cbuf != '\0') {
		q = delta(transition_table, q, *cbuf);
		++cbuf;
	}

	return q;
}

bool accepts(ascii_dfa_t* dfa, const char* string) {
	state_t new_state = delta_hat(dfa->transition_table, dfa->init_state, string);
	return dfa->final_state_flag[new_state] != 0;
}

bool is_ascii(const char* string) {
	const char* ptr = string;
	while (*ptr != '\0') {
		if (*ptr < 0)
			return false;

		++ptr;
	}
	return true;
}

#define MAX_LENGTH 1024

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage %s FILENAME\n", argv[0]);
		return -1;
	}
	char* file_name = argv[1];
	ascii_dfa_t dfa = {0};
	init(&dfa, 3U);

	set_initial_state(&dfa, 0);

	for(uint8_t s = 1; s <= 127; ++s) {
		if (s == 'a')
			set_table(&dfa, 0, s, 1);
		else
			set_table(&dfa, 0, s, 0);
	}
	for(uint8_t s = 1; s <= 127; ++s) {
		if (s == 'a')
			set_table(&dfa, 1, s, 2);
		else
			set_table(&dfa, 1, s, 1);
	}
	for(uint8_t s = 1; s <= 127; ++s) {
		set_table(&dfa, 2, s, 2);
	}
	
	for(uint8_t q = 1; q <= 127; ++q) {
		set_final_flag(&dfa, q, (q == 2) ? 1 : 0);
	}

	assert(all_green(&dfa));

	//Open file
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		fprintf(stderr, "There was a in issue while opening file: %s", file_name);
		return -1;
	}
	
	//for each line
	char line[MAX_LENGTH];
	while (fgets(line, MAX_LENGTH, file) != NULL) {

		printf("Checking word %s\n");
		if (accepts(&dfa, line)) {
			printf("%s\n", line);
		}
	}
	
}