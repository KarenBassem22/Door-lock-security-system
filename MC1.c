/*******************************************************************************
 * File name: MC1.c
 * Description: Source file for door locker security system
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "MC1.h"
#define F_CPU 8000000UL

uint8 str1[PW_SIZE];
uint8 str2[PW_SIZE];

void sendPassword(){
	for(int i=0;i<PW_SIZE;i++){
		UART_sendByte(str1[i]);
	}
}

void sendConfirmPassword(){
	for(int i=0;i<PW_SIZE;i++){
		UART_sendByte(str2[i]);
	}
}

char* get_password(void){
	//char str1[PW_SIZE+1];
	uint8 key_num;
	LCD_displayStringRowColumn(0,0,"Enter password  ");
	for(int i=0;i<PW_SIZE;i++){
		key_num=KEYPAD_getPressedKey();
		str1[i]=key_num;
		LCD_moveCursor(1,i);
		LCD_displayCharacter('*');
		_delay_ms(4000);
	}
	return str1;
}

char* Confirm_password(void){
	//char str2[PW_SIZE+1];
	uint8 key_num;
	LCD_displayStringRowColumn(0,0,"R_enter password");
	for(int i=0;i<PW_SIZE;i++){
		key_num=KEYPAD_getPressedKey();
		str2[i]=key_num;
		LCD_moveCursor(1,i);
		LCD_displayCharacter('*');
		_delay_ms(4000);
	}
	return str2;
}



int main(void){
	uint8 flag=0;
	SREG|=(1<<7);

	LCD_init();

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec, 1 stop bit no parity bit and 8 data bits */
	UART_configFrame config_Uptr={9600,ONE_BIT,DISABLED,EIGHT_BIT};
	UART_init(&config_Uptr);

	uint8 key_num;
	uint8 false_times=0;

	//Timer_ConfigType config_Tptr={PRESCALER_8,CTC_WZ_OCR,125,0};


	while(1){
		get_password();

		/* Wait until MC2 is ready to receive the string */
		///while(UART_receiveByte() != MC2_READY){}

		/////UART_sendString(str1);
		sendPassword();

		/*LCD_displayStringRowColumn(0,0,"R_enter password");
		for(int i=0;i<PW_SIZE;i++){
			UART_sendByte(KEYPAD_getPressedKey());
			LCD_moveCursor(1,i);
			LCD_displayCharacter('*');
		}*/

		LCD_sendCommand(CLEAR_SCREEN);
		_delay_ms(500);

		Confirm_password();

		/* Wait until MC2 is ready to receive the string */
		//while(UART_receiveByte() != MC2_READY){}

		////UART_sendString(str2);
		sendConfirmPassword();

		LCD_sendCommand(CLEAR_SCREEN);
		_delay_ms(500);

		///while(flag==0){
		UART_sendByte(MC1_READY);
		if(UART_receiveByte()== MATCH){
			flag=1;
			LCD_displayString("Match!");
			_delay_ms(4000);
		}
		else{
			LCD_displayString("Mismatch!");
			_delay_ms(4000);
		}
		///}

		while(flag==1){
			LCD_displayStringRowColumn(0,0,"+:open door");
			LCD_displayStringRowColumn(1,0,"-:change password");
			if(KEYPAD_getPressedKey()=='+'){
				LCD_sendCommand(CLEAR_SCREEN);
				_delay_ms(4000);
				get_password();
				sendPassword();
				//compare passwords
				UART_sendByte(MC1_READY);
				if(UART_receiveByte()== MATCH){
					UART_sendByte(OPEN_DOOR);
					//to continue		//Timer1_init(&config_Tptr);
					// for 15 secs
					LCD_sendCommand(CLEAR_SCREEN);
					LCD_displayString("door is opening");
					_delay_ms(4000);
					//stop for 3 secs
					// for 15 secs
					LCD_sendCommand(CLEAR_SCREEN);
					LCD_displayString("door is closing");
				}
				else{
					LCD_sendCommand(CLEAR_SCREEN);
					LCD_displayString("Mismatch!");
					_delay_ms(4000);
					//break; //to get out of the loop
				}

				LCD_sendCommand(CLEAR_SCREEN);
				_delay_ms(500);

			}
			else if(KEYPAD_getPressedKey()=='-'){
				LCD_sendCommand(CLEAR_SCREEN);
				_delay_ms(500);
				LCD_displayStringRowColumn(0,0,"current password");
				_delay_ms(4000);
				uint8 key_num;
				for(int i=0;i<PW_SIZE;i++){
					key_num=KEYPAD_getPressedKey();
					str1[i]=key_num;
					LCD_moveCursor(1,i);
					LCD_displayCharacter('*');
					_delay_ms(4000);
				}
				sendPassword();

				UART_sendByte(MC1_READY);
				if(UART_receiveByte()== MATCH){
					UART_sendByte(CHANGE_PW);
					LCD_sendCommand(CLEAR_SCREEN);
					false_times=0; /* to reset counter of false times if pw matches */
					break;         /* to begin from start */
				}
				else{
					UART_sendByte(ERROR_CHANGE_PW);
					false_times++;
					LCD_sendCommand(CLEAR_SCREEN);
					_delay_ms(500);
					LCD_displayString("Mismatch!");
					_delay_ms(4000);
					if(false_times==3){
						//to continue			//lock system for 1 min
						//send by uart to activate buzzer
						UART_sendByte(MISMATCH3);
						LCD_sendCommand(CLEAR_SCREEN);
						_delay_ms(500);
						LCD_displayString("error 3 times");
						_delay_ms(4000);
					}
				}

				//flag=0; /* to get out of this while loop */
				//if match
				//break;
			}
		}

	}

}
