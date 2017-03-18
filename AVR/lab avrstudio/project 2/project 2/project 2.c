/*
 * project_2.c
 *
 * Created: 11/26/2015 12:50:24 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#define led  0
int main(void)
{
	unsigned int dem=1;
	//ADCSRA=0xA3;
	//SFIOR&=0xF7;
	ACSR=0x00;
	TIMSK=(1<< TICIE1);
	
	DDRD=0xFF;
	DDRB=0x00;
    while(1)
    {
		
		ACSR &=0xFF;
		if(bit_is_clear(ACSR,ACO)){
			PORTD=dem;
			
			//_delay_ms(5000);
		}	
		else PORTD&=0x00;
					
    }
return 0;
}