
#include <stdlib.h>
#include "setandclear_bit.h"
#include "text_LCD.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <math.h>

#define RS   2
#define EN   1
#define RW   0
#define DATA_output  PORTB
#define DATA_input   PINB
#define CTRL         PORTB
#define DDR_DATA     DDRB
#define DDR_CTRL     DDRB                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 


char read_2Nib(void){
    unsigned char HNib,LNib;
	
	setbit(CTRL,EN);
	DDR_DATA=0x0F;
	HNib=DATA_input&0xF0;
	clearbit(CTRL,EN);
	
	setbit(CTRL,EN);
	LNib=DATA_input&0xF0;
	clearbit(CTRL,EN);
	LNib>>=4;
	
	return (HNib|LNib);
}
void write_2Nib(unsigned char data){
	unsigned char HNib, LNib, temp;
	temp=DATA_output&0x0F;
	HNib=data&0xF0;
	LNib=(data<<4)&0xF0;
	
	DATA_output=HNib|temp;
	setbit(CTRL,EN);
	clearbit(CTRL,EN);
	
	DATA_output=LNib|temp;
	setbit(CTRL,EN);
	clearbit(CTRL,EN);
	
}
void wait_lcd(void){
	unsigned char temp;
	
	while(1){
     	clearbit(CTRL,RS);
		setbit(CTRL,RW);
		temp=read_2Nib();
		
		if(bit_is_clear(temp,7)) break;
	}
	clearbit(CTRL,RW);
	DDR_DATA=0xFF;
	
}

void init_lcd(){//uses mode 4 bit
	DDR_CTRL=0xFF;
	DDR_DATA=0xFF;
	clearbit(CTRL,RS);
	clearbit(CTRL,RW);
	clearbit(CTRL,EN);
	
//function set	
	setbit(CTRL,EN);
	setbit(DATA_output,5);
	clearbit(CTRL,EN);
	wait_lcd();
	write_2Nib(0x28);
	wait_lcd();
//display on/off control
    write_2Nib(0x0E);
	wait_lcd();

//entry mode set 
    
    write_2Nib(0x06);
    wait_lcd();		
}
void putchar_lcd(unsigned char data){
	
	setbit(CTRL,RS);
	write_2Nib(data);
	wait_lcd();
}
void cursor_home(){
	clearbit(CTRL,RS);
	write_2Nib(0x03);
	wait_lcd();
}
void clear_lcd(){
	clearbit(CTRL,RS);
	write_2Nib(0x01);
	wait_lcd();
}
void movecursor(uint8_t dong,uint8_t cot){
	uint8_t x;
	x=64*(dong-1)+(cot-1)+0x80;
	clearbit(CTRL,RS);
	write_2Nib(x);
	wait_lcd();
}
int count_number(unsigned int number){
	int dem=0;
	while(number){
		number=number/10;
		dem++;
	}
	return dem;
}
void printnumber_lcd(unsigned int number){
	int a,n,i,temp;
	n= count_number(number);
	temp=pow(10,n-1);
	for(i=0;i<n;i++){
		a=number/temp;
		number=number%temp;
		temp=temp/10;
		putchar_lcd(a+48);
	}
}
putstr_lcd(unsigned char *str, unsigned int lenght){
	unsigned int i;
	for(i=0;i<lenght;i++){
		if(*(str+i)>0){ 
			putchar_lcd(*(str+i));
			}
		else putchar_lcd(0);	
}
}






