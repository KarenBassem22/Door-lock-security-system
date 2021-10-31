/*******************************************************************************
 * File name: buzzer.c
 * Description: Source file for buzzer
 * Module: buzzer
 * Author: Karen Bassem
 ******************************************************************************/
#include "buzzer.h"

void BUZZER_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);  /* set the buzzer pin as output pin */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);            /* Initialize the buzzer with zero */
}

void BUZZER_ON(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);           /* turn on buzzer */
}

void BUZZER_OFF(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);            /* turn off buzzer */
}
