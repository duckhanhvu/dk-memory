

#define F_CPU	4000000UL
#include <avr/io.h>
#include "text_LCD.h"
#include <util/delay.h>


int main(void)
{
	init_lcd();
	
	_delay_ms(50);
	cursor_home();
	
	putchar_lcd("khanh");
    while(1){};

	return 0;
}