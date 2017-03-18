/*
 * project_9.c
 *
 * Created: 1/7/2016 2:06:43 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <avr/sfr_defs.h>
#include "text_LCD.h"
#include "setandclear_bit.h"
#include <avr/delay.h>
#include "matrix4x4.h"

#define MOTOR_DDR   DDRD
#define MOTOR_PORT  PORTD
#define MOTOR_DIR   6
#define MOTOR_EN    7
#define Time_period_PWM  8000

volatile unsigned char  k,key,x=0;
volatile long int control_speed=5, count=0;
volatile long int Reality_speed;
volatile long int pulse, pre_pulse=0;
volatile long int error_PID, pre_error, P_PID, D_PID, I_PID=0, output_PID=0;
volatile long int kp=8, ki=1, kd=10;

void PID_control_speed(long int Titular_speed){
	Reality_speed = pulse - pre_pulse;
	pre_pulse=pulse;
	
	error_PID= Titular_speed- abs(Reality_speed);
	
	//cac thanh phan PID
	P_PID=error_PID*kp;
	D_PID=(error_PID-pre_error)*40*kd;  
	I_PID+= (ki*error_PID*25)/1000;
	
	output_PID+= P_PID + D_PID + I_PID;
	
	//dieu chinh dau ra PID phu hop voi PWM
	
	if(output_PID>=Time_period_PWM){
	  output_PID= Time_period_PWM-1;
	  }
	if(output_PID<=0){
	  output_PID=1;
	  }
	
	// bam xung PWM cho output_PID
	
	OCR1A=output_PID;
	pre_error=error_PID;
}

int main(void)
{
	PORTB=0xFF;
	
	PORTA=0xFF;
    DDRA=0x0F; 
	
	MOTOR_DDR=0xF0;
	setbit(MOTOR_PORT,MOTOR_DIR);
	
	//khoi tao ngat ngoai tren chan INT2
	MCUCSR=(0<<ISC2);
	GICR=(1<<INT2);
	
	//tao bo dinh thoi gian 25ms bang timer 0
	TCCR0=(1<<CS02)|(1<<CS00);//|(1<<CS20);
	TCNT0=60;
	TIMSK=(1<<TOIE0);
	
	//tao bo PWM tren timer 1, mode 14, fast PwM 
	TCCR1A=(1<<COM1A1)|(1<<WGM11);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
	
	
	TCCR2=0;
	TIMSK|=(1<<TOIE2);

	
	
	init_lcd();
	movecursor(1,1);
	putstr_lcd("DUC KHANH",9);
	movecursor(2,1);
	putstr_lcd("28-4-2016",9);
	_delay_ms(10000);
	clear_lcd();
	movecursor(1,1);
    putstr_lcd("set van toc:",12);
	movecursor(2,4);
	
	/*clear_lcd();
	movecursor(1,1);
	putstr_lcd("vset:      /25ms",16);
	movecursor(2,1);
	putstr_lcd("vthuc:     /25ms",16);
	*/
	OCR1A=1;
	ICR1=Time_period_PWM;
	
	//setbit(MOTOR_PORT,MOTOR_EN);
	sei();
	
    while(1)
    {

		/*if(count>=10){
			control_speed=(PINB>>4)&0x0F;
		    movecursor(1,6);
			printnumber_lcd(control_speed);
			movecursor(2,7);
			printnumber_lcd(Reality_speed);
			count=0;
		}*/
	   key =KEY4x4_Getkey();
	   
	   if(key){
		   TCNT2=0;
		   TCCR2=(1<<CS22);
		   k=key;
	   }
	   if(bit_is_clear(PINB,3)){
		   break;
	   }
        
    }
	  clear_lcd();
	  movecursor(1,1);
	  putstr_lcd("da nhap du lieu",15);
	  movecursor(2,4);
	  putstr_lcd("thanh cong",10);
	  _delay_ms(20000);
	  clear_lcd();

	  
	  movecursor(1,1);
	  putstr_lcd("vset:      /25ms",16);
	  movecursor(2,1);
	  putstr_lcd("vthuc:     /25ms",16);
	  setbit(MOTOR_PORT,MOTOR_EN);
	  while(1){
		  	if(count>=10){

			control_speed=x;
			movecursor(1,6);
			printnumber_lcd(control_speed);
			movecursor(2,7);
			printnumber_lcd(Reality_speed);
			count=0;
	  }
}
	}
ISR(TIMER0_OVF_vect){
	TCNT2=60;
	PID_control_speed(control_speed);
	count++;
}
ISR(INT2_vect){
	if(bit_is_set(PORTB,0)) pulse++;
	else pulse--;	
}
ISR(TIMER2_OVF_vect){
	printnumber_lcd(k);
	x=x*10+k;
	TCNT2=0;
	TCCR2=0;
	
}