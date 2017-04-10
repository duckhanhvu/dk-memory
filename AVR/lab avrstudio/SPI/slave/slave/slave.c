/*
 * slave.c
 *
 * Created: 11/18/2015 11:26:00 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <stdio.h>
#include "text_LCD.h"

#define  DDR_SLAVE    DDRB
#define  PORT_SLAVE   PORTB
#define  SS           4

#define  SLAVE_SCK    7
#define  SLAVE_MISO   6
#define  SLAVE_MOSI   5
#define  DDR_SPI_SLAVE   DDRB
#define  PORT_SPI_SLAVE  PORTB

volatile unsigned char data;
void init_slave(void){
	DDR_SPI_SLAVE|=(1<<SLAVE_MISO)|(1<<SLAVE_SCK);
	PORT_SPI_SLAVE|=(1<<SLAVE_MOSI)|(1<<SS);
	
	SPCR=(1<<SPIE)|(1<<SPE)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0);
}

int main(void)
{
	sei();
	init_lcd();
	init_slave();
	//clear_lcd();
    while(1){};
		return 0;
}
ISR(SPI_STC_vect){
	data=SPDR;
	//clear_lcd();
	movecursor(1,1);
	printnumber_lcd(data);
}