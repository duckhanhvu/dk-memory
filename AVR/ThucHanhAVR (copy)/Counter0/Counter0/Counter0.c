/*
 * Counter0.c
 *
 * Created: 11/22/2015 10:00:19 PM
 * Author: Le Ngoc An
 */

#include <mega16.h>
#include <delay.h>
#define RS PORTC.6
#define EN PORTC.7
#define LCD_data PORTD
void LCD_instruction(unsigned char x)
{
    RS = 0;
    LCD_data = x;
    EN = 0;
    EN = 1;
    delay_ms(2);
}

void LCD_write(unsigned char c)
{
    RS = 1;
    LCD_data = c;
    EN = 0;
    EN = 1;
    delay_ms(2);
}

void LCD_init()
{
    LCD_instruction(0x30);
    LCD_instruction(0x01);
    LCD_instruction(0x0C);
    LCD_instruction(0x38);
}


void main(void)
{
    unsigned char i;
    DDRB = 0;
    DDRC = 0xFF;
    DDRD = 0xFF;

    TCCR0 = (1<<CS02)|(1<<CS01)|(0<<CS00);
    TCNT0 = 0;
    LCD_init();
while (1)
    {
        i = TCNT0;
        LCD_instruction(0x82);
        LCD_write(i/100+0x30);
        LCD_write(i%100/10+0x30);
        LCD_write(i%10+0x30);
    }
}
