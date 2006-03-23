/*
 *	$Id
 *	ftable header which defines the function table lookups
 */
#include "../shared/ftabledefines.h"

//function pointer types for different modes
typedef bool (*fpRover)(uint8_t flags);
typedef uint8_t &(*fpModule)(uint8_t flags);

bool rvModeRover;//global which holds the mode for the rover
				//when rvModeRover = true then call GetRoverFunction
				//when false call GetModuleFunction

//call this to handle incoming rf byte
void HandleIncoming(const uint8_t &rf_byte);//call this to handle incoming rf data on rover

//these should not be called directly, but should be called from the HandleIncoming Function
fpRover *GetRoverFunction(const uint8_t incoming_byte, uint8_t &flags);
fpModule *GetModuleFunction(const uint8_t incoming_byte, uint8_t &flags);

//all of the functions have to be defined below....
extern bool ftable_RoverMoveF(uint8_t flags); //forward movement with 5 bits for speed
extern bool ftable_RoverMoveB(uint8_t flags); //backward movement with 5 bits for speed
extern bool ftable_RoverMoveRL(uint8_t flags); //this allows the right wheels to spin faster or slower then the left wheel by the magnitude defined with the 5 bits
extern bool ftable_RoverMoveLR(uint8_t flags); //this allows the left wheels to spin faster or slower then the right wheel by the magnitude defined with the 5 bits
extern bool ftable_RoverSpin(uint8_t flags); //spin the rover in circles (for testing?)