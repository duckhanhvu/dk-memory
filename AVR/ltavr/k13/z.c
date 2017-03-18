/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 9/2/2015
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
#include <mega16.h>
#include <delay.h>


#define LE1 PORTA.3
#define LE2 PORTA.4

#define PORT_LED7 PORTB

#define KEY4x4_COL1 PIND.4
#define KEY4x4_COL2 PIND.5
#define KEY4x4_COL3 PIND.6
#define KEY4x4_COL4 PIND.7

#define KEY4x4_ROW1 PORTD.3
#define KEY4x4_ROW2 PORTD.2
#define KEY4x4_ROW3 PORTD.1
#define KEY4x4_ROW4 PORTD.0  


static unsigned char LED7_Buffer[8];
static unsigned char chu_so[10]={0b01111110,0b00000110,0b01101101,0b01001111,0b00010111,0b01011011,0b01111011,0b00001110,0b01111111,0b01011111}  ;
void LED7_cacucode(unsigned long number){
unsigned char i,j,flag=0;
unsigned long int temp;
for(i=7;i>0;i--){
temp=1;
for(j=i;j>0;j--){
temp *=10;
}
if(flag) LED7_Buffer[i]=chu_so[number/temp];
else
{
if(number/temp) {
 LED7_Buffer[i]=chu_so[number/temp];
 flag=1;
}
else
LED7_Buffer[i]=0xFF;
}
number=number%temp;
}
LED7_Buffer[0]=chu_so[number/temp];
}

void LED7_OnLED(unsigned char point)
{
PORT_LED7=0xFF;
LE1=1;
LE1=0;
PORT_LED7=0x80>>point;
LE2=1;
LE2=0;
PORT_LED7=LED7_Buffer[point];
LE1=1;
LE1=0;
}
void LED7_Display(unsigned long int value){
unsigned char i;
LED7_cacucode(value);
for(i=0;i<8;i++){
LED7_OnLED(i);
delay_ms(10);
}
}
static unsigned char KEY_4x4[4][4]={1,2,3,4,
                                    5,6,7,8,
                                    9,10,11,12,
                                    13,14,15,16,};
unsigned char KEY4x4_Ispush(void){
if((KEY4x4_COL1==0)|(KEY4x4_COL2==0)|(KEY4x4_COL3==0)|(KEY4x4_COL4==0))
return 1;
else return 0;
}
void KEY4x4_checkROW(unsigned char i){
KEY4x4_ROW1 =KEY4x4_ROW2 =KEY4x4_ROW3 =KEY4x4_ROW4 =1;
if(i==0){
    KEY4x4_ROW1=0;
}
else if(i==1){
    KEY4x4_ROW2=0;
}
else if(i==2){
    KEY4x4_ROW3=0;
}
else{
    KEY4x4_ROW4=0;
}   
}
unsigned char KEY4x4_Getkey(void){
unsigned char i;
KEY4x4_ROW1=0;
KEY4x4_ROW2=0;
KEY4x4_ROW3=0;
KEY4x4_ROW4=0;
if(KEY4x4_Ispush()){
delay_ms(5);
if(KEY4x4_Ispush()){
for(i=0;i<4;i++){
KEY4x4_checkROW(i);
if(!KEY4x4_COL1)  return KEY_4x4[i][0];
if(!KEY4x4_COL2)  return KEY_4x4[i][1];
if(!KEY4x4_COL3)  return KEY_4x4[i][2];
if(!KEY4x4_COL4)  return KEY_4x4[i][3];
}
}
}
return 0;
}


void main (void){ 
unsigned char key;
unsigned long int value;  
PORTA=0x18;
DDRA=0x18;

PORTB=0xFF;
DDRB=0xFF;

PORTC=0x00;
DDRC=0x00;

PORTD=0xFF;
DDRD=0x0F;

TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;


TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

MCUCR=0x00;
MCUCSR=0x00;

TIMSK=0x00;

UCSRB=0x00;

ACSR=0x80;
SFIOR=0x00;

ADCSRA=0x00;

SPCR=0x00;

TWCR=0x00;

                              
while (1)
      {
      // Place your code here
       key=KEY4x4_Getkey();
       if(key){
       value=key;
       }
      LED7_Display(value);
      }
}

