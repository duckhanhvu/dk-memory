/*
 * project_ex.c
 *
 * Created: 8/26/2016 12:32:51 AM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{
	DDRA=0xFF;
    while(1)
    {
       PORTA=0x0F;
	   _delay_us(100);
	   PORTA=0x1F;
	   _delay_us(100);

    }
}