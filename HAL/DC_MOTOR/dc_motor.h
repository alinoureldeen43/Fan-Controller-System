/*
 * dc_motor.h
 *
 *  Created on: Apr 7, 2023
 *      Author: Ali Hassan
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_H_
#define HAL_DC_MOTOR_DC_MOTOR_H_

#include "../../LIBRARIES/std_types.h"

#define DC_PORT_ID		PORTB_ID

#define DC_PIN1_ID		PIN0_ID
#define DC_PIN2_ID		PIN1_ID

typedef enum{
	stop,clockwise,anti_clockwise,
}Rotate_type;

void DcMotor_CallBack(const void(*ptr)(uint8));
void DcMotor_init();
void DcMotor_Rotate(Rotate_type state,uint8 speed);

#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
