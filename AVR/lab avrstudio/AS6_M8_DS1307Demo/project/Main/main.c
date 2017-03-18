/*****************************************************************************
  *Ten Tep          :     main.c
  *Ngay             :     05/07/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Hien thi thoi gian, ngay thang len LCD16x2, su dung DS1307
  ******************************************************************************/

#include "Main\main.h"
#include "ProjectLib\Include\var.h"

#if (__MAIN_H!=5072014)
    #error "Include Sai #File Main.h"
#endif

// Declare your global variables here

void main(void)
{
    uint8_t Str[16];
    uint8_t Hour, Min, Sec;
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=1 State6=1 State5=1 State4=1 State3=T State2=T State1=T State0=T 
PORTB=0xF0;
DDRB=0xF0;

// Port C initialization
// Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=In Func1=Out Func0=Out 
// State7=T State6=T State5=1 State4=1 State3=1 State2=T State1=0 State0=0 
PORTC=0x00;
DDRC=0xff;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

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

LCD16X2_Init();    // Khoi tao LCD16X2
DS1307_Init();
DS1307_SetControl(1,DS1307_SQW_1Hz);
if(FlagSetTime)
{
    DS1307_SetTime(11,15,0);
    FlagSetTime=0;
}
LCD16X2_Gotoxy(0,0);
LCD16X2_Puts(" DS1307 AVR V4  ");
while (1)
{
    DS1307_GetTime(&Hour,&Min,&Sec);
    sprintf(Str,"Time: %2u-%2u-%2u",Hour,Min,Sec);
    LCD16X2_Gotoxy(0,1);
    LCD16X2_Puts(Str);
    delay_ms(200);
}
}
/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/
