/*
 * project_35.c
 *
 * Created: 8/21/2016 6:31:57 PM
 *  Author: Duc Khanh
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include "lcd2.h"
int main(void)
{


    DDRD=0xFF;
	PORTD=0xFF;


    lcd_init_4d();                                


    LCD_goto(2,1);
    lcd_write_string_4d("khanh thanh");
	
}