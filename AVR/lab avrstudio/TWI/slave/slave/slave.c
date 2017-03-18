/*
 * slave.c
 *
 * Created: 11/23/2015 4:07:32 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "text_LCD.h"
#include "TWI.h"

int main(void)
{
	DDRD=0x00;
	PORTD=0xFF;
	Device_Addr=PIND>>6;
	Init_TWI();
	init_lcd();
	sei();
	//Device_Addr=PIND>>6;
	for(int i=0;i<50;i++) slave_trans_data[i]=i;
	_delay_ms(200);
	movecursor(1,1);
	putstr_lcd("device addr :",13);
	printnumber_lcd(Device_Addr);
	
	movecursor(2,1);
	putstr_lcd("data :",6);

    while(1)
    {
		movecursor(2,8);
		printnumber_lcd(slave_trans_data[Tr_byte_num]);
        
    }
	return 0;
}