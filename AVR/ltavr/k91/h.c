/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 1/12/2016
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>

#define KEY4x4_COL1 PIND.4
#define KEY4x4_COL2 PIND.5
#define KEY4x4_COL3 PIND.6
#define KEY4x4_COL4 PIND.7

#define KEY4x4_ROW1 PORTD.3
#define KEY4x4_ROW2 PORTD.2
#define KEY4x4_ROW3 PORTD.1
#define KEY4x4_ROW4 PORTD.0  

void main(void)
{
DDRD=0x0F;
PORTD=0xFF;
     (KEY4x4_COL1==0)|(KEY4x4_COL2==0)|(KEY4x4_COL3==0)|(KEY4x4_COL4==0);
     
}