/*
 *	$Id
 *	ftable code which defines the function table lookups
 */
#include <sdcc/include/stdint.h>
#include <sdcc/include/stdbool.h>
#include "ftable.h"

//call this to handle incoming rf byte
void HandleIncoming(uint8_t *rf_byte)
{
	if(rf_byte == MODE_SWITCH_ROVER)
		rvModeRover = MODE_ROVER;	//put an LED on a pin to determine which mode?
	else if(rf_byte == MODE_SWITCH_MODULE)
		rvModeRover = MODE_MODULE;
	else
	{
		int flags;
		if(rvModeRover == MODE_ROVER)
		{
			fpRover *func = GetRoverFunction(rf_byte, &flags);
			if(func)
				(*func)(flags);
		}
		else if(rvModeRover == MODE_MODULE)
		{
			fpModule *func = GetModuleFunction(rf_byte, &flags);
			if(func)
				(*func)(flags);
		}
	}//call function from recieved byte

}//call this to handle incoming rf data on rover

//these should not be called directly, but should be called from the HandleIncoming Function
fpRover *GetRoverFunction(uint8_t incoming_byte, uint8_t *flags)
{
	//get first 3 bits seperate
	uint8_t compare_byte = (incoming_byte & FTABLE_FUNC_MASK);//mask out bottom bytes

	flags = incoming_byte & ~FTABLE_FUNC_MASK;
	fpRover *func = 0;

	switch(compare_byte)
	{
	case ROVER_MOVEF:
		func = &ftable_RoverMoveF;
		break;
	case ROVER_MOVEB:
		func = &ftable_RoverMoveB;
		break;
	case ROVER_MOVERL:
		func = &ftable_RoverMoveRL;
		break;
	case ROVER_MOVELR:
		func = &ftable_RoverMoveLR;
		break;
	case ROVER_SPIN:
		func = &ftable_RoverSpin;
		break;
	default:
		func = 0;
		break;
	}

	return func;
}//return function pointer to function to call

fpModule *GetModuleFunction(uint8_t incoming_byte, uint8_t *flags)
{
	return 0;//fill this in later.....
}//return function pointer to function
