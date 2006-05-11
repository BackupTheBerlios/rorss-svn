int main(void)
{
	;setup_oscillator(OSC_4MHZ);
	INTCON |= 0xe8;;enable global/tmr0/IOCA interrupts
	;enable_interrupts(GLOBAL & INT_TIMER0 & INT_RA & INT_RA0 & INT_RA1);
	PIE1 |= 0x30;;enable TXIE and RCIE on PIE1 (p.29)
	; Apparently not available on the 16f685
	; RCSTA |= 0x90;;enable serial port and continuous recieve enable bit

	;up-down output bits are TRISC 0 and 1
	;open-close output bits 2 and 3
	TRISC &= 0x0f; ;001111
	;set_tris_c(0x0f);
	;up-down input is TRISA 0
	;open-close input is TRISA 1,2
	TRISA &= 0x08; ;001000
	;set_tris_a(0x0f);

	;enable interrupt on change A
	IOCA &= 0x08;

	SYNC = 0;clearing sync
	;assuming 4 mhz
	SPBRG = 2; ;19200 baud

	SPEN = 1; ;enabling serial port asynchronously (p.146)
	RCIE = 1;;enabling interrupts

	return 0;
}

MAIN:	MOVLW 11101000
		MOVWF 11
		MOVLW 00110000
		MOVWF 0001100
		MOVLW 01000000
		MOVWF
		MOVLW 000111
		MOVWF
		MOVLW 12
		MOVWF
		MOVLW 10011000
		MOVWF 
		MOVLW 00100100
		MOVWF 0011000

TRISC	0087	01000000
TRISA	0085	000111
SPBRG	0099	12

RCSTA	0018	10011000
TXSTA	0098	00100100


MYISR:	BTFSC 5, 2
		GOTO IF1
		BTFSC 5, 1
		GOTO IF1
		BCF 7, 1 ; Sets OC1_OUT to 0
		BCF 7, 0 ; Sets OC2_OUT to 0
IF1:	BTFSC 5, 0
		GOTO IF2
		BCF 7, 3 ; Sets UD1_OUT to 0
		BCF 7, 2 ; Sets UD2_OUT to 0
IF2:
;Switch statement equivalent- used for serial ISR
		BTFSS 26, 0
		GOTO CASE0
		BTFSS 26, 1
		GOTO CASE1
		BTFSS 26, 2
		GOTO CASE2
		BTFSS 26, 3
		GOTO CASE3
		BTFSS 26, 4
		GOTO CASE4
		BTFSS 26, 5
		GOTO CASE5
		BTFSS 26, 6
		GOTO CASE6
		GOTO ENDISR
CASE0:		BSF 7, 3 ; Sets UD1_OUT to 1
			BCF 7, 2 ; Sets UD2_OUT to 0
			GOTO ENDISR
CASE1:		BSF 7, 2 ; Sets UD2_OUT to 1
			BCF 7, 3 ; Sets UD1_OUT to 0
			GOTO ENDISR
CASE2:		BSF 7, 1 ; Sets OC2_OUT to 1
			BCF 7, 0 ; Sets OC1_OUT to 0
			GOTO ENDISR
CASE3:		BSF 7, 0 ; Sets OC1_OUT to 1
			BCF 7, 1 ; Sets OC2_OUT to 0
			GOTO ENDISR
CASE4:		BCF 7, 3 ; Sets UD1_OUT to 0
			BCF 7, 2 ; Sets UD2_OUT to 0
			GOTO ENDISR
CASE5:		BCF 7, 1 ; Sets OC1_OUT to 0
			BCF 7, 0 ; Sets OC2_OUT to 0
			GOTO ENDISR
CASE6:		BCF 7, 0 ; Sets OC1_OUT to 0
			BCF 7, 1 ; Sets OC2_OUT to 0
			BCF 7, 2 ; Sets UD1_OUT to 0
			BCF 7, 3 ; Sets UD2_OUT to 0
ENDISR:		RETFIE
