/*
 * ArduinoCode.c
 *
 * Created: 2/11/2025 1:47:44 PM
 * Author : steoh
 */

#include "global.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Bios/bios_io.h"
#include "stepper_motors.h"
#include "Bios/bios_uart0.h"
#include "commands.h"
#include "position_control.h"
#include "magnet.h"
#include "Bios/bios_leds.h"




#define B_X_NEG 0b00000001
#define B_X_POS 0b00000010
#define B_Y_NEG 0b00000100
#define B_Y_POS 0b00001000
#define B_ALL   0b00001111

int main(void)
{

    sei();


    CommandsInit();

    StepperInit();
    MagnetInit();
    MagnetOn();
    ledsInit();
    ledsUpdate();
//     SetDDRC(GetDDRC() & ~B_ALL);
//     SetPortC(GetPortC() | B_ALL);




    /* Replace with your application code */
    while (1)
    {
        zeroAll();
        ledsUpdate();
//
//         uint8_t buttons = GetPortC() & B_ALL;
//
//         int steps_x = 0;
//         int steps_y = 0;
//
//         if(!(buttons & B_X_NEG)) {
//             steps_x = -10;
//         }
//         if(!(buttons & B_X_POS)) {
//             steps_x = 10;
//         }
//         if(!(buttons & B_Y_NEG)) {
//             steps_y = -10;
//         }
//         if(!(buttons & B_Y_POS)) {
//             steps_y = 10;
//         }
//
//         MoveSteps(steps_x, steps_y);

//         MoveSteps(500, 0);
//         _delay_ms(500);
//         MoveSteps(0, 500);
//         _delay_ms(500);
//         MoveSteps(-500, 0);
//         _delay_ms(500);
//         MoveSteps(0, -500);

        moveToSpace(0, 0);
        _delay_ms(2500);
        moveToSpace(3, 0);
        _delay_ms(2500);

        moveToSpace(0,3);
        _delay_ms(2500);
        moveToSpace(7,7);
        _delay_ms(2500);
        moveToSpace(7,0);
        _delay_ms(2500);
        moveToSpace(0,7);
        _delay_ms(2500);
        moveToSpace(3,4);
        _delay_ms(2500);


    }
    return 0;
}

