/*
 *
 * $Id$
 * gloves.c - Gloves functions
 *
 */
#include <sdcc/include/stdbool.h>
#include <sdcc/include/stdint.h>
#include "gloves.h"

uint8_t do_hash()
{
	uint8_t final;

	final= r_thumb + r_index + r_middle + r_ring + r_little + pitch + roll;

	return final;
}