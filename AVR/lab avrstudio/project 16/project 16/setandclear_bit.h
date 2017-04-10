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

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_MEM_ADDR(sfr) (sfr)

#define _SFR_ADDR(sfr) _SFR_MEM_ADDR(sfr)



#define _SFR_BYTE(sfr) _MMIO_BYTE(_SFR_ADDR(sfr))

#define set(sfr, bit) (_SFR_BYTE(sfr) & bv(bit))
#define clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

#endif /* SETANDCLEAR_BIT_H_ */