/*
 *	$Id
 *	ftable header which defines the function table lookups
 */
#include <sdcc/include/stdint.h>
#include <sdcc/include/stdbool.h>
#include "shared/ftabledefines.h"

//function pointer types for different modes
typedef bool (*fpRover)(uint8_t flags);
typedef uint8_t (*fpModule)(uint8_t flags);

bool rvModeRover;//global which holds the mode for the rover
				//when rvModeRover = true then call GetRoverFunction
				//when false call GetModuleFunction

//call this to handle incoming rf byte
void HandleIncoming(uint8_t *);//call this to handle incoming rf data on rover

//these should not be called directly, but should be called from the HandleIncoming Function
fpRover *GetRoverFunction(uint8_t incoming_byte, uint8_t *flags);
fpModule *GetModuleFunction(uint8_t incoming_byte, uint8_t *flags);

//all of the functions have to be defined below....
extern bool ftable_RoverMoveF(uint8_t); //forward movement with 5 bits for speed
extern bool ftable_RoverMoveB(uint8_t); //backward movement with 5 bits for speed
extern bool ftable_RoverMoveRL(uint8_t); //this allows the right wheels to spin faster or slower then the left wheel by the magnitude defined with the 5 bits
extern bool ftable_RoverMoveLR(uint8_t); //this allows the left wheels to spin faster or slower then the right wheel by the magnitude defined with the 5 bits
extern bool ftable_RoverStop(uint8_t); //stop the rover

extern bool ftable_RoverBlink(uint8_t);//blink an LED (testing)
