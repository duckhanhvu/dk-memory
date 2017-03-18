/*
 * project_12.c
 *
 * Created: 1/12/2016 1:38:17 AM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "setandclear_bit.h"
#include <avr/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRA=0x00;
	PORTA=0xFF;
   init_lcd();
   clear_lcd();
   TCCR0=(1<<CS01);
                 
   TIMSK=(1<<TOIE0);
   sei();                      

 
   return 0;
}
ISR(TIMER0_OVF_vect){
	if(bit_is_clear(PINA,3)){
		printnumber_lcd(3);
	}
}