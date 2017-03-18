/*****************************************************************************
  *Ten Tep          :     ds1307.c
  *Ngay             :     19/03/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac ham giao tiep DS1307
  ******************************************************************************/
  
#include "User/Include/ds1307.h"

#if (__DS1307_H!=19032014)
    #error "Include Sai File ds1307.h"
#endif

/*******************************************************************************
Noi Dung    :   Khoi tao DS1307.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_Init(void)
{
    I2CSOFT_Init();
}

/*******************************************************************************
Noi Dung    :   Ghi du lieu vao 1 thanh ghi trong DS1307.
Tham Bien   :   Address : Dia chi thanh ghi.
                Data    : Du lieu can ghi.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_WriteData(uint8_t Address, uint8_t Data)
{
   uint8_t Dataw;
   Dataw =  ((Data/10)<<4) + (Data % 10);
   I2CSOFT_Start();
   I2CSOFT_WriteData(DS1307_ADDR_WRITE);
   I2CSOFT_WriteData(Address);
   I2CSOFT_WriteData(Dataw);
   I2CSOFT_Stop();
}

/*******************************************************************************
Noi Dung    :   Doc du lieu cua 1 thanh ghi trong DS1307.
Tham Bien   :   Address: Dia chi thanh ghi.
Tra Ve      :   Du lieu cua thanh ghi.
********************************************************************************/

uint8_t DS1307_ReadData(uint8_t Address)
{
   uint8_t Data;
   I2CSOFT_Start();
   I2CSOFT_WriteData(DS1307_ADDR_WRITE);
   I2CSOFT_WriteData(Address);
   I2CSOFT_Start();
   I2CSOFT_WriteData(DS1307_ADDR_READ);
   Data=I2CSOFT_ReadData(0);
   I2CSOFT_Stop();
   Data = ((Data>>4) * 10 + Data % 16);
   return(Data);
}

/*******************************************************************************
Noi Dung    :   Cho phep xuat xung vuong tren chan SQW/OUT.
Tham Bien   :   State=0: Khong cho phep xuat xung vuong.
                     =1: Cho phep xuat xung vuong.
			    Mode   : Thiet lap tan so xung vuong xuat ra.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetControl(uint8_t State,uint8_t Mode)
{
    if(!State)
    {
        DS1307_WriteData(DS1307_ADDR_CONTROL,0x00);
    }
    else
    {
        DS1307_WriteData(DS1307_ADDR_CONTROL,Mode);
    }    
}

/*******************************************************************************
Noi Dung    :   Ghi du lieu Thu/Ngay/Thang/Nam vao DS1307.
Tham Bien   :   Day   : Thu.
                Date  : Ngay.
                Month : Thang.
				Year  : Nam.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetDate(uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year)
{
    DS1307_WriteData(DS1307_ADDR_DAY,Day);
    DS1307_WriteData(DS1307_ADDR_DATE,Date);
    DS1307_WriteData(DS1307_ADDR_MONTH,Month);
    DS1307_WriteData(DS1307_ADDR_YEAR,Year);
}

/*******************************************************************************
Noi Dung    :   Ghi du lieu Giay/Phut/Gio vao DS1307.
Tham Bien   :   Second : Giay.
                Minute : Phut.
				Hour   : Gio.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_SetTime(uint8_t Hour, uint8_t Minute, uint8_t Second)
{
    DS1307_WriteData(DS1307_ADDR_SECOND,Second);
    DS1307_WriteData(DS1307_ADDR_MINUTE,Minute);
    DS1307_WriteData(DS1307_ADDR_HOUR,Hour);
}

/*******************************************************************************
Noi Dung    :   Doc du lieu Thu/Ngay/Thang/Nam tu DS1307.
Tham Bien   :   *Day   : Thu.
				*Date  : Ngay.
                *Month : Thang.
				*Year  : Nam.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_GetDate(uint8_t *Day, uint8_t *Date, uint8_t *Month, uint8_t *Year)
{
    *Day    =   DS1307_ReadData(DS1307_ADDR_DAY);
    *Date   =   DS1307_ReadData(DS1307_ADDR_DATE);
    *Month  =   DS1307_ReadData(DS1307_ADDR_MONTH);
    *Year   =   DS1307_ReadData(DS1307_ADDR_YEAR);     
}

/*******************************************************************************
Noi Dung    :   Doc du lieu Giay/Phut/Gio tu DS1307.
Tham Bien   :   *Second : Giay.
                *Minute : Phut.
				*Hour   : Gio.
Tra Ve      :   Khong.
********************************************************************************/

void DS1307_GetTime(uint8_t *Hour, uint8_t* Minute, uint8_t* Second)
{
    *Hour    =  DS1307_ReadData(DS1307_ADDR_HOUR);
    *Minute  =  DS1307_ReadData(DS1307_ADDR_MINUTE);
    *Second  =  DS1307_ReadData(DS1307_ADDR_SECOND);
}

/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/                                                                                               