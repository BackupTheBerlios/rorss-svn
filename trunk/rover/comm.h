/*
*  comm.h - communication header module thingie
*  Created: 29 Sep 2005
*  $Id$
*/

#ifndef COMM_H
#define COMM_H

// Flags in each communication packet
#define DIRECTION	0x01

/*
*  Standard packet for transmitting data
*  across a link (serial, RF, etc)
*/ 
struct comm_protocol
{
	char start_code;		// Constant start byte
	unsigned char device;		// Device type
	unsigned char magnitude;	// Device-dependant (i.e. speed of a motor)
	char flags;			// 
	char checksum;			// 7-bit checksum & 1-bit checksum parity bit
	char end_code;			// Constant end byte
};

#endif
