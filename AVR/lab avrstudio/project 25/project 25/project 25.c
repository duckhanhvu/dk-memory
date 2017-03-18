/*
 * project_25.c
 *
 * Created: 7/1/2016 9:23:19 AM
 *  Author: Duc Khanh
 */ 


#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

 
#define LCD_DATA PORTA //LCD data port
 
#define ctrl PORTC
#define en PC2 // enable signal
#define rw PC1 // read/write signal
#define rs PC0 // register select signal

volatile unsigned char x;
volatile uint8_t val=0;

void printnumber_lcd(uint8_t number);
void LCD_blink();
void LCD_scroll(unsigned char direction);
void putstr_lcd(unsigned char *str, unsigned int lenght);
void LCD_goto(unsigned char dong, unsigned char cot); 
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
 
int main()
{
	uint8_t b=0;
	DDRD=0x00;
	PORTD=0xFF;	
	
DDRA=0xff; 
DDRC=0x07; 
    MCUCR|=(1<<ISC11)|(1<<ISC01); //c? 2 ng?t là ng?t c?nh xu?ng     
    GICR    |=(1<<INT1)|(1<<INT0);   
init_LCD(); // initialization of LCD
sei();  
_delay_ms(50); // delay of 50 mili seconds

    
	
	
	val=eeprom_read_byte((uint8_t*)46);
	LCD_goto(1,12);
	printnumber_lcd(val);
while(1){
	 if(bit_is_clear(PIND,PD4)){
		 eeprom_write_byte((uint8_t *)46,val);
		 LCD_goto(1,2);
		 putstr_lcd("khanh",5); 
	 }

	 } 
return 0;
}

ISR(INT0_vect){
	val++;
	//eeprom_write_byte((uint8_t *)46,val);
	LCD_goto(1,12);
	printnumber_lcd(val);
}
ISR(INT1_vect){
	val--;
	//eeprom_write_byte((uint8_t *)46,val);
	LCD_goto(1,12);
	printnumber_lcd(val);
}
void init_LCD(void)
{
LCD_cmd(0x38); // initialization of 16X2 LCD in 8bit mode
_delay_ms(1);
 
LCD_cmd(0x01); // clear LCD
_delay_ms(1);
 
LCD_cmd(0x0C); // cursor ON
_delay_ms(1);

    LCD_cmd(0x06);
   
	_delay_ms(1);	
 

return;
}
void clear_lcd(){
	
	LCD_cmd(0x01);
	
	_delay_ms(1);
} 
void LCD_cmd(unsigned char cmd)
{
LCD_DATA=cmd;
ctrl =(0<<rs)|(0<<rw)|(1<<en); 
_delay_ms(1);
ctrl =(0<<rs)|(0<<rw)|(0<<en); 
_delay_ms(50);
return;
}
 
void LCD_write(unsigned char data)
{
LCD_DATA= data;
ctrl = (1<<rs)|(0<<rw)|(1<<en); 
_delay_us(2);
ctrl = (1<<rs)|(0<<rw)|(0<<en); 
_delay_us(100); 
return ;
}
void LCD_print(char *string)
{
	unsigned char i;

	while(string[i]!=0)
	{
		LCD_write(string[i]);
		i++;
	}
	return;
} 
void LCD_write_string(unsigned char *str) //store address value of the string in pointer *str
{
int i=0;
while(str[i]!='\0') // loop will go on till the NULL character in the string 
{
LCD_write(str[i]); // sending data on LCD byte by byte
i++;
  }
return;
}
void LCD_goto(unsigned char dong, unsigned char cot)
{
	//unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};
 
	//LCD_send_command(firstAddress[y-1] + x-1);
	//_delay_ms(10);	
	
	unsigned char x;
	x=64*(dong-1)+(cot-1)+0x80;
	//clearbit(CTRL,RS);
	LCD_cmd(x);
	
	_delay_ms(1);
	return;
}
void putstr_lcd(unsigned char *str, unsigned int lenght){
	unsigned char i;
	for(i=0;i<lenght;i++){
		if(*(str+i)>0){ 
			LCD_write(*(str+i));
			}
		else LCD_write(0);	
}
}
void LCD_scroll(unsigned char direction)
{
	if(direction == 0)
		LCD_cmd(0x18);
	else
		LCD_cmd(0x1C);
 
	_delay_ms(500);
}
void LCD_blink()
{
	LCD_cmd(0x08);
	_delay_ms(250);
	LCD_cmd(0x0C);
	_delay_ms(250);
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
	/*
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
		LCD_write(e+48);
	}
	else if(a==0 && b==0 && c==0){
		LCD_write(d+48);
		LCD_write(e+48);
	}
	else if(a==0 && b==0){
		LCD_write(c+48);
		LCD_write(d+48);
		LCD_write(e+48);
	}
	else if(a==0){
		LCD_write(b+48);
	    LCD_write(c+48);
		LCD_write(d+48);
		LCD_write(e+48);
	}
	else if(a!=0 && b!=0 && c!=0 && d!=0){
		LCD_write(a+48);
		LCD_write(b+48);
	    LCD_write(c+48);
		LCD_write(d+48);
		LCD_write(e+48);
	} 
 }
*/
	uint8_t a,b;
	 a=number/10;
	 LCD_write(a+48);
	 b=number%10;
	 LCD_write(b+48);
	
	}	
 
/* 
 #include <avr/eeprom.h>   
 int main(void)  {      
 uint8_t ByteOfData;      
 uint16_t WordOfData;     
 uint8_t StringOfData[10];       //??c byte có ??a ch? 46     
 ByteOfData = eeprom_read_byte((uint8_t*)46);      //??c word ? ??a ch? 20     
 WordOfData = eeprom_read_word((uint16_t*)20);       //??c block 10 byte b?t ??u t? ??a ch? 12     
 eeprom_read_block((void*)&StringOfData, (const void*)12, 10);     
 eeprom_write_byte (uint8_t *addr, uint8_t value)  
 return 0; }
 */