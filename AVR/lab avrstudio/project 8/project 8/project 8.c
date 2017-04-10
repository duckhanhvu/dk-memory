#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "text_LCD.h"

volatile long int  pulseA=0;    
int main(void){

    init_lcd();
    DDRD=0x00;    
    PORTD=0xFF; 
    DDRB=0xFF;    
    
    MCUCR|=(0<<ISC11)|(0<<ISC01);     
    GICR    |=(1<<INT1)|(1<<INT0);    
    sei();                                           
    //printnumber_lcd(12);
    DDRC=0xFF;                                  
    while (1){                                    
        
    }
    return 0;
}

ISR(INT1_vect){
    pulseA++;
	movecursor(1,1);                                        
    printnumber_lcd(pulseA);
	
	PORTB=pulseA;
}