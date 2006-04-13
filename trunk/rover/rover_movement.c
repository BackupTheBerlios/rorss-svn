/*
 *
 * $Id
 * this file contains the movement functions for the rover
 *
 */
#include "ftable.h"
#include "unistd.h"

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

bool ftable_RoverMoveB(uint8_t speed_mag)
{
	LMOTOR_IN1 = 0;
	LMOTOR_IN2 = 1;
	RMOTOR_IN1 = 0;
	RMOTOR_IN2 = 1;

	LMOTOR_DC = speed_mag<<3;
	RMOTOR_DC = speed_mag<<3;
}//backward movement with 5 bits for speed

bool ftable_RoverMoveRL(uint8_t speed_mag)
{
	//move the right wheel by speed_mag
	LMOTOR_IN1 = 0;
	LMOTOR_IN2 = 0;
	RMOTOR_IN1 = 1;
	RMOTOR_IN2 = 0;

	LMOTOR_DC = 0;
	RMOTOR_DC = speed_mag<<3;
}//this allows the right wheels to spin faster or slower then the left wheel by the magnitude defined with the 5 bits

bool ftable_RoverMoveLR(uint8_t speed_mag)
{
	LMOTOR_IN1 = 1;
	LMOTOR_IN2 = 0;
	RMOTOR_IN1 = 0;
	RMOTOR_IN2 = 0;

	LMOTOR_DC = speed_mag<<3;
	RMOTOR_DC = 0;
}//this allows the left wheels to spin faster or slower then the right wheel by the magnitude defined with the 5 bits


bool ftable_RoverStop(uint8_t not_used)
{
	LMOTOR_IN1 = 0;
	LMOTOR_IN2 = 0;
	RMOTOR_IN1 = 0;
	RMOTOR_IN2 = 0;

	LMOTOR_DC = 0;
	RMOTOR_DC = 0;
}

bool ftable_RoverBlink(uint8_t not_used)
{
	BLED = LED_ON;
	sleep(250);// 250ms is a normal blink rate
	BLED = LED_OFF;
	sleep(250);
	RLED = LED_ON;
	sleep(250);
	RLED = LED_OFF;
	sleep(250);
	GLED = LED_ON;//keep green LED on
}//blink and LED