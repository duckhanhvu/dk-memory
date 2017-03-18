/*******************************************************************************
  *Ten Tep         :     main.h
  *Ngay            :     05/07/2014
  *Tac Gia         :     MinhHa R&D Team
  *Cong Ty         :     MinhHaGroup
  *Webside         :     mcu.banlinhkien.vn
  *Phien Ban       :     V1.0
  *Tom Tat         :     Khai bao cac thu vien.
  *                      Cau hinh mot so chuc nang cho trinh bien dich.
  *                      Cau hinh mot so chuc nang cho CHIP.
  *                      Dinh nghia I/O.
  *
  *
  *****************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H    5072014

/******************************************************************************
PRO_DATA - FOSC - PRO_DATA - FOSC -PRO_DATA - FOSC -PRO_DATA - FOSC - PRO_DATA
******************************************************************************/
#define PRO_DATA   flash
/*    Kieu So Nguyen Co Dau    */
typedef   signed          char int8_t;
typedef   signed 	       int int16_t;
typedef   signed long      int int32_t;

/*	Kieu So Nguyen Khong Dau */
typedef   unsigned         char uint8_t;
typedef   unsigned 	       int  uint16_t;
typedef   unsigned long    int  uint32_t;
/*	Kieu So Thuc */
typedef   float            float32_t;
/******************************************************************************
  COMPILER LIB - COMPILER LIB - COMPILER LIB - COMPILER LIB - COMPILER LIB
******************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>
#include <mega16.h>
/******************************************************************************
  PROJECT LIB - PROJECT LIB - PROJECT LIB - PROJECT LIB - PROJECT LIB 
******************************************************************************/

/******************************************************************************
  USERAVR LIB - USERAVR LIB - USERAVR LIB - USERAVR LIB - USERAVR LIB 
******************************************************************************/
#include "UserAVR\Include\DEF_AVR.h"
/******************************************************************************
  USER LIB - USER LIB - USER LIB - USER LIB - USER LIB - USER LIB - USER LIB
******************************************************************************/
#include "User\Include\lcd16x2.h"
#include "User\Include\i2c.h"
#include "User\Include\ds1307.h"
/******************************************************************************
DEFINE GPIO - DEFINE GPIO - DEFINE GPIO - DEFINE GPIO - DEFINE GPIO - DEFINE GPIO
******************************************************************************/
/*________________________________ GPIO A ____________________________________*/
/*________________________________ GPIO B ____________________________________*/
#define LCD16X2_D4    PORTB_4
#define LCD16X2_D5    PORTB_5
#define LCD16X2_D6    PORTB_6
#define LCD16X2_D7    PORTB_7
/*________________________________ GPIO C ____________________________________*/
#define I2CSOFT_SDADDR    DDRC_1
#define I2CSOFT_SDAOUT    PORTC_1
#define I2CSOFT_SDAIN     PINC_1       
#define I2CSOFT_SCLDDR    DDRC_0
#define I2CSOFT_SCL       PORTC_0

#define	LCD16X2_RS    PORTC_3
#define	LCD16X2_RW    PORTC_4
#define	LCD16X2_EN    PORTC_5
/*________________________________ GPIO D ____________________________________*/
/*________________________________ GPIO E ____________________________________*/
/*________________________________ GPIO F ____________________________________*/
/*________________________________ GPIO G ____________________________________*/

#endif 
/*------------------------------KET THUC FILE-------------------------------
______________________________MinhHa R&D Team______________________________*/