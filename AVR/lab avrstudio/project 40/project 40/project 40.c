/******************************************************************************
Simple digital clock using DS1307 chip interfaced with ATmega8. 

MCU: ATmega8A
Speed: 16MHz External Crystal
Fuse Low: FF
Fuse High: C9

Written By
 Avinash Gupta
Contact
 gmail@avinashgupta.com

For more interesting microcontroller tutorials and projects. Please visit
http://www.extremeelectronics.co.in

NOTICE:
PROGRAM SAMPLE PROVIDED FOR SELF LEARNING PURPOSE ONLY!
NO PART OF THIS WORK SHOULD BE USED IN ANY COMMERCIAL PROJECTS OR IN ANY 
TEACHING INSTITUTES FOR TEACHING THEIR STUDENTS
NO PART OF THIS WORK SHOULD BE PUBLISHED IN ANY FORM LIKE PRINTED OR ELECTRONIC
MEDIA

COPYRIGHT (C) 2008-2015 EXTREME ELECTRONICS, INDIA


If this helped you, please leave a 5 star review @ http://ex-tr.me/review

I know most Indians won't do this! They just know how to take, but not how to give!
But we have your mobile number and email with us! And we maintain a database of
all mobiles and email IDs. And it takes only a click to ban anyone. Once banned,
the user will not be able to download anything from our servers!

Am I threatening you? Well, the answer is yes! 

After 7 years of publishing my works online and helping more than 3000 persons 
on daily basis, and still finding lack of loyalty in them, I was forced to develop 
this system.

I spent lots of time and money to develop this system just to keep *****rs away!

******************************************************************************/


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lib/lcd/lcd_hd44780_avr.h"
#include "lib/rtcc/clock.h"
#include "lib/keypad/keypad.h"

typedef bool uint8_t;

#define TRUE	1
#define FALSE	0

bool SetTime();

int main(void)
{
	//Initialize the LCD module
	LCDInit(LS_NONE);
	
	//Write a intro text
	LCDWriteFStringXY(0,0,PSTR("    eXtreme"));
	LCDWriteFStringXY(0,1,PSTR("  Electronics"));
	
	_delay_ms(2000);
	
	LCDClear();
	//Initialize the Clock Module
	if(!ClockInit())
	{
		//If we fail to initialize then warn user
		LCDClear();
		LCDWriteString("Error !");
		LCDWriteStringXY(0,1,"DS1307 Not Found");

		while(1); //Halt
	}
	
	//Initialize the keypad
	KeypadInit();
	
	//Now Read and display time
	char Time[12];	//hh:mm:ss AM/PM
	
	while(1)
	{
		LCDClear();
		
		LCDWriteFString(PSTR("  DS1307 Demo"));
		
		//Loop, read time from chip and show on lcd
		while(1)
		{
		
			//Get the Current Time as a String
			if(!GetTimeString(Time))
			{
				/*
				If return value is false then some error has occurred
			
				Check
				 ->DS1307 Installed Properly
				*/

				LCDClear();
				LCDWriteString("xBoard MINI v2.0");
				LCDWriteStringXY(0,1,"I2C i/o Error !");
			
				while(1);//halt
			}

			//Display it
			LCDWriteStringXY(2,1,Time);
		
			//Check input for ENTER key
			uint8_t key = GetKeypadCmd(FALSE);
		
			if(key==KEY_ENTER)
			{
				//Enter time setup
				SetTime();
				
				break;
			}
		
			_delay_ms(500);
		}		
		
	}
	
}

bool SetTime()
{

	uint8_t hr,min,sec,am_pm;

	//Get Seconds
	sec=GetSecond();

	//Get Minute
	min=GetMinute();

	//Get Hour
	hr=GetHour();

	//Get AM/PM
	am_pm=GetAmPm();

	//If Hour is 0 make it 12, as 00:00:00 invalid time
	if(hr==0 && min==0 && sec==0) hr=12;

	uint8_t sel=0;
	
	bool done=FALSE;

	while(!done)
	{
		LCDClear();

		LCDWriteString("00:00:00    <OK>");
		
		LCDWriteIntXY(0,0,hr,2);
		LCDWriteIntXY(3,0,min,2);
		LCDWriteIntXY(6,0,sec,2);

		if(am_pm)
		{
			LCDWriteStringXY(9,0,"PM");
		}
		else
		{
			LCDWriteStringXY(9,0,"AM");
		}

		//Draw Pointer
		LCDWriteStringXY(sel*3,1,"^^");
		
		uint8_t key=GetKeypadCmd(1);

		switch(key)
		{
			case KEY_RIGHT:
			
				if(sel==0)
				{
					//Hour
					if(hr==12)
					{
						hr=1;
					}
					else
					{
						hr++;
					}
				}

				if(sel==1)
				{
					//Min
					if(min==59)
					{
						min=0;
					}
					else
					{
						min++;
					}
				}

				if(sel==2)
				{
					//Sec
					if(sec==59)
					{
						sec=0;
					}
					else
					{
						sec++;
					}
				}

				if(sel==3)
				{
					//AM-PM
					if(am_pm==0)
					{
						am_pm=1;
					}
					else
					{
						am_pm=0;
					}
				}
				if(sel == 4)
				{
					//OK
					done=TRUE;
				}
			
			break;
			
			case KEY_LEFT:
			
				if(sel==0)
				{
					//Hour
					if(hr==1)
					{
						hr=12;
					}
					else
					{
						hr--;
					}
				}

				if(sel==1)
				{
					//Min
					if(min==0)
					{
						min=59;
					}
					else
					{
						min--;
					}
				}

				if(sel==2)
				{
					//Sec
					if(sec==0)
					{
						sec=59;
					}
					else
					{
						sec--;
					}
				}

				if(sel==3)
				{
					//AM-PM
					if(am_pm==0)
					{
						am_pm=1;
					}
					else
					{
						am_pm=0;
					}
				}
				if(sel == 4)
				{
					//OK
					done=TRUE;
				}
			
			break;
			
			case KEY_ENTER:
			
			//Change Selection
			if(sel==4)
				sel=0;
			else
				sel++;
			
			break;
		}

	}

	//Now write time back to RTC Module
	if(!SetSecond(sec))
	{
		LCDClear();
		LCDWriteString("Error !");
		LCDWriteStringXY(0,1,"Cannot Set Time");
		return 0;
	}
	if(!SetMinute(min))
	{
		LCDClear();
		LCDWriteString("Error !");
		LCDWriteStringXY(0,1,"Cannot Set Time");
		return 0;
	}
	if(!SetHour(hr))
	{
		LCDClear();
		LCDWriteString("Error !");
		LCDWriteStringXY(0,1,"Cannot Set Time");
		return 0;
	}
	if(!SetAmPm(am_pm))
	{
		LCDClear();
		LCDWriteString("Error !");
		LCDWriteStringXY(0,1,"Cannot Set Time");
		return 0;
	}


	//Show Message
	LCDClear();
	LCDWriteString("Message !");
	LCDWriteStringXY(0,1,"Main Time Set");

	uint8_t i;
	for(i=0;i<100;i++)
	_delay_loop_2(0);
	
	return 1;

}