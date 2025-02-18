/*
 * bios_io.c
 *
 * Created: 2/12/2025 10:53:53 AM
 *  Author: steoh
 */

#include "bios_io.h"



#define MASK_PORTD 0b11111100
#define MASK_PORTC 0b00111111
#define MASK_PORTB 0b00111111


///////PORT D/////////


uint8_t GetPortD (void)
{
    return(PIND & MASK_PORTD);
}

void SetPortD(uint8_t out) {
    PORTD = (PORTD & ~MASK_PORTD) | ((out & MASK_PORTD));
}

uint8_t GetDDRD(void)
{
    return(DDRD & MASK_PORTD);
}

void SetDDRD(uint8_t direction, uint8_t pull_up) {
    DDRD = (DDRD & ~MASK_PORTD) | (direction & MASK_PORTD);
    PORTD = (PORTD & ~MASK_PORTD) | (pull_up & MASK_PORTD & ~direction);
}






///////PORT C/////////


uint8_t GetPortC (void)
{
    return(PINC & MASK_PORTC);
}

void SetPortC(uint8_t x) {
    PORTC = (PORTC & ~MASK_PORTC) | (x & MASK_PORTC);
}

uint8_t GetDDRC(void)
{
    return(DDRC & MASK_PORTD);
}

void SetDDRC(uint8_t direction, uint8_t pull_up) {
    DDRC = (DDRC & ~MASK_PORTC) | (direction & MASK_PORTC);
    PORTC = (PORTC & ~MASK_PORTC) | (pull_up & MASK_PORTC & ~direction);
}




///////PORT B/////////


uint8_t GetPortB (void)
{
    return(PINB & MASK_PORTB);
}

void SetPortB(uint8_t x) {
    PORTB = (PORTB & ~MASK_PORTB) | (x & MASK_PORTB);
}

uint8_t GetDDRB(void)
{
    return(DDRB & MASK_PORTB);
}

void SetDDRB(uint8_t direction, uint8_t pull_up) {
    DDRB = (DDRB & ~MASK_PORTB) | (direction & MASK_PORTB);
    PORTD = (PORTB & ~MASK_PORTB) | (pull_up & MASK_PORTB & direction);
}



