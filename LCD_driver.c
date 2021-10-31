/*******************************************************************************
 * File name: LCD_driver.c
 * Description: Source file for LCD
 * Module: LCD
 * Author: Karen Bassem
 ******************************************************************************/
#include "LCD_driver.h"

/* LCD initialization function */
void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT,LCD_RS_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT,LCD_RW_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT,LCD_E_PIN,PIN_OUTPUT);

	GPIO_setupPortDirection(LCD_DATA_PORT,PORT_OUTPUT);

	LCD_sendCommand(TWO_LINES_8_BITS); /* 2-lines, 8-bits mode */
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_SCREEN);
}

/* function to send commands to LCD */
void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LOGIC_LOW); /* select command register */
	GPIO_writePin(LCD_RW_PORT,LCD_RW_PIN,LOGIC_LOW); /* write on LCD */
	_delay_ms(1); /* tas = 50 nsec */
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  /* Enable LCD */
	_delay_ms(1); /* tpw-tdsw =290-100=190 nsec */
	GPIO_writePort(LCD_DATA_PORT,command);           /* write the command on the data port to be executed */
	_delay_ms(1); /* tdsw=100 nsec */
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);   /* Disable LCD */
	_delay_ms(1); /* Th=13 nsec */
}

/* function to display a character on LCD */
void LCD_displayCharacter(uint8 character){
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LOGIC_HIGH);/* select data register */
	GPIO_writePin(LCD_RW_PORT,LCD_RW_PIN,LOGIC_LOW); /* write on LCD */
	_delay_ms(1); /* tas = 50 nsec */
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  /* Enable LCD */
	_delay_ms(1); /* tpw-tdsw =290-100=190 nsec */
	GPIO_writePort(LCD_DATA_PORT,character);         /* write the command on the data port to be executed */
	_delay_ms(1); /* tdsw=100 nsec */
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);   /* Disable LCD */
	_delay_ms(1); /* Th=13 nsec */

}

/* function to display a string on LCD */
void LCD_displayString(uint8* str){
	while((*str)!='\0'){
		LCD_displayCharacter(*str);
		str++;
	}
}

/* function to move the cursor to a specific location */
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 address;
	/* calculate the required address */
	switch(row){
	case 0:
		address=col+LCD_LINE1_START_ADDRESS;
		break;

	case 1:
		address=col+LCD_LINE2_START_ADDRESS;
		break;

	case 2:
		address=col+LCD_LINE3_START_ADDRESS;
		break;

	case 3:
		address=col+LCD_LINE4_START_ADDRESS;
		break;
	}
	/* to move cursor to this location */
	LCD_sendCommand(address|SET_CURSOR_LOCATION);
}

/* function to display a string at a given row and column */
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}

/* function to clear the screen */
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_SCREEN);
}

/* function to display a value given in a variable on LCD */
void LCD_integerToString(uint8 variable){
	char buff[16];          /* String to hold the ASCII result */
	itoa(variable,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff);/* Display the string */
}


