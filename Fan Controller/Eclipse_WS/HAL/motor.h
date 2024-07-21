/*
 *  File: motor.h
 *
 *  Created on: Jun 6, 2024
 *  Author: Ahmed Aman
 */

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_

#include "../MCAL/gpio.h"
#include "../MCAL/pwm.h"
#include "../LIB/std_types.h"

/*DC Motor HW pins and ports*/
#define DC_MOTOR_H_BRIDGE_IN1_PORT     PORTB_ID
#define DC_MOTOR_H_BRIDGE_IN2_PORT     PORTB_ID

#define DC_MOTOR_H_BRIDGE_IN1_PIN      PIN0_ID
#define DC_MOTOR_H_BRIDGE_IN2_PIN      PIN1_ID

/*Types Declarations*/
typedef enum
{
	STOP,CW,ACW
}MOTOR_STATE;

/*Functions Prototype*/

/*Initialization of the DC Motor*/
void DCMOTOR_Init(void);

/*Setup the direction of rotation of the motor*/
void DCMOTOR_Rotate(MOTOR_STATE state,uint8 speed);

#endif /* HAL_MOTOR_H_ */
