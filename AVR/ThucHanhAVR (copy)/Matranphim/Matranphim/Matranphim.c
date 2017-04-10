/*
 * Matranphim.c
 *
 * Created: 10/3/2015 5:04:36 PM
 * Author: Le Ngoc An
 * Group : D13CQDT02-N
 */

#include <mega16.h>
#include <delay.h>
    // Khai bao ket noi Key Matrix
#define Col1 PORTB.0
#define Col2 PORTB.1
#define Col3 PORTB.2
#define Col4 PORTB.3

#define Row1 PINB.4
#define Row2 PINB.5
#define Row3 PINB.6
#define Row4 PINB.7

#define Led7seg PORTC

unsigned char Array_7seg[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0E};
unsigned char Get_key4x4(void)
{
    unsigned char Key;
    Col1 = 0;
    if(Row1==0) Key = 0x07;
    if(Row2==0) Key = 0x04;
    if(Row3==0) Key = 0x01;
    if(Row4==0) Key = 0x00;
    Col1 = 1;

    Col2 = 0;
    if(Row1==0) Key = 0x08;
    if(Row2==0) Key = 0x05;
    if(Row3==0) Key = 0x02;
    if(Row4==0) Key = 0x0A;
    Col2 = 1;

    Col3 = 0;
    if(Row1==0) Key = 0x09;
    if(Row2==0) Key = 0x06;
    if(Row3==0) Key = 0x03;
    if(Row4==0) Key = 0x0B;
    Col3 = 1;

    Col4 = 0;
    if(Row1==0) Key = 0x0F;
    if(Row2==0) Key = 0x0E;
    if(Row3==0) Key = 0x0D;
    if(Row4==0) Key = 0x0C;
    Col4 = 1;
    return Key;
}

void main(void)
{
    unsigned char Key_val;
    // PORTB PIN0,1,2,3 out; PIN4,5,6,7 in
    DDRB = 0x0F;
    // PORTD, PORTC out
    DDRC = 0xFF;
    DDRD = 0xFF;
    Col1 = Col2 = Col3 = Col4 = 1;
while (1)
    {
        Key_val = Get_key4x4();
        Led7seg = Array_7seg[Key_val];
        PORTD.3 = 1;
        delay_ms(2);
        PORTD.3 = 0;
    }
}
