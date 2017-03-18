/*
 * project_27.c
 *
 * Created: 7/29/2016 9:33:31 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "text_LCD.h"



volatile unsigned int val=0;
int main(void)
{
	
	
	DDRD=0x00;
	PORTD=0xFF;
	init_lcd();
	clear_lcd();
	
	MCUCR|=(1<<ISC11)|(1<<ISC01);
	GICR    |=(1<<INT1)|(1<<INT0);
	sei(); 
	 while(1)
    {
		
    }
	return 0;
   
}

ISR(INT0_vect){
    val++;                                       //n?u có ng?t INT0 x?y ra, t?ng val thêm 1
    if (val>9) val=0;                        //gi?i h?n không v??t quá 9
    		movecursor(1,1);
	    printnumber_lcd(val);
}

//Trình ph?c v? ng?t c?a  INT1
ISR(INT1_vect){
    val--;                                        //n?u có ng?t INT1 x?y ra, gi?m val ?i 1
    if (val<0) val=9;                       //gi?i h?n không nh? h?n 0
    		movecursor(1,1);
	    printnumber_lcd(val);
}