#ifndef __STATE_CREATION_H__
#define __STATE_CREATION_H__

#include "math_functions.h"
#include "gen_def.h"

void create_all_states();
void create_and_validate_all_states();
void print_values(uint8_t pos,uint8_t count, uint8_t *values);
uint8_t state_creation(uint8_t pos1, uint8_t values[]);
uint8_t state_recursion(uint8_t pos1, uint8_t values[]);


#endif
