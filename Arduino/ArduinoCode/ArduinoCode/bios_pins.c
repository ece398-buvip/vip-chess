/*
 * bios_pins.c
 *
 * Created: 2/12/2025 10:53:53 AM
 *  Author: steoh
 */

#include "bios_pins.h"


uint8_t GetPortD (void)
{
    return(PIND & 0b11111100);
}

void SetPortD(uint8_t x) {
    PORTD = (PORTD & 0b00000011) | (x & 0b11111100);
}

uint8_t GetPortC (void)
{
    return(PIND & 0b00111111);
}

void SetPortC(uint8_t x) {
    PORTD = (PORTD & 0b11000000) | (x & 0b00111111);
}


uint8_t GetPortB (void)
{
    return(PINB & 0b00111111);
}

void SetPortB(uint8_t x) {
    PORTB = (PORTB & 0b11000000) | (x & 0b00111111);
}