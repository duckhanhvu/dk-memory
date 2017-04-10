/*
 * USART.c
 *
 * Created: 11/20/2015 9:07:43 PM
 * Author: Le Ngoc An
 * Group : D13CQDT02-N
 */
    //Clock 8Mhz

#include <mega16.h>
#include <delay.h>
    // Dien ap tham chieu AVCC, du lieu dich trai
#define VREF_TYPE ((0<<REFS1)|(1<<REFS0)|(1<<ADLAR))

// Khai bao ket noi LCD
#define RS PORTD.2
#define EN PORTD.3
#define LCD_data PORTC

unsigned char ADC_data;

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
void LCD_init()
{
    LCD_instruction(0x30);
	LCD_instruction(0x38); // 2 dong, font 5x7
	LCD_instruction(0x01); // Xoa man hinh
	LCD_instruction(0x0C); // Bat hien thi, xoa con tro
}

// Ghi gia tri dang thap phan
void Decimal_Convert(unsigned char d)
{
      LCD_write(d/100+0x30);
      LCD_write(d%100/10+0x30);
      LCD_write(d%10+0x30);
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
    // Chuyen doi ADC
unsigned char Read_ADC(unsigned char ADC_Input)
{
    ADMUX |= ADC_Input|VREF_TYPE;
    ADCSRA |= (1<<ADSC);
    return ADCH;
}
    //Ngat ADC
interrupt[ADC_INT]void ADC_ISR(void)
{
    ADC_data = ADCH;
    ADCSRA |= (1<<ADSC);
}
void USART_Transmit(unsigned char data)
{
    while(!(UCSRA&(1<<UDRE)));
    UDR = data;
}
unsigned char USART_Receive(void)
{
    while(!(UCSRA&(1<<RXC)));
    return UDR;
}



void main(void)
{
    unsigned char x;
    DDRC = 0xFF; // PORTC out
    DDRD = (1<<DDD3)|(1<<DDD2)|(1<<DDD1)|(0<<DDD0); // RxD: in; TxD: out
    DDRA = (0<<DDA0);

    // ADC initialization
    ADMUX = VREF_TYPE;
    ADCSRA = (1<<ADEN)|(0<<ADSC)|(1<<ADATE)|(0<<ADIF)|(1<<ADIE)|(0<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
    SFIOR = (0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);

    // USART initalization
    // Communication parameter : 8 Data, 1 Stop bit, Even Parity bit
    // Mode : Asyschronous
    // Baud rate: 9600
    UCSRA = (0<<RXC)|(0<<TXC)|(0<<UDRE)|(0<<FE)|(0<<DOR)|(0<<PE)|(0<<U2X)|(0<<MPCM);
    UCSRB = (0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2)|(0<<RXB8)|(0<<TXB8);
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(1<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
    UBRRH=0x00;
    UBRRL=0x33;

    #asm("sei"); // Cho phep ngat toan cuc

    Read_ADC(0);
    LCD_init();
while (1)
    {
        USART_Transmit(ADC_data);
        x = USART_Receive();
        LCD_instruction(0x82);
        Decimal_Convert(x);
        LCD_instruction(0xC2);
        Voltage_Convert(x);
    }
}
