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
#include "shared/ftable.h"
#include "comm.h"


COMM_PACKET		incoming_rf_data;
uint8_t			*next_incoming_rf_byte = &incoming_rf_data;

GLOVE_SERIAL_DATA	incoming_glove_data;
uint8_t			*next_incoming_glove_byte = &incoming_glove_data;

bool sending_serial_data;
bool sending_rf_data;

bool verify_checksum(uint8_t, uint8_t *, uint8_t);

// Verifies that the data is correct 
// according to its checksum
bool verify_checksum(uint8_t checksum, uint8_t *data_ptr, uint8_t size_of_data)
{
	uint8_t sum, i;
	
	for(i = 0; i < size_of_data; i += sizeof(size_of_data))
	{
		sum += *data_ptr;
		data_ptr++;
	}
	
	return (bool)(sum == checksum);
}

// Compress the serial data in from the gloves
// to 1-bit numbers
GLOVE_COMPRESSED_DATA compress_glove_gesture(GLOVE_SERIAL_DATA *data_to_compress, bool which_hand)
//which_hand is true/1 when the right hand is being operated on, it is false/0 when the left hand is being operated on
{
	GLOVE_COMPRESSED_DATA gc;

	gc.hand = (bit) which_hand;

	if (which_hand)
	{
		gc.thumb  = (*data_to_compress.hand.right.thumb  > 127 ? 1 : 0);
		gc.index  = (*data_to_compress.hand.right.index  > 127 ? 1 : 0);
		gc.middle = (*data_to_compress.hand.right.middle > 127 ? 1 : 0);
		gc.ring   = (*data_to_compress.hand.right.ring   > 127 ? 1 : 0);
		gc.pinky  = (*data_to_compress.hand.right.pinky  > 127 ? 1 : 0);
		gc.pitch  = (*data_to_compress.hand.right.pitch  > 127 ? 1 : 0);
		gc.roll   = (*data_to_compress.hand.right.roll   > 127 ? 1 : 0);
	}
	else
	{
		gc.thumb  = (*data_to_compress.hand.left.thumb  > 127 ? 1 : 0);
		gc.index  = (*data_to_compress.hand.left.index  > 127 ? 1 : 0);
		gc.middle = (*data_to_compress.hand.left.middle > 127 ? 1 : 0);
		gc.ring   = (*data_to_compress.hand.left.ring   > 127 ? 1 : 0);
		gc.pinky  = (*data_to_compress.hand.left.pinky  > 127 ? 1 : 0);
		gc.pitch  = (*data_to_compress.hand.left.pitch  > 127 ? 1 : 0);
		gc.roll   = (*data_to_compress.hand.left.roll   > 127 ? 1 : 0);
	}

	return gc;
}

void interpret_gesture(GLOVE_COMPRESSED_DATA compressed_glove_gesture)
{

}

/****************************************************************************
 *                                ISRs                                      *
 ****************************************************************************/

// RF transmit/receive interrupt
// Interrupt enable: EIE_RFIE
// Interrupt flag:   EXIF_RFIF
void rf_isr(void) interrupt 0x43
{
	
	if (!(RFMAIN & RFMAIN_RXTX))
	{
		// We're receiving something
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
				ser_puts( (unsigned char *) &incoming_rf_data );
				// Toggle Blue LED
				P1_1 = (P1_1 ^ 1);
			}
			// else data was bad, chuck it
		}
	}
	else
	{
		// We've just finished sending something
		sending_rf_data = false;
	}
	
	// Clear interupt flag
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
		// Grab buffer data, stick it at pointer location
		*next_incoming_glove_byte = SBUF0;
		
		// Increment pointer if it won't go past the end of
		// the global buffer
		if ( (&(uint8_t)incoming_glove_data - next_incoming_glove_byte) < \
		       (sizeof(incoming_glove_data) - sizeof(next_incoming_glove_byte)) )
		{
			next_incoming_glove_byte++;
		}
		// Otherwise, reset it to the beginning of the
		// global buffer
		else
		{
			next_incoming_glove_byte = &(uint8_t)incoming_glove_data;
			
			// Process the data since the buffer is full
			if ( verify_checksum(incoming_glove_data.checksum, &(uint8_t)incoming_glove_data + sizeof(incoming_glove_data.start_code), \
					sizeof(incoming_glove_data) - sizeof(incoming_glove_data.start_code) - sizeof(incoming_glove_data.end_code) - sizeof(incoming_glove_data.checksum)) )
			{
				// Send it out serially
				ser_puts( (unsigned char) &incoming_glove_data );
				// Toggle P0.0
				P0 ^= 0x01;
			}
			// else data was bad, chuck it
		}		
		
		// Test to see if current buffer is filled with enough
		// data to compress and interpret
		if ( (next_incoming_glove_byte - &incoming_glove_data) > sizeof(GLOVE_SERIAL_DATA) )
		{
			interpret_gesture( \
				compress_glove_gesture( (GLOVE_SERIAL_DATA*) &incoming_glove_data, RIGHT_GLOVE ) \
			);
		}
		
		// Clear flag
		SCON0 &= ~SCON_RI;
	
	}
	// Sending data?
	else
	{
		sending_serial_data = false;
		
		// Clear flag
		SCON0 &= ~SCON_TI;
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

/****************************************************************************
 *                        Helper functions                                  *
 ****************************************************************************/

// Puts data into the serial buffer
// and blocks until it's done
// Select the port with sel (0 or 1)
void send_serial_data(bit port, uint8_t *data_start, uint8_t length)
{
	uint8_t *current_data;
	uint8_t i;
	
	current_data = data_start;
	
	if (port == 0)
	{
		for (i = 0; i < length; i += 8)
		{
			sending_serial_data = true;
			SBUF0 = *current_data;
			while (sending_serial_data);
			current_data++;
		}
	}
	else
	{
		for (i = 0; i < length; i += 8)
		{
			sending_serial_data = true;
			SBUF1 = *current_data;
			while (sending_serial_data);
			current_data++;
		}
	}
}

// Puts data into the RF buffer
// and blocks until it's done
void send_rf_data(uint8_t *data_start, uint8_t length)
{
	uint8_t *current_data;
	uint8_t i;
	
	current_data = data_start;
	
	for (i = 0; i < length; i += 8)
	{
		sending_rf_data = true;
		RFBUF = *current_data;
		while (sending_rf_data);
		current_data++;
	}
	
}
