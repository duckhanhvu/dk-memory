/*
 * project1.c
 *
 * Created: 10/30/2015 8:52:11 PM
 *  Author: 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> 

ISR (INT0_vect){
	if(OCR1A==1000) OCR1A=2000;
	else OCR1A=1000;
}
int main(void)
{
	PORTD=0x00;
	DDRD=0x20;
	
	TCCR1A=(1<<COM1A1)|(1<<WGM11);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
	
	MCUCR=(1<<ISC01);
	GICR=(1<<INT0);
	
	OCR1A=1000;
	ICR1=20000;
	
	sei();
	
    while(1)
    {
      
    }
}
