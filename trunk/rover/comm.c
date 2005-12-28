/*
 *
 * $Id$
 * comm.c - Communications functions, including ISRs
 *
 */

#include <sdcc/include/stdbool.h>
#include <sdcc/include/stdint.h>
#include <sdcc/include/string.h> // for memcpy and memset
#include "unistd.h"
#include "gloves/gloves.h"
#include "comm.h"


#define SERIAL_SEND_PORT	(0)
#define SERIAL_RECV_PORT	(1)

#define OUTGOING_BUFFER_SIZE	(10)

COMM_PACKET		incoming_rf_data;
uint8_t			*next_incoming_rf_byte = &incoming_rf_data;

GLOVE_SERIAL_DATA	incoming_glove_data;
uint8_t			*next_incoming_glove_byte = &incoming_glove_data;

TRANSMITTING_SERIAL_DATA	serial_data_0, serial_data_1, rf_data;

// The following buffers are really queues.  The data keeps shifting 
// towards 0 and last_byte_idx_* indicates the index of the last byte
// of data in the queue.
uint8_t 		outgoing_serial_buffer[2][OUTGOING_BUFFER_SIZE];
int8_t			last_byte_idx_serial[2];
uint8_t			outgoing_rf_buffer[OUTGOING_BUFFER_SIZE];
int8_t			last_byte_idx_rf = -1;

/*
 * Function prototypes
 */
bool verify_checksum(uint8_t, uint8_t *, uint8_t);
void send_serial_data(bit, uint8_t *, uint8_t *);

/*
 * Function definitions
 */
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
			// Process the data since the buffer is full
			if ( verify_checksum(incoming_rf_data.checksum, &(uint8_t)incoming_rf_data + sizeof(incoming_rf_data.start_code), \
					sizeof(incoming_rf_data) - sizeof(incoming_rf_data.start_code) - sizeof(incoming_rf_data.end_code) - sizeof(incoming_rf_data.checksum)) )
			{
				// Send it out serially
				send_serial_data( SERIAL_SEND_PORT, (uint8_t *) &incoming_rf_data, (uint8_t *)(&incoming_rf_data + sizeof(incoming_rf_data)) );
				// Toggle the green LED
				//GLED ^= 0x04;
				P1 = GLED;
			}
			// else data was bad, chuck it
			
			
			next_incoming_rf_byte = &(uint8_t)incoming_rf_data;
		}
	}
	else
	{
		// We've just finished sending a byte
		if (last_byte_idx_rf >= 0)
		{
			uint8_t *ptr = &outgoing_rf_buffer[1];
			
			RFBUF = outgoing_rf_buffer[0];
			
			// Shift the old data out
			//outgoing_rf_buffer >>= 8;
			for ( ; ptr != &outgoing_rf_buffer[OUTGOING_BUFFER_SIZE-1]; ptr++)
			{
				*(ptr-1) = *ptr;
			}
			
			*ptr = 0;
			
			last_byte_idx_rf--;
		}
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
		*next_incoming_glove_byte = RFBUF;
		
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
			if ( verify_checksum(incoming_glove_data.checksum, &(uint8_t)incoming_glove_data, \
					sizeof(incoming_glove_data) - sizeof(incoming_glove_data.checksum)) )
			{
				// Toggle P2.0
				P2 ^= 0x01;
			}
			// else data was bad, chuck it
		}		
		
		// Clear flag
		SCON0 &= ~SCON_RI;
	
	}
	// Sending data?
	else
	{
		if (serial_data_0.current != 0)
		{
			// Increment the pointer to the next byte to be sent
			serial_data_0.current++;
			
			// If we're not at the end, shove this byte into the buffer
			// (assuming memory locations increment as they're requested...)
			if (serial_data_0.current < serial_data_0.end)
			{
				SBUF0 = *(serial_data_0.current);
			}
			// If we are at the end, reset the 'current' pointer to 0
			else
			{
				serial_data_0.current = 0;
			}
		}
		
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
// Select the port with sel (0 or 1)
void send_serial_data(bit port, uint8_t *data_start, uint8_t *data_end)
{
	uint8_t length = (uint8_t)(data_end - data_start); // length of data in bytes
	
	/*if (port == 0)
	{
		SBUF0 = *current_data;
		serial_data_0.start = *data_start;
		serial_data_0.end = data_end;
		serial_data_0.current = ++data_start;
	}
	else
	{
		SBUF1 = *current_data;
		serial_data_1.start = *data_start;
		serial_data_1.end = data_end;
		serial_data_1.current = ++data_start;
	}*/
	if ( length < OUTGOING_BUFFER_SIZE - 1 - last_byte_idx_rf )
	{
		// If there's nothing currently in the SBUFx buffer,
		// the next bytes in the local buffer won't get put
		// in there by the ISR
	        // So here we put the first byte in there
		if ( last_byte_idx_serial[port] < 0 )
		{
			if ( port == 0 )
				SBUF0 = *data_start;
			else
				SBUF1 = *data_start;
			
			// Copy the remaining bytes to the outgoing_serial_buffer
			// from the data_start passed in
			memcpy( &(outgoing_serial_buffer[port][last_byte_idx_serial[port] + 1]),
				(++data_start), (--length));
			
			last_byte_idx_serial[port] += length;
		}
	}
}

// Puts data into the RF buffer
void send_rf_data(uint8_t *data_start, uint8_t *data_end)
{
	/*uint8_t *current_data;
	uint8_t i;
	
	current_data = data_start;
	
	for (i = 0; i < length; i += 8)
	{
		sending_rf_data = true;
		RFBUF = *current_data;
		while (sending_rf_data);
		current_data++;
	}*/
	
	uint8_t length = (uint8_t)(data_end - data_start); // length of data in bytes
	
	if ( length < OUTGOING_BUFFER_SIZE - 1 - last_byte_idx_rf )
	{
		// If there's nothing currently in the RFBUF buffer,
		// the next bytes in the local buffer won't get put 
		// in there by the ISR
		// So here we put the first byte in there
		if ( last_byte_idx_rf < 0 )
		{
			RFBUF = *data_start;
			
			memcpy( &(outgoing_rf_buffer[last_byte_idx_rf + 1]), 
				(++data_start), (--length));
		}
		
		memcpy( &(outgoing_rf_buffer[last_byte_idx_rf + 1]), 
			data_start, length);
		
		last_byte_idx_rf += length;
	}
	
}
