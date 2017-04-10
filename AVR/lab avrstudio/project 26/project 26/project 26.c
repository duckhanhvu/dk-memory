/*
 * project_26.c
 *
 * Created: 7/4/2016 3:35:01 PM
 *  Author: Duc Khanh
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

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
#define lcd_E_bit       PORTA2
#define lcd_E_ddr       DDRA

#define lcd_RS_port     PORTA                   
#define lcd_RS_bit      PORTA1
#define lcd_RS_ddr      DDRA

// LCD module information
#define lcd_LineOne     0x00                    // line 1
#define lcd_LineTwo     0x40                    // line 2


// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position


uint8_t program_author[]   = "tanso : ";
uint8_t program_version[]  = "LCD-AVR-4d (gcc)";
uint8_t program_date[]     = "Sep 16, 2013";

// Function Prototypes
void lcd_write_4(uint8_t);
void lcd_write_instruction_4d(uint8_t);
void lcd_write_character_4d(uint8_t);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);

/********************************************************/
int main(void)
{
// configure the microprocessor pins for the data lines
    lcd_D7_ddr |= (1<<lcd_D7_bit);                  // 4 data lines - output
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);

// configure the microprocessor pins for the control lines
    lcd_E_ddr |= (1<<lcd_E_bit);                    // E line - output
    lcd_RS_ddr |= (1<<lcd_RS_bit);                  // RS line - output


    DDRD=0xFF;
	PORTD=0xFF;


// initialize the LCD controller as determined by the defines (LCD instructions)
    lcd_init_4d();                                  // initialize the LCD display for a 4-bit interface

// display the first line of information
    lcd_write_string_4d("khanh thanh");
	//putstr_lcd("tanso",5);

// set cursor to start of second line
  while(1){
	  if(bit_is_clear(PIND,PD4)){
   lcd_write_instruction_4d(lcd_SetCursor | lcd_LineTwo);
    _delay_us(80);                                  // 40 uS delay (min)

// display the second line of information
    lcd_write_string_4d("khanh");
  }   
	  }  
// endless loop

    return 0;
}
/******************************* End of Main Program Code ******************/

/*============================== 4-bit LCD Functions ======================*/


void lcd_init_4d(void)
{
// Power-up delay
    _delay_ms(100);                                 // initial 40 mSec delay



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


//    lcd_write_instruction_4d(lcd_Clear);             
//    _delay_ms(4);                                   


    lcd_write_instruction_4d(lcd_EntryMode);         
    _delay_us(80);                                  


    lcd_write_instruction_4d(lcd_DisplayOn);         // turn the display ON
    _delay_us(80);                                  // 40uS delay (min)
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
