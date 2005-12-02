/*
 *
 * $Id$
 * run_astronaut.c - The main program for the astronaut
 * Created: 6 Oct 2005
 *
 */

#define PREAMBLE_LENGTH (10)

#include <sdcc/include/sdcc-lib.h>
#include <sdcc/include/stddef.h>
#include <sdcc/include/stdint.h>
#include <sdcc/include/ser_ir.h>
#include <sdcc/include/string.h> // for memset
#include "gloves/gloves.h"
#include "comm.h"

extern COMM_PACKET		incoming_rf_data;
extern uint8_t			*next_incoming_rf_byte;

extern GLOVE_SERIAL_DATA	incoming_glove_data;
extern uint8_t			*next_incoming_glove_byte;


// Function prototypes for ISRs
// these need to be here
void rf_isr(void)   interrupt 0x43;
void ser0_isr(void) interrupt 0x23;
void ser1_isr(void) interrupt 0x3B;


int main(void)
{
	
	// Initialize serial
	ser_init();
	
	// Initialize RF parameters
	RFCON  = RFCON_BYTEMODE;  // enable bytemode (rcv 8-bits before interrupt fired)
	PDET   = (PDET_PEN & 0) | (PDET_PLEN & PREAMBLE_LENGTH);
	MODEM0 = (MODEM0_BAUDRATE & MODEM0_0_6K) | \
				(MODEM0_DATA_FMT & MODEM0_MANCHESTER) | \
				(MODEM0_XOSC_FREQ & 0x00);
	RFMAIN = RFMAIN_RXTX;  // enable TX, power everything up
	
	memset(&incoming_rf_data, 0, sizeof(COMM_PACKET));
	next_incoming_rf_byte = &(uint8_t) incoming_rf_data;
	
	while(1);

}

