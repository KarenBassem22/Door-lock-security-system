/*******************************************************************************
 * File name: I2C.h
 * Description: header file for I2C driver
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"
#include "avr\io.h"

/* Enums for dynamic configuration */
typedef enum{
	I2C_PRESCALER_1,I2C_PRESCALER_4,I2C_PRESCALER_16,I2C_PRESCALER_64
}I2C_PRESCALER;

typedef enum{
	NORMAL_MODE=100000,FAST_MODE=400000,FAST_MODE_PLUS=1000000,HIGH_SPEED_MODE=3400000
}I2C_DATA_RATE;

/* structure for dynamic configuration of I2C*/
typedef struct{
	uint16 address;
	I2C_DATA_RATE data_rate;
	I2C_PRESCALER prescaler;
}I2C_configType;

/* definitions */
//#define F_CPU 8000000UL
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/* function prototypes */
void I2C_init(const I2C_configType* config_ptr);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(uint8 data);
uint8 I2C_readWithAck(void);
uint8 I2C_readWithNack(void);
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
