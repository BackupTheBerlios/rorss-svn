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
uint8_t at 0xD3 PDET;	// Preamble Detection Control Register
uint8_t at 0xD4 BSYNC;	// Byte Synchronisation Register
uint8_t at 0xE2 PA_POW;	// Output Power Control Regster

uint8_t at 0x99 SBUF0;	// Serial Data Buffer 0
uint8_t at 0xC1 SBUF1;	// Serial Data Buffer 1
uint8_t at 0x98 SCON0;	// Serial Port 0 Control Register
uint8_t at 0xC0 SCON1;	// Serial Port 1 Control Register


uint8_t at 0x91 EXIF;	// Extended interrupt flag
