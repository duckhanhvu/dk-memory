/*
 * project_6.c
 *
 * Created: 1/5/2016 10:15:39 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include "text_LCD.h"
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <math.h>
#include <stdio.h>

#ifndef cbi
     #define cbi(port,bit)  (port)&=~(1<<bit)
#endif
#ifndef sbi
     #define sbi(port,bit)  (port)|=(1<<bit)
#endif

#define MOTOR_DDR   DDRD
#define MOTOR_PORT  PORTD
#define MOTOR_DIR   6
#define MOTOR_EN    7
#define Sampling_time        25    //ms
#define inv_Sampling_time    40 
#define PWM_period    8000

volatile long int pulse, pre_pulse;
volatile long int rSpeed, Err, pre_Err,kp=8, kd=10,ki=1;
volatile long int pPart=0, iPart=0, dPart=0;
volatile long int Ctrl_speed=5;
volatile long int output;
volatile unsigned char sample_count=0;

void MOTOR_Speed_PID(long int des_speed){
	rSpeed=pulse-pre_pulse;
	pre_pulse=pulse;
	
	Err=des_speed-abs(rSpeed);
	
	pPart=kp*Err;
	dPart=kd*(Err-pre_Err)*inv_Sampling_time;
	iPart+=ki*Err*Sampling_time/1000;
	
	output+=pPart+dPart+iPart;
	
	if(output>=PWM_period) output=PWM_period-1;
	if(output<=0) output=1;
	
	OCR1A=output;
	pre_Err=Err;
	
}

int main(void)
{
	pulse=0;
	
	DDRB=0x00;
	PORTB=0xFF;
	
	MOTOR_DDR=0xF0;
	sbi(MOTOR_PORT,MOTOR_DIR);
	
	MCUCSR|=(0<<ISC2);
	GIFR|=(1<<INT2);
	
	TCCR2=(1<<CS22)|(1<<CS21)|(1<<CS20);
	TCNT2=60;
	TIMSK=(1<<TOIE2);
	
	TCCR1A=(1<<COM1A1)|(1<<WGM11);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
	
	init_lcd();
	_delay_ms(1000);
	clear_lcd();
	putstr_lcd("Actual:   /25ms",15);
	movecursor(2,1);
	putstr_lcd("Desired:   /25ms",16);
	
	OCR1A=1;
	ICR1=PWM_period;
	sbi(MOTOR_PORT,MOTOR_EN);
	sei();
    while(1)
    {
		if(sample_count>=10){
			Ctrl_speed=(PINB>>4)*0x0F;
			movecursor(1,8);
			printnumber_lcd(rSpeed);
			movecursor(2,9);
			printnumber_lcd(Ctrl_speed);
			sample_count=0;
		}
    }
}
ISR(TIMER2_OVF_vect){
	TCNT2=60;
	MOTOR_Speed_PID(Ctrl_speed);
	sample_count++;
}
ISR(INT2_vect){
	if(bit_is_set(PORTB,0)) pulse++;
	else pulse--;
}