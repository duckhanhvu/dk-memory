/*
 * matrix4x4.h
 *
 * Created: 1/14/2016 10:58:33 PM
 *  Author: Duc Khanh
 */ 


#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_
#include <avr/io.h>

#define control_port PORTC
#define control_pin  PINC
#define KEY4x4_COL1  4
#define KEY4x4_COL2  5
#define KEY4x4_COL3  6
#define KEY4x4_COL4  7

#define KEY4x4_ROW1  3
#define KEY4x4_ROW2  2
#define KEY4x4_ROW3  1
#define KEY4x4_ROW4  0


unsigned char KEY4x4_Ispush(void);
unsigned char KEY4x4_Getkey(void);
void KEY4x4_checkROW(unsigned char i);

#endif /* MATRIX4X4_H_ */