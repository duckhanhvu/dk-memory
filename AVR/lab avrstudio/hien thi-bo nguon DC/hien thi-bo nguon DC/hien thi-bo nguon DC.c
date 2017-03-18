/*
 * hien_thi_bo_nguon_DC.c
 *
 * Created: 4/2/2016 4:08:19 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <math.h>
#include "text_LCD.h"
#include "setandclear_bit.h"


#define ADC_VREF_TYPE 0x40

uint16_t read_adc(uint8_t chanel_adc){

	ADMUX=(ADC_VREF_TYPE)|(chanel_adc);
	_delay_ms(1);
	ADCSRA|=(1<<ADSC);
	while((ADCSRA&0x10)==0);
	return ADCW;
}


int main(void)
{
	int adc;
	float Vol_in;
	init_lcd();
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
	ADMUX=(ADC_VREF_TYPE);
	
    while(1)
    {
		adc=read_adc(0);
        Vol_in=(((float)adc*8.5)/1023)*1000;
		movecursor(1,1);
		printnumber_lcd(Vol_in);  
    }
	return 0;
}