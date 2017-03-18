/*
 * setandclear_bit.h
 *
 * Created: 11/17/2015 9:40:56 PM
 *  Author: Duc Khanh
 */ 


#ifndef SETANDCLEAR_BIT_H_
#define SETANDCLEAR_BIT_H_

#define bv(bit)                     (1<<bit)
#define setbit(register_data,bit)   register_data|=bv(bit)
#define clearbit(register_data,bit) register_data&=~bv(bit)


#endif /* SETANDCLEAR_BIT_H_ */