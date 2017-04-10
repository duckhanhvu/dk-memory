/*
 * i2c.h
 *
 * Created: 2/7/2017 16:07:12
 *  Author: duckhanh
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t v_i2cData_u8);
uint8_t I2C_Read(uint8_t v_ackOption_u8);




#endif /* I2C_H_ */