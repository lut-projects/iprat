#ifndef __MODEL_CALC_FUNCS_H__
#define __MODEL_CALC_FUNCS_H__

#include "gen_def.h"

// Step 1
#define ATTACK_ACTUALIZATION 0
#define PRIVACY_DAMAGE 1
#define DATA_CAPABILITIES 2
#define ASSET_ACCESS 3
#define ASSET_ROLE 4
#define DATA_ACCESS 5
#define DATA_QUANTITY 6
#define DATA_SIGNIFICANCE 7
#define DATA_STORAGE_TIME 8
#define DATA_IDENTIFIABILITY 9

// Step 2
#define DATA_VALUE 10
#define USER_DAMAGE 11
#define DAMAGE_LEVEL 12
#define ASSET_MISUSE_POTENTIAL 13
#define ATTACK_GAIN 14
#define ASSET_VALUE 15

// Step 3
#define IMPACT 16
#define LIKELIHOOD 17
#define PRIVACY_RISK 18


#define TYPE_INITIAL 0
#define TYPE_UPDATE 1

uint8_t init_data_value(uint8_t state[]);
uint8_t init_asset_value(uint8_t state[]);
uint8_t init_user_damage(uint8_t state[]);
uint8_t init_damage_level(uint8_t state[]);
uint8_t init_data_capabilitites(uint8_t state[]);

uint8_t calc_data_value(uint8_t state[], int pos);
uint8_t calc_asset_value(uint8_t state[], int pos);
uint8_t calc_damage_level(uint8_t state[], int pos);
uint8_t calc_asset_misuse_potential(uint8_t state[], int pos);
uint8_t calc_attack_actualization(uint8_t state[], int pos);
uint8_t calc_attack_gain(uint8_t state[], int pos);
uint8_t calc_data_capabilities(uint8_t state[], int pos);
uint8_t calc_privacy_damage(uint8_t state[], int pos);
uint8_t calc_user_damage(uint8_t state[], int pos);

uint8_t calc_nothing(uint8_t state[], int pos);

uint8_t calc_impact(uint8_t state[], int pos);
uint8_t calc_likelihood(uint8_t state[], int pos);
uint8_t calc_privacy_risk(uint8_t state[]);

#endif
