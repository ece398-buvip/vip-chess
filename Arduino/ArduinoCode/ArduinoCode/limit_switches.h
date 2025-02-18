/*
 * limit_switches.h
 *
 * Created: 2/17/2025 10:13:31 PM
 *  Author: steoh
 */


#ifndef LIMIT_SWITCHES_H_
#define LIMIT_SWITCHES_H_

#include "bios_io.h"
#include <stdbool.h>

//Lets define these as the top four bits of port D
#define LS_NEG_X 0b00010000
#define LS_POS_X 0b00100000
#define LS_NEG_Y 0b01000000
#define LS_POS_Y 0b10000000
#define LS_ALL  (LS_NEG_X | LS_NEG_Y | LS_POS_X | LS_POS_Y)

void LimitSwitchesInit();

uint8_t CheckLimitSwitches();




#endif /* LIMIT_SWITCHES_H_ */