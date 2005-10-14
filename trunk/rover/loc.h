/*
 * $Id$
 * loc.h - Specifies locations of variables in memory
 *
 */

#include <sdcc/include/stdint.h>

uint8_t at 0xA8 IE;	// Interrupt enable

//More info on P 50 of CC1010 Data Sheet
uint8_t at 0x80 P0;	// only bits 0-3 used
uint8_t at 0x90 P1;
uint8_t at 0xA0 P2;
uint8_t at 0xB0 P3;	// only bits 0-5 used

uint8_t at 0xa4 P0DIR;  // Port0 direction
uint8_t at 0xa5 P1DIR;	// Port1 direction
uint8_t at 0xa6 P2DIR;	// Port2 direction
uint8_t at 0xa7 P3DIR;	// Port3 direction

uint8_t at 0xD2 WDT;	// Watchdog timer

uint8_t at 0xDB MODEM0;	// Modem Control Register 0
uint8_t at 0xDA MODEM1;	// Modem Control Register 1
uint8_t at 0xD9 MODEM2; // Modem Control Register 2

uint8_t at 0xC9 RFBUF;	// RF Data Buffer
uint8_t at 0xC2 RFCON;	// RF Control Register
