/********************************************************************

Keypad library for three way navigation and one delete(X) key.
[LEFT] [RIGHT] [ENTER] [X]
For xBoard MINI v2.1

Features:
	Automatic 80 FPS scanning using TIMER0
	3 point major polling for complete noise free operation
	Fully debounced.
	Automatic buffering of commands (no missed key press!)
	Automatic repeat when user presses and hold a key.  

Written By:
	Avinash Gupta


Copyright 2008-2014
eXtreme Electronics, India
www.eXtremeElectronics.co.in
********************************************************************/

#ifndef DPAD_H
#define DPAD_H

#include <avr/io.h>

/******************************************************************************

Simple HAL (Hardware Abstraction Layer) for a standard 2 direction + 1 center
DPAD (directional key pad).

******************************************************************************/

/*

Connection Area, Can be used to configure the i/o line of buttons.

*/


//LEFT KEY
#define D_LEFT_KEY_DDR 		DDRC
#define D_LEFT_KEY_PORT 	PORTC
#define D_LEFT_KEY_PIN		PINC
#define D_LEFT_KEY_POS		PC0

//RIGHT KEY
#define D_RIGHT_KEY_DDR 	DDRC
#define D_RIGHT_KEY_PORT 	PORTC
#define D_RIGHT_KEY_PIN		PINC
#define D_RIGHT_KEY_POS		PC1

//ENTER KEY
#define D_ENTER_KEY_DDR 	DDRC
#define D_ENTER_KEY_PORT 	PORTC
#define D_ENTER_KEY_PIN		PINC
#define D_ENTER_KEY_POS		PC2

//DEL KEY
#define DEL_KEY_DDR 	DDRC
#define DEL_KEY_PORT 	PORTC
#define DEL_KEY_PIN		PINC
#define DEL_KEY_POS		PC3


#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_ENTER	3
#define KEY_DEL		4
#define KEY_NONE	99


#define PRESSED		0
#define RELEASED	1

//Queue
#define KEYPAD_QMAX 32


void KeypadInit();
uint8_t GetRawKeyState(uint8_t KeyCode);
uint8_t MajorVote(uint8_t keycode);
uint8_t GetKeypadCmd(char wait);

#endif




