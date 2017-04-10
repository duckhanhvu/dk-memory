/*
 * project_14.c
 *
 * Created: 1/15/2016 12:09:42 AM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include "matrix4x4.h"
#include "text_LCD.h"
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/sfr_defs.h>

volatile long int x=0,y;
int main(void)
{
DDRC=0x00;
PORTC=0xFF;	
	
PORTD=0xFF;
DDRD=0x0F; 
TIMSK=(1<<TOIE0);
sei();
init_lcd();
/*
movecursor(1,3);
putstr_lcd("khanh",5);
_delay_ms(10000);
clear_lcd();
cursor_home();
*/	
movecursor(1,1);
putstr_lcd("set van toc:",12);
movecursor(1,14);
while(1){
       int i;
       key =KEY4x4_Getkey();
	   
	   if(key){
		   TCNT0=0;
		   TCCR0=(1<<CS01)|(1<<CS00);
		   k=key;
	   }
	   if(bit_is_clear(PINC,2)){
		   break;
	   }	     
	   }
      
      //_delay_ms(1000);
	  clear_lcd();
	  movecursor(1,1);
	  putstr_lcd("da nhap du lieu",15);
	  movecursor(2,4);
	  putstr_lcd("thanh cong",10);
	  _delay_ms(20000);
	  clear_lcd();
	  movecursor(2,1);
	  printnumber_lcd(x);
	  	   	  
return 0;
}
ISR(TIMER0_OVF_vect){
	printnumber_lcd(k);
	x=x*10+k;
	TCNT0=0;
	TCCR0=0;
}