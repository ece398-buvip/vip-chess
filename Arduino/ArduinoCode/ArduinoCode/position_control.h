/*
 * position_control.h
 *
 * Created: 3/25/2025 1:54:58 PM
 *  Author: steoh
 */


#ifndef POSITION_CONTROL_H_
#define POSITION_CONTROL_H_


void zeroX();

void zeroY();

void zeroAll() {
    zeroX();
    zeroY();
};

void setPosition(float x, float y);




#endif /* POSITION_CONTROL_H_ */