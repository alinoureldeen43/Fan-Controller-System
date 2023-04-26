/*
 * pwm.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Hassan
 */

#include "pwm.h"

#include<avr/io.h>
#include "../GPIO/gpio_a.h"

void PWM_TIMER0_start(uint8 value)
{
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
	TCNT0=0;
	OCR0=value;
}
