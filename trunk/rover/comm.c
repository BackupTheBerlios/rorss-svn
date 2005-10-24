/*
 *
 * $Id$
 * comm.c - Communications functions, including ISRs
 *
 */

#include <sdcc/include/stdbool.h>
#include <sdcc/include/stdint.h>
#include <sdcc/include/ser_ir.h>
#include "gloves/gloves.h"
#include "comm.h"


COMM_PACKET		incoming_rf_data;
uint8_t			*next_incoming_rf_byte = &incoming_rf_data;

GLOVE_SERIAL_DATA	incoming_glove_data;
uint8_t			*next_incoming_glove_byte = &incoming_glove_data;

bool verify_checksum(uint8_t, uint8_t*, uint8_t);

// Verifies that the data is correct 
// according to its checksum
bool verify_checksum(uint8_t checksum, uint8_t *data, uint8_t size_of_data)
{
	uint8_t sum, i;
	
	for(i = 0; i < size_of_data; i += sizeof(size_of_data))
	{
		sum += *data;
		data++;
	}
	
	return (bool)(sum == checksum);
}

// RF transmit/receive interrupt
// Interrupt enable: EIE_RFIE
// Interrupt flag:   EXIF_RFIF
void rf_isr(void) interrupt 0x43
{
	// Grab buffer data, stick it at pointer location
	*next_incoming_rf_byte = RFBUF;
	
	// Increment pointer if it won't go past the end of
	// the global buffer
	if ( (&(uint8_t)incoming_rf_data - next_incoming_rf_byte) < \
	       (sizeof(incoming_rf_data) - sizeof(next_incoming_rf_byte)) )
	{
		next_incoming_rf_byte++;
	}
	// Otherwise, reset it to the beginning of the
	// global buffer
	else
	{
		next_incoming_rf_byte = &(uint8_t)incoming_rf_data;
		
		// Process the data since the buffer is full
		if ( verify_checksum(incoming_rf_data.checksum, &(uint8_t)incoming_rf_data + sizeof(incoming_rf_data.start_code), \
				sizeof(incoming_rf_data) - sizeof(incoming_rf_data.start_code) - sizeof(incoming_rf_data.end_code) - sizeof(incoming_rf_data.checksum)) )
		{
			// Send it out serially
			ser_puts( (unsigned char) &incoming_rf_data );
			// Toggle P0.0
			P0 ^= 0x01;
		}
		// else data was bad, chuck it
	}
	
	// Clear flag
	EXIF &= ~EXIF_RFIF;
}

// Serial Port 0 transmit/receive interrupt
// Interrupt enable: IE_ES0
// Transmit:
//  Interrupt flag: SCON0_TI_0
// Receive:
//  Interrupt flag: SCON0_RI_0
void ser0_isr(void) interrupt 0x23
{
	// Receiving data?
	if (SCON0 & SCON_RI)
	{
		
		
		// Clear flag
		SCON0 &= ~SCON_RI;
	}
}

// Serial Port 1 transmit/receive interrupt
// Interrupt enable: IE_ES1
// Transmit:
//  Interrupt flag: SCON0_TI_1
// Receive:
//  Interrupt flag: SCON0_RI_1
void ser1_isr(void) interrupt 0x3B
{

}
