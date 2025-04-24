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





#define X_WIDTH_CM 76.0
#define Y_HEIGHT_CM 48.0


#define X_STEPS_TO_CM (7.5482 / 1000.0)  //7.3 cm to 1000 steps
#define Y_STEPS_TO_CM (7.015 / 1000.0) //7.05 cm to 1000 steps


#define X_WIDTH_STEPS (float)X_WIDTH_CM / X_STEPS_TO_CM
#define Y_WIDTH_STEPS (float)Y_HEIGHT_CM / Y_STEPS_TO_CM


float x_position = 0;
float y_position = 0;


void zeroAll() {
    zeroX();
    zeroY();
}


void zeroX() {
    bool hit_edge = false;
    while(!hit_edge) {
        MoveSteps(-100, 0);
        if(CheckLimitSwitch(LS_NEG_X)) {
            hit_edge = true;
        }
    }

    x_position = 0;

}

void zeroY() {
    bool hit_edge = false;
    while(!hit_edge) {
        MoveSteps(0, -100);
        if(CheckLimitSwitch(LS_NEG_Y)) {
            hit_edge = true;
        }
    }

    y_position = 0;

}



//Set position of electromagnet in cm x and y
void setPosition(float x, float y) {
    float delta_x = x - x_position;
    float delta_y = y - y_position;

    int steps_x = (int)(delta_x / X_STEPS_TO_CM);
    int steps_y = (int)(delta_y / Y_STEPS_TO_CM);

    bool succeeded = MoveSteps(steps_x, steps_y);
    if(succeeded) {
        x_position += delta_x;
        y_position += delta_y;
    } else {
        x_position += delta_x - GetExtraStepsX();
        y_position += delta_y - GetExtraStepsY();
    }

}


#define BOARD_ORIGIN_X 10.2
#define BOARD_ORIGIN_Y 0.85

#define SPACE_WIDTH 6.05


void moveToSpace(uint8_t x, uint8_t y) {
    float x_cm = BOARD_ORIGIN_X + SPACE_WIDTH * x;
    float y_cm = BOARD_ORIGIN_Y + SPACE_WIDTH * y;
    setPosition(x_cm, y_cm);
}