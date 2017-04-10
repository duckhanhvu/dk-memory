/*
 * master.c
 *
 * Created: 11/23/2015 3:07:41 PM
 *  Author: Duc Khanh
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "TWI.h"
#include "text_LCD.h"
volatile uint8_t s;
volatile uint8_t x,a[2];
int main(){
	unsigned int data_1[50];
	unsigned int data_2[50];
	DDRD =0x00;
	PORTD=0xFF;
	Init_TWI();
	init_lcd();
	MCUCR |=(1<<ISC01);
	GICR  |=(1<<INT0);
	sei();
	_delay_ms(100);
	cursor_home();
	putstr_lcd("from slave:",11);
	
	for(int i=0;i<50;i++) data_1[i]=i; 
	MASTER_Trans(2,data_1,55);
	
	for(int i=0;i<44;i++) data_2[i]=i;
	MASTER_Trans(3,data_2,44);
	
	

	while(1){}
	
	return 0;
}

ISR(INT0_vect){
 
    unsigned int c;
    s=PIND&0x03;
	MASTER_Receiver(s,a,1);
	movecursor(1,12);

	printnumber_lcd(a[0]);

 	
}
