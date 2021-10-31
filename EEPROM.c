/*******************************************************************************
 * File name: EEPROM.c
 * Description: source file for EEPROM driver
 * Module: EERPROM
 * Author: Karen Bassem
 ******************************************************************************/
#include "EEPROM.h"

uint8 EEPROM_writeByte(uint16 address, uint8 data){
	I2C_start();                /* send the start bit */
	if (I2C_getStatus() != TWI_START)
		return ERROR;

	/* send the device address including 3 bits of memory address in EEPROM */
	I2C_write((uint8)(FIRST_FOUR_DEVICE_ADDRESS_BITS | ((address & 0x0700) >> 7))); /* 1010 A10 A9 A8 | ((address & 0b 0000 0111 0000 0000) >> 7) */
	if (I2C_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	I2C_write((uint8) address); /* send the memory address location */
	if (I2C_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	I2C_write(data);            /* send the data byte to EEPROM */
	if (I2C_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	I2C_stop();                 /* send the stop bit */

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 address, uint8* data){
	I2C_start();                                         /* send the start bit */
	if (I2C_getStatus() != TWI_START)
		return ERROR;

	/* send the 7-bit device address, the 8th bit is zero to write */
	I2C_write((uint8)(FIRST_FOUR_DEVICE_ADDRESS_BITS | ((address & 0x0700) >> 7))); /* send the device address */
	if (I2C_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	I2C_write((uint8) address);                          /* send the memory address location */
	if (I2C_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	I2C_start();                                         /* send another start (repeated start) bit */
	if (I2C_getStatus() != TWI_REP_START)
		return ERROR;
    /* send the 7-bit device address and OR with 1 to set read */
	I2C_write((uint8)(FIRST_FOUR_DEVICE_ADDRESS_BITS | ((address & 0x0700) >> 7) | 1)); /* send the device address */
	if (I2C_getStatus() != TWI_MT_SLA_R_ACK)
		return ERROR;

	*data = I2C_readWithNack();                          /* read byte from EEPROM */
	if (I2C_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	I2C_stop();                                          /* send the stop bit */

	return SUCCESS;
}

