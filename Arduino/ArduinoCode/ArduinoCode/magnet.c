/*
 * magnet.c
 *
 * Created: 4/22/2025 7:59:29 PM
 *  Author: steoh
 */

#include "magnet.h"

void MagnetInit() {
    SetDDRC(0b00000001 | GetDDRC());
    SetPortC(0b11111110 & GetPortC());
}

void MagnetOn() {
    SetPortC(0b00000001 | GetPortC());
}

void MagnetOff() {
    SetPortC(0b11111110 & GetPortC());
}