/*******************************************************************************
 * File name: UART.h
 * Description: Header file for UART
 * Module: UART
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"
#include "avr\io.h"

/* enums for dynamic configuration */
typedef enum{
	ONE_BIT,TWO_BITS
}UART_stopBit;

typedef enum{
	FIVE_BIT,SIX_BITS,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_dataBit;

typedef enum{
	DISABLED,EVEN_PARITY=2,ODD_PARITY
}UART_parityBit;

/* structure for frame configuration */
typedef struct{
	uint32 baud_rate;
	UART_stopBit stop_bits;
	UART_parityBit parity_bit;
	UART_dataBit data_bits_num;
}UART_configFrame;

#define F_CPU 8000000UL
#define DOUBLE_SPEED_MODE
#define ASYNCHRONOUS

/* function prototypes */
void UART_init(const UART_configFrame * config_ptr);
void UART_sendByte(const uint8 data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8* str);
void UART_receiveString(uint8* str);

#endif /* UART_H_ */
