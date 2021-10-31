/*******************************************************************************
 * File name: MC1.c
 * Description: Source file for door locker security system
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "MC1.h"
#define F_CPU 8000000UL

int main(void){
LCD_init();
LCD_displayString("FINALLY! ");
LCD_integerToString(KEYPAD_getPressedKey());
	while(1){


	}

}
