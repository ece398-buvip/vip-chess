/*
 * position_control.c
 *
 * Created: 3/25/2025 1:54:20 PM
 *  Author: steoh
 */

#include "position_control.h"
#include "stepper_motors.h"
#include "limit_switches.h"

#include <stdbool.h>





#define X_WIDTH_CM 76
#define Y_HEIGHT_CM 48


#define X_STEPS_TO_CM (7.3 / 1000)  //7.3 cm to 1000 steps
#define Y_STEPS_TO_CM (7.05 / 1000) //7.05 cm to 1000 steps


#define X_WIDTH_STEPS (float)X_WIDTH_CM / X_STEPS_TO_CM
#define Y_WIDTH_STEPS (float)Y_WIDTH_CM / Y_STEPS_TO_CM


float x_position = 0;
float y_position = 0;


void zeroX() {
    bool hit_edge = false;
    while(!hit_edge) {
        MoveSteps(-20, 0);
        if(CheckLimitSwitch(LS_NEG_X)) {
            hit_edge = true;
        }
    }

    x_position = 0;

}

void zeroY() {
    bool hit_edge = false;
    while(!hit_edge) {
        MoveSteps(0, -20);
        if(CheckLimitSwitch(LS_NEG_Y)) {
            hit_edge = true;
        }
    }

    y_position = 0;

}




void setPosition(float x, float y) {
    float delta_x = x - x_position;
    float delta_y = y - y_position;

    int steps_x = delta_x * X_STEPS_TO_CM;
    int steps_y = delta_y * Y_STEPS_TO_CM;

    bool succeeded = MoveSteps(steps_x, steps_y);


}