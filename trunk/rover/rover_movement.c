/*
 *
 * $Id
 * this file contains the movement functions for the rover
 *
 */
#include "ftable.h"

bool ftable_RoverMoveF(uint8_t speed_mag)
{
	//go forward on left and right sides
	LMOTOR_IN1 = 1;
	LMOTOR_IN2 = 0;
	RMOTOR_IN1 = 1;
	RMOTOR_IN2 = 0;

	LMOTOR_DC = speed_mag<<3;
	RMOTOR_DC = speed_mag<<3;
}//move the rover forward
