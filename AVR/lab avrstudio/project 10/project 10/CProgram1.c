/*
 * CProgram1.c
 *
 * Created: 1/14/2016 11:10:34 PM
 *  Author: Duc Khanh
 */ 
#include <avr/io.h>
#include "text_LCD.h"
#include <avr/sfr_defs.h>
#include "setandclear_bit.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "matrix4x4.h"
void main(void)
{
	
init_lcd();

PORTA=0xFF;
DDRA=0xFF;

DDRC=0xFF;
PORTC=0x00;
 


PORTD=0xFF;
DDRD=0x0F; 

/*
DDRD=0xF0;
PORTD=0x0F;
*/

TCCR0=0;//TCCR0=(1<<CS02)|(1<<CS00);

TIMSK=(1<<TOIE0);
sei();
clear_lcd();
cursor_home();
movecursor(1,6);
while(1){
       int i;
       key =KEY4x4_Getkey();
	   
	   if(key){
		   
		   TCNT0=0;
		   TCCR0=(1<<CS02)|(1<<CS00);
		   k=key;
	   }	       
	   }	  
return 0;
}
ISR(TIMER0_OVF_vect){
	    
	    printnumber_lcd(k);
		TCNT0=0;
	    TCCR0=0;	
}