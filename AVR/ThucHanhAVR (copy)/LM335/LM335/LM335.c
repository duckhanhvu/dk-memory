/*
 * LM335.c
 *
 * Created: 11/21/2015 10:28:25 PM
 * Author: Le Ngoc An
 * Group : D13CQDT02-N
 */

#include <mega16.h>
#include <delay.h>
#include <string.h>
#include <math.h>

    // Khai bao ket noi LCD
#define RS PORTC.6
#define EN PORTC.7
#define LCD_data PORTD

    // Ghi lenh len LCD
void LCD_instruction(unsigned char x)
{
    RS = 0;
    LCD_data = x;
    EN = 0;
    EN = 1;
    delay_ms(2);
}
    // Ghi du ieu len LCD
void LCD_write(unsigned char c)
{
    RS = 1;
    LCD_data = c;
    EN = 0;
    EN = 1;
    delay_ms(2);
}

    // Khoi dong LCD
void LCD_init()
{
    LCD_instruction(0x30);
	LCD_instruction(0x38);
	LCD_instruction(0x01);
	LCD_instruction(0x0C);
}

    // Hien thi dien ap
void Voltage_Display(unsigned int d)
{
      LCD_write(d/100+0x30);
      LCD_write('.');
      LCD_write(d%100/10+0x30);
      LCD_write(d%10+0x30);
      LCD_write('V');
}
    // Hien thi nhiet do
void Temp_Display(unsigned int i)
{
      LCD_write(i/10+0x30);
      LCD_write(i%10+0x30);
      LCD_write(0xDF);
      LCD_write('C');
}


void main(void)
{
    unsigned int i,j;
        // Port A,C,D out
    DDRD = 0xFF;
    DDRC = 0xFF;
    DDRA = 0xFF;
    DDRB = 0x00; // PORTB in

    //Timer 1
    TCCR1A = 0;
    //Analog Comparator
    SFIOR = (0<<ACME);
    ACSR = (0<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

    LCD_init();

while (1)
    {
        TCNT1 = 0;
        PORTA.0 = 0; // Xa tu
        delay_ms(1000);
        PORTA.0 = 1; // Nap tu
            // Start Timer1
        TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10);

        while(!(ACSR&0x20));  // Cho nap tu
        TCCR1B = 0; // Stop Timer0
        PORTA.0 = 0;
        j = TCNT1;
        LCD_instruction(0x82);
        i = 5*(1-exp(-((j/3906.25)/10)))*100;
        Voltage_Display(i);
        LCD_instruction(0xC2);
        Temp_Display(i-273);
    }
}
