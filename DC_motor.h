/*************************************************************************************************************
 * Author: Karen Bassem
 * File Name: DC_motor.h
 * Description: header file for DC motor
 * Module: DC motor
 ************************************************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "PWM.h"
#include "gpio.h"

/* motor states */
typedef enum {
	STOP,CW,A_CW
}DcMotor_State;

/* motor pins */
#define DC_MOTOR_INPUT1_PIN PIN0_ID
#define DC_MOTOR_INPUT2_PIN PIN1_ID
#define DC_MOTOR_PORT_ID PORTB_ID

/* function prototypes */
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
