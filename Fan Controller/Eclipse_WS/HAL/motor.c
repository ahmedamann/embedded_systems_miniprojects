/*
 *  File: motor.c
 *
 *  Created on: Jun 6, 2024
 *  Author: Ahmed Aman
 */

#include "motor.h"

void DCMOTOR_Init(void)
{
	/* Setup Direction for IN1 and IN2 to be Output pins */
	GPIO_setupPinDirection(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,PIN_OUTPUT);

	/* Stop the Motor initially */
	GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
}



/*Setup the direction of rotation of the motor*/
void DCMOTOR_Rotate(MOTOR_STATE state, uint8 speed)
{
	switch(state)
	{
		case STOP:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_HIGH);
			break;
		case ACW:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
			break;
	}
	PWM_Timer0_Start(speed);
}
