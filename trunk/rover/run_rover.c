/*
 *
 * $Id$
 * run_rover.c - The main program for the rover
 * Created: 6 Oct 2005
 *
 */

#define PREAMBLE_LENGTH (10)

#include <sdcc/include/sdcc-lib.h>
#include <sdcc/include/stddef.h>
#include <sdcc/include/stdint.h>
#include <sdcc/include/stdbool.h>
#include <sdcc/include/string.h> // for memset
#include "gloves/gloves.h"
#include "comm.h"
#include "unistd.h"

extern COMM_PACKET		incoming_rf_data;
extern uint8_t			*next_incoming_rf_byte;

extern GLOVE_SERIAL_DATA	incoming_glove_data;
extern uint8_t			*next_incoming_glove_byte;

// Function prototypes for ISRs
// these need to be here
void rf_isr(void)   interrupt 0x43;
void ser0_isr(void) interrupt 0x23;
void ser1_isr(void) interrupt 0x3B;


void main(void)
{

	uint8_t bunk = 255;  // for testing only
	
	// Initialize serial for 19200 baud, 1 stop bit, no parity
	CKCON = (CKCON_T1M & 0);	// using table 23 on pg 69
	TH1   = 252;
	SCON0 = (SCON_SM0 & 0) | (SCON_SM1 & 1);
	
	// Set up serial receive
	SCON1 = (SCON_SM0 & 0) | (SCON_SM1 & 1) | (SCON_REN & 1);
	
	memset(&incoming_rf_data, 0, sizeof(COMM_PACKET));
	next_incoming_rf_byte = &(uint8_t) incoming_rf_data;
	
	// Initialize RF parameters
	RFCON  = RFCON_BYTEMODE;  // enable bytemode (rcv 8-bits before interrupt fired)
	PDET   = (PDET_PEN & 0) | (PDET_PLEN & PREAMBLE_LENGTH);
	MODEM0 = (MODEM0_BAUDRATE & MODEM0_0_6K) | \
				(MODEM0_DATA_FMT & MODEM0_MANCHESTER) | \
				(MODEM0_XOSC_FREQ & 0x00);
	RFMAIN = 0;  // enable RX, power everything up
	
	IE  = IE_EA | IE_ES1 | IE_ES0;  // enable all interrupts, and serial 0 and 1
	EIE = EIE_RFIE;  // enable RF interrupt
	
	while(1)
	{
		// just for testing
		send_rf_data( &bunk, &bunk + 1 );
		sleep( 500 );
	}

}
