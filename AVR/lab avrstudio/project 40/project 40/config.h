/*
 * config.h
 *
 * Created: 15/06/2014 12:44:43 PM
 *  Author: Avinash
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA		D		//Port PD3-PD6 are connected to D4-D7
#define LCD_DATA_POS	3

#define LCD_E			D		//Enable/strobe signal
#define LCD_E_POS		PD7		//Position of enable in above port

#define LCD_RS			B		//Register Select signal (RS)-> PB2
#define LCD_RS_POS		PB2

#define LCD_RW			B		//Read/Write signal (R/W) ->PB0
#define LCD_RW_POS		PB0

/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//************************************************

#endif /* CONFIG_H_ */