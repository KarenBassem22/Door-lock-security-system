/*******************************************************************************
 * File name: MC2.h
 * Description: header file for door locker security system
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef MC2_H_
#define MC2_H_

#include "buzzer.h"
#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"
#include "Timer1_driver.h"
#include "UART.h"
#include "PWM.h"
#include "I2C.h"
#include "EEPROM.h"
#include "DC_motor.h"

#include "LCD_driver.h"

#define PW_SIZE 5
#define MC1_READY 0x01 /* shake hand condition for UART*/
#define MISMATCH 0x21  /* choose any value to represent mismatch value */
#define MATCH 0x12
#define MISMATCH3 0x22 /* for 3 times mismatch of password */
#define OPEN_DOOR 0x77
#define CHANGE_PW 0x88
#define ERROR_CHANGE_PW 0x99

#endif /* MC2_H_ */
