/*
 * matrix4x4.c
 *
 * Created: 1/14/2016 10:59:55 PM
 *  Author: Duc Khanh
 */ 
/*
 * project_10.c
 *
 * Created: 1/8/2016 4:16:31 PM
 *  Author: Duc Khanh
 */ 


#include <avr/io.h>
#include "text_LCD.h"
#include <avr/sfr_defs.h>
#include "setandclear_bit.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "matrix4x4.h"




volatile unsigned char KEY_4x4[4][4]={{1,2,3,4},
                                    {5,6,7,8},
                                    {9,0,1,2},
                                    {3,4,5,6}};
//volatile uint8_t val=0;
/*
#define CTRL          PORTC
#define DDR_CTRL      DDRC

#define DATA_O        PORTC
#define DATA_I        PINC
#define DDR_DATA      DDRC

#define KEYPAD_DDR    DDRD
#define KEYPAD_PIN    PIND
#define KEYPAD_PORT   PORTD
*/
//volatile unsigned int hien[4]={0,0,0,0};
	/*
volatile unsigned char KEY_4x4[4][4]={{1,2,3,4},
                                    {5,6,7,8},
                                    {9,0,1,2},
                                    {3,4,5,6}};*/

/*
uint8_t scan_code[4]={0x0E,0x0D,0x0B,0x07};	
uint8_t ascii_code[4][4]={{'7','8','9','/'},
                          {'4','5','6','*'},
						  {'1','2','3','-'},
						  {'N','0','=','+'}};		
*/							  
							  							
/*
void quetlcd(void)
 {
  uint8_t x=0;
 // for(int j=3;j>=3;j++){
  x=hien[3]*100;
  movecursor(1,1);
  printnumber_lcd(x);
 //}
 } 
*/
/*           
unsigned int quet_phim(void){
    
    int a[4]={0b11111110,0b11111101,0b11111011,0b11110111};
    int dong;
   
    PORTD=0b11111111;
    for(dong=0;dong<4;dong++){
    PORTD=a[dong];

    if(bit_is_clear(PIND,4)){
    _delay_ms(5);
    if(bit_is_clear(PIND,4)){
    return KEY_4x4[dong][0];
    }
    }
    if(bit_is_clear(PIND,5)){
    _delay_ms(5);
    if(bit_is_clear(PIND,5)){
    return KEY_4x4[dong][1];
    }
    }
    if(bit_is_clear(PIND,6)){
    _delay_ms(5);
    if(bit_is_clear(PIND,6)){
    return KEY_4x4[dong][2];
    }
    }
    if(bit_is_clear(PIND,7)){
    _delay_ms(5);
    if(bit_is_clear(PIND,7)){
    return KEY_4x4[dong][3];
    }
    }
}

return 0;
}
*/

unsigned char KEY4x4_Ispush(void){
if((bit_is_clear(control_pin,KEY4x4_COL1))|(bit_is_clear(control_pin,KEY4x4_COL2))|(bit_is_clear(control_pin,KEY4x4_COL3))|(bit_is_clear(control_pin,KEY4x4_COL4)))
return 1;
else return 0;
}
void KEY4x4_checkROW(unsigned char i){

setbit(control_port,KEY4x4_ROW1);
setbit(control_port,KEY4x4_ROW2);
setbit(control_port,KEY4x4_ROW3);
setbit(control_port,KEY4x4_ROW4);
if(i==0){
    clearbit(control_port,KEY4x4_ROW1);
}
if(i==1){
    clearbit(control_port,KEY4x4_ROW2);
}
if(i==2){
    clearbit(control_port,KEY4x4_ROW3);
}
if(i==3){
    clearbit(control_port,KEY4x4_ROW4);
}   
}
unsigned char KEY4x4_Getkey(void){
unsigned char i,button;
clearbit(control_port,KEY4x4_ROW1);
clearbit(control_port,KEY4x4_ROW2);
clearbit(control_port,KEY4x4_ROW3);
clearbit(control_port,KEY4x4_ROW4);

if(KEY4x4_Ispush()){
_delay_ms(5);
if(KEY4x4_Ispush()){
for(i=0;i<4;i++){
KEY4x4_checkROW(i);
if(bit_is_clear(control_pin,KEY4x4_COL1))  return KEY_4x4[i][0];
if(bit_is_clear(control_pin,KEY4x4_COL2))  return KEY_4x4[i][1];
if(bit_is_clear(control_pin,KEY4x4_COL3))  return KEY_4x4[i][2];
if(bit_is_clear(control_pin,KEY4x4_COL4))  return KEY_4x4[i][3];
}
}
}
return 0;
}

/*
uint8_t key;
uint8_t checkpad();
uint8_t checkpad(void){
	uint8_t i,j,keyin;
	for(i=0;i<4;i++){
		KEYPAD_PORT=0xFF-(1<<(i+4));
		_delay_us(10);
		keyin=KEYPAD_PIN&0x0F;
		if(keyin!=0x0F){
			for(j=0;j<4;j++){
				if(keyin==scan_code[j])
				   return ascii_code[j][i];
			}
		}
	}
}
*/
/*
void main(void)
{
	
init_lcd();

PORTA=0xFF;
DDRA=0xFF;

DDRC=0xFF;
PORTC=0x00;
 


PORTD=0xFF;
DDRD=0x0F; 

/*
DDRD=0xF0;
PORTD=0x0F;
*/
/*
TCCR0=0;//TCCR0=(1<<CS02)|(1<<CS00);

TIMSK=(1<<TOIE0);
sei();
clear_lcd();
cursor_home();

while(1){
       int i;
       key =KEY4x4_Getkey();
	   
	   if(key){
		   TCNT0=0;
		   TCCR0=(1<<CS02)|(1<<CS00);
		   k=key;
	   }	       
	   }	  
return 0;
}
ISR(TIMER0_OVF_vect){
	    printnumber_lcd(k);
		TCNT0=0;
	    TCCR0=0;	
}
*/