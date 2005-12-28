/*
 *
 * $Id$
 * unistd.h - Tastes good with cheese
 *
 */

#ifndef UNISTD_H
#define UNISTD_H

#include <sdcc/include/stdint.h>
#include "loc.h"

#define CLKFREQ 14746

/********** LED macros ***********/
#define RLED (P1 ^ 0x02) // pin 2
#define YLED (P1 ^ 0x04) // pin 3
#define GLED (P1 ^ 0x08) // pin 4
#define BLED (P2 ^ 0x10) // pin 5

#define LED_ON  0
#define LED_OFF 1

// LED pin output enable macros
#define RLED_OE(x) {P1DIR=(x) ? P1DIR&~0x04 : P1DIR|0x04;}
#define YLED_OE(x) {P1DIR=(x) ? P1DIR&~0x08 : P1DIR|0x08;}
#define GLED_OE(x) {P1DIR=(x) ? P1DIR&~0x10 : P1DIR|0x10;}
#define BLED_OE(x) {P2DIR=(x) ? P2DIR&~0x20 : P2DIR|0x20;}


/********** Function Prototypes ***********/
void sleep(uint8_t);

#endif
