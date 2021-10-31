/*******************************************************************************
 * File name: I2C.c
 * Description: source file for I2C driver
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "I2C.h"

/* function to initiate I2C */
void I2C_init(const I2C_configType* config_ptr){
	TWSR=(TWSR&0b11111100)|(config_ptr->prescaler); /* Set prescaler value */
	TWBR=(uint8)(((F_CPU/(config_ptr->data_rate))-16)/(2*(4^(config_ptr->prescaler)))); /* calculate TWBR given the prescaler and Fscl */
	//TWBR = 0x02;
	TWAR=(config_ptr->address)<<1;                  /* set the slave address */
	TWCR=(1<<TWEN);                                 /* Enable I2C */
}

/* function to start I2C */
void I2C_start(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA); /* clear I2C interrupt flag, Enable I2C and send start condition bit */
	while(BIT_IS_CLEAR(TWCR,TWINT));      /* wait until it successfully sends the start bit */
} /*t*/

/* function to stop I2C */
void I2C_stop(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO); /* clear I2C interrupt flag, Enable I2C and send stop condition bit */
}


void I2C_write(uint8 data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);            /* Clear TWINT flag and enable I2C */
	/**/	while(BIT_IS_CLEAR(TWCR,TWINT));  /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
}


uint8 I2C_readWithAck(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);  /* Clear TWINT flag, enable I2C and enable ACK bit */
	/**/	while(BIT_IS_CLEAR(TWCR,TWINT));  /* Wait for TWINT flag set in TWCR Register(data is received successfully) */
	return TWDR;
}


uint8 I2C_readWithNack(void){
	TWCR=(1<<TWINT)|(1<<TWEN);            /* Clear TWINT flag, enable I2C and disable ACK bit */
	/**/	while(BIT_IS_CLEAR(TWCR,TWINT));  /* Wait for TWINT flag set in TWCR Register(data is received successfully) */
	return TWDR;
}

/* function to get the status of I2C */
uint8 I2C_getStatus(void){
	uint8 status;
	status=(TWSR&0xF8); /* Exclude the last 3 bits as bit 3 is reserved and bit 1&2 carry the prescaler */
	return status;
}
