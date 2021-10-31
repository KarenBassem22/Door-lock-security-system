/*******************************************************************************
 * File name: Timer1_driver.h
 * Description: Header file for timer driver
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef TIMER1_DRIVER_H_
#define TIMER1_DRIVER_H_

#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"
#include "avr\io.h"
#include <avr/interrupt.h>

/* enums for dynamic configuration */
typedef enum{
	NO_CLK,NO_PRESCALER,PRESCALER_8,PRESCALER_64,PRESCALER_256,PRESCALER_1024,CLK_FALLING_EDGE,CLK_RISING_EDGE
}Timer1_prescaler;

typedef enum{
	NORMAL,CTC_WZ_OCR=4,FAST_PWM_8,FAST_PWM_9,FAST_PWM_10,CTC_WZ_ICR=12,FAST_PWM_WZ_ICR=14,FAST_PWM_WZ_OCR
}Timer1_mode;

/* Structure for configuration */
typedef struct{
	Timer1_prescaler prescaler;
	Timer1_mode mode;
	uint16 compare_value;
	uint16 initial_value;
}Timer_ConfigType;

/* function prototypes */
void Timer1_init(const Timer_ConfigType* config_ptr);
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer1_DeInit(void);

#endif /* TIMER1_DRIVER_H_ */
