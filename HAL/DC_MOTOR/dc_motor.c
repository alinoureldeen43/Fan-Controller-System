/*
 * dc_motor.c
 *
 *  Created on: Apr 7, 2023
 *      Author: Ali Hassan
 */

#include "dc_motor.h"

#include "../../MCAL/GPIO/gpio_a.h"
#include "../../MCAL/PWM/pwm.h"

void DcMotor_init()
{
	GPIO_setupPinDirection(DC_PORT_ID,DC_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT_ID,DC_PIN2_ID,PIN_OUTPUT);

	GPIO_writePin(DC_PORT_ID, DC_PIN1_ID,LOGIC_LOW);
	GPIO_writePin(DC_PORT_ID, DC_PIN2_ID,LOGIC_LOW);
}
void DcMotor_Rotate(Rotate_type state,uint8 speed)
{
	uint8 res;

	res=(uint8)((float)(speed*255/100));

	if(state==stop)
	{
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID,LOGIC_LOW);
		PWM_TIMER0_start(0);
	}
	else if(state==clockwise)
	{
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID,LOGIC_HIGH);
		PWM_TIMER0_start(res);
	}
	else if(state==anti_clockwise)
	{
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID,LOGIC_HIGH);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID,LOGIC_LOW);
		PWM_TIMER0_start(res);
	}

}

