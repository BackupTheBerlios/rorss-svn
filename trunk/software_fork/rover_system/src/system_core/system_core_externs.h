/*
Filename: system_core_externs.h

Project:  PSU Mars Society Rover Project

Description:

	Header file which must be included in each module of the rover software project. All variables which need to be accessable via other modules must be set as extern in this file.
	
*/

#ifndef _system_core_externs
#define _system_core_externs

#include "../gloves/glove_externs.h"

#include "../trainer/src/trainer_app.h"
#include "../micro_controller_comm/micro_controller_comm_externs.h"
#include "../command/neural_network/neural_network_externs.h"
//#include "../command/src/interpreter_externs.h"


extern char *Device_Port1;
extern char *Device_Port2;

#endif

