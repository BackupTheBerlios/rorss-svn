/*
 * $Id$
 * loc.h - Specifies locations of variables in memory
 *
 */

#include <sdcc/include/stdint.h>

uint8_t at 0xA8 IE;

//More info on P 50 of CC1010 Data Sheet
uint8_t at 0x80 P0;// only bits 0-3 used
uint8_t at 0x90 P1;
uint8_t at 0xA0 P2;
uint8_t at 0xB0 P3;//only bits 0-5 used

uint8_t at 0xa4 P0DIR;
uint8_t at 0xa5 P1DIR;
uint8_t at 0xa6 P2DIR;
uint8_t at 0xa7 P3DIR;