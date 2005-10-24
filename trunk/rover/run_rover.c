/*
 * $Id$
 * run_rover.c - The main program for the rover
 * Created: 6 Oct 2005
 */

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
void rf_isr(void)   interrupt 0x43;
void ser0_isr(void) interrupt 0x23;
void ser1_isr(void) interrupt 0x3B;


int main(void)
{
	
	// Initialize serial
	ser_init();
	
	// Initialize RF parameters
	RFCON = RFCON_BYTEMODE;  // enable bytemode (8-bits before interrupt fired)
	
	memset(&incoming_rf_data, 0, sizeof(COMM_PACKET));
	next_incoming_rf_byte = &(uint8_t) incoming_rf_data;
	
	while(1);

}

