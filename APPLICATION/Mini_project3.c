/*
 * 	Mini_project3.c
 *
 *	Application code to control a fan based on temperature
 *
 *  Created on: Apr 7, 2023
 *      Author: Ali Hassan
 */

/*include avr libraries to use interrupt and interrupt registers*/
#include<avr/interrupt.h>
#include<avr/io.h>

/*include microcontroller abstraction layers which are GPIO,PWM & ADC drivers*/
#include "../MCAL/ADC/adc_a.h"
#include "../MCAL/GPIO/gpio_a.h"
#include "../MCAL/PWM/pwm.h"

/*include hardware abstraction layers which are LCD,SENSOR & DC MOTOR drivers*/
#include "../HAL/DC_MOTOR/dc_motor.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LM_SENSOR/lm35_sensor.h"



int main()
{
	/*variable from type struct to configure adc driver */
	ADC_ConfigType adc;

	/*variable to store temperature value */
	uint8 temp;

	/*variable to check temperature every time in looping
	 * initialized with negative value because temperature value is positive */
	sint16 prev=-1;

	/*Calling LCD initialization function */
	LCD_init();

	/*Calling motor initialization function */
	DcMotor_init();

	/*Configure adc prescaler and voltage and pass the address of configure
	 * struct to adc initialization funztion */
	adc.prescaler=prescaler8;
	adc.reference=internal;
	ADC_init(&adc);

	/*Enable global interrupt flag */
	SREG |= (1<<7);

	LCD_displayStringRowColumn(0,4,"FAN IS ");
	LCD_displayStringRowColumn(1,4,"TEMP =     C");

	/*infinity loop for application */
	while(1)
	{
		 /*read the value of temperature by calling sensor function */
		temp=LM35_getTemperature();

		/*check the value of temperature is changed or not to avoid unnecessary code action*/
		if(temp!=prev)
		{
			/*check if temperature below 30 C
			 * 1-write state of the fan which is 'OFF' in it's position
			 * 2-Move cursor to the position where display temperature
			 * 3-display temperature
			 * 4-turn the fan off
			 * */
			if(temp<30)
			{
				LCD_displayStringRowColumn(0,11,"OFF");
				LCD_moveCursor(1,11);
				LCD_integrToString(temp);

				DcMotor_Rotate(stop,0);
			}
			/*check if temperature between 30 C & 59 C
			 * 1-write state of the fan which is 'ON' in it's position
			 * 2-Move cursor to the position where display temperature
			 * 3-display temperature
			 * 4-turn the fan on with 25% of its speed
			 * */
			else if(temp>=30 && temp <60)
			{
				LCD_displayStringRowColumn(0,11,"ON ");
				LCD_moveCursor(1,11);
				LCD_integrToString(temp);

				DcMotor_Rotate(clockwise,25);
			}
			/*check if temperature between 60 C & 89 C
			 * 1-write state of the fan which is 'ON' in it's position
			 * 2-Move cursor to the position where display temperature
			 * 3-display temperature
			 * 4-turn the fan on with 50% of its speed
			 * */
			else if(temp>=60 && temp <90)
			{
				LCD_displayStringRowColumn(0,11,"ON ");
				LCD_moveCursor(1,11);
				LCD_integrToString(temp);

				DcMotor_Rotate(clockwise,50);
			}
			/*check if temperature between 90 C & 119 C
			 * 1-write state of the fan which is 'ON' in it's position
			 * 2-Move cursor to the position where display temperature
			 * 3-display temperature
			 * 4-handle any extra character on the screen
			 * 5-turn the fan on with 75% of its speed
			 * */
			else if(temp>=90 && temp <120)
			{
				LCD_displayStringRowColumn(0,11,"ON ");
				LCD_moveCursor(1,11);
				LCD_integrToString(temp);
				if(temp<100)
				{
					LCD_displayCharacters(' ');
				}

				DcMotor_Rotate(clockwise,75);
			}
			/*check if temperature bigger than or equal 120 C
			 * 1-write state of the fan which is 'ON' in it's position
			 * 2-Move cursor to the position where display temperature
			 * 3-display temperature
			 * 4-turn the fan on with 100% of its speed
			 * */
			else if(temp>=120)
			{
				LCD_displayStringRowColumn(0,11,"ON ");
				LCD_moveCursor(1,11);
				LCD_integrToString(temp);

				DcMotor_Rotate(clockwise,100);
			}
			/*Give the value of current temperature to this variable to check if temperature is changed */
			prev=temp;
		}
	}
}
