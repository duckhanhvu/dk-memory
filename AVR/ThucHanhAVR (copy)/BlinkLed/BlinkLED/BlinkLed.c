/*
 * BlinkLed.c
 *
 * Created: 09/1/2015 8:08:50 AM
 * Author: Le Ngoc An
 */

#include <mega16.h>
#include <delay.h>

void main(void)
{
    unsigned char Left_val, Right_val;
    unsigned char Save_val, Move_val; // Save_val: bien luu gia tri, Move_val: bien di chuyen
    unsigned char i,j;
    DDRC = 0xFF; // PORTD out
    DDRA = 0x00;    // PORTA in
while (1)
    {
        switch(PINA)
        {
            // 1 Led sang chay qua lai
            case 0x01:
               {
                    PORTC = 0x01;
                    for(i=0;i<7;i++)
                    {
                         delay_ms(50);
                         PORTC = PORTC << 1;
                    }
                    for(i=0;i<8;i++)
                    {
                         delay_ms(50);
                         PORTC = PORTC >> 1;
                    }
                    break;
               }
            // 8 led sang dan sau do tat dan
            case 0x02:
               {
                    PORTC = 0x01;
                    for(i=0;i<7;i++)
                    {
                         delay_ms(50);
                         PORTC = PORTC << 1;
                         PORTC = PORTC | 0x01;
                    }
                    for(i=0;i<8;i++)
                    {
                         delay_ms(50);
                         PORTC = PORTC >> 1;
                    }
                    break;
               }
            // 8 led sang tu hai ben sau do tat tu 2 ben vao
            case 0x04:
            {
                Left_val  = 0x80;
                Right_val = 0x01;
                for(i=0;i<4;i++)
                {
                    PORTC = Left_val|Right_val;
                    delay_ms(50);
                    Left_val = (Left_val >> 1)|0x80;
                    Right_val = (Right_val << 1)|0x01;
                }
                Left_val  = 0x7F;
                Right_val = 0xFE;
                for(i=0;i<4;i++)
                {
                    PORTC = Left_val&Right_val;
                    delay_ms(50);
                    Left_val = Left_val >> 1;
                    Right_val = Right_val << 1;
                }
                break;
            }
            // 8 led sang don
            case 0x08:
               {
                    Save_val = 0;
                    for(j=8;j>0;j--)
                    {
                         Move_val = 0x80;
                         for(i=0;i<j;i++)
                         {
                              PORTC = Save_val | Move_val;
                              delay_ms(50);
                              Move_val = Move_val >> 1;
                         }
                         Save_val = PORTC;
                    }
                    break;
               }
               // 8 led chop tat
               case 0x10:
               {
                    PORTC = 0xF0;
                    delay_ms(50);
                    PORTC = ~PORTC;
                    delay_ms(50);
                    PORTC = 0xAA;
                    delay_ms(50);
                    PORTC = ~PORTC;
                    delay_ms(50);
                    break;
               }
               // So Led chay qua lai tang dan
               case 0x20:
               {
                    Save_val = 0x01;
                    for(j=7;j>0;j--)
                    {
                         PORTC = Save_val;
                         for(i=0;i<j;i++)
                         {
                              delay_ms(50);
                              PORTC = PORTC << 1;
                         }
                         for(i=0;i<j;i++)
                         {
                              delay_ms(50);
                              PORTC = PORTC >> 1;
                         }
                         Save_val = (Save_val<<1)|0x01;
                    }
                    break;
               }
               // LED chay vao tu 2 ben va sang tu giua ra
               case 0x40:
               {
                    Left_val = 0x80;
                    Right_val = 0x01;
                    for(i=0;i<3;i++)
                    {
                        PORTC = Left_val|Right_val;
                        delay_ms(50);
                        Left_val = Left_val >> 1;
                        Right_val = Right_val << 1;
                    }
                    for(i=0;i<4;i++)
                    {
                        PORTC = Left_val|Right_val;
                        Left_val = (Left_val<<1)|0x10;
                        Right_val = (Right_val>>1)|0x08;
                        delay_ms(50);
                    }
                    break;
               }
               // 2 LED chay vao tu 2 ben va chay ra 2 ben
               case 0x80:
               {
                    Left_val = 0x80;
                    Right_val = 0x01;
                    for(i=0;i<3;i++)
                    {
                         PORTC = Left_val|Right_val;
                         delay_ms(50);
                         Left_val = Left_val >> 1;
                         Right_val = Right_val <<1;
                    }
                    for(i=0;i<4;i++)
                    {
                         PORTC = Left_val|Right_val;
                         delay_ms(50);
                         Left_val = Left_val << 1;
                         Right_val = Right_val >> 1;
                    }
                    break;

               }
        }

    }
}
