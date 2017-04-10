/*
 * DC_motor.c
 *
 * Created: 12/14/2015 4:02:36 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/sfr_defs.h>

int main(void)
{ 
	
	PORTA=0xFF;
	DDRC=0xFF;
	
    while(1)
    {
		PORTA=0xFF;
      
	 if(PINA==0b11111110){
       _delay_ms(5);
	 if(PINA==0b11111110){
       PORTC=0x01;
    }
    }
	if(PINA==0b11111101){
       _delay_ms(5);
	 if(PINA==0b11111101){
       PORTC=0x02;
    }
    }
	if(PINA==0b11111011){
       _delay_ms(5);
	 if(PINA==0b11111011){
       PORTC=0x00;
	}
	}
	}		
	return 0;
}