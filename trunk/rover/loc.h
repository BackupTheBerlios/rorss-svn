/*
 *
 * $Id$
 * loc.h - Specifies locations of variables in memory
 *
 */

#include <sdcc/include/stdint.h>
#include <sdcc/include/mcs51/8051.h>

__sfr __at 0xA8 IE;	// Interrupt enable

//More info on P 50 of CC1010 Data Sheet
/*__sfr __at 0x80 P0;	// only bits 0-3 used
__sfr __at 0x90 P1;
__sfr __at 0xA0 P2;
__sfr __at 0xB0 P3;	// only bits 0-5 used
*/
__sfr __at 0xa4 P0DIR;	// Port0 direction
__sfr __at 0xa5 P1DIR;	// Port1 direction
__sfr __at 0xa6 P2DIR;	// Port2 direction
__sfr __at 0xa7 P3DIR;	// Port3 direction

__sfr __at 0xD2 WDT;	// Watchdog timer
__sfr __at 0x8E CKCON;	// Timer Clock Rate Control Register

__sfr __at 0xDB MODEM0;	// Modem Control Register 0
__sfr __at 0xDA MODEM1;	// Modem Control Register 1
__sfr __at 0xD9 MODEM2;	// Modem Control Register 2

__sfr __at 0xC8 RFMAIN; // RF Main Control Register
__sfr __at 0xC9 RFBUF;	// RF Data Buffer
__sfr __at 0xC2 RFCON;	// RF Control Register
__sfr __at 0xD3 PDET;	// Preamble Detection Control Register
__sfr __at 0xD4 BSYNC;	// Byte Synchronisation Register
__sfr __at 0xE2 PA_POW;	// Output Power Control Regster

__sfr __at 0x99 SBUF0;	// Serial Data Buffer 0
__sfr __at 0xC1 SBUF1;	// Serial Data Buffer 1
__sfr __at 0x98 SCON0;	// Serial Port 0 Control Register
__sfr __at 0xC0 SCON1;	// Serial Port 1 Control Register

__sfr __at 0xE8 EIE;	// Extended interrupt enable
__sfr __at 0x91 EXIF;	// Extended interrupt flag

__sfr __at 0x89 TMOD;	// Timer / Counter 0 and 1 Mode Register
__sfr __at 0x88 TCON;	// Timer / Counter 0 and 1 Control Register

#define LMOTOR_IN1 P1_1
#define LMOTOR_IN2 P1_2
#define RMOTOR_IN1 P1_3
#define RMOTOR_IN2 P1_4

__sfr __at 0xAC RMOTOR_DC; //T2, Used for Duty-Cycle for Right Motor
__sfr __at 0xAD LMOTOR_DC; //T3, Used for Duty-cycle for Left Motor

__sfr __at 0xA9 TCON2; //control register for timers 2-3
__sfr __at 0xAA T2PRE; //Timer 2 Prescalar
__sfr __at 0xAB T3PRE; //Timer 3 Prescalar
