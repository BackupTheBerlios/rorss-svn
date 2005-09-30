/*comm.h - communication header module thingie
*Author: Phil Hurwitz & Programming Team (eXtreme style)
*Created: 29 Sep 2005
*Modified: 29 Sep 2005
*/

#ifndef COMM_H
#define COMM_H

#define DIRECTION	0x01

struct comm_protocol
{
	char start_code;
	unsigned char device;
	unsigned char magnitude;
	char flags;
	char checksum; //7-bit checksum & 1-bit checksum parity bit
	char end_code;
};

#endif