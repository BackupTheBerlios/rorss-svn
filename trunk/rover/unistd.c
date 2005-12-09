/*
 *
 * $Id$
 * unistd.c - Tastes good with cheese
 *
 */

#include <sdcc/include/stdint.h>

void sleep(uint8_t milliseconds)
{

	milliseconds;
	_asm
		; get milliseconds into r2
		mov	r2, dpl
	outerloop$:
		; take up ~14741 clock cycles in this loop
		mov r0, #15		; 2 cycles
	middleloop$:
		mov r1, #244		; 2 cycles
	innerloop$:
		djnz r1, innerloop$	; 4 cycles
		djnz r0, middleloop$	; 4 cycles
		djnz r2, outerloop$	; 4 cycles
	finish$:
		; return from function
		ret
	_endasm;

}

