/*
 * CProgram1.c
 *
 * Created: 1/7/2016 1:21:54 AM
 *  Author: Duc Khanh
 */ 
/*
 * PID_encoder_motor.c
 *
 * Created: 1/3/2016 10:12:54 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <avr/sfr_defs.h>
#include "text_LCD.h"
#include "setandclear_bit.h"
#include <avr/delay.h>

#define MOTOR_DDR   DDRD
#define MOTOR_PORT  PORTD
#define MOTOR_DIR   6
#define MOTOR_EN    7
#define Time_period_PWM  8000


volatile long int control_speed, count=0;
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
	
	if(output_PID>=Time_period_PWM){  output_PID= Time_period_PWM-1;}
	else	if(output_PID<=0){ output_PID=1;}
	
	// bam xung PWM cho output_PID
	
	OCR1A=output_PID;
	pre_error=error_PID;
}
int main(){
	pulse=0;
	
	DDRA=0xFF;
	PORTA=0xFF;
	DDRB=0x00;
	PORTB=0xFF;
	
	DDRD=0xF0;
	//sbi(MOTOR_PORT,MOTOR_DIR);
	
	MCUCSR|=(0<<ISC2);
	GICR|=(1<<INT2);
	
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
	ICR1=Time_period_PWM;
	setbit(MOTOR_PORT,MOTOR_EN);
	


	sei();
    while(1)
    {
		if(count>=10){
			control_speed=(PINB>>4)&0x0F;
			movecursor(1,8);
			printnumber_lcd(Reality_speed);
			movecursor(2,9);
			printnumber_lcd(control_speed);
			count=0;
		}
    }
}
ISR(TIMER2_OVF_vect){
	TCNT2=60;
	PID_control_speed(control_speed);
	count++;
}
ISR(INT2_vect){
	if(bit_is_set(PORTB,0)) pulse++;
	else pulse--;
}