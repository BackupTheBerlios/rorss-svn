/*
*  $Id$
*  comm.h - communication header module thingie
*  Created: 29 Sep 2005
*/

#ifndef COMM_H
#define COMM_H

//Ie (0xa8) interrupt Enable Register
#define IE_GLOBAL_INTERRUPT	(0x80)
#define IE_SERIAL_PORT_1	(0x40)
#define IE_SERIAL_PORT_0	(0x10)
#define IE_TIMER_1		(0x08)
#define IE_EXTERNAL_1		(0x04)
#define IE_TIMER_0		(0x02)
#define IE_EXTERNAL_0		(0x01)

//EIE (0xE8) Extended Interrupt Enable Register
#define EIE_REALTIME_CLOCK	(0x10)
#define EIE_TIMER_3		(0x08)
#define EIE_ADC_DES		(0x04)
#define EIE_TIMER_2		(0x02)
#define EIE_RF_INTERRUPT	(0x01)


// Flags in each communication packet
#define DIRECTION	0x01

/*
*  Standard packet for transmitting data
*  across a link (serial, RF, etc)
*/ 
struct comm_protocol
{
	int8_t start_code;	// Constant start byte
	uint8_t device;		// Device type
	uint8_t magnitude;	// Device-dependant (i.e. speed of a motor)
	int8_t flags;		// 
	int8_t checksum;	// 7-bit checksum & 1-bit checksum parity bit
	int8_t end_code;	// Constant end byte
};

#endif
