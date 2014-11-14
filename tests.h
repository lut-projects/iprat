#ifndef __VALIDATOR_TESTS_H__
#define __VALIDATOR_TESTS_H__

#include "gen_def.h"

uint8_t test_attack_gain( uint8_t value, uint8_t datav, uint8_t dataq, int* changes);
uint8_t test_user_damage(uint8_t value, uint8_t datav, uint8_t datac, int* changes);
uint8_t test_asset_misuse_potential(uint8_t value, uint8_t datav, uint8_t damag, int* changes);

#endif
