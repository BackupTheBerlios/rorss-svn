/*
 *
 * $Id$
 * comm.c - Communications functions, including ISRs
 *
 */

#include <sdcc/include/stdint.h>
#include "comm.h"

// RF transmit/receive interrupt
// Interrupt enable: EIE_RFIE
// Interrupt flag:   EXIF_RFIF
void rf_isr(void) interrupt 0x43
{

}

// Serial Port 0 transmit/receive interrupt
// Interrupt enable: IE_ES0
// Transmit:
//  Interrupt flag: SCON0_TI_0
// Receive:
//  Interrupt flag: SCON0_RI_0
void ser0_isr(void) interrupt 0x23
{

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
