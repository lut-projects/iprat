#include "model_calc_functions.h"
#include "math_functions.h"

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

uint8_t init_data_value(uint8_t state[]) { return calc_data_value(state,DATA_VALUE); }

uint8_t init_asset_value(uint8_t state[]) { return calc_asset_value(state,ASSET_VALUE); }

uint8_t init_damage_level(uint8_t state[]) { return (state[PRIVACY_DAMAGE] + state[USER_DAMAGE]) / 2; }

uint8_t calc_data_value(uint8_t state[], int pos) {
	return divide((state[DATA_SIGNIFICANCE] + state[DATA_ACCESS]),2);
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
	
	uint8_t matrix[6][6] = {{1,2,3,4,5,5},
				{1,2,3,4,5,5},
				{1,2,3,4,5,5},
				{3,3,4,4,5,6},
				{4,4,5,5,5,6},
				{4,5,6,6,6,6}};
				
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

	uint8_t matrix[6][6] = {{1,2,3,3,3,3},
				{1,2,3,3,3,3},
				{2,2,3,4,5,5},
				{2,3,3,4,5,5},
				{4,4,4,4,5,6},
				{4,4,4,5,5,6}};
				
	value = matrix[aaccess-1][value-1];
	
	return value;
	
}

uint8_t calc_attack_gain(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t datav = state[DATA_VALUE];
	uint8_t dataq = state[DATA_QUANTITY];
	
	uint8_t matrix[6][6] = {{1,1,1,1,1,2},
				{1,1,2,2,2,3},
				{1,2,2,3,4,5},
				{1,3,4,4,5,5},
				{1,4,4,5,5,6},
				{1,5,5,6,6,6}};
				
	value = matrix[datav-1][dataq-1];
	
	return value;
}

uint8_t calc_data_capabilities(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t pdamage = state[PRIVACY_DAMAGE];

	uint8_t matrix[6][6] = {{1,2,3,3,3,3},
				{1,2,3,3,3,3},
				{1,2,3,4,4,4},
				{3,4,4,4,5,6},
				{4,5,5,5,5,6},
				{4,5,5,5,6,6}};
				
	value = matrix[pdamage-1][value-1];
	
	return value;
	
}

uint8_t calc_privacy_damage(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t signific = state[DATA_SIGNIFICANCE];
	
	uint8_t matrix[6][6] = {{1,2,3,3,3,3},
				{1,2,3,3,3,3},
				{1,2,3,4,4,4},
				{3,4,4,4,5,6},
				{4,5,5,5,5,6},
				{4,5,5,5,6,6}};
				
	value = matrix[signific-1][value-1];
	
	return value;
}

uint8_t calc_user_damage(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t datav = state[DATA_VALUE];
	uint8_t datac = state[DATA_CAPABILITIES];
	
	uint8_t matrix[6][6] = {{1,2,2,2,2,3},
				{1,1,2,2,3,3},
				{1,2,2,3,4,4},
				{1,2,3,4,5,5},
				{2,3,4,5,5,6},
				{3,4,5,5,6,6}};
				
	value = matrix[datav-1][datac-1];
	
	return value;
}

uint8_t calc_nothing(uint8_t state[], int pos) {
	return state[pos];
}

uint8_t calc_privacy_risk(uint8_t state[]) {
	uint8_t asset_value = state[ASSET_VALUE];
	uint8_t damage = state[DAMAGE_LEVEL];
	uint8_t attack_act = state[ATTACK_ACTUALIZATION];
	uint8_t ams = state[ASSET_MISUSE_POTENTIAL];
	uint8_t attack_gain = state[ATTACK_GAIN];
	
	uint8_t impact = divide(asset_value+damage,2);
	uint8_t likelihood = divide(ams+attack_act+attack_gain,3);
	printf("Impact: %hd\nLikelihood: %hd\n",impact,likelihood);
	
	return divide(impact+likelihood,2);
	
}