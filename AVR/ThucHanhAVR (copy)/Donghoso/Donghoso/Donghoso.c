/*
 * Donghoso.c
 *
 * Created: 11/7/2015 9:08:15 PM
 * Author: Le Ngoc An
 * Group : D13CQDT02-N
 */

#include <mega16.h>
#include <delay.h>


#define Led7seg PORTC
#define Leddv_s PORTD.5
#define Ledch_s PORTD.4
#define Leddv_m PORTD.3
#define Ledch_m PORTD.2
#define Leddv_h PORTD.1
#define Ledch_h PORTD.0

unsigned char Array_7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

unsigned char hour=0,minute=0,second=0;
unsigned int i=0;


    // Chuong trinh ngat so sanh Timer0
interrupt [TIM0_COMP]void Donghoso (void)
{
    i++;
    if(i==1000)
    {
        i=0;
        second = second + 1;
        if(second == 60)
        {
            second = 0;
            minute = minute + 1;
            if(minute == 60)
            {
                minute = 0;
                hour = hour + 1;
                if(hour == 24)
                {
                    hour = 0;
                }
            }
        }
    }
}

void main(void)
{
        // PORTC, PORTD out
    DDRC = 0xFF;
    DDRD = 0xFF;
        // Khoi dong Timer0
        // Che do CTC
        // Clock 250KHz
    TCCR0 = (1<<WGM01) | (0<<WGM00) | (0<<CS02) | (1<<CS01) | (0<<CS00);
    TIMSK = (1<<OCIE0); // Cho phep ngat so sanh Timer0
    TCNT0 = 0;
    OCR0 = 250; // Set gia tri so sanh
    #asm("sei"); // Cho phep ngat toan cuc

while (1)
    {
        // Hien thi len led 7 doan
        Led7seg = Array_7seg[hour/10];
        Ledch_h = 1;
        delay_ms(1);
        Ledch_h = 0;

        Led7seg = Array_7seg[hour%10];
        Leddv_h = 1;
        delay_ms(1);
        Leddv_h = 0;


        Led7seg = Array_7seg[minute/10];
        Ledch_m = 1;
        delay_ms(1);
        Ledch_m = 0;

        Led7seg = Array_7seg[minute%10];
        Leddv_m = 1;
        delay_ms(1);
        Leddv_m = 0;

        Led7seg = Array_7seg[second/10];
        Ledch_s = 1;
        delay_ms(1);
        Ledch_s = 0;

        Led7seg = Array_7seg[second%10];
        Leddv_s = 1;
        delay_ms(1);
        Leddv_s = 0;
    }
}
