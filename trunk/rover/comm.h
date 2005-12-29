/*
*  $Id$
*  comm.h - communication header module thingie
*  Created: 29 Sep 2005
*/

#ifndef COMM_H
#define COMM_H

#include "loc.h"

// Function prototypes
void send_rf_data(uint8_t *, uint8_t *);
void send_serial_data(bit, uint8_t *, uint8_t *);

// Macros
// Disable all interrupts (except flash/debug)
#define BEGIN_CRITICAL_SECTION() \
	(IE &= 0x7F)

// Enable all interrupts
#define END_CRITICAL_SECTION() \
	(IE |= 0x80)

//IE (0xa8) Interrupt Enable Register
//P 29 of  http://www.chipcon.com/files/CC1010_Data_Sheet_1_3.pdf
#define IE_EA		(0x80)//GLOBAL_INTERRUPT
#define IE_ES1		(0x40)//SERIAL_PORT_1
#define IE_ES0		(0x10)//SERIAL_PORT_0
#define IE_ET1		(0x08)//TIMER_1
#define IE_TX1		(0x04)//EXTERNAL_1
#define IE_ET0		(0x02)//TIMER_0
#define IE_TX0		(0x01)//EXTERNAL_0
//EIE (0xE8) Extended Interrupt Enable Register
#define EIE_RTCIE	(0x10)//REALTIME_CLOCK
#define EIE_ET3		(0x08)//TIMER_3
#define EIE_ADIE	(0x04)//ADC_DES
#define EIE_ET2		(0x02)//TIMER_2
#define EIE_RFIE	(0x01)//RF_INTERRUPT
//EXIF (0x91) Exted interrupt Flag
#define EXIF_TF3	(0x80)//Timer 3 interrupt flag
#define EXIF_ADIF	(0x40)//ADC/DES interrupt Flag
#define EXIF_TF2	(0x20)//Timer 2 interrupt flag
#define EXIF_RFIF	(0x10)//RF Transmit/receive interrupt flag


/* RF Control */
// RFMAIN (0xC8) RF Main Control Register
#define RFMAIN_RXTX	(0x80) // RX/TX Switch - 0: RX, 1: TX
#define RFMAIN_F_REG	(0x40) // 0: Select freq registers A, 1: B
#define RFMAIN_RX_PD	(0x20) // Power down for LNA, mixer, IF, digital demod
#define RFMAIN_TX_PD	(0x10) // Power down of digital modem and PA
#define RFMAIN_FS_PD	(0x08) // Power down of freq synthesizer
#define RFMAIN_CORE_PD	(0x04) // Power down of main crystal oscillator core
#define RFMAIN_BIAS_PD	(0x02) // Power down of bias current generator and xtal oscillator buffer

// RFCON (0xC2) RF Control Register
#define RFCON_MVIOL	(0x10) // Manchester code violation status
#define RFCON_MLIMIT	(0x0E) // Clk regen logic limit (Manchester mode)
#define RFCON_BYTEMODE	(0x01) // Select bitmode (0) or bytemode (1)

// CKCON (0x8E) Timer Clock Rate Control Register
#define CKCON_T1M	(0x10)
#define CKCON_T0M	(0x08)
#define CKCON_MD	(0x07)

// MODEM0 (0xDB) Modem Control Register 0
#define MODEM0_BAUDRATE			(0xE0)
	#define MODEM0_0_6K		(0x00)
	#define MODEM0_1_2K		(0x01)
	#define MODEM0_2_4K		(0x02)
	#define MODEM0_4_8K		(0x03)
	#define MODEM0_9_6K		(0x04)
	#define MODEM0_19_2K		(0x05)
#define MODEM0_DATA_FMT			(0x18)
	#define MODEM0_NRZ		(0x00)
	#define MODEM0_MANCHESTER	(0x01)
	#define MODEM0_TRANSPARENT	(0x02)
	#define MODEM0_UART		(0x03)
#define MODEM0_XOSC_FREQ		(0x07)

// MODEM1 (0xDA) Modem Control Register 1

// MODEM2 (0xD9) Modem Control Register 2

// PDET (0xD3) Preamble Detection Control Register
#define PDET_PEN	(0x80) // Preamble and byte sync enable
#define PDET_PLEN	(0x7F) // Preamble length

// BSYNC (0xD4) Byte Synchronisation Register
#define SYNC_BYTE	(0xA5) // The synchronisation byte

// SCON - Serial Control Registers
#define SCON_SM0	(0x80) // Mode bits
#define SCON_SM1	(0x40)
#define SCON_SM2	(0x20) // Multiprocessor comm enable
#define SCON_REN	(0x10) // Receive enable (1)
#define SCON_TB8	(0x08) // Defines state of 9th bit transmitted in modes 2 & 3
#define SCON_RB8	(0x04) // Indicates state of 9th bit received
#define SCON_TI		(0x02) // Transmit interrupt flag
#define SCON_RI		(0x01) // Receive interrupt flag

//WDT (0xD2) Watchdog Timer Control (P63)
#define WDT_SE		(0x10)
#define WDT_EN		(0x08)
#define WDT_CLR		(0x04)
#define WDT_PRE1	(0x02)
#define WDT_PRE0	(0x01)
//PDET (0xD3) Preamble Detection Control
#define PDET_PEN	(0x80)
#define PDET_PRE0	(0xEF)//bits 0-6

/***************************************
 * Communications protocol
 ***************************************
 */


// Flags in each communication packet
#define DIRECTION	(0x01)
	#define DIR_FORWARD	0
	#define DIR_REVERSE	1

/*
 *  Standard packet for transmitting data
 *  across a link (serial, RF, etc)
 */ 
struct comm_protocol
{
	int8_t 	start_code;	// Constant start byte
	uint8_t	device;		// Device type
	uint8_t	magnitude;	// Device-dependant (i.e. speed of a motor)
	int8_t 	flags;		// 
	int8_t 	checksum;	// 7-bit checksum & 1-bit checksum parity bit
	int8_t 	end_code;	// Constant end byte
};

typedef struct comm_protocol	COMM_PACKET;

/*
 *  Pointers to keep track of where 
 *  we are when sending data serially
 */
struct transmitting_serial_data
{
	uint8_t start;
	uint8_t *end;
	uint8_t *current;
};

typedef struct transmitting_serial_data	TRANSMITTING_SERIAL_DATA;

/*
 ****************************************
 * Global variables
 ****************************************
 */

#endif
