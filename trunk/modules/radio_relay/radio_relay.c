/* created on 4/6/2006
* by: Phil Hurwitz (pghurwitz)
* comment: this is the main code for the radio relay module
* data sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/41262A.pdf
*/

#include "shared/p16f685.h"

//#device *=16
//#use rs232(baud=19200, xmit=PIN_B2, rcv=PIN_B1, stream=PC)

//define up-down and open-close bits as registers A3-A0
#define UD1 (PIN_A3)
#define UD2 (PIN_A2)
#define OC1 (PIN_A1)
#define OC2 (PIN_A0)
/*
void open(void);
void close(void);
void up(void);
void down(void);
void stopUD(void);
void stopOC(void);
void stopALL(void);
*/

#define OPEN() \
	(output_low(OC1); output_high(OC2))
#define CLOSE() \
	(output_low(OC2); output_high(OC1))
#define UP() \
	(output_low(UD1); output_high(UD2))
#define DOWN() \
	(output_low(UD2); output_high(UD1))

#define STOPOC() \
	(output_low(OC2); output_low(OC1))
#define STOPUD() \
	(output_low(UD2); output_low(UD1))
#define STOPALL() \
	(STOPUD(); STOPOC())


int main(void)
{
	//setup_oscillator(OSC_4MHZ);
	INTCON |= 0xe8;//enable global/tmr0/IOCA interrupts
	//enable_interrupts(GLOBAL & INT_TIMER0 & INT_RA & INT_RA0 & INT_RA1);
	PIE1 |= 0x30;//enable TXIE and RCIE on PIE1 (p.29)
	RCSTA |= 0x90;//enable serial port and continuous recieve enable bit

	//up-down output bits are TRISC 0 and 1
	//open-close output bits 2 and 3
	TRISC &= 0x0f;
	//set_tris_c(0x0f);
	//up-down input is TRISA 0
	//open-close input is TRISA 1
	TRISA &= 0x03;
	//set_tris_a(0x0f);

	//enable interrupt on change A
	IOCA &= 0x03;

	SYNC = 0;//clearing sync
	//assuming 4 mhz
	SPBRG = 2; //19200 baud

	SPEN = 1; //enabling serial port asynchronously (p.146)
	RCIE = 1;//enabling interrupts

	return 0;
}
/*
void down(void)
{
	UD1 = 0;
	UD2 = 1;
}

void up(void)
{
	UD1 = 1;
	UD2 = 0;
}

void open(void)
{
	OC1 = 0;
	OC2 = 1;
}

void close(void)
{
	OC1 = 1;
	OC2 = 0;
}

void stopUD(void)
{
	UD1 = 0;
	UD2 = 0;
}

void stopOC(void)
{
	OC1 = 0;
	OC2 = 0;
}

void stopALL(void)
{
	UD1 = 0;
	UD2 = 0;
	OC1 = 0;
	OC2 = 0;
}
*/
