/*
 * master.c
 *
 * Created: 11/18/2015 10:47:57 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "setandclear_bit.h"
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include "text_LCD.h"
//create mark to select chip slave  
#define DDR_MASTER   DDRB
#define PORT_MASTER  PORTB
#define sl_0         0
#define sl_1         1
#define sl_2         2
// create mark for PINS SPI 
#define SCK_MASTER   7
#define MISO_MASTER  6
#define MOSI_MASTER  5
#define DDR_SPI_MASTER      DDRB
#define PORT_SPI_MASTER     PORTB

volatile unsigned int da_ta[3]={5,40,70};
// initailization modes for master 
void init_master(void){
	DDR_SPI_MASTER|=(1<<SCK_MASTER)|(1<<MOSI_MASTER);
	PORT_SPI_MASTER|=(1<<MISO_MASTER);
	
	SPCR=(1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0);
	
	DDR_MASTER|=(1<<sl_2)|(1<<sl_1)|(1<<sl_0);
	PORT_MASTER|=(1<<sl_2)|(1<<sl_1)|(1<<sl_0);
}

//transmit data to chip slave
void MASTER_trans(unsigned int chip_slave_selected,unsigned int data){
	clearbit(PORT_MASTER,chip_slave_selected);
	SPDR=data;
	while(bit_is_clear(SPSR,SPIF)){};
	setbit(PORT_MASTER,chip_slave_selected);	
} 

int main(){
	init_master();
	_delay_ms(100);
	while(1){
		MASTER_trans(0,da_ta[0]++);
		if(da_ta[0]==40) da_ta[0]=5;
		//_delay_ms(10);
		
		MASTER_trans(1,da_ta[1]++);
		if(da_ta[1]==70) da_ta[1]=40;
		//_delay_ms(10);
		
		MASTER_trans(2,da_ta[2]++);
		if(da_ta[2]==99) da_ta[2]=70;
		_delay_ms(500);
	}
	return 0;
}