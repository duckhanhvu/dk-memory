/*
 * GiaotiepLCD.c
 *
 * Created: 10/30/2015 8:11:05 PM
 * Author: Le Ngoc An
 * Group : D13CQDT02-N
 * School: PTIT
 */

#include <string.h>
#include <mega16.h>
#include <delay.h>

    // Khai bao ket noi LCD
#define RS PORTC.6
#define EN PORTC.7
#define LCD_Data PORTD

    // Ghi lenh len LCD
void LCD_Inst(unsigned char x)
{
    RS = 0; // Chon ghi lenh
    LCD_Data = x; // Ghi lenh x len LCD
    EN = 1; // Enable LCD
    EN = 0;
    delay_ms(2);
}
    // Ghi ky tu len LCD
void LCD_Write(unsigned char c)
{
    RS = 1; // Chon ghi du lieu
    LCD_Data = c; // Ghi ki tu c len LCD
    EN = 1; // Enable LCD
    EN = 0;
    delay_ms(2);
}
    // Ghi ky tu kem theo vi tri len LCD
void LCD_Write_Addr(unsigned char row, unsigned char col, char c)
{
    unsigned char Addr; // Bien vi tri cua ky tu can ghi
    Addr = (row == 1 ? 0x80 : 0xC0) + col - 1;
    LCD_Inst(Addr); // Dat con tro tai vi tri Addr
    LCD_Write(c);   // Ghi ky tu c len LCD
}

    // Ghi chuoi len LCD
void LCD_Write_String(char *str)
{
    int i = 0;
    while(str[i] != 0)
    {
        LCD_Write(str[i]);
        i++;
    }
}

void LCD_Write_String_Addr(unsigned char row, unsigned char col, char *str)
{
    unsigned char Addr; // Bien vi tri cua ky tu can ghi
    Addr = (row == 1 ? 0x80 : 0xC0) + col - 1;
    LCD_Inst(Addr); // Dat con tro tai vi tri Addr
    LCD_Write_String(str);   // Ghi chuoi str len LCD
}
    // Khoi dong LCD
void LCD_Init(void)
{
    LCD_Inst(0x01); // Xoa man hinh
    LCD_Inst(0x0C); // Bat hien thi, tat con tro
    LCD_Inst(0x38); // 2 dong, font 5x7;
}

void main(void)
{
    // PORTC: Pin6 ,Pin7 out
    DDRC = (1<<DDC7) | (1<<DDC6);
    // PORTD out
    DDRD = (1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);

    // Khoi dong LCD
    LCD_Init();
while (1)
    {
        LCD_Write_String_Addr(1,2,"ATmega16");
        LCD_Write_String_Addr(2,2,"Flash ");
        LCD_Write(1+0x30);
        LCD_Write(6+0x30);
        LCD_Write_String("KB");
        LCD_Inst(0x1C);
    }
}
