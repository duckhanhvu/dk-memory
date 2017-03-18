/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/28/2015
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 2.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <delay.h>
// Timer1 output compare A interrupt service routine
volatile unsigned int val=0;
volatile unsigned int giay=0;
volatile unsigned int phut=0;
volatile unsigned int gio=0;
void hien_giay(unsigned int n){
  int a,b;
         a=n/10;
         b=n%10;
         
         PORTA.4=1;
         PORTD=a;
         delay_ms(1);
         PORTA.4=0;
         
         PORTA.5=1;
         PORTD=b;
         delay_ms(1);
         PORTA.5=0;
            
     
}
void hien_phut(unsigned int n){
  int a,b;
         a=n/10;
         b=n%10;
         
         PORTA.2=1;
         PORTC=(a<<4);
         delay_ms(1);
         PORTA.2=0;
         
         PORTA.3=1;
         PORTC=(b<<4);
         delay_ms(1);
         PORTA.3=0;
            
     
}
void hien_gio(unsigned int n){
  int a,b;
         a=n/10;
         b=n%10;
         
         PORTA.0=1;
         PORTC=a;
         delay_ms(1);
         PORTA.0=0;
         
         PORTA.1=1;
         PORTC=b;
         delay_ms(1);
         PORTA.1=0;
            
     
}
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{


  val++;
  if(val==50){
     val=0;
     giay++;
     
     if(giay==60){
        giay=0;
        phut++;
        if(phut==60) 
           gio++;
           
           if(gio==24) gio=0;    
    }
  }
    
   hien_giay(giay);
   hien_phut(phut);
   hien_gio(gio);
  
 
}




void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0xFF;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0xFF;

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
// Clock value: 250.000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x0A;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1A=4999;
//OCR1AL=0x00;
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
TIMSK=0x10;

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

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
