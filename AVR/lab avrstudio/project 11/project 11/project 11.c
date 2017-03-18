/*
 * project_11.c
 *
 * Created: 1/10/2016 10:01:27 PM
 *  Author: Duc Khanh
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "text_LCD.h"

int main(void)
{
  init_lcd();
  int i;	
  while(1){
  for(i=0;i<4;i++){
	  movecursor(1,i+1);
	  printnumber_lcd(i);
  }  
  }  
  return 0;
}