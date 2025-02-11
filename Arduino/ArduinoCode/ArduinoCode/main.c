/*
 * ArduinoCode.c
 *
 * Created: 2/11/2025 1:47:44 PM
 * Author : steoh
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bios_timer_int.h"




uint8_t GetPortB (void)
{
    return(PINB & 0b00111111);
}

void SetPortB(uint8_t x) {
    PORTB = (PORTB & 0b11000000) | (x & 0b00111111);
}




#define Stepper1 0b00000001

static volatile uint8_t     semaphore = 0;  // volatile keyword is very important here!
static volatile uint16_t duty_cycle = 312/2;


void fn(void) {
    static uint16_t cnt = 0;
    static uint16_t pwm = 0;

    if(cnt<312) cnt++;
    else {
        cnt = 0;
        semaphore = 1;
        pwm = duty_cycle;
    }

    if(pwm>cnt) {
        SetPortB(GetPortB() | Stepper1);
    } else {
        SetPortB(GetPortB() & ~Stepper1);
    }
}


int main(void)
{
    DDRB |= 0b00000001;
    PORTB |= 0b00000001;

    Timer1_initialize( 51200, &fn, timer_prescale_256);
    sei();


    /* Replace with your application code */
    while (1)
    {

        while(semaphore == 0);
        semaphore = 0;


    }
}

