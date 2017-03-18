/*
 * project_15.c
 *
 * Created: 2/3/2u016 9:04:44 PM
 *  Author: Duc Khanh
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/sfr_defs.h>
#include "text_LCD.h"
#include <avr/interrupt.h>
#include "setandclear_bit.h"
#include "twi.h"
#include "ds1307.h"

#define DS1307_SlA   0xd0
#define TWI_W        0
#define TWI_R        1

#define F_SCL 100000L
#define READ 1
#define TW_START        0xA4              // send start condition (TWINT,TWSTA,TWEN)
#define TW_STOP         0x94              // send stop condition (TWINT,TWSTO,TWEN)
#define TW_ACK          0xC4              // return ACK to slave
#define TW_NACK         0x84              // don't return ACK to slave
#define TW_SEND         0x84              // send data (TWINT,TWEN)
#define TW_READY        (TWCR & 0x80)     // ready when TWINT returns to logic 1
#define TW_STATUS       (TWSR & 0xF8)     // returns value of status register
#define I2C_Stop()      TWCR = TW_STOP    // inline macro for stop condition

#define TWI_clear_TWINT   (1<<TWINT)|(1<<TWEN)
#define TWI_Read_ACK      (1<<TWINT)|(1<<TWEA)|(1<<TWEN)
#define TWI_start         (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_stop          (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)

typedef uint8_t byte;
typedef int8_t sbyte;

#define DS1307 0xD0 // I2C bus address of DS1307 RTC
#define SECONDS_REGISTER 0x00
#define MINUTES_REGISTER 0x01
#define HOURS_REGISTER 0x02
#define DAYOFWK_REGISTER 0x03
#define DAYS_REGISTER 0x04
#define MONTHS_REGISTER 0x05
#define YEARS_REGISTER 0x06
#define CONTROL_REGISTER 0x07
#define RAM_BEGIN 0x08
#define RAM_END 0x3F

volatile uint8_t data[7]={0};
volatile uint8_t giay=55, phut=23, gio=3;
volatile uint8_t day=1, ngay=11,thang=2,nam=9;
volatile unsigned int count=0;
volatile uint8_t a=0, b=0;
//khoi dong TWI(I2C)
void Init_TWI(void){
	TWBR=32;
	TWSR=0x00;
	TWCR=(1<<TWINT)|(1<<TWEN);
}
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
byte I2C_Detect(byte addr)
// look for device at specified address; return 1=found, 0=not found
{
TWCR = TW_START; // send start condition
while (!TW_READY); // wait
TWDR = addr; // load device's bus address
TWCR = TW_SEND; // and send it
while (!TW_READY); // wait
return (TW_STATUS==0x18); // return 1 if found; 0 otherwise
}

void I2C_Start (byte slaveAddr)
{
I2C_Detect(slaveAddr);
}

byte I2C_FindDevice(byte start)
// returns with address of first device found; 0=not found
{
for (byte addr=start;addr<0xFF;addr++) // search all 256 addresses
{
if (I2C_Detect(addr)) // I2C detected?
return addr; // leave as soon as one is found
}
return 0; // none detected, so return 0.
}

byte I2C_Write (byte data) // sends a data byte to slave
{
TWDR = data; // load data to be sent
TWCR = TW_SEND; // and send it
while (!TW_READY); // wait
return (TW_STATUS!=0x28);
}
byte I2C_ReadACK () // reads a data byte from slave
{
TWCR = TW_ACK; // ack = will read more data
while (!TW_READY); // wait
return TWDR;
//return (TW_STATUS!=0x28);
}
byte I2C_ReadNACK () // reads a data byte from slave
{
TWCR = TW_NACK; // nack = not reading more data
while (!TW_READY); // wait
return TWDR;
//return (TW_STATUS!=0x28);
}


void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data){
I2C_Start(busAddr); // send bus address
I2C_Write(deviceRegister); // first byte = device register address
I2C_Write(data); // second byte = data for device register
I2C_Stop();
}

byte I2C_ReadRegister(byte busAddr, byte deviceRegister)
{
byte data = 0;
I2C_Start(busAddr); // send device address
I2C_Write(deviceRegister); // set register pointer
I2C_Start(busAddr+READ); // restart as a read operation
data = I2C_ReadNACK(); // read the register data
I2C_Stop(); // stop
return data;
}
void DS1307_GetTime()
// returns hours, minutes, and seconds in BCD format
{
data[2] = I2C_ReadRegister(DS1307,HOURS_REGISTER);
data[1] = I2C_ReadRegister(DS1307,MINUTES_REGISTER);
data[0] = I2C_ReadRegister(DS1307,SECONDS_REGISTER);

}

void DS1307_GetDate()
// returns months, days, and years in BCD format
{
data[5] = I2C_ReadRegister(DS1307,MONTHS_REGISTER);
data[4] = I2C_ReadRegister(DS1307,DAYS_REGISTER);
data[6] = I2C_ReadRegister(DS1307,YEARS_REGISTER);
}
void SetTimeDate()
// simple, hard-coded way to set the date.
{
I2C_WriteRegister(DS1307,MONTHS_REGISTER, data[5]);
I2C_WriteRegister(DS1307,DAYS_REGISTER, data[4]);
I2C_WriteRegister(DS1307,YEARS_REGISTER, data[6]);
I2C_WriteRegister(DS1307,HOURS_REGISTER, data[2]); // add 0x40 for PM
I2C_WriteRegister(DS1307,MINUTES_REGISTER, data[1]);
I2C_WriteRegister(DS1307,SECONDS_REGISTER, data[0]);
}
/*
//ham set dia chi thanh ghi cua DS1307
uint8_t set_addr_register_DS (uint8_t addr){
	TWCR=TWI_start;
	while((TWCR&0x80)==0x00);
	if((TWSR&0xF8)!=0x08) return TWSR;
	
	TWDR=(DS1307_SlA<<1)+TWI_W;
	TWCR=(TWI_clear_TWINT);
	while((TWCR&0x80)==0x00);
	if((TWSR&0xF8)!=0x18) return TWSR;

	TWDR=addr;
	TWCR=(TWI_clear_TWINT);
	while((TWCR&0x80)==0x00);
	if((TWSR&0xF8)!=0x28) return TWSR;

    TWCR=TWI_stop;
	return 0;
}

//ham ghi du lieu can thiet lap vao DS1307
uint8_t TWI_write_DS(uint8_t addr, uint8_t DATA){
	unsigned int i;
	TWCR=TWI_start;
	//while((TWCR&0x80)==0x00);
	while(!(TWCR & (1<<TWINT)));
	//if((TWSR&0xF8)!=0x08) return TWSR;
	
	TWDR=(DS1307_SlA<<1)+TWI_W;
	TWCR=(TWI_clear_TWINT);
	//while((TWCR&0x80)==0x00);
	while(!(TWCR & (1<<TWINT)));
	//if((TWSR&0xF8)!=0x18) return TWSR;	
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		return 1;
	}
	else
		return 0;	//Error
	
	TWDR=addr;
	TWCR=(TWI_clear_TWINT);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		return 1;
	}
	else
		return 0;	//Error
	
	
	TWDR=DATA;
	TWCR=TWI_clear_TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
		{
			return 1;
		}
	else
			return 0;	//Error
		
	
	TWCR=TWI_stop;
	return 1;
}	

//ham doc du lieu tu DS1307
uint8_t TWI_read_DS(uint8_t addr, uint8_t DATA){
	unsigned int i;
	TWCR=TWI_start;
	while(!(TWCR & (1<<TWINT)));
	
	TWDR=(DS1307_SlA<<1)+TWI_W;
	TWCR=TWI_clear_TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		return 1;
	}
	else
		return 0;	//Error
		
	TWDR=addr;
	TWCR=(TWI_clear_TWINT);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		return 1;
	}
	else
		return 0;	//Error	
       	
	
	TWCR=TWI_start;
	while(!(TWCR & (1<<TWINT)));
	
	TWDR=(DS1307_SlA<<1)+TWI_R;
	TWCR=TWI_clear_TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		return 1;
	}
	else
		return 0;	//Error
		
	TWCR=TWI_Read_ACK;
	while(!(TWCR & (1<<TWINT)));
	DATA=TWDR;
	
	TWCR=TWI_clear_TWINT;
	while(!(TWCR & (1<<TWINT)));
	
	TWCR=TWI_stop;
	return 1;
}
*/

void Display(void){
	
	 giay=BCD_Dec(data[0]&0x7F);
	 phut=BCD_Dec(data[1]);
	 gio=BCD_Dec(data[2]&0x1F);// su dung mode 12h
	 
	 ngay=BCD_Dec(data[4]);
	 thang=BCD_Dec(data[5]);
	 nam=BCD_Dec(data[6]);
	 
	 
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
	 if(bit_is_clear(data[2],5)) putchar_lcd('A');
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
volatile uint8_t x;
int main(void)
{
	init_lcd();

	//tao khoang thoi gian duoi 50ms bang timer 0;
	
	TCCR0=(1<<CS02)|(0<<CS01)|(1<<CS00);
	TIMSK=(1<<TOIE0);
	sei();
	//
	Init_TWI();
	
	data[0]=Dec_BCD(21);
	/*data[1]=Dec_BCD(phut);
	data[2]=Dec_BCD(gio)|(1<<6)|(1<<5);
	data[3]=Dec_BCD(day);
	data[4]=Dec_BCD(ngay);
	data[5]=Dec_BCD(thang);
	data[6]=Dec_BCD(nam);*/
	
	Init_TWI();		
	
	//ghi cac byte data vao chip DS1307
	//TWI_write_DS(0x00,data,7);
	//SetTimeDate();
	I2C_WriteRegister(DS1307,SECONDS_REGISTER, data[0]);		
	_delay_ms(2);
	//set dia chi bat dau doc
	//set_addr_register_DS(0x00);
	
	//doc du lieu tu DS1307
	data[0] = I2C_ReadRegister(DS1307,SECONDS_REGISTER);
	x=BCD_Dec(data[0]&0x7F);
	//DS1307_GetTime();
	//DS1307_GetDate();	
	//Display();
	movecursor(1,1);
	printnumber_lcd(x);
    while(1)
    {    
    }
	return 0;
}

ISR(TIMER0_OVF_vect){
	count++;
	
	if(count==11){

	set_addr_register_DS(0x00);
	_delay_ms(1);
	//doc du lieu tu DS1307
	DS1307_GetTime();
	DS1307_GetDate();	
	if(BCD_Dec(data[0]&0x7F)!=giay){
	data[0] = I2C_ReadRegister(DS1307,SECONDS_REGISTER);
	giay=BCD_Dec(data[0]&0x7F);
		movecursor(1,14);                                                         
		putchar_lcd("  ");
		movecursor(1,14);
		printnumber_lcd(giay);
		if(giay==0) Display();
	}
	count=0;
	}
}