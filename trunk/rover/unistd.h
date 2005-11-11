/*
 *
 * $Id$
 * unistd.h - Tastes good with cheese
 *
 */

#include <sdcc/include/stdint.h>

void delay(uint8_t milliseconds) {
	uint8_t loop1, loop2;
	milliseconds;
	_asm
		; save registers
		push a
		push b
	outerloop$:
		; take up ~14741 clock cycles in this loop
		mov _loop1, 15			; 2 cycles
	middleloop$:
		mov _loop2, 244			; 2 cycles
	innerloop$:
		djnz _loop2, innerloop$		; 4 cycles
		djnz _loop1, middleloop$	; 4 cycles
		djnz _milliseconds, outerloop$	; 4 cycles
	finish$:
		; restore registers
		pop b
		pop a
		; return from function
		ret
	_endasm;
}

