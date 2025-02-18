/*
 * limit_switches.c
 *
 * Created: 2/17/2025 10:13:14 PM
 *  Author: steoh
 */

#include "limit_switches.h"

void LimitSwitchesInit() {
    SetDDRD(GetDDRD() & ~LS_ALL);
    SetPortD(GetPortD() | LS_ALL);
}

//returns whether or not a specific limit switch is activated
bool CheckLimitSwitch(uint8_t limit_switch) {
    return (GetPortD() & limit_switch);
}