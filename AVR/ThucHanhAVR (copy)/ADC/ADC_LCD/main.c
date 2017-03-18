/*
 * main.c
 *
 * Created: 11/5/2015 3:22:44 PM
 * Author: Le Ngoc An
 * Group : D13DCDT02-N
 */
#include <mega16.h>
#include <delay.h>
#include <string.h>

    // Khai bao ket noi LCD
#define RS PORTC.6
#define EN PORTC.7
#define LCD_data PORTD
    // Dien ap tham chieu AVCC, du lieu dich trai
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (1<<ADLAR))

    // Ghi lenh len LCD
void LCD_instruction(unsigned char x)
{
    RS = 0;
    LCD_data = x;
    EN = 0;
    EN = 1;
    delay_ms(2);
}
    // Ghi ky tu len LCD
void LCD_write(unsigned char c)
{
    RS = 1;
    LCD_data = c;
    EN = 0;
    EN = 1;
    delay_ms(2);
}

    // Ghi chuoi len LCD
void LCD_writes(char *str)
{
    int i=0;
    while(str[i] != 0)
    {
        LCD_write(str[i]);
        i++;

    }
}
    // Set dia chi, ghi chuoi len LCD
void LCD_string(unsigned char row, unsigned char col, char *str)
{
    unsigned char cmd;
    cmd = (row == 1 ? 0x80 : 0xC0) + col - 1;
    LCD_instruction(cmd);
    LCD_writes(str);
}

void LCD_init()
{
    LCD_instruction(0x30);
	LCD_instruction(0x38); // 2 dong, font 5x7
	LCD_instruction(0x01); // Xoa man hinh
	LCD_instruction(0x0C); // Bat hien thi, xoa con tro
}

    // Doc gia tri ADC
unsigned char read_adc(unsigned char adc_input)
{
    ADMUX = adc_input | ADC_VREF_TYPE; // Khoi dong ADC
    delay_us(10);
    ADCSRA |= (1<<ADSC);   // Start ADC
    while((ADCSRA & (1<<ADIF))==0);  // Doi chuyen doi
    ADCSRA |= (1<<ADIF); // Xoa co ngat
    return ADCH;      // Tra ve gia tri o thanh ghi ADCH
}
    // Ghi gia tri dang thap phan
void Decimal_Convert(unsigned char d)
{
      LCD_write(d/100+0x30);
      LCD_write(d%100/10+0x30);
      LCD_write(d%10+0x30);
}
    // Ghi gia tri dang nhi phan
void Binary_Convert(unsigned char b)
{
    unsigned char i,bits;

    for(i=0;i<8;i++)
    {
        bits = b & 0x80;
        if(bits == 0x80)
            LCD_write(1+0x30);
        else
            LCD_write(0x30);
        b = b << 1;
    }
}

    // Ghi gia tri dang thap luc phan
void Hexa_Convert(unsigned char h)
{
    unsigned char ch,dv;
    ch = h/16;
    dv = h%16;
    LCD_writes("0x");

    if(ch<10)
        LCD_write(ch+0x30);
    else
        LCD_write(ch-10+0x41);
    if(dv<10)
        LCD_write(dv+0x30);
    else
        LCD_write(dv-10+0x41);
}

    // Hien thi dien ap
void Voltage_Convert(unsigned char v)
{
    unsigned int voltage;
    voltage = v * 1.953125f;
    LCD_write(voltage/100+0x30);
    LCD_write('.');
    LCD_write(voltage%100/10+0x30);
    LCD_write(voltage%10+0x30);
    LCD_write('V');
}


void main(void)
{
    unsigned char n;
    DDRD = 0xFF;
    DDRC = (1<<DDC7) | (1<<DDC6);

    // Khoi dong LCD
    ADMUX = ADC_VREF_TYPE;
    ADCSRA = (1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
    SFIOR = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

    LCD_init();
while (1)
    {
        LCD_string(1,1,"Kenh0: ");
        Decimal_Convert(read_adc(0));
        LCD_writes("D ");
        Binary_Convert(read_adc(0));
        LCD_writes("B ");
        Hexa_Convert(read_adc(0));
        LCD_writes(" DIEN AP:");
        Voltage_Convert(read_adc(0));

        LCD_instruction(0xC0);
        for(n=1;n<8;n++)
        {
            Voltage_Convert(read_adc(n));
            LCD_write(' ');
        }
        LCD_instruction(0x18);
    }
}
