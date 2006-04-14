/* created on 4/6/2006
* by: Phil Hurwitz (pghurwitz)
* comment: this is the main code for the radio relay module
* data sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/41262A.pdf
*/

#include //something really important

//define up-down and open-close bits as registers A3-A0
#define UD1 (RA3)
#define UD2 (RA2)
#define OC1 (RA1)
#define OC2 (RA0)

void open(void);
void close(void);
void up(void);
void down(void);
void stopUD(void);
void stopOC(void);
void stopALL(void);

int main(void)
{
	INTCON |= 0xe8;//enable global/tmr0/IOCA interrupts
	PIE1 |= 0x30;//enable TXIE and RCIE on PIE1 (p.29)
	RCSTA |= 0x90;//enable serial port and continuous recieve enable bit

	//up-down output bits are TRISC 0 and 1
	//open-close output bits 2 and 3
	TRISC &= 0x0f;
	//up-down input is TRISA 0
	//open-close input is TRISA 1
	TRISA &= 0x03;

	//enable interrupt on change A
	IOCA &= 0x03;

	SYNC = 0;//clearing sync
	//assuming 4 mhz
	SPBRG = 2; //19200 baud

	SPEN = 1; //enabling serial port asynchronously (p.146)
	RCIE = 1;//enabling interrupts

	return 0;
}

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