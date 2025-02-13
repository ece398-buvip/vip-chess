/*
 * stepper_motors.h
 *
 * Created: 2/12/2025 10:47:20 AM
 *  Author: steoh
 */


#ifndef STEPPER_MOTORS_H_
#define STEPPER_MOTORS_H_



#include <avr/io.h>
#include <avr/interrupt.h>
#include "bios_timer_int.h"


void StepperInit();

void RunStepper(uint8_t steps);



#endif /* STEPPER_MOTORS_H_ */