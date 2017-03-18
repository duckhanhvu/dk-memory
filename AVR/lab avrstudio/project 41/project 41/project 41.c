/*
 * project_41.c
 *
 * Created: 1/24/2017 20:47:52
 *  Author: duckhanh
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/delay.h>
#include "text_LCD.h"

typedef uint8_t byte;
typedef int8_t sbyte;

#define F_SCL 100000L
#define READ            1
#define TW_START        0xA4              // send start condition (TWINT,TWSTA,TWEN)
#define TW_STOP         0x94              // send stop condition (TWINT,TWSTO,TWEN)
#define TW_ACK          0xC4              // return ACK to slave
#define TW_NACK         0x84              // don't return ACK to slave
#define TW_SEND         0x84              // send data (TWINT,TWEN)
#define TW_READY        (TWCR & 0x80)     // ready when TWINT returns to logic 1
#define TW_STATUS       (TWSR & 0xF8)     // returns value of status register
#define I2C_Stop()      TWCR = TW_STOP    // inline macro for stop condition


#define DS1307           0xD0 // I2C bus address of DS1307 RTC
#define SECONDS_REGISTER 0x00
#define MINUTES_REGISTER 0x01
#define HOURS_REGISTER   0x02
#define DAYOFWK_REGISTER 0x03
#define DAYS_REGISTER    0x04
#define MONTHS_REGISTER  0x05
#define YEARS_REGISTER   0x06
#define CONTROL_REGISTER 0x07
#define RAM_BEGIN        0x08
#define RAM_END          0x3F

volatile uint8_t  ngay=3, thang=5, nam=2016, gio=3, phut=20, giay=30; 
void I2C_Init()
// at 16 MHz, the SCL frequency will be 16/(16+2(TWBR)), assuming prescalar of 0.
// so for 100KHz SCL, TWBR = ((F_CPU/F_SCL)-16)/2 = ((16/0.1)-16)/2 = 144/2 = 72.
{
TWSR = 0; // set prescalar to zero
TWBR = ((F_CPU/F_SCL)-16)/2; // set SCL frequency in TWI bit register
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
gio = I2C_ReadRegister(DS1307,HOURS_REGISTER);
phut = I2C_ReadRegister(DS1307,MINUTES_REGISTER);
giay = I2C_ReadRegister(DS1307,SECONDS_REGISTER);
if (gio & 0x40) // 12hr mode:
gio &= 0x1F; // use bottom 5 bits (pm bit = temp & 0x20)
else gio &= 0x3F; // 24hr mode: use bottom 6 bits
}

void DS1307_GetDate()
// returns months, days, and years in BCD format
{
thang = I2C_ReadRegister(DS1307,MONTHS_REGISTER);
ngay = I2C_ReadRegister(DS1307,DAYS_REGISTER);
nam = I2C_ReadRegister(DS1307,YEARS_REGISTER);
}

void SetTimeDate()
// simple, hard-coded way to set the date.
{
I2C_WriteRegister(DS1307,MONTHS_REGISTER, Dec_BCD(thang));
I2C_WriteRegister(DS1307,DAYS_REGISTER, Dec_BCD(ngay));
I2C_WriteRegister(DS1307,YEARS_REGISTER, Dec_BCD(nam));
I2C_WriteRegister(DS1307,HOURS_REGISTER, Dec_BCD(gio)+0x40); // add 0x40 for PM
I2C_WriteRegister(DS1307,MINUTES_REGISTER, Dec_BCD(phut));
I2C_WriteRegister(DS1307,SECONDS_REGISTER, Dec_BCD(giay));
}
void LCD_TwoDigits(byte data)
// helper function for WriteDate()
// input is two digits in BCD format
// output is to LCD display at current cursor position
{
byte temp = data>>4;
putchar_lcd(temp+'0');
data &= 0x0F;
putchar_lcd(data+'0');
}

void WriteDate()
{
byte *months, *days, *years;
DS1307_GetDate();
printnumber_lcd(BCD_Dec(thang));
putchar_lcd('/');
printnumber_lcd(BCD_Dec(ngay));
putchar_lcd('/');
printnumber_lcd(BCD_Dec(nam));
}

void WriteTime()
{
byte *hours, *minutes, *seconds;
DS1307_GetTime();
printnumber_lcd(BCD_Dec(gio));
putchar_lcd(':');
printnumber_lcd(BCD_Dec(phut));
putchar_lcd(':');
printnumber_lcd(BCD_Dec(giay));
}

void LCD_TimeDate()
{
movecursor(1,1) ; WriteTime();
movecursor(2,1) ; WriteDate();
}

void MainLoop()
{
while(1)
{
LCD_TimeDate(); // put time & date on LCD
_delay_ms(1000); // one second between updates
}
}

int main(void)
{
	DDRC=0x00;
	PORTC=0x00;
    init_lcd(); // initialize HD44780 LCD controller

	I2C_Init(); // set I2C clock frequency

	_delay_ms(400);
	clear_lcd();
	MainLoop();
    return 0;
}
