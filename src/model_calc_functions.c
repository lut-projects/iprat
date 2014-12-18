#include "model_calc_functions.h"
#include "math_functions.h"

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

uint8_t init_data_value(uint8_t state[]) { return calc_data_value(state,DATA_VALUE); }

uint8_t init_asset_value(uint8_t state[]) { return calc_asset_value(state,ASSET_VALUE); }

uint8_t init_user_damage(uint8_t state[]) { return divide(state[DATA_CAPABILITIES] + state[DATA_VALUE],2); }

uint8_t init_damage_level(uint8_t state[]) { return divide(state[PRIVACY_DAMAGE] + state[USER_DAMAGE],2); }

uint8_t init_data_capabilitites(uint8_t state[]) {
	uint8_t identif = state[DATA_IDENTIFIABILITY];
	uint8_t value = state[DATA_CAPABILITIES];
	
	uint8_t matrix[3][6] = {{1,1,2,3,4,4},
				{1,3,4,4,5,6},
				{3,4,5,6,6,6}};
	
	value = matrix[identif-1][value-1];
	
	return value;
}

uint8_t calc_data_value(uint8_t state[], int pos) {
	return divide((state[DATA_SIGNIFICANCE] + state[DATA_ACCESS] + state[DATA_CAPABILITIES]),3);
}

uint8_t calc_asset_value(uint8_t state[], int pos) {
	return divide((state[ASSET_ROLE] +
					state[ASSET_ACCESS] +
					state[DATA_CAPABILITIES] +
					state[DATA_STORAGE_TIME] +
					state[DATA_QUANTITY]), 5);
}

uint8_t calc_damage_level(uint8_t state[], int pos) {
	uint8_t value = divide((state[PRIVACY_DAMAGE] + state[USER_DAMAGE]),2);
	uint8_t attack = state[ATTACK_ACTUALIZATION];
	
	uint8_t matrix[6][6] = {{1,1,2,2,3,3},
				{1,2,3,3,4,4},
				{1,2,3,4,4,5},
				{1,2,3,4,5,5},
				{1,2,3,4,5,6},
				{2,3,4,5,6,6}};
				
	value = matrix[attack-1][value-1];

	return value;
}

uint8_t calc_asset_misuse_potential(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t damage = state[DAMAGE_LEVEL];
	uint8_t dataval = state[DATA_VALUE];

	uint8_t matrix[6][6] = {{1,1,1,1,1,2},
				{1,2,2,3,4,4},
				{1,2,3,4,4,5},
				{1,3,3,4,5,6},
				{1,3,4,5,5,6},
				{2,4,5,5,6,6}};
				
	value = matrix[dataval-1][damage-1];

	return value;
}

uint8_t calc_attack_actualization(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t aaccess = state[ASSET_ACCESS];

	uint8_t matrix[6][6] = {{1,1,1,2,2,3},
				{1,2,3,3,3,4},
				{2,2,3,4,5,5},
				{2,3,3,4,5,5},
				{4,4,4,5,5,6},
				{5,5,5,5,6,6}};
				
	value = matrix[aaccess-1][value-1];
	
	return value;
	
}

uint8_t calc_attack_gain(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t datav = state[DATA_VALUE];
	uint8_t dataq = state[DATA_QUANTITY];
	
	uint8_t matrix[6][6] = {{1,1,1,1,1,2},
				{1,2,2,2,3,4},
				{1,2,3,3,4,5},
				{1,3,4,4,5,6},
				{1,4,5,5,5,6},
				{1,5,6,6,6,6}};
				
	value = matrix[datav-1][dataq-1];
	
	return value;
}

uint8_t calc_data_capabilities(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t pdamage = state[PRIVACY_DAMAGE];

	uint8_t matrix[6][6] = {{1,2,3,3,3,3},
				{1,2,3,3,3,4},
				{1,2,3,4,5,6},
				{1,3,4,4,5,6},
				{1,3,5,5,5,6},
				{1,4,5,5,6,6}};
				
	value = matrix[pdamage-1][value-1];
	
	return value;
	
}

uint8_t calc_privacy_damage(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t signific = state[DATA_SIGNIFICANCE];
	
	uint8_t matrix[6][6] = {{1,1,2,3,4,5},
				{1,2,3,4,5,5},
				{1,2,3,4,5,5},
				{1,2,3,4,5,6},
				{1,2,4,5,5,6},
				{1,2,4,5,6,6}};
				
	value = matrix[signific-1][value-1];
	
	return value;
}

uint8_t calc_user_damage(uint8_t state[], int pos) {
	uint8_t value = divide(state[DATA_CAPABILITIES] + state[DATA_VALUE],2);
	uint8_t role = state[ASSET_ROLE];
	
	uint8_t matrix[6][6] = {{1,2,3,4,5,6},
				{1,2,3,4,5,6},
				{1,2,3,4,5,6},
				{2,3,4,4,5,6},
				{3,4,5,5,5,6},
				{4,5,6,6,6,6}};
				
	value = matrix[role-1][value-1];
	
	return value;
}

uint8_t calc_nothing(uint8_t state[], int pos) {
	return state[pos];
}

uint8_t calc_impact(uint8_t state[], int pos) {
	uint8_t asset_value = state[ASSET_VALUE];
	uint8_t damage = state[DAMAGE_LEVEL];
	
	uint8_t value = divide(asset_value+damage,2);
	return value;
}

uint8_t calc_likelihood(uint8_t state[], int pos) {
	uint8_t attack_act = state[ATTACK_ACTUALIZATION];
	uint8_t ams = state[ASSET_MISUSE_POTENTIAL];
	uint8_t attack_gain = state[ATTACK_GAIN];
	
	uint8_t value = divide(ams+attack_act+attack_gain,3);
	return value;
}



uint8_t calc_privacy_risk(uint8_t state[]) {
	state[PRIVACY_RISK] = divide(state[IMPACT]+state[LIKELIHOOD],2);
	return state[PRIVACY_RISK];
	
}