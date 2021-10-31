/*************************************************************************************************************
 * Author: Karen Bassem
 * File Name: DC_motor.c
 * Description: source file for DC motor
 * Module: DC motor
 ************************************************************************************************************/
#include "DC_motor.h"

/* Function to setup the direction for the two motor pins and Stop at the DC-Motor at the beginning */
void DcMotor_Init(void){
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT2_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT1_PIN,PIN_OUTPUT);
	/* STOP the MOTOR at the beginning */
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT2_PIN,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT1_PIN,LOGIC_LOW);
}

/* rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value */
/* Send the required duty cycle to the PWM driver based on the required speed value */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	PWM_Timer0_Start(speed);

	if(state==A_CW){
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT2_PIN,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT1_PIN,LOGIC_HIGH);
	}
	else if(state==CW){
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT2_PIN,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT1_PIN,LOGIC_LOW);
	}
	else{
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT2_PIN,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_INPUT1_PIN,LOGIC_LOW);
	}

}

