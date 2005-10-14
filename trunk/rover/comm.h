/*
*  $Id$
*  comm.h - communication header module thingie
*  Created: 29 Sep 2005
*/

#ifndef COMM_H
#define COMM_H

#include "loc.h"

// Macros
// Disable all interrupts (except flash/debug)
#define BEGIN_CRITICAL_SECTION() \
	(IE &= 0x7F)

// Enable all interrupts
#define END_CRITICAL_SECTION() \
	(IE |= 0x80)

//IE (0xa8) interupt Enable Register
//P 29 of  http://www.chipcon.com/files/CC1010_Data_Sheet_1_3.pdf
#define IE_EA		(0x80)//GLOBAL_INTERRUPT
#define IE_ES1		(0x40)//SERIAL_PORT_1
#define IE_ES0		(0x10)//SERIAL_PORT_0
#define IE_ET1		(0x08)//TIMER_1
#define IE_TX1		(0x04)//EXTERNAL_1
#define IE_ET0		(0x02)//TIMER_0
#define IE_TX0		(0x01)//EXTERNAL_0
//EIE (0xE8) Extended Interrupt Enable Register
#define EIE_RTCIE	(0x10)//REALTIME_CLOCK
#define EIE_ET3		(0x08)//TIMER_3
#define EIE_ADIE	(0x04)//ADC_DES
#define EIE_ET2		(0x02)//TIMER_2
#define EIE_RFIE	(0x01)//RF_INTERRUPT
//EXIF (0x91) Exted interrupt Flag
#define EXIF_TF3	(0x80)//Timer 3 interrupt flag
#define EXIF_ADIF	(0x40)//ADC/DES interrupt Flag
#define EXIF_TF2	(0x20)//Timer 2 interrupt flag
#define EXIF_RFIF	(0x10)//RF Transmit/receive interrupt flag

// Flags in each communication packet
#define DIRECTION	(0x01)

//WDT (0xD2) Watchdog Timer Control (P63)
#define WDT_SE		(0x10)
#define WDT_EN		(0x08)
#define WDT_CLR		(0x04)
#define WDT_RE1		(0x02)
#define WDT_RE0		(0x00)



/*
*  Standard packet for transmitting data
*  across a link (serial, RF, etc)
*/ 
struct comm_protocol
{
	int8_t 	start_code;	// Constant start byte
	uint8_t	device;		// Device type
	uint8_t	magnitude;	// Device-dependant (i.e. speed of a motor)
	int8_t 	flags;		// 
	int8_t 	checksum;	// 7-bit checksum & 1-bit checksum parity bit
	int8_t 	end_code;	// Constant end byte
};

#endif
