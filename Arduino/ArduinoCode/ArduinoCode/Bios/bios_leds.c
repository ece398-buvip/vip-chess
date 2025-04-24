/*
 * bios_leds.c
 *
 * Created: 4/23/2025 7:22:45 PM
 *  Author: steoh
 */

// This is AVR code for driving the RGB LED strips from Pololu.
//
// It allows complete control over the color of an arbitrary number of LEDs.
// This implementation disables interrupts while it does bit-banging with
// inline assembly.
//
// This version uses "cbi" and "sbi" instructions, which only work on registers
// in the first 32 bytes of I/O memory.  For a more flexible version of this
// that can work on any register, see led_strip_ds.c.

// This line specifies the frequency your AVR is running at.
// This code supports 20 MHz, 16 MHz and 8MHz
#define F_CPU 16000000

// These lines specify what pin the LED strip is on.
// You will either need to attach the LED strip's data line to PC0 or change these
// lines to specify a different pin.
#define LED_STRIP_PORT PORTC
#define LED_STRIP_DDR  DDRC
#define LED_STRIP_PIN  2

#include "bios_leds.h"
#include "light_ws2812.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <math.h>


// The rgb_color struct represents the color for an 8-bit RGB LED.
// Examples:
//   Black:      (rgb_color){ 0, 0, 0 }
//   Pure red:   (rgb_color){ 255, 0, 0 }
//   Pure green: (rgb_color){ 0, 255, 0 }
//   Pure blue:  (rgb_color){ 0, 0, 255 }
//   White:      (rgb_color){ 255, 255, 255}
typedef struct rgb_color
{
    uint8_t red, green, blue;
} rgb_color;

// led_strip_write sends a series of colors to the LED strip, updating the LEDs.
// The colors parameter should point to an array of rgb_color structs that hold
// the colors to send.
// The count parameter is the number of colors to send.
// This function takes about 1.1 ms to update 30 LEDs.
// Interrupts must be disabled during that time, so any interrupt-based library
// can be negatively affected by this function.
// Timing details at 20 MHz:
//   0 pulse  = 400 ns
//   1 pulse  = 850 ns
//   "period" = 1300 ns
// Timing details at 16 MHz:
//   0 pulse  = 375 ns
//   1 pulse  = 812.5 ns
//   "period" = 1500 ns
void __attribute__((noinline)) led_strip_write(rgb_color * colors, uint16_t count)
{
    // Set the pin to be an output driving low.
    LED_STRIP_PORT &= ~(1 << LED_STRIP_PIN);
    LED_STRIP_DDR |= (1 << LED_STRIP_PIN);

    cli();   // Disable interrupts temporarily because we don't want our pulse timing to be messed up.
    while (count--)
    {
        uint8_t portValue = LED_STRIP_PORT;
        // Send a color to the LED strip.
        // The assembly below also increments the 'colors' pointer,
        // it will be pointing to the next color at the end of this loop.
        asm volatile (
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0\n"
        "rcall send_led_strip_byte%=\n"  // Send red component.
        "ld __tmp_reg__, -%a0\n"
        "rcall send_led_strip_byte%=\n"  // Send green component.
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0+\n"
        "rcall send_led_strip_byte%=\n"  // Send blue component.
        "rjmp led_strip_asm_end%=\n"     // Jump past the assembly subroutines.

        // send_led_strip_byte subroutine:  Sends a byte to the LED strip.
        "send_led_strip_byte%=:\n"
        "rcall send_led_strip_bit%=\n"  // Send most-significant bit (bit 7).
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"  // Send least-significant bit (bit 0).
        "ret\n"

        // send_led_strip_bit subroutine:  Sends single bit to the LED strip by driving the data line
        // high for some time.  The amount of time the line is high depends on whether the bit is 0 or 1,
        // but this function always takes the same time (2 us).
        "send_led_strip_bit%=:\n"
        #if F_CPU == 8000000
        "rol __tmp_reg__\n"                      // Rotate left through carry.
        #endif
        "sts %2, %4\n"                           // Drive the line high.

        #if F_CPU != 8000000
        "rol __tmp_reg__\n"                      // Rotate left through carry.
        #endif

        #if F_CPU == 16000000
        "nop\n" "nop\n"
        #elif F_CPU == 20000000
        "nop\n" "nop\n" "nop\n" "nop\n"
        #elif F_CPU != 8000000
        #error "Unsupported F_CPU"
        #endif

        // If the bit to send is 0, drive the line low now.
        "brcs .+4\n" "sts %2, %3\n"

        #if F_CPU == 8000000
        "nop\n" "nop\n"
        #elif F_CPU == 16000000
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        #elif F_CPU == 20000000
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n"
        #endif

        // If the bit to send is 1, drive the line low now.
        "brcc .+4\n" "sts %2, %3\n"

        "ret\n"
        "led_strip_asm_end%=: "
        : "=b" (colors)
        : "0" (colors),           // %a0 points to the next color to display
        "" (&LED_STRIP_PORT),   // %2 is the port register (e.g. PORTH)
        "r" ((uint8_t)(portValue & ~(1 << LED_STRIP_PIN))),  // %3
        "r" ((uint8_t)(portValue | (1 << LED_STRIP_PIN)))    // %4
        );

        // Uncomment the line below to temporarily enable interrupts between each color.
        //sei(); asm volatile("nop\n"); cli();
    }
    sei();          // Re-enable interrupts now that we are done.
    _delay_us(80);  // Send the reset signal.
}






#define xtal 16000000L


void Timer0_initialize ( uint32_t frequency, uint8_t prescaler )
{
    // -  1  8 64 256 1024
    const static uint8_t prescales[] = {0, 0, 3, 6, 8, 10};

    TCNT0=0x00;
    // set timer0 counter initial value to 0
    // (note: entirely redundant as it was never used before)

    OCR0A = ((uint32_t)(xtal)>>prescales[prescaler]) / frequency - 1;

    TCCR0A = 0x00;
    // AABBCCMM - lower two bits of 4-bit mode MMMM

    TCCR0B = 0x08 | (0x07 & prescaler);
    // ??-MMPPP - MM is upper two bits of mode MMMM, PPP is clock rescale
    // where PPP of 011 is clock rescale of 64
    // where MM MM is the Timer mode, we use 01 00 - CTC

    TIFR0  = 0;
    // reset any pending Timer1 interrupts
    // (note: entirely redundant as none is pending - it was never used before)

    TIMSK0 = (1<<OCIE0A);
    //  ICIE1  - enable Timer1 capture interrupt
    //  OCIE1A - enable Timer1 match OCR1A match interrupt
    //  TOIE1  - enable Timer1 overflow interrupt
}

void Timer0_shutdown ()
{
    TIMSK0 &= ~(1<<TOIE0 | 1<<OCIE0A | 1<<OCIE0B | 1<<TOIE0);
    // disable all Timer1 interrupts
    // which is the same effort as disabling just one interrupt but can be reused in other examples

    TCCR0A = 0;
    TCCR0B = 0;
    TIMSK0 = 0;
    TIFR0  = 0;
}













#define LED_COUNT 164
rgb_color colors[LED_COUNT];


void ledsInit() {
    //Timer0_initialize(10, 8);
    for (uint16_t i = 0; i < LED_COUNT; i++) {
        double angle = (2.0 * M_PI * 5.0 * i) / LED_COUNT;
        uint8_t out = (uint8_t)(255.0 * pow((sin(angle) * 0.5 + 0.5), 4));
        colors[i] = (rgb_color){255, out, out};
    }
}


void ledsUpdate() {
    rgb_color last = colors[LED_COUNT - 1];

    for (int i = LED_COUNT - 1; i > 0; i--) {
        colors[i] = colors[i - 1];
    }

    colors[0] = last;

    led_strip_write(colors, LED_COUNT);

}


ISR(TIMER0_COMPA_vect)
{
    // Note:    if time is critical (high frequency interrupt that
    //          is optimized for speed then put the code here
    //          instead of calling it in another function
    //ledsUpdate();
}

