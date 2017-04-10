/*
 * project_44.c
 *
 * Created: 2/7/2017 16:06:36
 *  Author: duckhanh
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "text_LCD.h"
#include "i2c.h"
#include "rtc.h"

rtc_t time; 
rtc_t thoi_gian={55,23,3,2,23,5,16}; 

volatile uint8_t giay=55, phut=12, gio=4;
volatile uint8_t day=2, ngay=12,thang=5,nam=16;
volatile unsigned int count=0;

uint8_t Dec_BCD(uint8_t Dec){
	uint8_t temp,H,L;
	L=(Dec%10);
	H=(Dec/10)<<4;
	
	return (H+L);
}

uint8_t BCD_Dec(uint8_t BCD){
	uint8_t L,H;
	L=BCD&0x0F;
	H=(BCD>>4)*10;
	return (H+L);	
}

void Display(void){
	
	 giay=BCD_Dec((time.sec)&0x7F);
	 phut=BCD_Dec(time.min);
	 gio=BCD_Dec((time.hour)&0x1F);// su dung mode 12h
	 
	 thang=BCD_Dec(time.month);
	 ngay=BCD_Dec(time.date);
	 nam=BCD_Dec(time.year);
	 
	 cursor_home();
	 putstr_lcd("Time: ",6);
	 movecursor(1,8);
	 printnumber_lcd(gio);
	 movecursor(1,10);
	 putchar_lcd(':');
	 movecursor(1,11);
	 printnumber_lcd(phut);
	 movecursor(1,13);
	 putchar_lcd(':');
	 movecursor(1,14);
	 printnumber_lcd(giay);
	 
	 movecursor(1,16);
	 if(bit_is_clear((time.hour),5)) putchar_lcd('A');
	 else putchar_lcd('P');
	 
	 //date=BCD_Dec(data[4]);
	 //month=BCD_Dec(data[5]);
	// year=BCD_Dec(data[6]);
	 movecursor(2,1);
	 putstr_lcd("Date: ",6);
	 movecursor(2,8);
	 printnumber_lcd(ngay);
	 putchar_lcd('-');
	 printnumber_lcd(thang);
	 putchar_lcd('-');
	 printnumber_lcd(nam);
	 
}
int main(void)
{
	init_lcd();
	_delay_ms(1000);
	//tao khoang thoi gian duoi 50ms bang timer 0;
	
	TCCR0=(1<<CS02)|(0<<CS01)|(1<<CS00);
	TIMSK=(1<<TOIE0);
	sei();
	
	time.sec = Dec_BCD(giay);                // read second and return Positive ACK
    time.min = Dec_BCD(phut);                 // read minute and return Positive ACK
    time.hour= Dec_BCD(gio);               // read hour and return Negative/No ACK
    time.weekDay = Dec_BCD(day);           // read weekDay and return Positive ACK
    time.date= Dec_BCD(ngay);              // read Date and return Positive ACK
    time.month=Dec_BCD(thang);            // read Month and return Positive ACK
    time.year =Dec_BCD(nam); 
	RTC_Init();	
	
	//ghi cac byte data vao chip DS1307

	RTC_SetDateTime(time);		
	_delay_ms(2);
	//set dia chi bat dau doc
	
	//doc du lieu tu DS1307
	RTC_GetDateTime(time);

	Display();

    while(1)
    {    
    }
	return 0;
}

ISR(TIMER0_OVF_vect){
	count++;
	
	if(count>=10){
	RTC_GetDateTime(time);
	clear_lcd();
	printnumber_lcd(BCD_Dec((time.sec)&0x7F));
	//set_addr_register_DS(0x00);
	
	//doc du lieu tu DS1307
	//DS1307_GetTime();
	//DS1307_GetDate();	
	if(BCD_Dec((time.sec)&0x7F)!=giay){
	giay=BCD_Dec((time.sec)&0x7F);
		movecursor(1,14);                                                         
		putchar_lcd("  ");
		movecursor(1,14);
		printnumber_lcd(giay);
		if(giay==0) Display();
	}
	count=0;
	}
}