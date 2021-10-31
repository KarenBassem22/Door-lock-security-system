/*******************************************************************************
 * File name: Timer1_driver.c
 * Description: source file for timer driver
 * Date: 24/10/2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "Timer1_driver.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR; /* global pointer to function to hold address of call back function */

/* interrupt service routine of compare mode */
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr!=NULL_PTR){  /* check if the global pointer is assigned a function address */
		(*g_callBackPtr)();       /* Call the Call Back function in the application after the edge is detected */
	}
}

/* interrupt service routine of normal overflow mode */
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr!=NULL_PTR){  /* check if the global pointer is assigned a function address */
		(*g_callBackPtr)();       /* Call the Call Back function in the application after the edge is detected */
	}
}

/* function to initialize the timer with required style */
void Timer1_init(const Timer_ConfigType* config_ptr){
	TCNT1 = config_ptr->initial_value;		/* Set timer1 initial count to initial value given */

	if(config_ptr->mode){                   /* if mode != 0 this means CTC is chosen */
	OCR1A = config_ptr->compare_value;      /* Set the Compare value to the given value */

	SET_BIT(TIMSK,OCIE1A);    /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A */
	SET_BIT(TCCR1A,FOC1A);    /* force compare match on channel A */
	}

	else if(!(config_ptr->mode)){   /* if mode = 0 this means OVF is chosen */
		SET_BIT(TIMSK,TOIE1);       /* Overflow interrupt enable */
	}

	/* Configure timer control register TCCR1B */
	/*TCCR1B = (1<<WGM12) | (1<<CS11);*/
	TCCR1B=(TCCR1B & 0xE7) | (((config_ptr->mode)& 0xC)<<1); /* to get the first two bits only of waveform mode */
	TCCR1B=(TCCR1B & 0xF8) | (config_ptr->prescaler);        /* Prescaler = F_CPU/8 */
}

/* function to save the address of call back function in a global pointer to function */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}

/* function to reset timer1 */
void Timer1_DeInit(void){
	TCNT1=0;   /* reset counter value */
	TCCR1A=0;
	TCCR1B=0;
	OCR1A=0;
	CLEAR_BIT(TIMSK,OCIE1A); /* disable timer1 compare A interrupt */
}
