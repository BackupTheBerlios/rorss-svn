/*
 *
 *	$Id
 *	All the shared defines between the astronaut and rover
 *
 */

//defines for function table
#define MODE_MODULE false
#define MODE_ROVER true
#define MODE_SWITCH_ROVER 0xFF
#define MODE_SWITCH_MODULE 0xFE

//this defines what to look at to determine function to call, the rest of the bits will be used for flags
#define FTABLE_FUNC_MASK 0b11100000

//use this to define what the upper 3 bits should look like
//ie - bytes_to_send = ROVER_MOVEF & flags, assuming 5 bits for flags 
#define ROVER_MOVEF		0b00000000
#define ROVER_MOVEB		0b00100000
#define ROVER_MOVERL	      0b01000000
#define ROVER_MOVELR	      0b01100000
#define ROVER_SPIN		0b10000000