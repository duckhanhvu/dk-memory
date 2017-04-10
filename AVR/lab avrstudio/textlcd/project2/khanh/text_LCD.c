
#include <stdlib.h>
#include "setandclear_bit.h"
#include "text_LCD.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/delay.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                


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
	_delay_us(1);
	clearbit(CTRL,EN);
	_delay_us(1);
	
	DATA_output=LNib|temp;
	setbit(CTRL,EN);
	_delay_us(1);
	//_delay_us(2);
	clearbit(CTRL,EN);
	//_delay_us(100);
	_delay_us(1);
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
/*	
	DDR_CTRL=0xFF;
	DDR_DATA=0xFF;
	clearbit(CTRL,RS);
	clearbit(CTRL,RW);
	clearbit(CTRL,EN);
	
//function set	
	setbit(CTRL,EN);
	setbit(DATA_output,5);
	clearbit(CTRL,EN);
	//wait_lcd();
	_delay_ms(10);
	write_2Nib(0x28);
	//wait_lcd();
	_delay_ms(10);
//display on/off control
    write_2Nib(0x0C);
	//wait_lcd();
	_delay_ms(10);

    write_2Nib(0x01);
	//wait_lcd();
	_delay_ms(10);
//entry mode set 
    
    write_2Nib(0x06);
   // wait_lcd();
	_delay_ms(10);	
	
*/

	DDR_CTRL=0xFF;
	DDR_DATA=0xFF;
	clearbit(CTRL,RS);
	clearbit(CTRL,RW);
	clearbit(CTRL,EN);
	
	setbit(CTRL,EN);
	setbit(DATA_output,5);
	clearbit(CTRL,EN);


		
write_2Nib(0x28); // initialization of 16X2 LCD in 8bit mode
_delay_us(240);

write_2Nib(0x0C);
_delay_us(240);	

write_2Nib(0x01); // clear LCD
_delay_ms(10);
 
write_2Nib(0x06); // cursor ON
_delay_us(240);
 
	
}
void putchar_lcd(unsigned char data){
	
	setbit(CTRL,RS);
	clearbit(CTRL,RW);
	write_2Nib(data);
	//wait_lcd();
	_delay_us(240);
}
void cursor_home(){
	clearbit(CTRL,RS);
	clearbit(CTRL,RW);
	write_2Nib(0x03);
	//wait_lcd();
	_delay_ms(10);
}
void clear_lcd(){
	clearbit(CTRL,RS);
	clearbit(CTRL,RW);
	write_2Nib(0x01);
	//wait_lcd();
	_delay_ms(10);
}
void movecursor(uint8_t dong,uint8_t cot){
	uint8_t x;
	x=64*(dong-1)+(cot-1)+0x80;
	clearbit(CTRL,RS);
	write_2Nib(x);
	//wait_lcd();
	_delay_us(240);
}
int count_number(long int number){
	int dem=0;
	if(number!=0) {
	   while(number){
		number=number/10;
		dem++;
	}	
    } 
	else dem=dem+1; 
	return dem;
}
void printnumber_lcd(unsigned int number){
	/*int a,n,i,temp;
	n= count_number(number);
	temp=pow(10,n-1);
	for(i=0;i<n;i++){
		a=number/temp;
		number=number%temp;
		temp=temp/10;
		putchar_lcd(a+48);
	}*/
			int a,b,c,d,e;
	    a=number/10000;
	    //putchar_lcd(a+48);
		number=number%10000;
	    b=number/1000;
	    //putchar_lcd(b+48);
	    number=number%1000;
	    c=number/100;
	    //putchar_lcd(c+48);	
	    number=number%100;
	    d=number/10;
	    //putchar_lcd(d+48);	
	    e=number%10;
	   // putchar_lcd(e+48);
    if(a==0 && b==0 && c==0 && d==0){
		putchar_lcd(e+48);
	}
	else if(a==0 && b==0 && c==0){
		putchar_lcd(d+48);
		putchar_lcd(e+48);
	}
	else if(a==0 && b==0){
		putchar_lcd(c+48);
		putchar_lcd(d+48);
		putchar_lcd(e+48);
	}
	else if(a==0){
		putchar_lcd(b+48);
	    putchar_lcd(c+48);
		putchar_lcd(d+48);
		putchar_lcd(e+48);
	}
	else if(a!=0 && b!=0 && c!=0 && d!=0){
		putchar_lcd(a+48);
		putchar_lcd(b+48);
	    putchar_lcd(c+48);
		putchar_lcd(d+48);
		putchar_lcd(e+48);
	}
}
void putstr_lcd(unsigned char *str, unsigned int lenght){
	unsigned int i;
	for(i=0;i<lenght;i++){
		if(*(str+i)>0){ 
			putchar_lcd(*(str+i));
			}
		else putchar_lcd(0);	
}
}







