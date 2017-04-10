/*
 * master.c
 *
 * Created: 11/18/2015 10:47:57 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "setandclear_bit.h"
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include "text_LCD.h"

#define CTRL_DDR   DDRA
#define CTRL_PORT   PORTA
#define data  1
#define clk   2
#define en    3
volatile unsigned int b[14]={0}; 
volatile unsigned int n[10]={0};
volatile unsigned int a[10]={0};		
void write(unsigned int i){
	CTRL_DDR=0xFF;
	if(i==1){// chuan chuan
	      setbit(CTRL_PORT, data);    // Load 1 on DATA  
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
		b[i]=number%2;	
		number=number/2;
		i++;
	  }        
	  for(i=0;i<14;i++){
		write(b[i]) ;
	  }
	  write(1);
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
		a[j]=Anumber%2;	
		Anumber=Anumber/2;
		j++;
	  }
	  for(i=0;i<10;i++){
		write(n[i]) ;
	  }
	  for(j=0;i<8;j++){
		 write(a[j]); 
	  }
	  write(0);

}
void enable(void){
	CTRL_DDR=0xFF;
	setbit(CTRL_PORT,en);   // Bring ENABLE high
    _delay_ms(100);
    clearbit(CTRL_PORT,en);    // Then back low
}

int main(){
	while(1){
	_delay_ms(100);
	write_reference(512);
	enable();
	
	write_N_and_A_divide(452,0);
	enable();
	}	
	return 0;
}