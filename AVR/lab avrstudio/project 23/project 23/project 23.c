/*
 * project_23.c
 *
 * Created: 5/24/2016 12:21:28 PM
 *  Author: Duc Khanh
 */ 

/*
 * project_21.c
 *
 * Created: 5/23/2016 9:51:46 PM
 *  Author: Duc Khanh
 */ 

#define F_CPU	4000000UL
#include <avr/delay.h>
#include <avr/eeprom.h>
#include <avr/io.h>
 

void ghi_byte_command(unsigned char cmnd);
void ghi_byte_DDRAM(unsigned char data);
void LCD_init();
void move(uint8_t dong, uint8_t cot);
void LCD_print(char *string);
void LCD_nhapnhay();
void LCD_dich(unsigned char direction);
 
#define LCD_DATA_PORT	PORTA
#define LCD_DATA_DDR	DDRA
#define LCD_DATA_PIN	PINA
 
#define LCD_CNTRL_PORT	PORTC
#define LCD_CNTRL_DDR	DDRC
#define LCD_CNTRL_PIN	PINC
 
#define LCD_RS_PIN		0
#define LCD_RW_PIN		1
#define LCD_ENABLE_PIN	2
 
int main(void)
{
	unsigned char i; 
    unsigned int number;
    LCD_init();
	
	LCD_print("khanh");
    
	if(bit)
	
	

 

 
}
void ghi_byte_command(unsigned char cmnd)
{
	LCD_DATA_PORT = cmnd;
	LCD_CNTRL_PORT &= ~(1<<LCD_RW_PIN);
	LCD_CNTRL_PORT &= ~(1<<LCD_RS_PIN);
 
	LCD_CNTRL_PORT |= (1<<LCD_ENABLE_PIN);
	_delay_us(2);
	LCD_CNTRL_PORT &= ~(1<<LCD_ENABLE_PIN);
	_delay_us(100);
}
 
void ghi_byte_DDRAM(unsigned char data)
{
	LCD_DATA_PORT = data;
	LCD_CNTRL_PORT &= ~(1<<LCD_RW_PIN);
	LCD_CNTRL_PORT |= (1<<LCD_RS_PIN);
 
	LCD_CNTRL_PORT |= (1<<LCD_ENABLE_PIN);
	_delay_us(2);
	LCD_CNTRL_PORT &= ~(1<<LCD_ENABLE_PIN);
	_delay_us(100);
}
 
 
void LCD_init()
{
	LCD_CNTRL_DDR = 0xFF;
	LCD_CNTRL_PORT = 0x00;
	LCD_DATA_DDR = 0xFF;
	LCD_DATA_PORT = 0x00;
 
	_delay_ms(10);
	ghi_byte_command(0x38);
	ghi_byte_command(0x0C);
	ghi_byte_command(0x01);
	_delay_ms(10);
	ghi_byte_command(0x06);
}
 

void move(/*unsigned char*/ uint8_t dong, /*unsigned char*/ uint8_t cot)
{
	//unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};
 
	//ghi_mang_byte(firstAddress[y-1] + x-1);
	//_delay_ms(10);	
	
	uint8_t x;
	x=64*(dong-1)+(cot-1)+0x80;
	
	ghi_byte_command(x);
	
	_delay_ms(10);
}
 
void LCD_print(char *string)
{
	unsigned char i;
 
	while(string[i]!=0)
	{
		ghi_byte_DDRAM(string[i]);
		i++;
	}
}
 
void LCD_nhapnhay()
{
	ghi_byte_command(0x08);
	_delay_ms(250);
	ghi_byte_command(0x0C);
	_delay_ms(250);
}
 
void LCD_dich(unsigned char direction)
{
	if(direction == 0)
		ghi_byte_command(0x18);
	else
		ghi_byte_command(0x1C);
 
	_delay_ms(500);
}

void printnumber_lcd(uint8_t number){
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
		ghi_byte_DDRAM(e+48);
	}
	else if(a==0 && b==0 && c==0){
		ghi_byte_DDRAM(d+48);
		ghi_byte_DDRAM(e+48);
	}
	else if(a==0 && b==0){
		ghi_byte_DDRAM(c+48);
		ghi_byte_DDRAM(d+48);
		ghi_byte_DDRAM(e+48);
	}
	else if(a==0){
		ghi_byte_DDRAM(b+48);
	    ghi_byte_DDRAM(c+48);
		ghi_byte_DDRAM(d+48);
		ghi_byte_DDRAM(e+48);
	}
	else if(a!=0 && b!=0 && c!=0 && d!=0){
		ghi_byte_DDRAM(a+48);
		ghi_byte_DDRAM(b+48);
	    ghi_byte_DDRAM(c+48);
		ghi_byte_DDRAM(d+48);
		ghi_byte_DDRAM(e+48);
	} 
 }

