/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 9/15/2015
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

#define KEY4x4_COL1 PIND.4
#define KEY4x4_COL2 PIND.5
#define KEY4x4_COL3 PIND.6
#define KEY4x4_COL4 PIND.7

#define KEY4x4_ROW1 PORTD.3
#define KEY4x4_ROW2 PORTD.2
#define KEY4x4_ROW3 PORTD.1
#define KEY4x4_ROW4 PORTD.0  



static unsigned char KEY_4x4[4][4]={0b00111111,0b00000110,0b01011011,0b01001111,
                                    0b01100110,0b01101101,0b01111101,0b00000111,
                                    0b00111111,0b00000110,0b01011011,0b01001111,
                                    0b01100110,0b01101101,0b01111101,0b00000111,};
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
//delay_ms(5);
if(KEY4x4_Ispush()){
for(i=0;i<4;i++){
KEY4x4_checkROW(i);
if(KEY4x4_COL1==0)  return KEY_4x4[i][0];
if(KEY4x4_COL2==0)  return KEY_4x4[i][1];
if(KEY4x4_COL3==0)  return KEY_4x4[i][2];
if(KEY4x4_COL4==0)  return KEY_4x4[i][3];
}
}
}
return 0;
}





// Declare your global variables here

void main(void)
{

// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=T State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTA=0x00;
DDRA=0x7F;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0b11111111;
DDRC=0b00001111;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=P State6=P State5=P State4=P State3=1 State2=1 State1=1 State0=1 
PORTD=0xFF;
DDRD=0x0F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
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

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

while (1)
      { 
       int key;
       int i;
       int x=0b00000111;
       //key=KEY4x4_Getkey();
       for(key=0;key<4;key++){
       
       if(key=KEY4x4_Getkey()){
       PORTA=key;
       PORTC=x;
       x=x>>1;
       }
       else 
       PORTC=0b00001111;
       
       //x=x>>1;
      
             
       
       }
       
      
       
      

}
}