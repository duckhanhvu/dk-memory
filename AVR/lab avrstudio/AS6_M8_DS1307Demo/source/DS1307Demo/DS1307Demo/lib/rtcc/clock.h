/******************************************************************************

                          eXtreme Electronics xAPI(TM)
						  ----------------------------
xAPI is a Powerful but easy to use C library to program the xBoard(TM)
series of AVR development board. The library has support for commonly use tasks
like:-

*LCD interfacing
*MUXED 7 segment displays.
*Remote Control
*Serial Communication
*DC Motor Controls with Speed Control
*Analog Measurement for Sensor Interface.
*Temperature Measurement.
*I2C Communication.
*EEPROM Interface
*Real Time Clock (RTC Interface)

The APIs are highly documented and easy to use even by a beginner.

For More Info Log On to 
www.eXtremeElectronics.co.in

Copyright 2008-2009 eXtreme Electronics India

                                    Clock Core
						           ----------
This module is used for interfacing with DS1307 based clock module.
The library provide easy to use to use functions to get and set time.

For More information please see supplied tutorials and videos.

                                     NOTICE
									--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

*******************************************************************************/

#ifndef _CLOCK_H
#define _CLOCK_H

typedef uint8_t bool;

#include "ds1307.h"
#include "clock.h"

//Initialization Function
bool ClockInit();

//Get Function
uint8_t GetSecond();
uint8_t GetMinute();
uint8_t GetHour();
uint8_t GetAmPm();

//Set Function
bool SetSecond(uint8_t sec);
bool SetMinute(uint8_t min);
bool SetHour(uint8_t hr);
bool SetAmPm(bool pm);	


//Time as string e.g. "12:45:33 PM"
bool GetTimeString(char *Time);

//Ask user to enter Current Time using LCD and Keypad
//Then saves them to DS1307 RTC module.
bool SetTimeAuto();


#endif
