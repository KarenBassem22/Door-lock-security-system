/*************************************************************************************************************
 * Author: Karen Bassem Thabet
 * File Name: PWM.c
 * Description: source file for PWM
 * Date: 5/10/2021
 ************************************************************************************************************/

#include "PWM.h"

/* trigger the Timer0 with the PWM Mode ,the compare value based on the required input duty cycle */
void PWM_Timer0_Start(uint8 duty_cycle){
	/*SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,CS01);*/
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01);    /* prescaler Fcpu/8 ,non inverting mode , FAST PWM mode*/
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT); /* OC0 is set as an output pin */
	TCNT0 = 0;              /* Set Timer Initial Value to 0 */
	OCR0=duty_cycle;        /* set compare value given */
}
