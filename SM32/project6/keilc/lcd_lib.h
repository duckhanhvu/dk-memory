
#ifndef __LCD_LIB_H
#define __LCD_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_tim.h"

#define lcd_D7_port     GPIOB                   
#define lcd_D7_bit      7
#define lcd_D7_ddr      DDRA

#define lcd_D6_port     GPIOB                   
#define lcd_D6_bit      6
#define lcd_D6_ddr      DDRA

#define lcd_D5_port     GPIOB                   
#define lcd_D5_bit      5
#define lcd_D5_ddr      DDRA

#define lcd_D4_port     GPIOB                   
#define lcd_D4_bit      4
#define lcd_D4_ddr      DDRA

#define lcd_E_port      GPIOB                   
#define lcd_E_bit       PORTA1
#define lcd_E_ddr       DDRA

#define lcd_RS_port     GPIOB                   
#define lcd_RS_bit      PORTA0
#define lcd_RS_ddr      DDRA

#define LCD16X2_EN        GPIO_Pin_12
#define LCD16X2_RW        GPIO_Pin_11
#define LCD16X2_RS        GPIO_Pin_10

// LCD module information
#define lcd_LineOne     0x00                   
#define lcd_LineTwo     0x40                    


// LCD instructions
#define lcd_Clear           0x01          
#define lcd_Home            0x02        
#define lcd_EntryMode       0x06          
#define lcd_DisplayOff      0x08          
#define lcd_DisplayOn       0x0C         
#define lcd_FunctionReset   0x30         
#define lcd_FunctionSet4bit 0x28          
#define lcd_SetCursor       0x80          


void lcd_write_4(unsigned char);
void lcd_write_instruction_4d(uint8_t);
void lcd_write_character_4d(unsigned char);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);
void LCD_goto(unsigned char dong, unsigned char cot);
void printnumber_lcd(int number);

static uint8_t  fac_us=0;
static uint16_t fac_ms=0;

void delay_init(uint8_t SYSCLK)
{
			SysTick->CTRL&=0xfffffffb;
			fac_us=SYSCLK/8;         
			fac_ms=(uint16_t)fac_us*1000;
}

void delay_ms(uint16_t nms)
{   
	uint32_t temp;
			SysTick->CTRL&=0xfffffffb;
			fac_us=48/8;         
			fac_ms=(uint16_t)fac_us*1000;              
          
    SysTick->LOAD=(uint32_t)nms*fac_ms;
    SysTick->VAL =0x00;       
    SysTick->CTRL=0x01 ;     
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL=0x00;   
    SysTick->VAL =0X00;           
}
void delay_us(uint32_t nus)
{    

    uint32_t temp;  
				SysTick->CTRL&=0xfffffffb;
		fac_us=48/8;         
		
    SysTick->LOAD=nus*fac_us;         
    SysTick->VAL=0x00;     
    SysTick->CTRL=0x01 ;       
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL=0x00;   
    SysTick->VAL =0X00;     
}

void lcd_init_4d(void)
{

    delay_ms(100);                                 


    GPIO_ResetBits(GPIOC,LCD16X2_RS);
    GPIO_ResetBits(GPIOC,LCD16X2_EN);
	
/*
    lcd_write_4(lcd_FunctionReset);                 
    _delay_ms(10);                                  
*/
    lcd_write_4(lcd_FunctionReset);                 
    delay_us(200);                                 

    lcd_write_4(lcd_FunctionReset);                 
    delay_us(200);                                 

   
    lcd_write_4(lcd_FunctionSet4bit);               
    delay_us(80);                                  

    lcd_write_instruction_4d(lcd_FunctionSet4bit);   
    delay_us(80);                                  

    lcd_write_instruction_4d(lcd_Clear);             
    delay_ms(4); 


    lcd_write_instruction_4d(lcd_DisplayOff);        
    delay_us(80);                                  




    lcd_write_instruction_4d(lcd_EntryMode);         
    delay_us(80);                                  


    lcd_write_instruction_4d(lcd_DisplayOn);         
    delay_us(80);                                  
}

void lcd_write_string_4d(uint8_t theString[])
{
    volatile int i = 0;                            
    while (theString[i] != 0)
    {
        lcd_write_character_4d(theString[i]);
        i++;
        delay_us(80);                             
    }
}
void lcd_write_character_4d(uint8_t theData)
{
    GPIO_SetBits(GPIOC,LCD16X2_RS);                 
    GPIO_ResetBits(GPIOC,LCD16X2_EN);                 
    lcd_write_4(theData);                           
    lcd_write_4(theData << 4);                      
}


void lcd_write_instruction_4d(uint8_t theInstruction)
{
	  GPIO_ResetBits(GPIOC,LCD16X2_RS);
    GPIO_ResetBits(GPIOC,LCD16X2_EN);
                 
    lcd_write_4(theInstruction);                   
    lcd_write_4(theInstruction << 4);               
}



void lcd_write_4(uint8_t theByte)
{
		lcd_D7_port->ODR &= ~(1<<lcd_D7_bit);                        
    if ((theByte & (1<<7))==0x80)lcd_D7_port->ODR |= (1<<lcd_D7_bit);     

    lcd_D6_port->ODR &= ~(1<<lcd_D6_bit);                        
    if ((theByte & (1<<6))==0x40) lcd_D6_port->ODR |= (1<<lcd_D6_bit);

    lcd_D5_port->ODR &= ~(1<<lcd_D5_bit);
    if ((theByte & (1<<5))==0x20) lcd_D5_port->ODR |= (1<<lcd_D5_bit);

    lcd_D4_port->ODR &= ~(1<<lcd_D4_bit);
    if ((theByte & (1<<4))==0x10) lcd_D4_port->ODR |= (1<<lcd_D4_bit);


    GPIO_SetBits(GPIOC,LCD16X2_EN);
		delay_us(1); 
    GPIO_ResetBits(GPIOC,LCD16X2_EN);
		delay_us(70); 
	
    
	
}

                             
void LCD_goto(unsigned char dong, unsigned char cot)
{

	unsigned char x;
	x=64*(dong-1)+(cot-1)+0x80;

	lcd_write_instruction_4d(x);
	
	delay_ms(1);
	return;
}
void printnumber_lcd(int number){
			
	int a,b;
	    a=number/10;
	    lcd_write_character_4d(a+48);
	
	    b=number%10;
	    lcd_write_character_4d(b+48);
}


#ifdef __cplusplus
}
#endif

#endif /*__LCD_LIB_H*/	 
	 