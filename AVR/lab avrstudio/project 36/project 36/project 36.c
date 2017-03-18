/*
 * project_36.c
 *
 * Created: 8/21/2016 8:26:38 PM
 *  Author: Duc Khanh
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/eeprom.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <math.h>
#include "setandclear_bit.h"
#include "lcd2.h"

//#define CTRL_DDR    DDRB
//#define CTRL_PORT   PORTB
#define data  1
#define clk   2
#define en    3



volatile unsigned int n[22]={0};

	
volatile unsigned char x;
volatile int val=0;
volatile int N_tong;
volatile int a=0;
void write(unsigned int i){
	CTRL_DDR=0xFF;
	if(i==1){
	      setbit(CTRL_PORT, data);      
	      _delay_us(20);
          clearbit(CTRL_PORT,clk);    
          _delay_us(10);
          setbit(CTRL_PORT,clk);   
		  _delay_us(10);
	}
	if(i==0){
	      clearbit(CTRL_PORT,clk);	
	      _delay_us(20);
          setbit(CTRL_PORT,clk);    
          _delay_us(10);
          clearbit(CTRL_PORT,clk);    		
		  _delay_us(10); 
	}	 
	}    
void write_reference(unsigned int number){
	   unsigned int i=0;
	   while(number!=0){
		n[i]=number%2;	
		number=number/2;
		i++;
	  }        
	  for(i=18;i<22;i++){
		write(n[i]) ;
	  }
	
	}
void write_N_and_A_divide(unsigned int Nnumber, unsigned int Anumber){
	   unsigned int i=0;
	   unsigned int j=0;
	   while(Nnumber!=0){
		n[i]=Nnumber%2;	
		Nnumber=Nnumber/2;
		i++;
	  }
	   while(Anumber!=0){
		n[j]=Anumber%2;	
		Anumber=Anumber/2;
		j++;
	  }
	  for(i=0;i<7;i++){
		write(n[i]) ;
	  }
	  for(j=7;j<18;j++){
		 write(n[j]); 
	  }
}
void reset_pulse(void){
	CTRL_DDR=0xFF;
	setbit(CTRL_PORT,en);   
    _delay_us(70);
    clearbit(CTRL_PORT,en);    
}

int main()
{
	uint8_t b=0;
	DDRD=0x00;
	PORTD=0xFF;	
	
    DDRA=0xff; 
    DDRC=0x07; 
    MCUCR|=(1<<ISC11)|(1<<ISC01);      
    GICR    |=(1<<INT1)|(1<<INT0);   
    lcd_init_4d(); 
    sei();  
    _delay_ms(50); 

/*
	
	LCD_goto(1,1);
	lcd_write_string_4d("tan so : ");
	LCD_goto(1,9);
	//printnumber_lcd(val);
	
	val=eeprom_read_byte((uint8_t*)46);
	N_tong=(32*128 + val)*100*50*pow(10,-3);
	LCD_goto(1,9);
	printnumber_lcd(N_tong);
	
	*/
	LCD_goto(1,13);
	lcd_write_string_4d("MHz");
	LCD_goto(2,1);
	lcd_write_string_4d("chon tan so");
	
    while(1){
	 if(bit_is_clear(PIND,PD4)){
		 LCD_goto(2,1);
		 lcd_write_string_4d("chon tan so");
		 write_N_and_A_divide(32,val);
		 write_reference(0b0010);
     }
	 /*
	 if(bit_is_clear(PIND,PD1)){
		 lcd_write_instruction_4d(lcd_Clear); 
		 _delay_ms(10);
		// eeprom_write_byte((uint8_t *)46,val);
		 LCD_goto(1,1);
	     lcd_write_string_4d("luu tan so ");
		 LCD_goto(2,1);
		 printnumber_lcd(val);
		 LCD_goto(2,4);
		 lcd_write_string_4d("MHz");
	 }
	 */
   } 
return 0;
}

ISR(INT0_vect){
	val++;
    

    //N_tong=(32*128 + val)*100*50*pow(10,-3);
	
	LCD_goto(1,9);
	printnumber_lcd(val);
}
ISR(INT1_vect){
	val--;

	//N_tong=(32*128 + val)*100*50*pow(10,-3);
	
	LCD_goto(1,9);
	printnumber_lcd(val);
}