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
					state[ASSET_NETWORK] +
					state[DATA_CAPABILITIES] +
					state[DATA_STORAGE_TIME] +
					state[DATA_QUANTITY]), 5);
}

uint8_t calc_damage_level(uint8_t state[], int pos) {
	uint8_t value = divide((state[PRIVACY_DAMAGE] + state[USER_DAMAGE]),2);
	uint8_t attack = state[ATTACK_ACTUALIZATION];
	
	/*switch(attack) {
		case 6:
		case 5:
		case 4:
			if(value < 2) value += divide(attack,2);
			else if(value > 1 && value < 4) value += attack - 3;
			break;
		case 3:
		case 2:
		case 1:
			if(value == 6) value--;
			break;
	}*/
	
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
	
	/*switch(damage) {
		case 6:
		case 5:
			if(diff(value,damage) > 1) value = damage - 1;
			break;
		case 4:
		case 3:
		case 2:
			if(value > (damage + 1)) value--;
			else if(value < (damage - 1)) value++;
			break;
		case 1:
			if (value > damage) value--; // Changed to neg
			break;
	}
	
	switch(dataval) {
		case 6:
		case 5:
		case 4:
			if(value < dataval) value++;
			break;
		case 3:
		case 2:
		case 1:
			if(value > dataval) value--;
			break;
	}*/

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
	uint8_t network = state[ASSET_NETWORK];
	
	/*switch(network) {
		case 6:
		case 5:
			if(value < 4) value = 4;
			else if (value < (network - 1)) value++;
			break;
		case 4:
		case 3:
			if(value == 1) value++;
			else if (value == 6) value--;
			break;
		case 2:
		case 1:
			if(value > 3) value = 3;
			break;
	}*/
	uint8_t matrix[6][6] = {{1,2,3,3,3,3},
				{1,2,3,3,3,3},
				{2,2,3,4,5,5},
				{2,3,3,4,5,5},
				{4,4,4,4,5,6},
				{4,4,4,5,5,6}};
				
	value = matrix[network-1][value-1];
	
	return value;
	
}

uint8_t calc_attack_gain(uint8_t state[], int pos) {
	uint8_t value = state[pos];
	uint8_t datav = state[DATA_VALUE];
	uint8_t dataq = state[DATA_QUANTITY];
	
	/*switch(datav) {
		case 6:
		case 5:
		case 4:
			if(value < 3) value += 2;
			else if (value < datav) value++;
			break;
		case 3:
		case 2:
			if(value > 3) value--;
			break;
		case 1:
			//if(value == 6) value -= 2;
			//else if(value > 1) value--; // Value check > 1
			if(value > 4) value -= 2;
			else if(value > 2 && dataq < 4) value--;
			break;
	}
	
	switch(dataq) {
		case 6:
		case 5:
			if(value < 3) value += divide(dataq,2);
			break;
		case 4:
		case 3:
			if(diff(dataq,value) > 1) {
				if(value < (dataq - 1)) value++;
				else if (value > (dataq + 1)) value--;
			}
			break;
		case 2:
		case 1:
			if(value == 6) value--;
			break;
	}*/
	
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
	
	/*switch(pdamage) {
		case 6:
		case 5:
		case 4:
			if(value < 3) value += divide(pdamage,2);
			break;
		case 3:
		case 2:
			if(value > 4) value -= (diff(pdamage,value) - 1);
			break;
		case 1:
			if(value > 4) value -= 2;
			break;
	}*/
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
	
	/*switch(signific) {
		case 6:
		case 5:
		case 4:
			if(value < 3 ) value += divide(signific,2);
			else if(diff(value,signific) > 1) value++;
			break;
		case 3:
		case 2:
		case 1:
			if(value > signific + 1) value--; // < -> >
			break;
	}
	if(value < 1 || value > 6) printf("PD (s=%d):",signific);*/
	
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
	
	/*switch(datav) {
		case 6:
		case 5:
		case 4:
			if(value < 4) value++;
			break;
		case 3:
		case 2:
		case 1:
			if(value > datav) value--;
			break;
	}
	
	switch(datac) {
		case 6:
		case 5:
			if(value < 3) value += divide(datac,2);
			else if (value == 3) value++; // more than 3?
			break;
		case 4:
		case 3:
			if(value < 2) value++;
			else if (value > 5) value--;
			break;
		case 2:
		case 1:
			if(value > 4) value = 4;
			break;
	}
	if(value < 1 || value > 6) printf("UD (v=%d,c=%d):",datav,datac);*/
	
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