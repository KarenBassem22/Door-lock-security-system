/*******************************************************************************
 * File name: MC2.c
 * Description: Source file for door locker security system
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "util\delay.h"
#include "MC2.h"

#define F_CPU 8000000UL

int main(void){
	SREG|=(1<<7);

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec, 1 stop bit no parity bit and 8 data bits */
	UART_configFrame config_Uptr={9600,ONE_BIT,DISABLED,EIGHT_BIT};
	UART_init(&config_Uptr);

	/* Initialize the TWI/I2C Driver */
	I2C_configType config_Iptr={0x01,FAST_MODE,I2C_PRESCALER_1};
	I2C_init(&config_Iptr);

	BUZZER_init();
	DcMotor_Init();

	Timer1_setCallBack(BUZZER_OFF);

	int flag=0;
	LCD_init();///
	uint8 pw[PW_SIZE];

	uint8 str1[PW_SIZE];
	uint8 str2[PW_SIZE];

	while(1){
		//
		//		/* Send MC2_READY byte to MC1 to ask it to send the string */
		//		///UART_sendByte(MC2_READY);
		//
		//		/* Receive String from MC1 through UART */
		//		uint8* data1;
		//		UART_receiveString(data1);
		//		LCD_displayString(data1);///
		//		/* Send MC2_READY byte to MC1 to ask it to send the string */
		//		//UART_sendByte(MC2_READY);
		//
		//		uint8* data2;
		//		UART_receiveString(data2);
		//
		//		//EEPROM_writeByte(0x0311, &data); /* Write in the external EEPROM */
		//		//_delay_ms(10);


		for(int i=0;i<PW_SIZE;i++){
			str1[i]=UART_receiveByte();
		}
		LCD_integerToString(str1[0]); /* to check if it's received */

		for(int i=0;i<PW_SIZE;i++){
			str2[i]=UART_receiveByte();
		}
		LCD_integerToString(str2[4]); /* to check if it's received */

		for(int i=0;i<PW_SIZE;i++){
			if(str1[i]!=str2[i]){
				while(UART_receiveByte() != MC1_READY){}
				UART_sendByte(MISMATCH);
				break;
			}
			else if(i==(PW_SIZE-1)){
				while(UART_receiveByte() != MC1_READY){}
				UART_sendByte(MATCH);
				LCD_displayString("match"); /* check */
			}
		}

		for(int i=0;i<PW_SIZE;i++){
			EEPROM_writeByte(0x0311+i, str1[i]); /* Write in the external EEPROM */
			_delay_ms(10);
		}

		/**/while(flag==0){
			/**/	for(int i=0;i<PW_SIZE;i++){
				str1[i]=UART_receiveByte();
			}
			LCD_integerToString(str1[0]); /* to check if it's received */

			//LCD_displayString("saved");

			/* read password from EEPROM */
			for(int i=0;i<PW_SIZE;i++){
				EEPROM_readByte(0x0311+i,&pw[i]); //pw
				_delay_ms(10);
			}


			LCD_integerToString(pw[0]); /* to check */ //pw
			LCD_integerToString(pw[1]); LCD_integerToString(pw[2]); LCD_integerToString(pw[3]);
			_delay_ms(2000);



			//get password
			/**///while(flag==0){
			for(int i=0;i<PW_SIZE;i++){
				if(pw[i]!=str1[i]){ //pw
					while(UART_receiveByte() != MC1_READY){}
					UART_sendByte(MISMATCH);
					LCD_displayString("MISMATCH2");
					break; /* break out the loop */
				}
				else if(i==(PW_SIZE-1)){
					while(UART_receiveByte() != MC1_READY){}
					UART_sendByte(MATCH);
					LCD_displayString("match"); /* check */


				}
			}
			if(UART_receiveByte() == OPEN_DOOR){            /* happens when match password in open door */
				DcMotor_Rotate(CW,DUTY_CYCLE_100);
				//15 secs
				DcMotor_Rotate(STOP,DUTY_CYCLE_0);
				//3 secs
				DcMotor_Rotate(A_CW,DUTY_CYCLE_100);
				//15 secs
				LCD_displayString("opening");
			}
			else if(UART_receiveByte() == CHANGE_PW){       /* happens when match password in change password */
				break; /* begin from start again */
			}
			else if(UART_receiveByte() == ERROR_CHANGE_PW){ /* happens when Mismatch password in change password */
				if(UART_receiveByte() == MISMATCH3){        /* happens when Mismatch password 3 times in a row in change password */
					BUZZER_ON();
					//1-MIN
					BUZZER_OFF();
				}
			}

		}

	/**/	}
}
