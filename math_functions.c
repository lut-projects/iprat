#include "math_functions.h"

uint8_t diff(uint8_t first, uint8_t second) {

	return abs(first - second);

}

uint8_t divide(uint8_t divident, uint8_t divisor) {
	
	uint8_t res = divident / divisor;
	uint8_t rem = (((double)divident / divisor - res) >= 0.5) ? 1 : 0;

	return res + rem;
}

