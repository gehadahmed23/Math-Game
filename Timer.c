/*
 * Timer.c
 *
 * Created: 2/6/2024 8:17:57 AM
 *  Author: Dell
 */ 

#include "Timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "std_macros.h"

void timer_CTC_init_interrupt(void){
	/* select CTC mode */
	SET_BIT(TCCR0, WGM01);
	
	/*load value on OCR0*/
	OCR0 = 80;
	
	/* select clock  */
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02);
	
	/*enable interrupt*/
	sei();
	SET_BIT(TIMSK,OCIE0);
}
