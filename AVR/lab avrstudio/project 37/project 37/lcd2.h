/*
 * lcd2.h
 *
 * Created: 8/21/2016 6:32:40 PM
 *  Author: Duc Khanh
 */ 


#ifndef LCD2_H_
#define LCD2_H_

#include <avr/io.h>
#include <avr/delay.h>

#define DATA_output  PORTA
#define DATA_input   PINA
#define CTRL         PORTA
#define DDR_DATA     DDRA
#define DDR_CTRL     DDRA


#define lcd_D7_port     PORTA                   
#define lcd_D7_bit      PORTA7
#define lcd_D7_ddr      DDRA

#define lcd_D6_port     PORTA                   
#define lcd_D6_bit      PORTA6
#define lcd_D6_ddr      DDRA

#define lcd_D5_port     PORTA                   
#define lcd_D5_bit      PORTA5
#define lcd_D5_ddr      DDRA

#define lcd_D4_port     PORTA                   
#define lcd_D4_bit      PORTA4
#define lcd_D4_ddr      DDRA

#define lcd_E_port      PORTA                   
#define lcd_E_bit       PORTA1
#define lcd_E_ddr       DDRA

#define lcd_RS_port     PORTA                   
#define lcd_RS_bit      PORTA0
#define lcd_RS_ddr      DDRA

// LCD module information
#define lcd_LineOne     0x00                   
#define lcd_LineTwo     0x40                    


// LCD instructions
#define lcd_Clear           0b00000001          
#define lcd_Home            0b00000010        
#define lcd_EntryMode       0b00000110          
#define lcd_DisplayOff      0b00001000          
#define lcd_DisplayOn       0b00001100         
#define lcd_FunctionReset   0b00110000         
#define lcd_FunctionSet4bit 0b00101000          
#define lcd_SetCursor       0b10000000          




void lcd_write_4(unsigned char);
void lcd_write_instruction_4d(uint8_t);
void lcd_write_character_4d(unsigned char);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);
void LCD_goto(unsigned char dong, unsigned char cot);
void printnumber_lcd(int number);
void clear_lcd();

void lcd_init_4d(void)
{
	lcd_D7_ddr |= (1<<lcd_D7_bit);                  // 4 data lines - output
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);
	
	lcd_E_ddr |= (1<<lcd_E_bit);                    // E line - output
    lcd_RS_ddr |= (1<<lcd_RS_bit);

// Power-up delay
    _delay_ms(100);                                 



    lcd_RS_port &= ~(1<<lcd_RS_bit);                
    lcd_E_port &= ~(1<<lcd_E_bit);                  

/*
    lcd_write_4(lcd_FunctionReset);                 
    _delay_ms(10);                                  
*/
    lcd_write_4(lcd_FunctionReset);                 
    _delay_us(200);                                 

    lcd_write_4(lcd_FunctionReset);                 
    _delay_us(200);                                 

   
    lcd_write_4(lcd_FunctionSet4bit);               
    _delay_us(80);                                  

    lcd_write_instruction_4d(lcd_FunctionSet4bit);   
    _delay_us(80);                                  

    lcd_write_instruction_4d(lcd_Clear);             
    _delay_ms(4); 


    lcd_write_instruction_4d(lcd_DisplayOff);        
    _delay_us(80);                                  




    lcd_write_instruction_4d(lcd_EntryMode);         
    _delay_us(80);                                  


    lcd_write_instruction_4d(lcd_DisplayOn);         
    _delay_us(80);                                  
}

void clear_lcd(){
	lcd_RS_port &= ~(1<<lcd_RS_bit);                
    lcd_E_port &= ~(1<<lcd_E_bit); 
    lcd_write_instruction_4d(lcd_Clear);             
    _delay_ms(4); 

}
void lcd_write_string_4d(uint8_t theString[])
{
    volatile int i = 0;                            
    while (theString[i] != 0)
    {
        lcd_write_character_4d(theString[i]);
        i++;
        _delay_us(80);                             
    }
}
void lcd_write_character_4d(uint8_t theData)
{
    lcd_RS_port |= (1<<lcd_RS_bit);                 
    lcd_E_port &= ~(1<<lcd_E_bit);                 
    lcd_write_4(theData);                           
    lcd_write_4(theData << 4);                      
}


void lcd_write_instruction_4d(uint8_t theInstruction)
{
    lcd_RS_port &= ~(1<<lcd_RS_bit);                
    lcd_E_port &= ~(1<<lcd_E_bit);                 
    lcd_write_4(theInstruction);                   
    lcd_write_4(theInstruction << 4);               
}



void lcd_write_4(uint8_t theByte)
{
    lcd_D7_port &= ~(1<<lcd_D7_bit);                        
    if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);     

    lcd_D6_port &= ~(1<<lcd_D6_bit);                        
    if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);

    lcd_D5_port &= ~(1<<lcd_D5_bit);
    if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);

    lcd_D4_port &= ~(1<<lcd_D4_bit);
    if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);


                                                    
    lcd_E_port |= (1<<lcd_E_bit);                   
    _delay_us(1);                                   
    lcd_E_port &= ~(1<<lcd_E_bit);                  
    _delay_us(1);    
	
}

                             
void LCD_goto(unsigned char dong, unsigned char cot)
{

	unsigned char x;
	x=64*(dong-1)+(cot-1)+0x80;

	lcd_write_instruction_4d(x);
	
	_delay_ms(1);
	return;
}
void printnumber_lcd(int number){

	int a,n,i,temp;
	temp=100;
	for(i=0;i<3;i++){
		a=number/temp;
		number=number%temp;
		temp=temp/10;
		lcd_write_character_4d(a+48);
	}
}

#endif /* LCD2_H_ */