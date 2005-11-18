/*
 *
 * $Id$
 * pwm.c - Controls the I/O Pins using PWM
 *
 */

#define		PERIOD		255

#define		PWM_OUT_0	0x01
#define		PWM_OUT_1	0x02
#define		PWM_OUT_2	0x04
#define		PWM_OUT_3	0x08

uint8_t		period_counter = 0;
uint8_t		duty_cycle[4];		// make these separate variables?

void update_PWM_status() {
	period_counter++;
	

}
