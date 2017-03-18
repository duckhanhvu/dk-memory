/*
 * project_36.c
 *
 * Created: 8/21/2016 8:26:38 PM
 *  Author: Duc Khanh
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/eeprom.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <math.h>
#include "setandclear_bit.h"
#include "lcd2.h"

#define CTRL_DDR    DDRD
#define CTRL_PORT   PORTD
#define data  5
#define clk   6
#define en    7



volatile unsigned int n[22]={0};

	
volatile unsigned char x;
volatile int val=0;
volatile int N_tong;
volatile int a=0;
//Hàm ghi bit vào thanh ghi c?a chip d?a theo datasheet  
void write(unsigned int i){
	
	if(i==1){//ghi bít 1 vào thanh ghi
		  
	      setbit(CTRL_PORT, data);      
	      _delay_us(20);
		  /*kéo chân ?i?u khi?n clock c?a chip xu?ng m?c th?p sau th?i gian 10us kéo chân 
		    clock lên l?i m?c cao và ??nh th?i 10us sau ?ó */
          clearbit(CTRL_PORT,clk);    
          _delay_us(10);   
          setbit(CTRL_PORT,clk);   
		  _delay_us(10);
	}
	if(i==0){//ghi bít 0 vào thanh ghi
	      clearbit(CTRL_PORT,clk);	
	      _delay_us(20);
          setbit(CTRL_PORT,clk);    
          _delay_us(10);
          clearbit(CTRL_PORT,clk);    		
		  _delay_us(10); 
	}	 
	}   
//hàm ghi d? li?u b? chia tham chi?u R 
void write_reference(unsigned int number){
	   unsigned int i=0;
	   while(number!=0){
		n[i]=number%2;	
		number=number/2;
		i++;
	  }
	  /*ghi d? li?u b? chia tham chi?u R vào thanh ghi c?a chip
	  bao g?m 4 bit t? bit 18 ??n bit 21 */       
	  for(i=18;i<22;i++){
		write(n[i]) ;
	  }
	
	}
//hàm ghi d? li?u b? chia N và b? chia A
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
	  //ghi d? li?u b? chia A t? bit 1 ??n bit 7
	  for(i=0;i<7;i++){
		write(n[i]) ;
	  }
	  //ghi d? li?u b? chia N t? bit 8 ??n bit 18
	  for(j=7;j<18;j++){
		 write(n[j]); 
	  }
}
int main()
{
	
	uint8_t b=0;
	DDRD=0xF0;
	PORTD=0x0F;	
	
    DDRA=0xff; 
    DDRC=0x07; 
    MCUCR	|=(1<<ISC11)|(1<<ISC01);      
    GICR    |=(1<<INT1)|(1<<INT0);   
    lcd_init_4d(); 
    sei();  
    _delay_ms(50); 
	clear_lcd();	
	LCD_goto(1,1);
	lcd_write_string_4d("tan so : ");
	LCD_goto(1,9);

	//??c giá tr? b? chia t?ng t? epprom va hi?n th? lên LCD*/ 
	N_tong=eeprom_read_byte((uint8_t*)46);
	printnumber_lcd(N_tong);
	
    while(1){
		/*N?u nh?n phím select thì giá tr? t?n s? ???c ch?n
		s? truy?n vào thanh ghi c?a chip */
	 if(bit_is_clear(PIND,PD1)){
		 _delay_ms(10);
		 LCD_goto(2,1);
		 lcd_write_string_4d("chon tan so")
		 //tr??c khi b?t ??u truy?n kéo chân RST c?a chip xu?ng m?c th?p
		 clearbit(CTRL_PORT,en);
		 write_N_and_A_divide(15,val);
		 //sau khi truy?n t?t c? 21 bit vào thanh ghi kéo chân RST lên l?i m?c cao 
		 setbit(CTRL_PORT,en);
		 
     }
	 //n?u nh?n phím save thì n?p giá tr? b? nh? t?ng và epprom
	 else if(bit_is_clear(PIND,PD0)){
		 
		 _delay_ms(10);
		 eeprom_write_byte((uint8_t *)46,N_tong);
		 clear_lcd();
		 LCD_goto(1,1);
	     lcd_write_string_4d("luu tan so ");
		 LCD_goto(2,1);
		 printnumber_lcd(N_tong);
		 LCD_goto(2,4);
		 lcd_write_string_4d("MHz");
		 _delay_ms(10000);
		 clear_lcd();
		 LCD_goto(1,1);
	     lcd_write_string_4d("tan so : ");
	     LCD_goto(1,9);
	     
	
         N_tong=eeprom_read_byte((uint8_t*)46);

	     printnumber_lcd(N_tong);
	 }
	 
   } 
return 0;
}
//s? d?ng ng?t ngoài c?a chip atmega16 ?? t?ng gi?m giá tr? t?n s?
ISR(INT0_vect){
	//val là giá tr? c?a b? chia A
	val=val+20;
	//tính toán b? chia t?ng
    N_tong=((1*(pow(10,-3)))*50)*(128*15+val);	
	_delay_ms(10);
	LCD_goto(1,9);
	printnumber_lcd(N_tong);
	
}
ISR(INT1_vect){
	val=val-20;
	N_tong=((1*(pow(10,-3)))*50)*(128*15+val);
	_delay_ms(10);
	LCD_goto(1,9);
	printnumber_lcd(N_tong);
	
}