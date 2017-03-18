/*
 * Led7seg.c
 *
 * Created: 10/1/2015 9:23:06 AM
 * Author: Le Ngoc An
 */

#include <mega16.h>
#include <delay.h>

unsigned char  Array_7seg_switch1[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char  Array_7seg_switch2[] = {0xFF, 0xFF, 0xFF, 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,0xFF,0xFF,0xFF};

void main(void)
{
    unsigned char i,j,n;
    unsigned char Move_val;
    DDRC = 0xFF; // PORTC out
    DDRD = 0xFF; // PORTD out
    DDRA = (0<<DDA7)|(0<<DDA0); // PORTA: PIN7, PIN0 in
while (1)
    {
        switch(PINA)
        {
            // 4 Led hien thi 1234
            case 0x01:
            {
                Move_val = 0x01;
                for(i=1;i<5;i++)
                {
                    PORTC = Array_7seg_switch1[i];
                    PORTD = Move_val;
                    delay_ms(2);
                    PORTD = 0x00;
                    Move_val = Move_val << 1;
                }
                break;
            }
            // Chay tu 0 >> 9
            case 0x80:
            {
                // Gia tri LED
                for(i=0;i<13;i++)
                {
                    // Vong lap tang giam toc do
                    for(j=0;j<50;j++)
                    {
                        Move_val = 0x01;
                        // Chi so tang
                        for(n=0;n<4;n++)
                        {
                            PORTC = Array_7seg_switch2[i+n];
                            PORTD = Move_val;
                            delay_ms(2);
                            PORTD = 0x00;
                            Move_val = Move_val << 1;
                        }
                    }
                }
            }
        }

    }
}
