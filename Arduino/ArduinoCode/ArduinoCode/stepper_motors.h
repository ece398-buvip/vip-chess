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
#include "bios_io.h"
#include "limit_switches.h"
#include "bios_uart0.h"
#include <math.h>
#include <stdlib.h>


#define STEP_X 0b00000001
#define DIR_X 0b00000010
#define STEP_Y 0b00000100
#define DIR_Y 0b00001000


#define pulse_freq 1000
#define pwm_res 10
#define prescaler timer_prescale_256
#define timer_freq  ((uint16_t)pulse_freq * (pwm_res + 1))

#define duty_cycle pwm_res / 2



void StepperInit();

bool MoveSteps(int steps_x, int steps_y);



#endif /* STEPPER_MOTORS_H_ */