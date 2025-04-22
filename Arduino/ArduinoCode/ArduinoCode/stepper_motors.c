/*
 * stepper_motors.c
 *
 * Created: 2/12/2025 10:46:31 AM
 *  Author: steoh
 */

#include "stepper_motors.h"





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

int extraStepsX = 0;
int extraStepsY = 0;

int GetExtraStepsX() {
    return extraStepsX;
}

int GetExtraStepsY() {
    return extraStepsY;
}

int dirX = 0;
int dirY = 0;

int GetDirX() {

}
int GetDirY() {

}




//Moves both stepper motors the specified number of steps
bool MoveSteps(int steps_x, int steps_y) {

    if(steps_x == 0 && steps_y == 0) {
        return true;
    }

    //used to decide which steppers to pulse
    active_steppers = 0;

    //assume direction is positive, will set negative if needed later
    uint8_t direction = DIR_X | DIR_Y;

    //set x axis active and direction
    if(steps_x != 0) {
        active_steppers |= STEP_X;
        if(steps_x < 0) {
            direction &= ~DIR_X;
        }
    }

    //set y axis active and direction
    if(steps_y != 0) {
        active_steppers |= STEP_Y;
        if(steps_y < 0) {
            direction &= ~DIR_Y;
        }
    }

    extraStepsX = 0;
    extraStepsY = 0;

    bool limitSwitchHitX = false;
    bool limitSwitchHitY = false;

    //char buffer[32];
    //dtostrf((float)steps_x, 5, 3, buffer);
    //uart0_puts(buffer);
    //uart0_puts("\t\n");


    if(CheckLimitSwitch(LS_NEG_X)) {
        if(steps_x < 0) {
            limitSwitchHitX = true;
            extraStepsX = steps_x;
        }
    }
    if (CheckLimitSwitch(LS_POS_X)) {
        if(steps_x > 0) {
            limitSwitchHitX = true;
            extraStepsX = steps_x;
        }
    }

    if(CheckLimitSwitch(LS_NEG_Y)) {
        if(steps_y < 0) {
            limitSwitchHitY = true;
            extraStepsY = steps_y;
        }
    }
    if (CheckLimitSwitch(LS_POS_Y)) {
        if(steps_y > 0) {
            limitSwitchHitY = true;
            extraStepsY = steps_y;
        }
    }

    if(limitSwitchHitX && limitSwitchHitY) {
        return false;
    }




    steps_x = abs(steps_x);
    steps_y = abs(steps_y);



    if(active_steppers) {
        SetPortB((GetPortB() & ~(DIR_X | DIR_Y)) | direction);
    }


    Timer1_initialize( timer_freq, &PulseFn, prescaler);

    while(1) {
        while(semaphore == 0);
        semaphore = 0;

        //keeps track of steps and deactivates stepper when number of steps is complete


        if(CheckLimitSwitch(LS_NEG_X)) {
            if(!(direction & DIR_X)) {
                limitSwitchHitX = true;
                extraStepsX = -steps_x
            }
        }
        if (CheckLimitSwitch(LS_POS_X)) {
            if((direction & DIR_X)) {
                limitSwitchHitX = true;
                extraStepsX = steps_x;
            }
        }

        if(CheckLimitSwitch(LS_NEG_Y)) {
            if(!(direction & DIR_Y)) {
                limitSwitchHitY = true;
                extraStepsY = -steps_y;
            }
        }
        if (CheckLimitSwitch(LS_POS_Y)) {
            if(direction & DIR_Y) {
                limitSwitchHitY = true;
                extraStepsY = steps_y;
            }
        }



        if(limitSwitchHitX) {
            steps_x = 0;
            if(steps_y == 0) {
                SetPortB(GetPortB() & ~((STEP_X | STEP_Y)) );
                Timer1_shutdown();
                return false;
            }
        }

        if(limitSwitchHitY) {
            steps_y = 0;
            if(steps_x == 0) {
                SetPortB(GetPortB() & ~((STEP_X | STEP_Y)) );
                Timer1_shutdown();
                return false;
            }
        }




        if(steps_x > 0) {
            steps_x--;
        } else {
            active_steppers &= ~STEP_X;
        }


        if(steps_y > 0) {
            steps_y--;
        } else {
            active_steppers &= ~STEP_Y;
        }

        //If both steppers are no longer active, job is done so exit
        if(active_steppers == 0) {
            break;
        }
    }



    SetPortB(GetPortB() & ~((STEP_X | STEP_Y)) );
    Timer1_shutdown();
    if(limitSwitchHitX || limitSwitchHitY) {

    }
    return true;
}



