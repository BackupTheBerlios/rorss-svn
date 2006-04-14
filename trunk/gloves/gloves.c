/*
 *
 * $Id$
 * gloves.c - Gloves functions
 *
 */
#include <sdcc/include/stdbool.h>
#include <sdcc/include/stdint.h>
#include "shared/unistd.h"
#include "shared/comm.h"
#include "gloves.h"

uint8_t do_hash()
{
	uint8_t final;

	final = r_thumb + \
		r_index + \
		r_middle + \
		r_ring + \
		r_little + \
		pitch + \
		roll;

	return final;
}

void reset_glove(bit glove)
{
	// Resets a glove to command mode
	// Expect 0x55 back
	uint8_t reset_command = 0x41;
	send_serial_data( (bit)glove, &reset_command, &reset_command+1 );
	critical
	{
		serial_handler[glove] = &glove_reset_callback;
	};
}

void * glove_reset_callback(uint8_t returned_data)
{
	if (returned_data != 0x55)
	{
		RLED = LED_ON;
		return &reset_glove;
	}
	else
	{
		RLED = LED_OFF;
	}
	
	return NULL;
}

void test_glove(bit glove)
{
	// Sends 0x42 0xAA
	// Expect 0xAA back
	uint16_t test_command = 0x4200 | 0x00AA;
	send_serial_data( (bit)glove, &test_command, &test_command+2 );
	critical
	{
		serial_handler[glove] = &glove_test_callback;
	};
}

void * glove_test_callback(uint8_t returned_data)
{
	if (returned_data != 0xAA)
		RLED = LED_ON;
		return &test_glove;
	}
	else
	{
		RLED = LED_OFF;
	}
	
	return NULL;
}

void set_report_data_mode(bit glove)
{
	// Sends 0x43
	// Gets glove data back
	uint8_t set_report_data_command = 0x43;
	send_serial_data( (bit)glove, &set_report_data_command, &set_report_data_command+1 );
	critical
	{
		serial_handler[glove] = &buffer_glove_data_callback;
	};
}

void * buffer_glove_data_callback(int8_t glove_byte)
{

}
