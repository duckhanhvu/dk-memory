/*
 * project_16.c
 *
 * Created: 5/2/2016 8:36:27 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include "text_LCD.h"

int main(void)
{

	//uint8_t k;
	
	init_lcd();
	
	cursor_home();
	
	//eeprom_write_byte((uint8_t *)46, 10);
	//k=eeprom_read_dword((uint8_t *)46);
	printnumber_lcd(10);
	return 0;
    
}