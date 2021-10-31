/*******************************************************************************
 * File name: MC2.c
 * Description: Source file for door locker security system
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "buzzer.h"
#include "util\delay.h"
#include "DC_motor.h"

#define F_CPU 8000000UL

int main(void){
	BUZZER_init();
	DcMotor_Init();

	BUZZER_ON();
	_delay_ms(1000);
	BUZZER_OFF();

	DcMotor_Rotate(CW,DUTY_CYCLE_75);

	Timer1_setCallBack(BUZZER_OFF);
	while(1){

	}
}
