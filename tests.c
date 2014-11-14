#include "tests.h"
#include "math_functions.h"

uint8_t test_attack_gain(uint8_t val, uint8_t datav, uint8_t dataq, int* changes) {
	uint8_t value = val;
	uint8_t temp = val;
	
	switch(datav) {
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
	
	if(value != temp) {
		(*changes)++;
		temp = value;
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
	}
	if(value != temp) (*changes)++;
	//printf("+");
	return value;
}

uint8_t test_user_damage(uint8_t val, uint8_t datav, uint8_t datac, int* changes) {
	uint8_t value = val;
	uint8_t temp = val;
	
	switch(datav) {
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
	
	if(value != temp) {
		(*changes)++;
		temp = value;
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
	if(value != temp) (*changes)++;
	//printf(";");
	return value;
}

uint8_t test_asset_misuse_potential(uint8_t val, uint8_t datav, uint8_t damage, int* changes) {
	uint8_t value = val;
	uint8_t temp = val;
	
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
			if (value > damage) value--; // Should be neg?
			break;
	}
	if(value != temp) {
		(*changes)++;
		temp = value;
	}
	
	switch(datav) {
		case 6:
		case 5:
		case 4:
			if(value < datav) value++;
			break;
		case 3:
		case 2:
		case 1:
			if(value > datav) value--;
			break;
	}*/
	uint8_t matrix[6][6] = {{1,1,1,1,1,2},
				{1,2,2,3,4,4},
				{1,2,3,4,4,5},
				{1,3,3,4,5,6},
				{1,3,4,5,5,6},
				{2,4,5,5,6,6}};
				
	value = matrix[datav-1][damage-1];

	if(value != temp) (*changes)++;
	//printf(":");
	return value;
}
