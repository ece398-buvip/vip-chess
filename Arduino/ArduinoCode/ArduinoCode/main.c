/*
 * ArduinoCode.c
 *
 * Created: 2/11/2025 1:47:44 PM
 * Author : steoh
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bios_io.h"
#include "stepper_motors.h"
#include "bios_uart0.h"



#define F_CPU 16000000

#define B_X_NEG 0b00000001
#define B_X_POS 0b00000010
#define B_Y_NEG 0b00000100
#define B_Y_POS 0b00001000
#define B_ALL   0b00001111

int main(void)
{

    sei();


    uart0_initialize(uart_bps_9600);

    StepperInit();
    SetDDRC(GetDDRC() & ~B_ALL);
    SetPortC(GetPortC() | B_ALL);



    /* Replace with your application code */
    while (1)
    {
        uint8_t buttons = GetPortC() & B_ALL;

        int steps_x = 0;
        int steps_y = 0;

        if(!(buttons & B_X_NEG)) {
            steps_x = -20;
        }
        if(!(buttons & B_X_POS)) {
            steps_x = 20;
        }
        if(!(buttons & B_Y_NEG)) {
            steps_y = -20;
        }
        if(!(buttons & B_Y_POS)) {
            steps_y = 20;
        }

        MoveSteps(steps_x, steps_y);




        _delay_ms(0);
    }
    return 0;
}

