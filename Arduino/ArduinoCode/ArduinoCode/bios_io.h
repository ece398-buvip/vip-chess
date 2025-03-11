/*
 * bios_io.h
 *
 * Created: 2/12/2025 10:54:04 AM
 *  Author: steoh
 */


#ifndef BIOS_IO_H_
#define BIOS_IO_H_

#include <stdint.h>
#include <avr/io.h>


typedef enum {
    PortB,
    PortC,
    PortD
} Port;

uint8_t GetPortD (void);
void SetPortD(uint8_t x);
uint8_t GetDDRD(void);
void SetDDRD(uint8_t direction);



uint8_t GetPortC (void);
void SetPortC(uint8_t x);
uint8_t GetDDRC(void);
void SetDDRC(uint8_t direction);


uint8_t GetPortB (void);
void SetPortB(uint8_t x);
uint8_t GetDDRB(void);
void SetDDRB(uint8_t direction);




uint8_t GetPortX(Port port);
void SetPortX(Port port, uint8_t x);
uint8_t GetDDRX(Port port);
void SetDDRX(Port port, uint8_t direction);


#endif /* BIOS_PINS_H_ */