/*******************************************************************************
 * File name: EEPROM.h
 * Description: Header file for EEPROM driver
 * Module: EERPROM
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"

/* definitions */
#define FIRST_FOUR_DEVICE_ADDRESS_BITS 0xA0
#define ERROR 0
#define SUCCESS 1

/* function prototypes */
uint8 EEPROM_writeByte(uint16 address, uint8 data);
uint8 EEPROM_readByte(uint16 address, uint8* data);

#endif /* EEPROM_H_ */
