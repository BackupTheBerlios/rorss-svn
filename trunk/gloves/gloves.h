/*
 *
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
			int8_t		r_thumb;
			int8_t		r_index;
			int8_t		r_middle;
			int8_t		r_ring;
			int8_t		r_little;
		};
	
		struct left
		{
			int8_t		l_little;
			int8_t		l_ring;
			int8_t		l_middle;
			int8_t		l_index;
			int8_t		l_thumb;
		};
	} hand;
	
	int8_t		pitch;
	int8_t		roll;
	uint8_t		checksum;
};

typedef struct glove_serial_data	GLOVE_SERIAL_DATA;
