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
#define LED1 (P2_2) // pin 2
#define LED2 (P2_3) // pin 3
#define LED3 (P2_4) // pin 4
#define LED4 (P2_5) // pin 5

#define LED_ON  0
#define LED_OFF 1

// LED pin output enable macros
#define LED1_OE(x) {P2DIR=(x) ? P2DIR&~0x02 : P2DIR|0x02;}
#define LED2_OE(x) {P2DIR=(x) ? P2DIR&~0x04 : P2DIR|0x04;}
#define LED3_OE(x) {P2DIR=(x) ? P2DIR&~0x08 : P2DIR|0x08;}
#define LED4_OE(x) {P2DIR=(x) ? P2DIR&~0x10 : P2DIR|0x10;}


/********** Function Prototypes ***********/
void sleep(uint8_t);

#endif
