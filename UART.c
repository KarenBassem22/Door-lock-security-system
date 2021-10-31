/*******************************************************************************
 * File name: UART.c
 * Description: Source file for UART
 * Module: UART
 * Author: Karen Bassem
 ******************************************************************************/
#include "UART.h"

/* function to initialize UART with dynamic configuration */
void UART_init(const UART_configFrame * config_ptr){
	uint16 value=0;
#ifdef DOUBLE_SPEED_MODE
	SET_BIT(UCSRA,U2X);        /* double transmission speed */
#endif
	UCSRB=(1<<RXEN)|(1<<TXEN); /* receiver and transmitter Enable */
	/* clear bit 2, read the MSB from data bit number and then shift by 2 */
	UCSRB=(UCSRB&0b11111011)|((config_ptr->data_bits_num)&(1<<UCSZ2)); /* to choose number of data bits */
#ifdef NINE_DATA_BITS
	UCSRB|=(1<<RXB8)|(1<<TXB8); /* allow receiving and transmitting the ninth bit */
#endif
	UCSRC=(1<<URSEL); /* URSEL=0 to write in UCSRC */
	UCSRC=(UCSRC&0b11001111)|((config_ptr->parity_bit)<<4); /* to choose odd or even parity */
	UCSRC=(UCSRC&0b11110111)|((config_ptr->stop_bits)<<USBS);  /* to choose the number of stop bits (1 or 2) */
	/* take the least significant 2 bits only in this register */
	UCSRC=(UCSRC&0b11111001)|(((config_ptr->data_bits_num)&0x03)<<1);/* to choose number of data bits */
#ifdef ASYNCHRONOUS
#ifdef DOUBLE_SPEED_MODE
	value = (uint16)(((F_CPU / ((config_ptr->baud_rate) * 8UL))) - 1);  /* Asynchronous double speed mode*/
#else
	value = (uint16)(((F_CPU / ((config_ptr->baud_rate) * 16UL))) - 1); /* Asynchronous normal mode */
#endif
#else
	value = (uint16)(((F_CPU / ((config_ptr->baud_rate) * 2UL))) - 1);  /* Synchronous master mode */
#endif
	UBRRL=value;      /* put first 8 bits */
	UBRRH=value>>8;   /* put last 4 bits */
}

/* function to transmit a byte */
void UART_sendByte(const uint8 data){
	while(BIT_IS_CLEAR(UCSRA,UDRE)); /* wait until there's data to transmit */
	UDR=data;                        /* put the data in data register */
}

/* function to receive a byte */
uint8 UART_receiveByte(void){
	while(BIT_IS_CLEAR(UCSRA,RXC));  /* wait until receive complete flag is set */
	return UDR;                      /* read the data from UDR register */
}

/* function to transmit a string */
void UART_sendString(const uint8* str){
	while((*str)!='\0'){              /* Terminal condition */
		UART_sendByte(*str);          /* send character by character */
		str++;                        /* increment the pointer */
	}
}

/* function to receive a string */
/* input to the function is a pointer to char to store the characters of the string in it */
/* return type is void because the return occurs in the invocation of other function */
void UART_receiveString(uint8* str){
	*str=UART_receiveByte();
	while((*str)!='@'){      /* a symbol to indicate the end bec. the null terminator is not sent */
		*str=UART_receiveByte();  /* receive char by char */
		str++;               /* increment the pointer */
	}
	*str='\0'; /* add null terminator to indicate the end of string and replace the @ */
}
