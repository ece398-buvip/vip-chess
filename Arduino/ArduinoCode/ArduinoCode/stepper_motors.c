/*
 * stepper_motors.c
 *
 * Created: 2/12/2025 10:46:31 AM
 *  Author: steoh
 */

#include "stepper_motors.h"
#include "bios_timer_int.h"
#include "bios_io.h"
#include "limit_switches.h"





static volatile uint8_t semaphore = 0;

uint8_t active_steppers = 0;

//Function called by the interrupt to create a pulse signal for the stepper motors
//Could be made better by placing a lot of this code inside the MoveSteps function
void PulseFn(void) {
    static uint16_t cnt = 0;

    //increment count if still under the max value, otherwise reset
    if(cnt<pwm_res) cnt++;
    else {
        cnt = 0;
        semaphore = 1;
    }

    //generates the pulse for the percentage of the duty cycle
    if(duty_cycle>cnt) {
        SetPortB(GetPortB() | active_steppers);
    } else {
        SetPortB(GetPortB() & ~active_steppers);
    }
}

//sets up the stepper motor pins as outputs
void StepperInit(void)
{
    LimitSwitchesInit();
    SetDDRB(GetDDRB() | (STEP_X | STEP_Y) | (DIR_X | DIR_Y));
    SetPortB(GetPortB() & ~((STEP_X | STEP_Y)| (DIR_X | DIR_Y)) );


}


//Moves both stepper motors the specified number of steps
void MoveSteps(int32_t steps_x, int32_t steps_y) {
    //used to decide which steppers to pulse
    active_steppers = 0;
    //assume direction is positive, will set negative if needed later
    uint8_t direction = DIR_X | DIR_Y;

    //set x axis active and direction
    if(steps_x != 0) {
        active_steppers |= STEP_X;
        if(steps_x < 0) {
            direction &= DIR_X;
            steps_x *= -1;
        }
    }

    //set y axis active and direction
    if(steps_y > 0) {
        active_steppers |= STEP_Y;
        if(steps_y < 0) {
            direction &= DIR_Y;
            steps_y *= -1;
        }
    }



    Timer1_initialize( timer_freq, &PulseFn, prescaler);

    while(1) {
        while(semaphore == 0);
        semaphore = 0;

        //keeps track of steps and deactivates stepper when number of steps is complete



        if(steps_x != 0) {
            steps_x--;
        } else {
            active_steppers &= ~STEP_X;
        }


        if(steps_y != 0) {
            steps_y--;
        } else {
            active_steppers &= ~STEP_Y;
        }

        //If both steppers are no longer active, job is done so exit
        if(active_steppers == 0) {
            break;
        }
    }


    Timer1_shutdown();
}



