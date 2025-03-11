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


uint8_t GetPortD(void)
{
    return (PIND & MASK_PORTD);
}

void SetPortD(uint8_t out)
{
    PORTD = (PORTD & ~MASK_PORTD) | ((out & MASK_PORTD));
}

uint8_t GetDDRD(void)
{
    return (DDRD & MASK_PORTD);
}

void SetDDRD(uint8_t direction)
{
    DDRD = (DDRD & ~MASK_PORTD) | (direction & MASK_PORTD);
}






///////PORT C/////////


uint8_t GetPortC (void)
{
    return(PINC & MASK_PORTC);
}

void SetPortC(uint8_t x)
{
    PORTC = (PORTC & ~MASK_PORTC) | (x & MASK_PORTC);
}

uint8_t GetDDRC(void)
{
    return(DDRC & MASK_PORTC);
}

void SetDDRC(uint8_t direction)
{
    DDRC = (DDRC & ~MASK_PORTC) | (direction & MASK_PORTC);
}




///////PORT B/////////


uint8_t GetPortB (void)
{
    return(PINB & MASK_PORTB);
}

void SetPortB(uint8_t x)
{
    PORTB = (PORTB & ~MASK_PORTB) | (x & MASK_PORTB);
}

uint8_t GetDDRB(void)
{
    return(DDRB & MASK_PORTB);
}

void SetDDRB(uint8_t direction)
{
    DDRB = (DDRB & ~MASK_PORTB) | (direction & MASK_PORTB);
}




///////PORT X/////////

uint8_t GetPortX(Port port){
	switch(port) {
		case Port.PortB:
			return GetPortB();
			break;
		case Port.PortC:
			return GetPortC();
			break;
		case Port.PortD:
			return GetPortD();
			break;
		default:
			return GetPortB();			
	}
}


void SetPortX(Port port, uint8_t x) {
	switch(port) {
		case Port.PortB:
			SetPortB(x);
			break;
		case Port.PortC:
			SetPortC(x);
			break;
		case Port.PortD:
			SetPortD(x);
			break;
		default:
			SetPortB(x);			
	}
}


uint8_t GetDDRX(Port port) {
	switch(port) {
		case Port.PortB:
			return GetDDRB();
			break;
		case Port.PortC:
			return GetDDRC();
			break;
		case Port.PortD:
			return GetDDRD();
			break;
		default:
			return GetDDRB();			
	}
}
	
void SetDDRX(Port port, uint8_t direction) {
	switch(port) {
		case Port.PortB:
			SetDDRB(direction);
			break;
		case Port.PortC:
			SetDDRC(direction);
			break;
		case Port.PortD:
			SetDDRD(direction);
			break;
		default:
			SetDDRB(direction);			
	}

