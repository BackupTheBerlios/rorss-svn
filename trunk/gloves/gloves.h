/*
 * $Id$
 * gloves.h - Glove data header file
 *
 */

#include <sdcc/include/stdint.h>

#define HEADER		(0x80)

#define UNFLEXED	(0x00)
#define FLEXED		(0xFF)

struct glove_serial_data
{
	uint8_t		header;		// Defined as 0x80
	
	// All these are magnitudes from 0-255
	union
	{
		struct right
		{
			int8_t		thumb;
			int8_t		index;
			int8_t		middle;
			int8_t		ring;
			int8_t		little;
		};
	
		struct left
		{
			int8_t		little;
			int8_t		ring;
			int8_t		middle;
			int8_t		index;
			int8_t		thumb;
		};
	} hand;
	
	int8_t		pitch;
	int8_t		roll;
	uint8_t		checksum;
};

typedef struct glove_serial_data	GLOVE_SERIAL_DATA;
