/*
 * commands.c
 *
 * Created: 4/15/2025 2:21:13 PM
 *  Author: steoh
 */
#include "commands.h"
#include "Bios/bios_uart0.h"


void CommandsInit() {
    uart0_initialize(uart_bps_9600);
}



void WaitForCommand() {

}
