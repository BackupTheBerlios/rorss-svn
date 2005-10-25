/*
 * $Id$
 * gloves.h - Glove data header file
 *
 */

#include <sdcc/include/stdint.h>

#define UPPER_NIBBLE	(0xF0)
#define LOWER_NIBBLE	(0x0F)

struct glove_serial_data
{
	uint8_t		start;		// Defined as 0x3C '<'
	uint8_t		type;		// 0x10 for right, 0x11 for left
	
	uint8_t		version;
	uint8_t		LI1_HI2;
	uint8_t		LU2_LI2;
	uint8_t		HI3_LU3;
	uint8_t		LI3_HI4;
	uint8_t		LU4_LI4;
	uint8_t		HI5_LU5;
	uint8_t		LI5_HI6;
	uint8_t		LU6_LI6;
	uint8_t		HI7_LU7;
	uint8_t		LI7_HI8;
	uint8_t		LU8_LI8;
	uint8_t		HI9_LU9;
	uint8_t		LI9_HI10;
	uint8_t		LU10_LI10;
	uint8_t		HI11_LU11;
	uint8_t		LI11_HI12;
	uint8_t		LU12_LI12;
	uint8_t		HI13_LU13;
	uint8_t		LI13_HI14;
	uint8_t		LU14_LI14;
	uint8_t		HI15_LU15;
	uint8_t		LI15_HI16;
	uint8_t		LU16_LI16;
	
	uint8_t		checksum;
	uint8_t		footer;		// Defined as 0x3E '>'

};

typedef struct glove_serial_data	GLOVE_SERIAL_DATA;
