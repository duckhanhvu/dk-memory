/*
 * hienthi_lcd.c
 *
 * Created: 5/2/2016 9:17:18 AM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include "text_LCD.h"
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include "matrix4x4.h"

volatile uint8_t val=0;
volatile uint8_t ByteOfData;
volatile unsigned char  key,k,x=0;

int main(void)
{
	/*
	 DDRD=0x00;
	 PORTD=0xFF;
	 
	 MCUCR|=(1<<ISC11)|(1<<ISC01);
	 GICR|=(1<<INT0)|(1<<INT1);
	         
	 // uint8_t ByteOfData;            
	 
	 //eeprom_write_byte ((uint8_t *)46, 10);
	 
	 //??c byte có ??a ch? 46
	 // ByteOfData = eeprom_read_byte((uint8_t*)46);      
     
	 init_lcd();
	 cursor_home();
	 
     movecursor(1,4);
	 putstr_lcd("DUC KHANH",9);
	 _delay_ms(5000);
	 clear_lcd();
	 
	 movecursor(1,1);
	 putstr_lcd("Channels ",9);
	 movecursor(2,1);
	 putstr_lcd("lock channel",12);
	 sei();
	 

	 
	 while(1){
		 if(bit_is_clear(PIND,4)){
			 ByteOfData = eeprom_read_byte((uint8_t*)46);
			 movecursor(2,14);
			 printnumber_lcd(ByteOfData);
			 
		 }
	 };
	   
	 return 0; 
}
ISR(INT0_vect){
	val++;
	eeprom_write_byte((uint8_t *)46,val);
	movecursor(1,10);
	printnumber_lcd(val);
}
ISR(INT1_vect){
	val--;
	eeprom_write_byte((uint8_t *)46,val);
	movecursor(1,10);
	printnumber_lcd(val);
}
*/
	
	DDRD=0x00;
	PORTD=0xFF;
	
	DDRC=0x0F;
	PORTC=0xFF;
	
	TCCR2=0;
	TIMSK|=(1<<TOIE2);
	
	init_lcd();
	movecursor(1,1);
	putstr_lcd("DUC KHANH",9);
	movecursor(2,1);
	putstr_lcd("28-4-2016",9);
	_delay_ms(5000);
	clear_lcd();
	movecursor(1,1);
    putstr_lcd("Channels ",9);
	
	movecursor(2,1);
	putstr_lcd("lock channel",12);
	 
	movecursor(1,11);
	
	
	sei();
	while(1)
       {

	   key =KEY4x4_Getkey();
	   
	   if(key){
		   TCNT2=0;
		   TCCR2=(1<<CS22);
		   k=key;
	   }
	   if(bit_is_clear(PIND,4)){
		   movecursor(2,14);
		   ByteOfData=x;
		   printnumber_lcd(ByteOfData);
		   break;
	   }
        

}
}
ISR(TIMER2_OVF_vect){
	printnumber_lcd(k);
	x=x*10+k;
	TCNT2=0;
	TCCR2=0;
	
}