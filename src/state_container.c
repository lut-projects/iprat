#include "state_container.h"

state_container* new_state_container() {
	state_container *container = calloc(sizeof(state_container),sizeof(state_container));
	for(int i = 0; i < VALUES; i++) {
		container->state[i] = 1;
		for(int j = 0; j < HISTORY; j++) container->history[j][i] = 0; //History is set to uninitialized
	}
	for(int i = 0; i < HISTORY; i++) container->last_change_position_history[i] = -1;
	container->last_change_position = -1;
	container->changes_on_this_round = 0;
	container->round_number = 0;
	return container;
}

state_container* new_state_container_from_initial(char* initial_assessment) {
	state_container *container = new_state_container();
	
	char* initial_state = (char*)malloc(sizeof(char)*VALUES+1);
	memcpy(initial_state,initial_assessment,ASSESSABLE);
	for(int i = ASSESSABLE; i < VALUES+1; i++) initial_state[i] = '1';
	
	switch(set_state(container,initial_state)) {
		case 0:
			break; // Success
		case -1:
			printf("invalid input parameters for set_state() state = %s is wrong length\n",initial_state);
			break; //
		case -2:
			printf("set_state() no container\n");
			break;
		default:
			printf("The state is incomplete\n");// TODO: react to error if state invalid
			break;
	}
	free(initial_state);
	return container;
}

state_container* new_state_container_from_file(char* path) {
	if(path) return NULL;
	else return NULL;
}

void initialize_functions() {
	calculation[DATA_VALUE] = calc_data_value;
	calculation[ASSET_VALUE] = calc_asset_value;
	calculation[DAMAGE_LEVEL] = calc_damage_level;
	calculation[ASSET_MISUSE_POTENTIAL] = calc_asset_misuse_potential;
	calculation[ATTACK_GAIN] = calc_attack_gain;
	calculation[ATTACK_ACTUALIZATION] = calc_attack_actualization;
	calculation[ASSET_ROLE] = calc_nothing;
	calculation[ASSET_ACCESS] = calc_nothing;
	calculation[PRIVACY_DAMAGE] = calc_privacy_damage;
	calculation[USER_DAMAGE] = calc_user_damage;
	calculation[DATA_CAPABILITIES] = calc_data_capabilities;
	calculation[DATA_STORAGE_TIME] = calc_nothing;
	calculation[DATA_QUANTITY] = calc_nothing;
	calculation[DATA_SIGNIFICANCE] = calc_nothing;
	calculation[DATA_ACCESS] = calc_nothing;
	calculation[IMPACT] = calc_impact;
	calculation[LIKELIHOOD] = calc_likelihood;
}

void initialize_state(state_container* container) {
	//container->state[DATA_VALUE] = init_data_value(container->state);
	//container->state[ASSET_VALUE] = init_asset_value(container->state);
	//container->state[DAMAGE_LEVEL] = init_damage_level(container->state);
}

uint8_t update_state(state_container* container) {

	uint8_t update = 0;
	
	update_state_history(container);

	container->last_change_position = -1; // Update round start
	container->changes_on_this_round = 0; // Reset change counter

	for(int i = 0; i < VALUES; i++) {

		update = (*calculation[i])(container->state,i);
		
		if((update > 0) && (update < LIMIT)) {
			if((container->state[i] != update)) {
				container->changes_on_this_round++; // A change has been made
				container->last_change_position = i; // Record position
				container->state[i] = update; // Set value
			}
		}
		else {
			printf("ERROR, state[%d] update value is off limits: %d\n", i, update);
			print_state(container);
		}
	}
	container->round_number++; // Round finished
	return container->changes_on_this_round;
}

void update_state_history(state_container* container) {

	for(int i = (container->round_number < HISTORY ? container->round_number : HISTORY-1); i > 0 ; i--) {
		memcpy(&(container->history[i][0]),&(container->history[i-1][0]),sizeof(uint8_t)*VALUES);
		container->last_change_position_history[i] = container->last_change_position_history[i-1];
	}
	
	// Add current to first
	memcpy(&(container->history[0][0]),&(container->state),sizeof(uint8_t)*VALUES);
	container->last_change_position_history[0] = container->last_change_position;
}

int check_state_history_repetition(state_container* container) {

	// History is not full, cannot be repeated too much
	if(container->round_number < HISTORY) return 0;
	
	for(int i = 0; i < HISTORY; i++) {
		// If positions differ at any point -> no repetition
		if(container->last_change_position_history[i] != container->last_change_position) return 0;
	}
	return 1; // Repetition!
}

void print_state(state_container* container) {
	printf("              A P D A A D D D D D U D A A A I A\n");
	printf("              A D C A R A Q S T V D L M G V M L\n");
	printf("R%.5d (U=%.2d) ",container->round_number, container->changes_on_this_round);
	
	for(int i = 0; i < VALUES ; i++) printf("%u ",container->state[i]);

	printf("\n---------------------------------------------\n");
}

void print_state_history(state_container* container) {
	for(int i = HISTORY-1; i >= 0; i--) {
		printf("      %.2d c%.2d: ",i+1,container->last_change_position_history[i]);
		for(int j = 0; j < VALUES; j++) printf("%u ",container->history[i][j]);
		printf("\n");
	}
}

/**
 * Returns 0 or amount of errorous state variables in given state
*/
int set_state(state_container* container, char* state) {
	if(strlen(state) != VALUES+1) return -1;
	if(!container) return -2;
	
	int failures = 0;
	
	for(int i = 0; i < VALUES+1 ; i++) {
		uint8_t value = 0;
		char temp_value = 0;
		memcpy(&temp_value,&state[i],sizeof(char));
		value = (uint8_t)atoi(&temp_value);
		if ((value > 0) && (value < LIMIT)) container->state[i] = value;
		else {
			printf("Invalid state variable \"%u\" @ state[%d]\n",value,i);
			failures++;
		}
	}
	return failures;
}

int set_existing_state(state_container* container, uint8_t *state) {
	if(!container) return -1;
	
	int failures = 0;
	
	for(int i = 0; i < VALUES ; i++) {
		if ((state[i] > 0) && (state[i] < LIMIT)) container->state[i] = state[i];
		else {
			printf("Invalid state variable \"%u\" @ state[%d]\n",state[i],i);
			failures++;
		}
	}
	return failures;
}
