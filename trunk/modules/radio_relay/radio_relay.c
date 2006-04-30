/* created on 4/6/2006
* by: Phil Hurwitz (pghurwitz)
* comment: this is the main code for the radio relay module
* data sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/41262A.pdf
*/

#include "shared/p16f685.h"

//#device *=16
//#use rs232(baud=19200, xmit=PIN_B2, rcv=PIN_B1, stream=PC)

//define up-down and open-close bits as registers A3-A0
#define UD1_OUT (0x08)
#define UD2_OUT (0x04)
#define OC1_OUT (0x02)
#define OC2_OUT (0x01)

#define UD_OUTPUT_PORT (PORTC)
#define OC_OUTPUT_PORT (PORTC)

//define up-down and open-close inputs as 0 and 1,2 respectively
#define UD_IN  (0x01)
#define OC1_IN (0x02)
#define OC2_IN (0x04)

#define UD_INPUT_PORT (PORTA)
#define OC_INPUT_PORT (PORTA)

void open(void);
void close(void);
void up(void);
void down(void);
void stopUD(void);
void stopOC(void);
void stopALL(void);
void isr(void);

/*#define OPEN() \
	(output_low(OC1_OUT); output_high(OC2_OUT))
#define CLOSE() \
	(output_low(OC2_OUT); output_high(OC1_OUT))
#define UP() \
	(output_low(UD1_OUT); output_high(UD2_OUT))
#define DOWN() \
	(output_low(UD2_OUT); output_high(UD1_OUT))

#define STOPOC() \
	(output_low(OC2_OUT); output_low(OC1_OUT))
#define STOPUD() \
	(output_low(UD2_OUT); output_low(UD1_OUT))
#define STOPALL() \
	(STOPUD(); STOPOC())
*/

int main(void)
{
	//setup_oscillator(OSC_4MHZ);
	INTCON |= 0xe8;//enable global/tmr0/IOCA interrupts
	//enable_interrupts(GLOBAL & INT_TIMER0 & INT_RA & INT_RA0 & INT_RA1);
	PIE1 |= 0x30;//enable TXIE and RCIE on PIE1 (p.29)
	// Apparently not available on the 16f685
	// RCSTA |= 0x90;//enable serial port and continuous recieve enable bit

	//up-down output bits are TRISC 0 and 1
	//open-close output bits 2 and 3
	TRISC &= 0x0f;
	//set_tris_c(0x0f);
	//up-down input is TRISA 0
	//open-close input is TRISA 1,2
	TRISA &= 0x08;
	//set_tris_a(0x0f);

	//enable interrupt on change A
	IOCA &= 0x08;

	SYNC = 0;//clearing sync
	//assuming 4 mhz
	SPBRG = 2; //19200 baud

	SPEN = 1; //enabling serial port asynchronously (p.146)
	RCIE = 1;//enabling interrupts

	return 0;
}

void down(void)
{
	UD_OUTPUT_PORT &= (~UD1_OUT);  // Sets UD1_OUT to 0
	UD_OUTPUT_PORT |= (UD2_OUT);   // Sets UD2_OUT to 1
}

void up(void)
{
	UD_OUTPUT_PORT |= (UD1_OUT);   // Sets UD1_OUT to 1
	UD_OUTPUT_PORT &= (~UD2_OUT);  // Sets UD2_OUT to 0
}

void open(void)
{
	OC_OUTPUT_PORT &= (~OC1_OUT);  // Sets OC1_OUT to 0
	OC_OUTPUT_PORT |= (OC2_OUT);   // Sets OC2_OUT to 1
}

void close(void)
{
	OC_OUTPUT_PORT |= (OC1_OUT);   // Sets OC1_OUT to 1
	OC_OUTPUT_PORT &= (~OC2_OUT);  // Sets OC2_OUT to 0
}

void stopUD(void)
{
	OC_OUTPUT_PORT &= (~UD1_OUT);  // Sets OC1_OUT to 0
	OC_OUTPUT_PORT &= (~UD2_OUT);  // Sets OC2_OUT to 0
}

void stopOC(void)
{
	OC_OUTPUT_PORT &= (~OC1_OUT);  // Sets OC1_OUT to 0
	OC_OUTPUT_PORT &= (~OC2_OUT);  // Sets OC2_OUT to 0
}

void stopALL(void)
{
	stopUD();
	stopOC();
}

void isr(void)
{
	if ( (OC_INPUT_PORT && (OC1_IN & OC2_IN)) == 1) then stopOC();
	if ( (UD_INPUT_PORT && (UD_IN)) == 1) then stopUD();
	switch (SERIAL0)
	{
		case 0x00:
			up();
		case 0x01:
			down();
		case 0x02:
			open();
		case 0x03:
			close();
		case 0x04:
			stopUD();
		case 0x05:
			stopOC();
		case 0x06:
			stopALL();
		default:
	}
}
