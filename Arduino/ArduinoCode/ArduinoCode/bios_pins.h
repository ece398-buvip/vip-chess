/*
 * bios_pins.h
 *
 * Created: 2/12/2025 10:54:04 AM
 *  Author: steoh
 */


#ifndef BIOS_PINS_H_
#define BIOS_PINS_H_

#include <avr/io.h>

void SetPortD(uint8_t x);

uint8_t GetPortC (void);

void SetPortC(uint8_t x);


uint8_t GetPortB (void);

void SetPortB(uint8_t x);



#endif /* BIOS_PINS_H_ */