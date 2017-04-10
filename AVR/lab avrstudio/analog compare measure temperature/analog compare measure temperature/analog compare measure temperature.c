

#include <avr/interrupt.h>
#include "text_LCD.h"
#include <avr/delay.h>
#include <math.h>
 
volatile unsigned long val;
volatile float j;
volatile float i,t,V,T;


ISR(TIMER1_CAPT_vect)
{
	
	if (bit_is_clear(ACSR,ACO))
	{
		
		//TCCR1B = 0;
		j = ICR1;
		t=j*pow(10,-6);
		V=(5*(1-exp(-(100*t))))*1000;
		T=V/10-273;
		movecursor(2,1);
		printnumber_lcd(T+1);
		//TCNT1 = 0;
	}
	//TCCR1B = 0;
	/*else
	{
		// Frequency is less than 122 Hz
		frequency = 0;
 
		// Set the counter's overflow flag to 0
		ACSR &= ~(1 << ACI);
	}*/
}
int main()
{
	init_lcd();
 
	PINA=0x00;
	DDRA=0xff;
	
	PIND=0x00;
	DDRC=0xFF;

	
	TCNT1=0;
	_delay_ms(100);
	
	DDRA=0x00;
	PINA=0xff;
	TCCR1B = (1<<ICNC1)|(1 << CS10);
 
	
	TIMSK = (1 << TICIE1);
	
	ACSR=(1<<ACIC);
 
	
	sei();
 
	
	while (1){
		
	        }
			return 0; 
}	
