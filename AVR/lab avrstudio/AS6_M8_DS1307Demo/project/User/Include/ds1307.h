/*****************************************************************************
  *Ten Tep          :     ds1307.h
  *Ngay             :     19/03/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Khai bao cac ham giao tiep DS1307
  ******************************************************************************/
  
#ifndef __DS1307_H
#define __DS1307_H    19032014

#include "Main/main.h"

// Dinh nghia cac thanh ghi trong DS1307
#define DS1307_ADDR_WRITE     0xd0
#define DS1307_ADDR_READ      0xd1
#define DS1307_ADDR_SECOND    0x00
#define DS1307_ADDR_MINUTE    0x01
#define DS1307_ADDR_HOUR      0x02
#define DS1307_ADDR_DAY       0x03
#define DS1307_ADDR_DATE      0x04
#define DS1307_ADDR_MONTH     0x05
#define DS1307_ADDR_YEAR      0x06
#define DS1307_ADDR_CONTROL   0x07
#define DS1307_SQW_1Hz        0x10
#define DS1307_SQW_4096KHz    0x11    // 4.096KHz
#define DS1307_SQW_8192KHz    0x12    // 8.192KHz
#define DS1307_SQW_32768Hz    0x13    // 32.768KHz

/*******************************************************************************
Noi Dung    :   Khoi tao DS1307.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_Init(void);

/*******************************************************************************
Noi Dung    :   Ghi du lieu vao 1 thanh ghi trong DS1307.
Tham Bien   :   Address : Dia chi thanh ghi.
                Data    : Du lieu can ghi.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_WriteData(uint8_t Address, uint8_t Data);

/*******************************************************************************
Noi Dung    :   Doc du lieu cua 1 thanh ghi trong DS1307.
Tham Bien   :   Address : Dia chi thanh ghi.
Tra Ve      :   Du lieu cua thanh ghi.
********************************************************************************/

uint8_t DS1307_ReadData(uint8_t Address);

/*******************************************************************************
Noi Dung    :   Cho phep xuat xung vuong tren chan SQW/OUT.
Tham Bien   :   State=0: Khong cho phep xuat xung vuong.
                     =1: Cho phep xuat xung vuong.
			    Mode   : Thiet lap tan so xung vuong xuat ra.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetControl(uint8_t State,uint8_t Mode);

/*******************************************************************************
Noi Dung    :   Ghi du lieu Thu/Ngay/Thang/Nam vao DS1307.
Tham Bien   :   Day   : Thu.
                Date  : Ngay.
                Month : Thang.
				Year  : Nam.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetDate(uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year);

/*******************************************************************************
Noi Dung    :   Ghi du lieu Giay/Phut/Gio vao DS1307.
Tham Bien   :   Second : Giay.
                Minute : Phut.
				Hour   : Gio.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetTime(uint8_t Hour, uint8_t Minute, uint8_t Second);

/*******************************************************************************
Noi Dung    :   Doc du lieu Thu/Ngay/Thang/Nam tu DS1307.
Tham Bien   :   *Day   : Thu.
				*Date  : Ngay.
                *Month : Thang.
				*Year  : Nam.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_GetDate(uint8_t *Day, uint8_t *Date, uint8_t *Month, uint8_t *Year);

/*******************************************************************************
Noi Dung    :   Doc du lieu Giay/Phut/Gio tu DS1307.
Tham Bien   :   *Second : Giay.
                *Minute : Phut.
				*Hour   : Gio.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_GetTime(uint8_t *Hour, uint8_t* Minute, uint8_t* Second);

#endif
/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/