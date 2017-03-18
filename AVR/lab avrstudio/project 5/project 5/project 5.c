/*
 * project_5.c
 *
 * Created: 12/27/2015 2:20:37 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRA=0x01;
	PORTA=0x00;
    while(1)
    {
		_delay_ms(1000);
		PORTA=0x01;
		_delay_ms(1000);
		PORTA=0x00;
        //TODO:: Please write your application code 
    }
}