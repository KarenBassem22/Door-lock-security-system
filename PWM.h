/*************************************************************************************************************
 * Author: Karen Bassem Thabet
 * File Name: PWM.h
 * Description: header file for PWM
 * Date: 5/10/2021
 ************************************************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "common_macros.h"
#include "avr\io.h"
#include "std_types.h"
#include "gpio.h"

#define NON_INVERTING

/* function prototype */
void PWM_Timer0_Start(uint8 duty_DUTY_CYCLE);

/* define the corresponging values of duty cycles */
#ifdef NON_INVERTING
#define DUTY_CYCLE_0 0
#define DUTY_CYCLE_25 64
#define DUTY_CYCLE_50 128
#define DUTY_CYCLE_75 192
#define DUTY_CYCLE_100 255

#endif

#endif /* PWM_H_ */
