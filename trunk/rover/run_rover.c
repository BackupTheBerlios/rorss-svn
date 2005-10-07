/*
 * $Id$
 * run_rover.c - The main program for the rover
 * Created: 6 Oct 2005
 */

#include <sdcc/include/stdint.h>
#include <sdcc/include/ser_ir.h>
#include "comm.h"

// Function prototypes for ISRs
void rf_isr(void) interrupt 0x43;
void ser0_isr(void) interrupt 0x23;
void ser1_isr(void) interrupt 0x3B;


int main(void)
{
	
	// Initialize serial
	ser_init(void);
	while(1);

}

