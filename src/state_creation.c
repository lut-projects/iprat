
#include "state_creation.h"
#include "state_container.h"

uint32_t loops = 0;

void create_all_states() {
	uint8_t values[ASSESSABLE+1] = {0};
	for(uint8_t i = 0; i < ASSESSABLE; values[i] = 1, i++);
	
	uint8_t start = 0;
	
	state_creation(start,values);
}

void create_and_validate_all_states() {
	uint8_t values[VALUES+1] = {0};
	for(uint8_t i = 0; i < VALUES_TOTAL; values[i] = 1, i++);

	uint8_t start = 0;

	state_recursion(start,values);
}

void print_values(uint8_t pos, uint8_t count, uint8_t *values) {
	for(uint8_t i = 0; i < count ; i++) printf("%d",values[i]);
	//printf("\n");
}

uint8_t state_creation(uint8_t pos1, uint8_t values[]) {
	uint8_t pos = pos1;
	if(pos1 > ASSESSABLE-1) return 0;

	uint8_t temp[ASSESSABLE] = {0};
	memcpy(temp,values,sizeof(uint8_t)*ASSESSABLE);
	
	for(;temp[pos] < LIMIT; temp[pos]++) {
		if(state_creation(pos+1,temp) == 0) {
			print_values(pos,ASSESSABLE,temp);
			printf("\n");
		}
	}
	return 1;
}

uint8_t state_recursion(uint8_t pos1, uint8_t values[]) {
	uint8_t pos = pos1;
	if(pos1 > ASSESSABLE-1) return 0;
	int updates = 0;
	uint32_t repeating_one_value_updates = 0;

	uint8_t temp[VALUES_TOTAL] = {0};
	memcpy(temp,values,sizeof(uint8_t)*VALUES_TOTAL);
	
	for(;temp[pos] < LIMIT; temp[pos]++) {
		if(state_recursion(pos+1,temp) == 0) {
			state_container* state = new_state_container();
			set_existing_state(state,temp);

			initialize_state(state);
			//print_state(state);

			while((updates = update_state(state)) > 0) {
				//print_state(state,++round,updates);
				if(state->round_number == 1000) {
					printf("!!!A STUCK STATE WAS DETECTED, 1k ROUNDS!\n");
					print_state(state);
					print_state_history(state);
					break;
				}
				if(updates == 1) repeating_one_value_updates++;
				else repeating_one_value_updates = 0;
				
				if(repeating_one_value_updates > HISTORY) {
					if(check_state_history_repetition(state) == 1) {
						printf("History full of repetition, quitting at %u rounds\n",
							state->round_number);
						print_state(state);
						print_state_history(state);
						break;
					}
				}
			}
			printf("R%u ",state->round_number);
			print_values(pos,VALUES,temp);
			printf(" -> ");
			print_values(pos,VALUES,state->state);
			printf(" R = %hd\n",calc_privacy_risk(state->state));
			loops++;
			if(state) free(state);
		}
	}

	return 1;
}
