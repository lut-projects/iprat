#ifndef __STATE_CONTAINER_H_
#define __STATE_CONTAINER_H_

#include "gen_def.h"

#define HISTORY 5

typedef struct t_state_container {
	uint8_t state[VALUES];
	int8_t last_change_position;
	uint32_t round_number;
	uint8_t changes_on_this_round;
	uint8_t history[HISTORY][VALUES];
	int8_t last_change_position_history[HISTORY];
} state_container;

uint8_t (*calculation[VALUES]) (uint8_t state[], int pos);

state_container* new_state_container();
state_container* new_state_container_from_initial(char* initial_state);
state_container* new_state_container_from_file(char* path);

void initialize_functions();
void initialize_state(state_container* container);

uint8_t update_state(state_container* container);
void update_state_history(state_container* container);
int set_state(state_container* container, char* state);
int set_existing_state(state_container* container, uint8_t *state);

int check_state_history_repetition(state_container* container);

void print_state(state_container* container);
void print_state_history(state_container* container);


#endif
