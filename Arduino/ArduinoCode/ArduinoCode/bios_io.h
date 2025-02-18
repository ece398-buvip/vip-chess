/*
 * bios_io.h
 *
 * Created: 2/12/2025 10:54:04 AM
 *  Author: steoh
 */


#ifndef BIOS_IO_H_
#define BIOS_IO_H_

#include <avr/io.h>

uint8_t GetPortD (void);

void SetPortD(uint8_t x);

uint8_t GetDDRD(void);

void SetDDRD(uint8_t direction, uint8_t pull_up);



uint8_t GetPortC (void);

void SetPortC(uint8_t x);

uint8_t GetDDRC(void);

void SetDDRC(uint8_t direction, uint8_t pull_up)


uint8_t GetPortB (void);

void SetPortB(uint8_t x);



#endif /* BIOS_PINS_H_ */