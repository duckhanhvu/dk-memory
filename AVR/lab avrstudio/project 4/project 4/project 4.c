#include <avr/interrupt.h>
#include "text_LCD.h"
 
unsigned long val;
unsigned long frequency;

// Interrupt for the event

ISR(TIMER1_CAPT_vect)
{
	// Counter to 0
	TCNT1 = 0;
 
	// The result is valid only if the counter
	// has not overflowed yet
	if (bit_is_clear(ACSR,ACO))
	{
		// Calculating the frequency from the period
		frequency = ICR1;
		printnumber_lcd(frequency);
	}
	else
	{
		// Frequency is less than 122 Hz
		frequency = 0;
 
		// Set the counter's overflow flag to 0
		ACSR &= ~(1 << ACI);
	}
}
int main()
{
	init_lcd();
	DDRC=0xFF;
	// Register a rising front, prescaler value 1
	TCCR1B = (1<<ICNC1)| (1 << CS10);
 
	// Allow event interrupts
	TIMSK = (1 << TICIE1);
	
	ACSR=(1<<ACIC);
 
	// Allow interrupts globally
	sei();
 
	// Endless loop
	while (1) continue;
}