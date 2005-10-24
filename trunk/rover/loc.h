/*
 * $Id$
 * loc.h - Specifies locations of variables in memory
 *
 */

#include <sdcc/include/stdint.h>

xdata at 0xA8 uint8_t IE;	// Interrupt enable

//More info on P 50 of CC1010 Data Sheet
xdata at 0x80 uint8_t P0;	// only bits 0-3 used
xdata at 0x90 uint8_t P1;
xdata at 0xA0 uint8_t P2;
xdata at 0xB0 uint8_t P3;	// only bits 0-5 used

xdata at 0xa4 uint8_t P0DIR;	// Port0 direction
xdata at 0xa5 uint8_t P1DIR;	// Port1 direction
xdata at 0xa6 uint8_t P2DIR;	// Port2 direction
xdata at 0xa7 uint8_t P3DIR;	// Port3 direction

xdata at 0xD2 uint8_t WDT;	// Watchdog timer

xdata at 0xDB uint8_t MODEM0;	// Modem Control Register 0
xdata at 0xDA uint8_t MODEM1;	// Modem Control Register 1
xdata at 0xD9 uint8_t MODEM2;	// Modem Control Register 2

xdata at 0xC9 uint8_t RFBUF;	// RF Data Buffer
xdata at 0xC2 uint8_t RFCON;	// RF Control Register
xdata at 0xD3 uint8_t PDET;	// Preamble Detection Control Register
xdata at 0xD4 uint8_t BSYNC;	// Byte Synchronisation Register
xdata at 0xE2 uint8_t PA_POW;	// Output Power Control Regster

xdata at 0x99 uint8_t SBUF0;	// Serial Data Buffer 0
xdata at 0xC1 uint8_t SBUF1;	// Serial Data Buffer 1
xdata at 0x98 uint8_t SCON0;	// Serial Port 0 Control Register
xdata at 0xC0 uint8_t SCON1;	// Serial Port 1 Control Register


xdata at 0x91 uint8_t EXIF;	// Extended interrupt flag
