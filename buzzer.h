/*******************************************************************************
 * File name: buzzer.h
 * Description: Header file for buzzer
 * Module: buzzer
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"

/* define buzzer peripheral */
#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID  PIN6_ID

/* function prototypes **/
void BUZZER_init(void);
void BUZZER_ON(void);
void BUZZER_OFF(void);

#endif /* BUZZER_H_ */
