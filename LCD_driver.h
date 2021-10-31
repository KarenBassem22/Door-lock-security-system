/*******************************************************************************
 * File name: LCD_driver.h
 * Description: header file for LCD
 * Module: LCD
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "gpio.h"
#include"common_macros.h"
#include <util\delay.h> /* to use delay function */
#include <stdlib.h>     /* to use itoa function */

/* define LCD Control pins */
#define LCD_RS_PIN    PIN0_ID
#define LCD_RS_PORT   PORTB_ID

#define LCD_RW_PIN    PIN1_ID
#define LCD_RW_PORT   PORTB_ID

#define LCD_E_PIN     PIN2_ID
#define LCD_E_PORT    PORTB_ID

#define LCD_DATA_PORT PORTA_ID

/* define commands */
#define TWO_LINES_8_BITS  0x38
#define CURSOR_OFF        0x0C
#define CLEAR_SCREEN      0x01

#define SET_CURSOR_LOCATION 0x80

/* define start address of lines */
#define LCD_LINE1_START_ADDRESS 0x00
#define LCD_LINE2_START_ADDRESS 0x40
#define LCD_LINE3_START_ADDRESS 0x10
#define LCD_LINE4_START_ADDRESS 0x50

/* function prototypes */
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(uint8* str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str);
void LCD_clearScreen(void);
void LCD_integerToString(uint8 variable);

#endif /* LCD_DRIVER_H_ */
