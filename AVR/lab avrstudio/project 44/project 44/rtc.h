/*
 * rtc.h
 *
 * Created: 2/7/2017 16:22:20
 *  Author: duckhanh
 */ 


#ifndef RTC_H_
#define RTC_H_
#include <avr/io.h>

typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t weekDay;
  uint8_t date;
  uint8_t month;
  uint8_t year;  
}rtc_t;

#define C_Ds1307ReadMode_U8   0xD1u  // DS1307 ID
#define C_Ds1307WriteMode_U8  0xD0u  // DS1307 ID

#define C_Ds1307SecondRegAddress_U8   0x00u   // Address to access Ds1307 SEC register
#define C_Ds1307DateRegAddress_U8     0x04u   // Address to access Ds1307 DATE register
#define C_Ds1307ControlRegAddress_U8  0x07u   // Address to access Ds1307 CONTROL register

void RTC_Init(void);
void RTC_SetDateTime(rtc_t rtc);
void RTC_GetDateTime(rtc_t rtc);



#endif /* RTC_H_ */