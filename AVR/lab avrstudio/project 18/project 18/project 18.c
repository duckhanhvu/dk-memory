/*
 * project_18.c
 *
 * Created: 5/22/2016 8:39:06 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
//#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include "setandclear_bit.h"
int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	DDRA=0x00;
	PORTA=0xFF;
	
  
	while(1){
	if (bit_is_clear(PINA, PA5)) {

    PORTC |= (1<<PC5); // put LED HIGH

    } else {

     PORTC &= ~(1<<PC5); // put LED LOW

    }	

	}

	
	
		
	return 0;
}