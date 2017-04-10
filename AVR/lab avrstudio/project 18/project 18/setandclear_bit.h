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



#ifdef __ASSEMBLER__
#define _SFR_ASM_COM 1
#elif !defined(_SFR_ASM_COMPAT)
#define _SFR_ASM_COM 0
#endif

#ifndef __ASSEMBLER__
/* These only work in C programs.  */
#include <inttypes.h>

#define _MMIO_BY(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_W(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define _MMIO_DW(mem_addr) (*(volatile uint32_t *)(mem_addr))
#endif

#if _SFR_ASM_COM

#ifndef __SFR_OFF
/* Define as 0 before including this file for compatibility with old asm
   sources that don't subtract __SFR_OFFSET from symbolic I/O addresses.  */
#  if __AVR_ARCH__ >= 100
#    define __SFR_OFF 0x00
#  else
#    define __SFR_OFF 0x20
#  endif
#endif

#if (__SFR_OFF != 0) && (__SFR_OFF != 0x20)
#error "__SFR_OFF must be 0 or 0x20"
#endif

#define _SFR_ME8(mem_addr) (mem_addr)
#define _SFR_ME16(mem_addr) (mem_addr)
#define _SFR_ME32(mem_addr) (mem_addr)
#define _SFR_I8(io_addr) ((io_addr) + __SFR_OFF)
#define _SFR_I16(io_addr) ((io_addr) + __SFR_OFF)

#define _SFR_I_ADDR(sfr) ((sfr) - __SFR_OFF)
#define _SFR_M_ADDR(sfr) (sfr)
#define _SFR_I_REG_P(sfr) ((sfr) < 0x40 + __SFR_OFF)

#if (__SFR_OFFSET == 0x20)
/* No need to use ?: operator, so works in assembler too.  */
#define _SFR_AD(sfr) _SFR_M_ADDR(sfr)
#elif !defined(__ASSEMBLER__)
#define _SFR_AD(sfr) (_SFR_I_REG_P(sfr) ? (_SFR_I_ADDR(sfr) + 0x20) : _SFR_M_ADDR(sfr))
#endif

#else  /* !_SFR_ASM_COMPAT */

#ifndef __SFR_OFF
#  if __AVR_ARCH__ >= 100
#    define __SFR_OFF 0x00
#  else
#    define __SFR_OFF 0x20
#  endif
#endif

#define _SFR_ME8(mem_addr) _MMIO_BY(mem_addr)
#define _SFR_ME16(mem_addr) _MMIO_W(mem_addr)
#define _SFR_ME32(mem_addr) _MMIO_DW(mem_addr)
#define _SFR_I8(io_addr) _MMIO_BY((io_addr) + __SFR_OFF)
#define _SFR_I16(io_addr) _MMIO_W((io_addr) + __SFR_OFF)

#define _SFR_M_ADDR(sfr) ((uint16_t) &(sfr))
#define _SFR_I_ADDR(sfr) (_SFR_M_ADDR(sfr) - __SFR_OFF)
#define _SFR_I_REG_P(sfr) (_SFR_M_ADDR(sfr) < 0x40 + __SFR_OFF)

#define _SFR_AD(sfr) _SFR_M_ADDR(sfr)

#endif /* !_SFR_ASM_COMPAT */

#define _SFR_BY(sfr) _MMIO_BY(_SFR_AD(sfr))
#define _SFR_W(sfr) _MMIO_W(_SFR_AD(sfr))
#define _SFR_DW(sfr) _MMIO_DW(_SFR_AD(sfr))

#define bit_is_cl(sfr, bit) (!(_SFR_BY(sfr) & bv(bit)))
#endif /* SETANDCLEAR_BIT_H_ */