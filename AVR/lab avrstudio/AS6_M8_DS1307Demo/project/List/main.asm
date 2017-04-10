
;CodeVisionAVR C Compiler V2.05.0 Professional
;(C) Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega16
;Program type             : Application
;Clock frequency          : 8.000000 MHz
;Memory model             : Small
;Optimize for             : Size
;(s)printf features       : float, width, precision
;(s)scanf features        : long, width
;External RAM size        : 0
;Data Stack size          : 256 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : Yes
;'char' is unsigned       : Yes
;8 bit enums              : Yes
;global 'const' stored in FLASH: No
;Enhanced core instructions    : On
;Smart register allocation     : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega16
	#pragma AVRPART MEMORY PROG_FLASH 16384
	#pragma AVRPART MEMORY EEPROM 512
	#pragma AVRPART MEMORY INT_SRAM SIZE 1119
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x60

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU GICR=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0060
	.EQU __SRAM_END=0x045F
	.EQU __DSTACK_SIZE=0x0100
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_0x0:
	.DB  0x20,0x44,0x53,0x31,0x33,0x30,0x37,0x20
	.DB  0x41,0x56,0x52,0x20,0x56,0x34,0x20,0x20
	.DB  0x0,0x54,0x69,0x6D,0x65,0x3A,0x20,0x25
	.DB  0x32,0x75,0x2D,0x25,0x32,0x75,0x2D,0x25
	.DB  0x32,0x75,0x0
_0x2040060:
	.DB  0x1
_0x2040000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0,0x49,0x4E,0x46
	.DB  0x0
_0x2060000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0

__GLOBAL_INI_TBL:
	.DW  0x11
	.DW  _0x4
	.DW  _0x0*2

	.DW  0x01
	.DW  __seed_G102
	.DW  _0x2040060*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  GICR,R31
	OUT  GICR,R30
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,__SRAM_START
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x160

	.CSEG
;/*****************************************************************************
;  *Ten Tep          :     main.c
;  *Ngay             :     05/07/2014
;  *Tac Gia          :     MinhHa R&D Team
;  *Cong Ty          :     MinhHaGroup
;  *Webside          :     mcu.banlinhkien.vn
;  *Phien Ban        :     V1.0
;  *Tom Tat          :     Hien thi thoi gian, ngay thang len LCD16x2, su dung DS1307
;  ******************************************************************************/
;
;#include "Main\main.h"
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;#include "ProjectLib\Include\var.h"
;
;#if (__MAIN_H!=5072014)
;    #error "Include Sai #File Main.h"
;#endif
;
;// Declare your global variables here
;
;void main(void)
; 0000 0015 {

	.CSEG
_main:
; 0000 0016     uint8_t Str[16];
; 0000 0017     uint8_t Hour, Min, Sec;
; 0000 0018 // Declare your local variables here
; 0000 0019 
; 0000 001A // Input/Output Ports initialization
; 0000 001B // Port A initialization
; 0000 001C // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 001D // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 001E PORTA=0x00;
	SBIW R28,16
;	Str -> Y+0
;	Hour -> R17
;	Min -> R16
;	Sec -> R19
	LDI  R30,LOW(0)
	OUT  0x1B,R30
; 0000 001F DDRA=0x00;
	OUT  0x1A,R30
; 0000 0020 
; 0000 0021 // Port B initialization
; 0000 0022 // Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
; 0000 0023 // State7=1 State6=1 State5=1 State4=1 State3=T State2=T State1=T State0=T
; 0000 0024 PORTB=0xF0;
	LDI  R30,LOW(240)
	OUT  0x18,R30
; 0000 0025 DDRB=0xF0;
	OUT  0x17,R30
; 0000 0026 
; 0000 0027 // Port C initialization
; 0000 0028 // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=In Func1=Out Func0=Out
; 0000 0029 // State7=T State6=T State5=1 State4=1 State3=1 State2=T State1=0 State0=0
; 0000 002A PORTC=0x00;
	LDI  R30,LOW(0)
	OUT  0x15,R30
; 0000 002B DDRC=0xff;
	LDI  R30,LOW(255)
	OUT  0x14,R30
; 0000 002C 
; 0000 002D // Port D initialization
; 0000 002E // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 002F // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0030 PORTD=0x00;
	LDI  R30,LOW(0)
	OUT  0x12,R30
; 0000 0031 DDRD=0x00;
	OUT  0x11,R30
; 0000 0032 
; 0000 0033 // Timer/Counter 0 initialization
; 0000 0034 // Clock source: System Clock
; 0000 0035 // Clock value: Timer 0 Stopped
; 0000 0036 // Mode: Normal top=0xFF
; 0000 0037 // OC0 output: Disconnected
; 0000 0038 TCCR0=0x00;
	OUT  0x33,R30
; 0000 0039 TCNT0=0x00;
	OUT  0x32,R30
; 0000 003A OCR0=0x00;
	OUT  0x3C,R30
; 0000 003B 
; 0000 003C // Timer/Counter 1 initialization
; 0000 003D // Clock source: System Clock
; 0000 003E // Clock value: Timer1 Stopped
; 0000 003F // Mode: Normal top=0xFFFF
; 0000 0040 // OC1A output: Discon.
; 0000 0041 // OC1B output: Discon.
; 0000 0042 // Noise Canceler: Off
; 0000 0043 // Input Capture on Falling Edge
; 0000 0044 // Timer1 Overflow Interrupt: Off
; 0000 0045 // Input Capture Interrupt: Off
; 0000 0046 // Compare A Match Interrupt: Off
; 0000 0047 // Compare B Match Interrupt: Off
; 0000 0048 TCCR1A=0x00;
	OUT  0x2F,R30
; 0000 0049 TCCR1B=0x00;
	OUT  0x2E,R30
; 0000 004A TCNT1H=0x00;
	OUT  0x2D,R30
; 0000 004B TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 004C ICR1H=0x00;
	OUT  0x27,R30
; 0000 004D ICR1L=0x00;
	OUT  0x26,R30
; 0000 004E OCR1AH=0x00;
	OUT  0x2B,R30
; 0000 004F OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 0050 OCR1BH=0x00;
	OUT  0x29,R30
; 0000 0051 OCR1BL=0x00;
	OUT  0x28,R30
; 0000 0052 
; 0000 0053 // Timer/Counter 2 initialization
; 0000 0054 // Clock source: System Clock
; 0000 0055 // Clock value: Timer2 Stopped
; 0000 0056 // Mode: Normal top=0xFF
; 0000 0057 // OC2 output: Disconnected
; 0000 0058 ASSR=0x00;
	OUT  0x22,R30
; 0000 0059 TCCR2=0x00;
	OUT  0x25,R30
; 0000 005A TCNT2=0x00;
	OUT  0x24,R30
; 0000 005B OCR2=0x00;
	OUT  0x23,R30
; 0000 005C 
; 0000 005D // External Interrupt(s) initialization
; 0000 005E // INT0: Off
; 0000 005F // INT1: Off
; 0000 0060 // INT2: Off
; 0000 0061 MCUCR=0x00;
	OUT  0x35,R30
; 0000 0062 MCUCSR=0x00;
	OUT  0x34,R30
; 0000 0063 
; 0000 0064 // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 0065 TIMSK=0x00;
	OUT  0x39,R30
; 0000 0066 
; 0000 0067 // USART initialization
; 0000 0068 // USART disabled
; 0000 0069 UCSRB=0x00;
	OUT  0xA,R30
; 0000 006A 
; 0000 006B // Analog Comparator initialization
; 0000 006C // Analog Comparator: Off
; 0000 006D // Analog Comparator Input Capture by Timer/Counter 1: Off
; 0000 006E ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
; 0000 006F SFIOR=0x00;
	LDI  R30,LOW(0)
	OUT  0x30,R30
; 0000 0070 
; 0000 0071 // ADC initialization
; 0000 0072 // ADC disabled
; 0000 0073 ADCSRA=0x00;
	OUT  0x6,R30
; 0000 0074 
; 0000 0075 // SPI initialization
; 0000 0076 // SPI disabled
; 0000 0077 SPCR=0x00;
	OUT  0xD,R30
; 0000 0078 
; 0000 0079 // TWI initialization
; 0000 007A // TWI disabled
; 0000 007B TWCR=0x00;
	OUT  0x36,R30
; 0000 007C 
; 0000 007D LCD16X2_Init();    // Khoi tao LCD16X2
	RCALL _LCD16X2_Init
; 0000 007E DS1307_Init();
	CALL _DS1307_Init
; 0000 007F DS1307_SetControl(1,DS1307_SQW_1Hz);
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R30,LOW(16)
	ST   -Y,R30
	CALL _DS1307_SetControl
; 0000 0080 if(FlagSetTime)
	LDI  R26,LOW(_FlagSetTime)
	LDI  R27,HIGH(_FlagSetTime)
	CALL __EEPROMRDB
	CPI  R30,0
	BREQ _0x3
; 0000 0081 {
; 0000 0082     DS1307_SetTime(11,15,0);
	LDI  R30,LOW(11)
	ST   -Y,R30
	LDI  R30,LOW(15)
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	CALL _DS1307_SetTime
; 0000 0083     FlagSetTime=0;
	LDI  R26,LOW(_FlagSetTime)
	LDI  R27,HIGH(_FlagSetTime)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 0000 0084 }
; 0000 0085 LCD16X2_Gotoxy(0,0);
_0x3:
	LDI  R30,LOW(0)
	ST   -Y,R30
	ST   -Y,R30
	RCALL _LCD16X2_Gotoxy
; 0000 0086 LCD16X2_Puts(" DS1307 AVR V4  ");
	__POINTW1MN _0x4,0
	ST   -Y,R31
	ST   -Y,R30
	RCALL _LCD16X2_Puts
; 0000 0087 while (1)
_0x5:
; 0000 0088 {
; 0000 0089     DS1307_GetTime(&Hour,&Min,&Sec);
	IN   R30,SPL
	IN   R31,SPH
	ST   -Y,R31
	ST   -Y,R30
	PUSH R17
	IN   R30,SPL
	IN   R31,SPH
	ST   -Y,R31
	ST   -Y,R30
	PUSH R16
	IN   R30,SPL
	IN   R31,SPH
	ST   -Y,R31
	ST   -Y,R30
	PUSH R19
	CALL _DS1307_GetTime
	POP  R19
	POP  R16
	POP  R17
; 0000 008A     sprintf(Str,"Time: %2u-%2u-%2u",Hour,Min,Sec);
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,17
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	CALL SUBOPT_0x0
	MOV  R30,R16
	CALL SUBOPT_0x0
	MOV  R30,R19
	CALL SUBOPT_0x0
	LDI  R24,12
	CALL _sprintf
	ADIW R28,16
; 0000 008B     LCD16X2_Gotoxy(0,1);
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _LCD16X2_Gotoxy
; 0000 008C     LCD16X2_Puts(Str);
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	RCALL _LCD16X2_Puts
; 0000 008D     delay_ms(200);
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	CALL SUBOPT_0x1
; 0000 008E }
	RJMP _0x5
; 0000 008F }
_0x8:
	RJMP _0x8

	.DSEG
_0x4:
	.BYTE 0x11
;/*------------------------------KET THUC FILE-------------------------------
; ______________________________MinhHa R&D Team______________________________*/
;
;/*****************************************************************************
;  *Ten Tep          :     lcd16x2.h
;  *Ngay             :     14/03/2014
;  *Tac Gia          :     MinhHa R&D Team
;  *Cong Ty          :     MinhHaGroup
;  *Webside          :     mcu.banlinhkien.vn
;  *Phien Ban        :     V1.0
;  *Tom Tat          :     Dinh nghia cac ham giao tiep LCD16x2
;  ******************************************************************************
;  * Chu Y : Phai dinh nghia cac chan su dung cho LCD16X2 vao file main.h
;  * Vi Du :
;   // khai bao chan LCD16x2 TREN KIT AVR V2
;   #define     LCD16X2_RS     PORTB_1
;   #define     LCD16X2_RW     PORTC_2
;   #define     LCD16X2_EN     PORTC_3
;   #define     LCD16X2_D4     PORTD_4
;   #define     LCD16X2_D5     PORTD_5
;   #define     LCD16X2_D6     PORTD_6
;   #define     LCD16X2_D7     PORTD_7
;  ******************************************************************************
;**/
;/*********************************** VI DU ************************************
;   // khai bao 1 mang ki tu dung cho LCD16X2
;   uint8_t str[16];
;   // cac tham bien khac
;   uint8_t Do_am;
;   //Khoi tao LCD16X2
;   LCD16X2_Init();
;   // hien thi 1 chuoi ki tu
;   sprintf(str,"BanLinhKien.Vn");
;   LCD16X2_Puts(str);
;   sprintf(str,"Do Am: %u",Do_am);
;   LCD16X2_Gotoxy(0,1);
;   LCD16X2_Puts(str);
;*******************************************************************************/
;#include "User\Include\lcd16x2.h"
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;
;#if (__LCD16X2_H!=14032014)
;    #error "Include Sai File lcd16x2.h"
;#endif
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Gui tin hieu Enable den LCD16X2.
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_Enable(void)
; 0001 0031 {

	.CSEG
_LCD16X2_Enable:
; 0001 0032 	LCD16X2_EN=1;
	SBI  0x15,5
; 0001 0033 	delay_us(3);
	__DELAY_USB 8
; 0001 0034 	LCD16X2_EN=0;
	CBI  0x15,5
; 0001 0035 	delay_us(50);
	__DELAY_USB 133
; 0001 0036 }
	RET
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Gui 4 bit du lieu den LCD16X2.
;Tham Bien   :   Data: 4 bit thap cua Data chua 4 bit du lieu can gui.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_Send4Bit(uint8_t Data)
; 0001 003F {
_LCD16X2_Send4Bit:
; 0001 0040 	LCD16X2_D4=((Data&0x01)==0x01);
;	Data -> Y+0
	LD   R30,Y
	ANDI R30,LOW(0x1)
	LDI  R26,LOW(1)
	CALL __EQB12
	CPI  R30,0
	BRNE _0x20007
	CBI  0x18,4
	RJMP _0x20008
_0x20007:
	SBI  0x18,4
_0x20008:
; 0001 0041 	LCD16X2_D5=((Data&0x02)==0x02);
	LD   R30,Y
	ANDI R30,LOW(0x2)
	LDI  R26,LOW(2)
	CALL __EQB12
	CPI  R30,0
	BRNE _0x20009
	CBI  0x18,5
	RJMP _0x2000A
_0x20009:
	SBI  0x18,5
_0x2000A:
; 0001 0042 	LCD16X2_D6=((Data&0x04)==0x04);
	LD   R30,Y
	ANDI R30,LOW(0x4)
	LDI  R26,LOW(4)
	CALL __EQB12
	CPI  R30,0
	BRNE _0x2000B
	CBI  0x18,6
	RJMP _0x2000C
_0x2000B:
	SBI  0x18,6
_0x2000C:
; 0001 0043 	LCD16X2_D7=((Data&0x08)==0x08);
	LD   R30,Y
	ANDI R30,LOW(0x8)
	LDI  R26,LOW(8)
	CALL __EQB12
	CPI  R30,0
	BRNE _0x2000D
	CBI  0x18,7
	RJMP _0x2000E
_0x2000D:
	SBI  0x18,7
_0x2000E:
; 0001 0044 }
	RJMP _0x20A000B
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Gui 1 byte du lieu den LCD16X2.
;Tham Bien   :   command: lenh can ghi
;Tra Ve      :   Khong.
;vi du       :   LCD16X2_SendCommand (0x01);
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_SendCommand(uint8_t Command)
; 0001 004E {
_LCD16X2_SendCommand:
; 0001 004F 	LCD16X2_Send4Bit(Command>>4);   /* Gui 4 bit cao */
;	Command -> Y+0
	LD   R30,Y
	LDI  R31,0
	CALL __ASRW4
	CALL SUBOPT_0x2
; 0001 0050 	LCD16X2_Enable() ;
; 0001 0051 	LCD16X2_Send4Bit(Command);      /* Gui 4 bit thap*/
	LD   R30,Y
	CALL SUBOPT_0x2
; 0001 0052 	LCD16X2_Enable() ;
; 0001 0053 }
	RJMP _0x20A000B
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Khoi tao LCD16X2.
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_Init(void)
; 0001 005C {
_LCD16X2_Init:
; 0001 005D 	LCD16X2_Send4Bit(0x00);
	LDI  R30,LOW(0)
	ST   -Y,R30
	RCALL _LCD16X2_Send4Bit
; 0001 005E 	delay_ms(20);
	LDI  R30,LOW(20)
	LDI  R31,HIGH(20)
	CALL SUBOPT_0x1
; 0001 005F 	LCD16X2_RS=0;
	CBI  0x15,3
; 0001 0060 	LCD16X2_RW=0;
	CBI  0x15,4
; 0001 0061 	LCD16X2_Send4Bit(0x03);
	LDI  R30,LOW(3)
	CALL SUBOPT_0x2
; 0001 0062 	LCD16X2_Enable();
; 0001 0063 	delay_ms(5);
	CALL SUBOPT_0x3
; 0001 0064 	LCD16X2_Enable();
	RCALL _LCD16X2_Enable
; 0001 0065 	delay_us(100);
	__DELAY_USW 200
; 0001 0066 	LCD16X2_Enable();
	RCALL _LCD16X2_Enable
; 0001 0067 	LCD16X2_Send4Bit(0x02);
	LDI  R30,LOW(2)
	CALL SUBOPT_0x2
; 0001 0068 	LCD16X2_Enable();
; 0001 0069 	LCD16X2_SendCommand( 0x28);        // giao thuc 4 bit, hien thi 2 hang, ki tu 5x7
	LDI  R30,LOW(40)
	ST   -Y,R30
	RCALL _LCD16X2_SendCommand
; 0001 006A 	LCD16X2_SendCommand( 0x0c);        // cho phep hien thi man hinh
	LDI  R30,LOW(12)
	ST   -Y,R30
	RCALL _LCD16X2_SendCommand
; 0001 006B 	LCD16X2_SendCommand( 0x06);        // tang ID, khong dich khung hinh
	LDI  R30,LOW(6)
	ST   -Y,R30
	RCALL _LCD16X2_SendCommand
; 0001 006C 	LCD16X2_Clear();                   // xoa toan bo khung hinh
	RCALL _LCD16X2_Clear
; 0001 006D }
	RET
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Thiet lap vi tri con tro LCD16X2.
;Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 15.
;                y: vi tri hang cua con tro. y= 0,1.
;Tra Ve      :   Khong.
;Vi du       :   LCD16X2_Gotoxy(0,0);
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_Gotoxy(uint8_t  x, uint8_t  y)
; 0001 0078 {
_LCD16X2_Gotoxy:
; 0001 0079 	uint8_t  address;
; 0001 007A 	if(!y)
	ST   -Y,R17
;	x -> Y+2
;	y -> Y+1
;	address -> R17
	LDD  R30,Y+1
	CPI  R30,0
	BRNE _0x20013
; 0001 007B 		address = (0x80+x);
	LDD  R30,Y+2
	SUBI R30,-LOW(128)
	RJMP _0x2001C
; 0001 007C 	else
_0x20013:
; 0001 007D 		address = (0xC0+x);
	LDD  R30,Y+2
	SUBI R30,-LOW(192)
_0x2001C:
	MOV  R17,R30
; 0001 007E 	delay_ms(1);
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CALL SUBOPT_0x1
; 0001 007F 	LCD16X2_SendCommand(address);
	ST   -Y,R17
	RCALL _LCD16X2_SendCommand
; 0001 0080 	delay_ms(5);
	CALL SUBOPT_0x3
; 0001 0081 }
	LDD  R17,Y+0
	JMP  _0x20A0006
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Xoa noi dung hien thi tren LCD16X2.
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;
;void LCD16X2_Clear(void)
; 0001 008A {
_LCD16X2_Clear:
; 0001 008B 	LCD16X2_SendCommand(0x01);
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _LCD16X2_SendCommand
; 0001 008C 	delay_ms(5);
	CALL SUBOPT_0x3
; 0001 008D }
	RET
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Viet 1 ki tu len LCD16X2.
;Tham Bien   :   Data  :   Gia tri ki tu can hien thi.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;void LCD16X2_PutChar(uint8_t Data)
; 0001 0095 {
_LCD16X2_PutChar:
; 0001 0096 	LCD16X2_RS=1;
;	Data -> Y+0
	SBI  0x15,3
; 0001 0097 	LCD16X2_SendCommand( Data );
	LD   R30,Y
	ST   -Y,R30
	RCALL _LCD16X2_SendCommand
; 0001 0098 	LCD16X2_RS=0;
	CBI  0x15,3
; 0001 0099 }
_0x20A000B:
	ADIW R28,1
	RET
;
;/*------------------------------------------------------------------------------
;Noi Dung    :   Viet 1 chuoi ki tu len LCD16X2.
;Tham Bien   :   *s    :   chuoi du lieu can hien thi.
;Tra Ve      :   Khong.
; -------------------------------------------------------------------------------*/
;void LCD16X2_Puts(uint8_t *s)
; 0001 00A1 {
_LCD16X2_Puts:
; 0001 00A2 	while (*s)
;	*s -> Y+0
_0x20019:
	LD   R26,Y
	LDD  R27,Y+1
	LD   R30,X
	CPI  R30,0
	BREQ _0x2001B
; 0001 00A3 	{
; 0001 00A4 		LCD16X2_PutChar(*s);
	ST   -Y,R30
	RCALL _LCD16X2_PutChar
; 0001 00A5 		s++;
	LD   R30,Y
	LDD  R31,Y+1
	ADIW R30,1
	ST   Y,R30
	STD  Y+1,R31
; 0001 00A6 	}
	RJMP _0x20019
_0x2001B:
; 0001 00A7 }
	JMP  _0x20A0007
;/*------------------------------KET THUC FILE-------------------------------
; ______________________________MinhHa R&D Temp______________________________*/
;
;
;
;
;/*****************************************************************************
;  *Ten Tep          :     ds1307.c
;  *Ngay             :     19/03/2014
;  *Tac Gia          :     MinhHa R&D Team
;  *Cong Ty          :     MinhHaGroup
;  *Webside          :     mcu.banlinhkien.vn
;  *Phien Ban        :     V1.0
;  *Tom Tat          :     Dinh nghia cac ham giao tiep DS1307
;  ******************************************************************************/
;
;#include "User/Include/ds1307.h"
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;
;#if (__DS1307_H!=19032014)
;    #error "Include Sai File ds1307.h"
;#endif
;
;/*******************************************************************************
;Noi Dung    :   Khoi tao DS1307.
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_Init(void)
; 0002 0018 {

	.CSEG
_DS1307_Init:
; 0002 0019     I2CSOFT_Init();
	RCALL _I2CSOFT_Init
; 0002 001A }
	RET
;
;/*******************************************************************************
;Noi Dung    :   Ghi du lieu vao 1 thanh ghi trong DS1307.
;Tham Bien   :   Address : Dia chi thanh ghi.
;                Data    : Du lieu can ghi.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_WriteData(uint8_t Address, uint8_t Data)
; 0002 0024 {
_DS1307_WriteData:
; 0002 0025    uint8_t Dataw;
; 0002 0026    Dataw =  ((Data/10)<<4) + (Data % 10);
	ST   -Y,R17
;	Address -> Y+2
;	Data -> Y+1
;	Dataw -> R17
	LDD  R26,Y+1
	LDI  R27,0
	LDI  R30,LOW(10)
	LDI  R31,HIGH(10)
	CALL __DIVW21
	SWAP R30
	ANDI R30,0xF0
	MOV  R22,R30
	LDD  R26,Y+1
	CLR  R27
	LDI  R30,LOW(10)
	LDI  R31,HIGH(10)
	CALL __MODW21
	ADD  R30,R22
	MOV  R17,R30
; 0002 0027    I2CSOFT_Start();
	CALL SUBOPT_0x4
; 0002 0028    I2CSOFT_WriteData(DS1307_ADDR_WRITE);
; 0002 0029    I2CSOFT_WriteData(Address);
	LDD  R30,Y+2
	ST   -Y,R30
	RCALL _I2CSOFT_WriteData
; 0002 002A    I2CSOFT_WriteData(Dataw);
	ST   -Y,R17
	RCALL _I2CSOFT_WriteData
; 0002 002B    I2CSOFT_Stop();
	RCALL _I2CSOFT_Stop
; 0002 002C }
	LDD  R17,Y+0
	RJMP _0x20A0006
;
;/*******************************************************************************
;Noi Dung    :   Doc du lieu cua 1 thanh ghi trong DS1307.
;Tham Bien   :   Address: Dia chi thanh ghi.
;Tra Ve      :   Du lieu cua thanh ghi.
;********************************************************************************/
;
;uint8_t DS1307_ReadData(uint8_t Address)
; 0002 0035 {
_DS1307_ReadData:
; 0002 0036    uint8_t Data;
; 0002 0037    I2CSOFT_Start();
	ST   -Y,R17
;	Address -> Y+1
;	Data -> R17
	CALL SUBOPT_0x4
; 0002 0038    I2CSOFT_WriteData(DS1307_ADDR_WRITE);
; 0002 0039    I2CSOFT_WriteData(Address);
	LDD  R30,Y+1
	ST   -Y,R30
	RCALL _I2CSOFT_WriteData
; 0002 003A    I2CSOFT_Start();
	RCALL _I2CSOFT_Start
; 0002 003B    I2CSOFT_WriteData(DS1307_ADDR_READ);
	LDI  R30,LOW(209)
	ST   -Y,R30
	RCALL _I2CSOFT_WriteData
; 0002 003C    Data=I2CSOFT_ReadData(0);
	LDI  R30,LOW(0)
	ST   -Y,R30
	RCALL _I2CSOFT_ReadData
	MOV  R17,R30
; 0002 003D    I2CSOFT_Stop();
	RCALL _I2CSOFT_Stop
; 0002 003E    Data = ((Data>>4) * 10 + Data % 16);
	MOV  R30,R17
	LDI  R31,0
	CALL __ASRW4
	LDI  R26,LOW(10)
	MULS R30,R26
	MOV  R22,R0
	MOV  R26,R17
	CLR  R27
	LDI  R30,LOW(16)
	LDI  R31,HIGH(16)
	CALL __MODW21
	ADD  R30,R22
	MOV  R17,R30
; 0002 003F    return(Data);
	RJMP _0x20A0008
; 0002 0040 }
;
;/*******************************************************************************
;Noi Dung    :   Cho phep xuat xung vuong tren chan SQW/OUT.
;Tham Bien   :   State=0: Khong cho phep xuat xung vuong.
;                     =1: Cho phep xuat xung vuong.
;			    Mode   : Thiet lap tan so xung vuong xuat ra.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_SetControl(uint8_t State,uint8_t Mode)
; 0002 004B {
_DS1307_SetControl:
; 0002 004C     if(!State)
;	State -> Y+1
;	Mode -> Y+0
	LDD  R30,Y+1
	CPI  R30,0
	BRNE _0x40003
; 0002 004D     {
; 0002 004E         DS1307_WriteData(DS1307_ADDR_CONTROL,0x00);
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R30,LOW(0)
	RJMP _0x40005
; 0002 004F     }
; 0002 0050     else
_0x40003:
; 0002 0051     {
; 0002 0052         DS1307_WriteData(DS1307_ADDR_CONTROL,Mode);
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDD  R30,Y+1
_0x40005:
	ST   -Y,R30
	RCALL _DS1307_WriteData
; 0002 0053     }
; 0002 0054 }
	RJMP _0x20A0007
;
;/*******************************************************************************
;Noi Dung    :   Ghi du lieu Thu/Ngay/Thang/Nam vao DS1307.
;Tham Bien   :   Day   : Thu.
;                Date  : Ngay.
;                Month : Thang.
;				Year  : Nam.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_SetDate(uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year)
; 0002 0060 {
; 0002 0061     DS1307_WriteData(DS1307_ADDR_DAY,Day);
;	Day -> Y+3
;	Date -> Y+2
;	Month -> Y+1
;	Year -> Y+0
; 0002 0062     DS1307_WriteData(DS1307_ADDR_DATE,Date);
; 0002 0063     DS1307_WriteData(DS1307_ADDR_MONTH,Month);
; 0002 0064     DS1307_WriteData(DS1307_ADDR_YEAR,Year);
; 0002 0065 }
;
;/*******************************************************************************
;Noi Dung    :   Ghi du lieu Giay/Phut/Gio vao DS1307.
;Tham Bien   :   Second : Giay.
;                Minute : Phut.
;				Hour   : Gio.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_SetTime(uint8_t Hour, uint8_t Minute, uint8_t Second)
; 0002 0070 {
_DS1307_SetTime:
; 0002 0071     DS1307_WriteData(DS1307_ADDR_SECOND,Second);
;	Hour -> Y+2
;	Minute -> Y+1
;	Second -> Y+0
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDD  R30,Y+1
	ST   -Y,R30
	RCALL _DS1307_WriteData
; 0002 0072     DS1307_WriteData(DS1307_ADDR_MINUTE,Minute);
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDD  R30,Y+2
	ST   -Y,R30
	RCALL _DS1307_WriteData
; 0002 0073     DS1307_WriteData(DS1307_ADDR_HOUR,Hour);
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDD  R30,Y+3
	ST   -Y,R30
	RCALL _DS1307_WriteData
; 0002 0074 }
	RJMP _0x20A0006
;
;/*******************************************************************************
;Noi Dung    :   Doc du lieu Thu/Ngay/Thang/Nam tu DS1307.
;Tham Bien   :   *Day   : Thu.
;				*Date  : Ngay.
;                *Month : Thang.
;				*Year  : Nam.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_GetDate(uint8_t *Day, uint8_t *Date, uint8_t *Month, uint8_t *Year)
; 0002 0080 {
; 0002 0081     *Day    =   DS1307_ReadData(DS1307_ADDR_DAY);
;	*Day -> Y+6
;	*Date -> Y+4
;	*Month -> Y+2
;	*Year -> Y+0
; 0002 0082     *Date   =   DS1307_ReadData(DS1307_ADDR_DATE);
; 0002 0083     *Month  =   DS1307_ReadData(DS1307_ADDR_MONTH);
; 0002 0084     *Year   =   DS1307_ReadData(DS1307_ADDR_YEAR);
; 0002 0085 }
;
;/*******************************************************************************
;Noi Dung    :   Doc du lieu Giay/Phut/Gio tu DS1307.
;Tham Bien   :   *Second : Giay.
;                *Minute : Phut.
;				*Hour   : Gio.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void DS1307_GetTime(uint8_t *Hour, uint8_t* Minute, uint8_t* Second)
; 0002 0090 {
_DS1307_GetTime:
; 0002 0091     *Hour    =  DS1307_ReadData(DS1307_ADDR_HOUR);
;	*Hour -> Y+4
;	*Minute -> Y+2
;	*Second -> Y+0
	LDI  R30,LOW(2)
	ST   -Y,R30
	RCALL _DS1307_ReadData
	LDD  R26,Y+4
	LDD  R27,Y+4+1
	ST   X,R30
; 0002 0092     *Minute  =  DS1307_ReadData(DS1307_ADDR_MINUTE);
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _DS1307_ReadData
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ST   X,R30
; 0002 0093     *Second  =  DS1307_ReadData(DS1307_ADDR_SECOND);
	LDI  R30,LOW(0)
	ST   -Y,R30
	RCALL _DS1307_ReadData
	LD   R26,Y
	LDD  R27,Y+1
	ST   X,R30
; 0002 0094 }
	ADIW R28,6
	RET
;
;/*------------------------------KET THUC FILE-------------------------------
; ______________________________MinhHa R&D Team______________________________*/
;/*****************************************************************************
;  *Ten Tep          :     i2c.c
;  *Ngay             :     19/03/2014
;  *Tac Gia          :     MinhHa R&D Team
;  *Cong Ty          :     MinhHaGroup
;  *Webside          :     mcu.banlinhkien.vn
;  *Phien Ban        :     V1.0
;  *Tom Tat          :     Dinh nghia cac ham giao tiep I2C
;  ******************************************************************************
;  * Chu Y           :     Phai dinh nghia cac chan giao tiep chuan I2C vao main.h
;
;        #define I2CSOFT_SDADDR  DDRC_4
;        #define I2CSOFT_SDAOUT  PORTC_4
;        #define I2CSOFT_SDAIN   PINC_4
;        #define I2CSOFT_SCLDDR  DDRD_0
;        #define I2CSOFT_SCL     PORTD_0
;  ******************************************************************************
;**/
;
;#include "User/Include/i2c.h"
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;
;#if (__I2C_H!=19032014)
;    #error "Include Sai File i2c.h"
;#endif
;
;/*******************************************************************************
;Noi Dung    :   Khoi tao giao thuc I2C
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void I2CSOFT_Init(void)
; 0003 0021 {

	.CSEG
_I2CSOFT_Init:
; 0003 0022     I2CSOFT_SCLDDR=DDR_OUT;
	SBI  0x14,0
; 0003 0023     I2CSOFT_SDADDR=DDR_OUT;
	SBI  0x14,1
; 0003 0024     I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0025     delay_us(5);
; 0003 0026     I2CSOFT_SDAOUT=1;
	SBI  0x15,1
; 0003 0027     delay_us(5);
	RJMP _0x20A000A
; 0003 0028 }
;
;/*******************************************************************************
;Noi Dung    :   Gui lenh Start I2C (Keo chan SDA xuong 0 khi SCL o muc 1).
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void I2CSOFT_Start(void)
; 0003 0031 {
_I2CSOFT_Start:
; 0003 0032     I2CSOFT_SDADDR=DDR_OUT;
	SBI  0x14,1
; 0003 0033     I2CSOFT_SDAOUT=1;
	SBI  0x15,1
; 0003 0034     I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0035     delay_us(5);
; 0003 0036     I2CSOFT_SDAOUT=0;
	CBI  0x15,1
; 0003 0037     delay_us(5);
	RJMP _0x20A0009
; 0003 0038     I2CSOFT_SCL=0;
; 0003 0039     delay_us(5);
; 0003 003A }
;
;/*******************************************************************************
;Noi Dung    :   Gui lenh Stop I2C (Keo chan SDA len muc 1 khi SCL o muc 1).
;Tham Bien   :   Khong.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;void I2CSOFT_Stop(void)
; 0003 0043 {
_I2CSOFT_Stop:
; 0003 0044     I2CSOFT_SDADDR=DDR_OUT;
	SBI  0x14,1
; 0003 0045     I2CSOFT_SDAOUT=0;
	CBI  0x15,1
; 0003 0046     I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0047     delay_us(5);
; 0003 0048     I2CSOFT_SDAOUT=1;
	SBI  0x15,1
; 0003 0049     delay_us(5);
_0x20A0009:
	__DELAY_USB 13
; 0003 004A     I2CSOFT_SCL=0;
	CBI  0x15,0
; 0003 004B     delay_us(5);
_0x20A000A:
	__DELAY_USB 13
; 0003 004C }
	RET
;
;/*******************************************************************************
;Noi Dung    :   Viet du lieu len Bus I2C.
;Tham Bien   :   Data: Gia tri du lieu.
;Tra Ve      :   Khong.
;********************************************************************************/
;
;uint8_t I2CSOFT_WriteData(uint8_t Data)
; 0003 0055 {
_I2CSOFT_WriteData:
; 0003 0056     uint8_t i;
; 0003 0057     I2CSOFT_SDADDR=DDR_OUT;
	ST   -Y,R17
;	Data -> Y+1
;	i -> R17
	SBI  0x14,1
; 0003 0058     for(i=0;i<8;i++)
	LDI  R17,LOW(0)
_0x60022:
	CPI  R17,8
	BRSH _0x60023
; 0003 0059     {
; 0003 005A         if(Data&0x80)
	LDD  R30,Y+1
	ANDI R30,LOW(0x80)
	BREQ _0x60024
; 0003 005B             I2CSOFT_SDAOUT=1;
	SBI  0x15,1
; 0003 005C         else
	RJMP _0x60027
_0x60024:
; 0003 005D             I2CSOFT_SDAOUT=0;
	CBI  0x15,1
; 0003 005E         Data<<=1;
_0x60027:
	LDD  R30,Y+1
	LSL  R30
	STD  Y+1,R30
; 0003 005F         delay_us(5);
	__DELAY_USB 13
; 0003 0060         I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0061         delay_us(5);
; 0003 0062         I2CSOFT_SCL=0;
	CBI  0x15,0
; 0003 0063         delay_us(5);
	__DELAY_USB 13
; 0003 0064     }
	SUBI R17,-1
	RJMP _0x60022
_0x60023:
; 0003 0065     I2CSOFT_SDADDR=DDR_IN;
	CBI  0x14,1
; 0003 0066     I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0067     delay_us(5);
; 0003 0068     i=I2CSOFT_SDAIN;
	LDI  R30,0
	SBIC 0x13,1
	LDI  R30,1
	MOV  R17,R30
; 0003 0069     delay_us(5);
	__DELAY_USB 13
; 0003 006A     I2CSOFT_SCL=0;
	CBI  0x15,0
; 0003 006B     delay_us(5);
	__DELAY_USB 13
; 0003 006C     return i;
_0x20A0008:
	MOV  R30,R17
	LDD  R17,Y+0
_0x20A0007:
	ADIW R28,2
	RET
; 0003 006D }
;
;/*******************************************************************************
;Noi Dung    :   Lay du lieu tren Bus I2C.
;Tham Bien   :   Ack:
;Tra Ve      :   Gia tri du lieu.
;********************************************************************************/
;
;uint8_t I2CSOFT_ReadData(uint8_t Ack)
; 0003 0076 {
_I2CSOFT_ReadData:
; 0003 0077     uint8_t I2C_Data=0,i;
; 0003 0078     I2CSOFT_SDADDR=DDR_IN;
	ST   -Y,R17
	ST   -Y,R16
;	Ack -> Y+2
;	I2C_Data -> R17
;	i -> R16
	LDI  R17,0
	CBI  0x14,1
; 0003 0079     for(i=0;i<8;i++)
	LDI  R16,LOW(0)
_0x60037:
	CPI  R16,8
	BRSH _0x60038
; 0003 007A     {
; 0003 007B         I2CSOFT_SCL=1;
	SBI  0x15,0
; 0003 007C         delay_us(10);
	__DELAY_USB 27
; 0003 007D         I2C_Data<<=1;
	LSL  R17
; 0003 007E         if(I2CSOFT_SDAIN)I2C_Data|=1;
	SBIC 0x13,1
	ORI  R17,LOW(1)
; 0003 007F         delay_us(10);
	__DELAY_USB 27
; 0003 0080         I2CSOFT_SCL=0;
	CBI  0x15,0
; 0003 0081     }
	SUBI R16,-1
	RJMP _0x60037
_0x60038:
; 0003 0082     I2CSOFT_SDADDR=DDR_OUT;
	SBI  0x14,1
; 0003 0083     I2CSOFT_SCL=1;
	CALL SUBOPT_0x5
; 0003 0084     delay_us(5);
; 0003 0085     I2CSOFT_SDAOUT=Ack;
	LDD  R30,Y+2
	CPI  R30,0
	BRNE _0x60042
	CBI  0x15,1
	RJMP _0x60043
_0x60042:
	SBI  0x15,1
_0x60043:
; 0003 0086     delay_us(5);
	__DELAY_USB 13
; 0003 0087     I2CSOFT_SCL=0;
	CBI  0x15,0
; 0003 0088     return I2C_Data;
	MOV  R30,R17
	LDD  R17,Y+1
	LDD  R16,Y+0
_0x20A0006:
	ADIW R28,3
	RET
; 0003 0089 }
;
;/*------------------------------KET THUC FILE-------------------------------
; ______________________________MinhHa R&D Team______________________________*/

	.CSEG
_strcpyf:
    ld   r30,y+
    ld   r31,y+
    ld   r26,y+
    ld   r27,y+
    movw r24,r26
strcpyf0:
	lpm  r0,z+
    st   x+,r0
    tst  r0
    brne strcpyf0
    movw r30,r24
    ret
_strlen:
    ld   r26,y+
    ld   r27,y+
    clr  r30
    clr  r31
strlen0:
    ld   r22,x+
    tst  r22
    breq strlen1
    adiw r30,1
    rjmp strlen0
strlen1:
    ret
_strlenf:
    clr  r26
    clr  r27
    ld   r30,y+
    ld   r31,y+
strlenf0:
	lpm  r0,z+
    tst  r0
    breq strlenf1
    adiw r26,1
    rjmp strlenf0
strlenf1:
    movw r30,r26
    ret

	.CSEG

	.CSEG
_ftoa:
	SBIW R28,4
	LDI  R30,LOW(0)
	ST   Y,R30
	STD  Y+1,R30
	STD  Y+2,R30
	LDI  R30,LOW(63)
	STD  Y+3,R30
	ST   -Y,R17
	ST   -Y,R16
	LDD  R30,Y+11
	LDD  R31,Y+11+1
	CPI  R30,LOW(0xFFFF)
	LDI  R26,HIGH(0xFFFF)
	CPC  R31,R26
	BRNE _0x204000D
	CALL SUBOPT_0x6
	__POINTW1FN _0x2040000,0
	CALL SUBOPT_0x7
	RJMP _0x20A0005
_0x204000D:
	CPI  R30,LOW(0x7FFF)
	LDI  R26,HIGH(0x7FFF)
	CPC  R31,R26
	BRNE _0x204000C
	CALL SUBOPT_0x6
	__POINTW1FN _0x2040000,1
	CALL SUBOPT_0x7
	RJMP _0x20A0005
_0x204000C:
	LDD  R26,Y+12
	TST  R26
	BRPL _0x204000F
	__GETD1S 9
	CALL __ANEGF1
	CALL SUBOPT_0x8
	CALL SUBOPT_0x9
	LDI  R30,LOW(45)
	ST   X,R30
_0x204000F:
	LDD  R26,Y+8
	CPI  R26,LOW(0x7)
	BRLO _0x2040010
	LDI  R30,LOW(6)
	STD  Y+8,R30
_0x2040010:
	LDD  R17,Y+8
_0x2040011:
	MOV  R30,R17
	SUBI R17,1
	CPI  R30,0
	BREQ _0x2040013
	CALL SUBOPT_0xA
	CALL SUBOPT_0xB
	CALL SUBOPT_0xC
	RJMP _0x2040011
_0x2040013:
	CALL SUBOPT_0xD
	CALL __ADDF12
	CALL SUBOPT_0x8
	LDI  R17,LOW(0)
	__GETD1N 0x3F800000
	CALL SUBOPT_0xC
_0x2040014:
	CALL SUBOPT_0xD
	CALL __CMPF12
	BRLO _0x2040016
	CALL SUBOPT_0xA
	CALL SUBOPT_0xE
	CALL SUBOPT_0xC
	SUBI R17,-LOW(1)
	CPI  R17,39
	BRLO _0x2040017
	CALL SUBOPT_0x6
	__POINTW1FN _0x2040000,5
	CALL SUBOPT_0x7
	RJMP _0x20A0005
_0x2040017:
	RJMP _0x2040014
_0x2040016:
	CPI  R17,0
	BRNE _0x2040018
	CALL SUBOPT_0x9
	LDI  R30,LOW(48)
	ST   X,R30
	RJMP _0x2040019
_0x2040018:
_0x204001A:
	MOV  R30,R17
	SUBI R17,1
	CPI  R30,0
	BREQ _0x204001C
	CALL SUBOPT_0xA
	CALL SUBOPT_0xB
	CALL SUBOPT_0xF
	CALL __PUTPARD1
	CALL _floor
	CALL SUBOPT_0xC
	CALL SUBOPT_0xD
	CALL __DIVF21
	CALL __CFD1U
	MOV  R16,R30
	CALL SUBOPT_0x9
	CALL SUBOPT_0x10
	CALL SUBOPT_0xA
	CALL __CWD1
	CALL __CDF1
	CALL __MULF12
	CALL SUBOPT_0x11
	CALL SUBOPT_0x12
	RJMP _0x204001A
_0x204001C:
_0x2040019:
	LDD  R30,Y+8
	CPI  R30,0
	BREQ _0x20A0004
	CALL SUBOPT_0x9
	LDI  R30,LOW(46)
	ST   X,R30
_0x204001E:
	LDD  R30,Y+8
	SUBI R30,LOW(1)
	STD  Y+8,R30
	SUBI R30,-LOW(1)
	BREQ _0x2040020
	CALL SUBOPT_0x11
	CALL SUBOPT_0xE
	CALL SUBOPT_0x8
	__GETD1S 9
	CALL __CFD1U
	MOV  R16,R30
	CALL SUBOPT_0x9
	CALL SUBOPT_0x10
	CALL SUBOPT_0x11
	CALL __CWD1
	CALL __CDF1
	CALL SUBOPT_0x12
	RJMP _0x204001E
_0x2040020:
_0x20A0004:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LDI  R30,LOW(0)
	ST   X,R30
_0x20A0005:
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,13
	RET

	.DSEG

	.CSEG
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif

	.CSEG
_put_buff_G103:
	ST   -Y,R17
	ST   -Y,R16
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,2
	CALL __GETW1P
	SBIW R30,0
	BREQ _0x2060010
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,4
	CALL __GETW1P
	MOVW R16,R30
	SBIW R30,0
	BREQ _0x2060012
	__CPWRN 16,17,2
	BRLO _0x2060013
	MOVW R30,R16
	SBIW R30,1
	MOVW R16,R30
	__PUTW1SNS 2,4
_0x2060012:
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,2
	CALL SUBOPT_0x13
	SBIW R30,1
	LDD  R26,Y+4
	STD  Z+0,R26
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	CALL __GETW1P
	TST  R31
	BRMI _0x2060014
	CALL SUBOPT_0x13
_0x2060014:
_0x2060013:
	RJMP _0x2060015
_0x2060010:
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	LDI  R30,LOW(65535)
	LDI  R31,HIGH(65535)
	ST   X+,R30
	ST   X,R31
_0x2060015:
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,5
	RET
__ftoe_G103:
	SBIW R28,4
	LDI  R30,LOW(0)
	ST   Y,R30
	STD  Y+1,R30
	LDI  R30,LOW(128)
	STD  Y+2,R30
	LDI  R30,LOW(63)
	STD  Y+3,R30
	CALL __SAVELOCR4
	LDD  R30,Y+14
	LDD  R31,Y+14+1
	CPI  R30,LOW(0xFFFF)
	LDI  R26,HIGH(0xFFFF)
	CPC  R31,R26
	BRNE _0x2060019
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x2060000,0
	CALL SUBOPT_0x7
	RJMP _0x20A0003
_0x2060019:
	CPI  R30,LOW(0x7FFF)
	LDI  R26,HIGH(0x7FFF)
	CPC  R31,R26
	BRNE _0x2060018
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x2060000,1
	CALL SUBOPT_0x7
	RJMP _0x20A0003
_0x2060018:
	LDD  R26,Y+11
	CPI  R26,LOW(0x7)
	BRLO _0x206001B
	LDI  R30,LOW(6)
	STD  Y+11,R30
_0x206001B:
	LDD  R17,Y+11
_0x206001C:
	MOV  R30,R17
	SUBI R17,1
	CPI  R30,0
	BREQ _0x206001E
	CALL SUBOPT_0x14
	CALL SUBOPT_0x15
	RJMP _0x206001C
_0x206001E:
	__GETD1S 12
	CALL __CPD10
	BRNE _0x206001F
	LDI  R19,LOW(0)
	CALL SUBOPT_0x14
	CALL SUBOPT_0x15
	RJMP _0x2060020
_0x206001F:
	LDD  R19,Y+11
	CALL SUBOPT_0x16
	BREQ PC+2
	BRCC PC+3
	JMP  _0x2060021
	CALL SUBOPT_0x14
	CALL SUBOPT_0x15
_0x2060022:
	CALL SUBOPT_0x16
	BRLO _0x2060024
	CALL SUBOPT_0x17
	CALL SUBOPT_0xB
	CALL SUBOPT_0x18
	SUBI R19,-LOW(1)
	RJMP _0x2060022
_0x2060024:
	RJMP _0x2060025
_0x2060021:
_0x2060026:
	CALL SUBOPT_0x16
	BRSH _0x2060028
	CALL SUBOPT_0x17
	CALL SUBOPT_0xE
	CALL SUBOPT_0x18
	SUBI R19,LOW(1)
	RJMP _0x2060026
_0x2060028:
	CALL SUBOPT_0x14
	CALL SUBOPT_0x15
_0x2060025:
	__GETD1S 12
	CALL SUBOPT_0xF
	CALL SUBOPT_0x18
	CALL SUBOPT_0x16
	BRLO _0x2060029
	CALL SUBOPT_0x17
	CALL SUBOPT_0xB
	CALL SUBOPT_0x18
	SUBI R19,-LOW(1)
_0x2060029:
_0x2060020:
	LDI  R17,LOW(0)
_0x206002A:
	LDD  R30,Y+11
	CP   R30,R17
	BRLO _0x206002C
	__GETD2S 4
	CALL SUBOPT_0xB
	CALL SUBOPT_0xF
	CALL __PUTPARD1
	CALL _floor
	CALL SUBOPT_0x15
	__GETD1S 4
	CALL SUBOPT_0x17
	CALL __DIVF21
	CALL __CFD1U
	MOV  R16,R30
	CALL SUBOPT_0x19
	MOV  R30,R16
	SUBI R30,-LOW(48)
	ST   X,R30
	MOV  R30,R16
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2S 4
	CALL __MULF12
	CALL SUBOPT_0x17
	CALL __SWAPD12
	CALL __SUBF12
	CALL SUBOPT_0x18
	MOV  R30,R17
	SUBI R17,-1
	CPI  R30,0
	BRNE _0x206002A
	CALL SUBOPT_0x19
	LDI  R30,LOW(46)
	ST   X,R30
	RJMP _0x206002A
_0x206002C:
	CALL SUBOPT_0x1A
	SBIW R30,1
	LDD  R26,Y+10
	STD  Z+0,R26
	CPI  R19,0
	BRGE _0x206002E
	NEG  R19
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	LDI  R30,LOW(45)
	RJMP _0x2060111
_0x206002E:
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	LDI  R30,LOW(43)
_0x2060111:
	ST   X,R30
	CALL SUBOPT_0x1A
	CALL SUBOPT_0x1A
	SBIW R30,1
	MOVW R22,R30
	MOV  R26,R19
	LDI  R30,LOW(10)
	CALL __DIVB21
	SUBI R30,-LOW(48)
	MOVW R26,R22
	ST   X,R30
	CALL SUBOPT_0x1A
	SBIW R30,1
	MOVW R22,R30
	MOV  R26,R19
	LDI  R30,LOW(10)
	CALL __MODB21
	SUBI R30,-LOW(48)
	MOVW R26,R22
	ST   X,R30
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	LDI  R30,LOW(0)
	ST   X,R30
_0x20A0003:
	CALL __LOADLOCR4
	ADIW R28,16
	RET
__print_G103:
	SBIW R28,63
	SBIW R28,17
	CALL __SAVELOCR6
	LDI  R17,0
	__GETW1SX 88
	STD  Y+8,R30
	STD  Y+8+1,R31
	__GETW1SX 86
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
_0x2060030:
	MOVW R26,R28
	SUBI R26,LOW(-(92))
	SBCI R27,HIGH(-(92))
	CALL SUBOPT_0x13
	SBIW R30,1
	LPM  R30,Z
	MOV  R18,R30
	CPI  R30,0
	BRNE PC+3
	JMP _0x2060032
	MOV  R30,R17
	CPI  R30,0
	BRNE _0x2060036
	CPI  R18,37
	BRNE _0x2060037
	LDI  R17,LOW(1)
	RJMP _0x2060038
_0x2060037:
	CALL SUBOPT_0x1B
_0x2060038:
	RJMP _0x2060035
_0x2060036:
	CPI  R30,LOW(0x1)
	BRNE _0x2060039
	CPI  R18,37
	BRNE _0x206003A
	CALL SUBOPT_0x1B
	RJMP _0x2060112
_0x206003A:
	LDI  R17,LOW(2)
	LDI  R30,LOW(0)
	STD  Y+21,R30
	LDI  R16,LOW(0)
	CPI  R18,45
	BRNE _0x206003B
	LDI  R16,LOW(1)
	RJMP _0x2060035
_0x206003B:
	CPI  R18,43
	BRNE _0x206003C
	LDI  R30,LOW(43)
	STD  Y+21,R30
	RJMP _0x2060035
_0x206003C:
	CPI  R18,32
	BRNE _0x206003D
	LDI  R30,LOW(32)
	STD  Y+21,R30
	RJMP _0x2060035
_0x206003D:
	RJMP _0x206003E
_0x2060039:
	CPI  R30,LOW(0x2)
	BRNE _0x206003F
_0x206003E:
	LDI  R21,LOW(0)
	LDI  R17,LOW(3)
	CPI  R18,48
	BRNE _0x2060040
	ORI  R16,LOW(128)
	RJMP _0x2060035
_0x2060040:
	RJMP _0x2060041
_0x206003F:
	CPI  R30,LOW(0x3)
	BRNE _0x2060042
_0x2060041:
	CPI  R18,48
	BRLO _0x2060044
	CPI  R18,58
	BRLO _0x2060045
_0x2060044:
	RJMP _0x2060043
_0x2060045:
	LDI  R26,LOW(10)
	MUL  R21,R26
	MOV  R21,R0
	MOV  R30,R18
	SUBI R30,LOW(48)
	ADD  R21,R30
	RJMP _0x2060035
_0x2060043:
	LDI  R20,LOW(0)
	CPI  R18,46
	BRNE _0x2060046
	LDI  R17,LOW(4)
	RJMP _0x2060035
_0x2060046:
	RJMP _0x2060047
_0x2060042:
	CPI  R30,LOW(0x4)
	BRNE _0x2060049
	CPI  R18,48
	BRLO _0x206004B
	CPI  R18,58
	BRLO _0x206004C
_0x206004B:
	RJMP _0x206004A
_0x206004C:
	ORI  R16,LOW(32)
	LDI  R26,LOW(10)
	MUL  R20,R26
	MOV  R20,R0
	MOV  R30,R18
	SUBI R30,LOW(48)
	ADD  R20,R30
	RJMP _0x2060035
_0x206004A:
_0x2060047:
	CPI  R18,108
	BRNE _0x206004D
	ORI  R16,LOW(2)
	LDI  R17,LOW(5)
	RJMP _0x2060035
_0x206004D:
	RJMP _0x206004E
_0x2060049:
	CPI  R30,LOW(0x5)
	BREQ PC+3
	JMP _0x2060035
_0x206004E:
	MOV  R30,R18
	CPI  R30,LOW(0x63)
	BRNE _0x2060053
	CALL SUBOPT_0x1C
	CALL SUBOPT_0x1D
	CALL SUBOPT_0x1C
	LDD  R26,Z+4
	ST   -Y,R26
	CALL SUBOPT_0x1E
	RJMP _0x2060054
_0x2060053:
	CPI  R30,LOW(0x45)
	BREQ _0x2060057
	CPI  R30,LOW(0x65)
	BRNE _0x2060058
_0x2060057:
	RJMP _0x2060059
_0x2060058:
	CPI  R30,LOW(0x66)
	BREQ PC+3
	JMP _0x206005A
_0x2060059:
	MOVW R30,R28
	ADIW R30,22
	STD  Y+14,R30
	STD  Y+14+1,R31
	CALL SUBOPT_0x1F
	CALL __GETD1P
	CALL SUBOPT_0x20
	CALL SUBOPT_0x21
	LDD  R26,Y+13
	TST  R26
	BRMI _0x206005B
	LDD  R26,Y+21
	CPI  R26,LOW(0x2B)
	BREQ _0x206005D
	RJMP _0x206005E
_0x206005B:
	CALL SUBOPT_0x22
	CALL __ANEGF1
	CALL SUBOPT_0x20
	LDI  R30,LOW(45)
	STD  Y+21,R30
_0x206005D:
	SBRS R16,7
	RJMP _0x206005F
	LDD  R30,Y+21
	ST   -Y,R30
	CALL SUBOPT_0x1E
	RJMP _0x2060060
_0x206005F:
	LDD  R30,Y+14
	LDD  R31,Y+14+1
	ADIW R30,1
	STD  Y+14,R30
	STD  Y+14+1,R31
	SBIW R30,1
	LDD  R26,Y+21
	STD  Z+0,R26
_0x2060060:
_0x206005E:
	SBRS R16,5
	LDI  R20,LOW(6)
	CPI  R18,102
	BRNE _0x2060062
	CALL SUBOPT_0x22
	CALL __PUTPARD1
	ST   -Y,R20
	LDD  R30,Y+19
	LDD  R31,Y+19+1
	ST   -Y,R31
	ST   -Y,R30
	CALL _ftoa
	RJMP _0x2060063
_0x2060062:
	CALL SUBOPT_0x22
	CALL __PUTPARD1
	ST   -Y,R20
	ST   -Y,R18
	LDD  R30,Y+20
	LDD  R31,Y+20+1
	ST   -Y,R31
	ST   -Y,R30
	RCALL __ftoe_G103
_0x2060063:
	MOVW R30,R28
	ADIW R30,22
	CALL SUBOPT_0x23
	RJMP _0x2060064
_0x206005A:
	CPI  R30,LOW(0x73)
	BRNE _0x2060066
	CALL SUBOPT_0x21
	CALL SUBOPT_0x24
	CALL SUBOPT_0x23
	RJMP _0x2060067
_0x2060066:
	CPI  R30,LOW(0x70)
	BRNE _0x2060069
	CALL SUBOPT_0x21
	CALL SUBOPT_0x24
	STD  Y+14,R30
	STD  Y+14+1,R31
	ST   -Y,R31
	ST   -Y,R30
	CALL _strlenf
	MOV  R17,R30
	ORI  R16,LOW(8)
_0x2060067:
	ANDI R16,LOW(127)
	CPI  R20,0
	BREQ _0x206006B
	CP   R20,R17
	BRLO _0x206006C
_0x206006B:
	RJMP _0x206006A
_0x206006C:
	MOV  R17,R20
_0x206006A:
_0x2060064:
	LDI  R20,LOW(0)
	LDI  R30,LOW(0)
	STD  Y+20,R30
	LDI  R19,LOW(0)
	RJMP _0x206006D
_0x2060069:
	CPI  R30,LOW(0x64)
	BREQ _0x2060070
	CPI  R30,LOW(0x69)
	BRNE _0x2060071
_0x2060070:
	ORI  R16,LOW(4)
	RJMP _0x2060072
_0x2060071:
	CPI  R30,LOW(0x75)
	BRNE _0x2060073
_0x2060072:
	LDI  R30,LOW(10)
	STD  Y+20,R30
	SBRS R16,1
	RJMP _0x2060074
	__GETD1N 0x3B9ACA00
	CALL SUBOPT_0x25
	LDI  R17,LOW(10)
	RJMP _0x2060075
_0x2060074:
	__GETD1N 0x2710
	CALL SUBOPT_0x25
	LDI  R17,LOW(5)
	RJMP _0x2060075
_0x2060073:
	CPI  R30,LOW(0x58)
	BRNE _0x2060077
	ORI  R16,LOW(8)
	RJMP _0x2060078
_0x2060077:
	CPI  R30,LOW(0x78)
	BREQ PC+3
	JMP _0x20600B6
_0x2060078:
	LDI  R30,LOW(16)
	STD  Y+20,R30
	SBRS R16,1
	RJMP _0x206007A
	__GETD1N 0x10000000
	CALL SUBOPT_0x25
	LDI  R17,LOW(8)
	RJMP _0x2060075
_0x206007A:
	__GETD1N 0x1000
	CALL SUBOPT_0x25
	LDI  R17,LOW(4)
_0x2060075:
	CPI  R20,0
	BREQ _0x206007B
	ANDI R16,LOW(127)
	RJMP _0x206007C
_0x206007B:
	LDI  R20,LOW(1)
_0x206007C:
	SBRS R16,1
	RJMP _0x206007D
	CALL SUBOPT_0x21
	CALL SUBOPT_0x1F
	ADIW R26,4
	CALL __GETD1P
	RJMP _0x2060113
_0x206007D:
	SBRS R16,2
	RJMP _0x206007F
	CALL SUBOPT_0x21
	CALL SUBOPT_0x24
	CALL __CWD1
	RJMP _0x2060113
_0x206007F:
	CALL SUBOPT_0x21
	CALL SUBOPT_0x24
	CLR  R22
	CLR  R23
_0x2060113:
	__PUTD1S 10
	SBRS R16,2
	RJMP _0x2060081
	LDD  R26,Y+13
	TST  R26
	BRPL _0x2060082
	CALL SUBOPT_0x22
	CALL __ANEGD1
	CALL SUBOPT_0x20
	LDI  R30,LOW(45)
	STD  Y+21,R30
_0x2060082:
	LDD  R30,Y+21
	CPI  R30,0
	BREQ _0x2060083
	SUBI R17,-LOW(1)
	SUBI R20,-LOW(1)
	RJMP _0x2060084
_0x2060083:
	ANDI R16,LOW(251)
_0x2060084:
_0x2060081:
	MOV  R19,R20
_0x206006D:
	SBRC R16,0
	RJMP _0x2060085
_0x2060086:
	CP   R17,R21
	BRSH _0x2060089
	CP   R19,R21
	BRLO _0x206008A
_0x2060089:
	RJMP _0x2060088
_0x206008A:
	SBRS R16,7
	RJMP _0x206008B
	SBRS R16,2
	RJMP _0x206008C
	ANDI R16,LOW(251)
	LDD  R18,Y+21
	SUBI R17,LOW(1)
	RJMP _0x206008D
_0x206008C:
	LDI  R18,LOW(48)
_0x206008D:
	RJMP _0x206008E
_0x206008B:
	LDI  R18,LOW(32)
_0x206008E:
	CALL SUBOPT_0x1B
	SUBI R21,LOW(1)
	RJMP _0x2060086
_0x2060088:
_0x2060085:
_0x206008F:
	CP   R17,R20
	BRSH _0x2060091
	ORI  R16,LOW(16)
	SBRS R16,2
	RJMP _0x2060092
	CALL SUBOPT_0x26
	BREQ _0x2060093
	SUBI R21,LOW(1)
_0x2060093:
	SUBI R17,LOW(1)
	SUBI R20,LOW(1)
_0x2060092:
	LDI  R30,LOW(48)
	ST   -Y,R30
	CALL SUBOPT_0x1E
	CPI  R21,0
	BREQ _0x2060094
	SUBI R21,LOW(1)
_0x2060094:
	SUBI R20,LOW(1)
	RJMP _0x206008F
_0x2060091:
	MOV  R19,R17
	LDD  R30,Y+20
	CPI  R30,0
	BRNE _0x2060095
_0x2060096:
	CPI  R19,0
	BREQ _0x2060098
	SBRS R16,3
	RJMP _0x2060099
	LDD  R30,Y+14
	LDD  R31,Y+14+1
	LPM  R18,Z+
	STD  Y+14,R30
	STD  Y+14+1,R31
	RJMP _0x206009A
_0x2060099:
	LDD  R26,Y+14
	LDD  R27,Y+14+1
	LD   R18,X+
	STD  Y+14,R26
	STD  Y+14+1,R27
_0x206009A:
	CALL SUBOPT_0x1B
	CPI  R21,0
	BREQ _0x206009B
	SUBI R21,LOW(1)
_0x206009B:
	SUBI R19,LOW(1)
	RJMP _0x2060096
_0x2060098:
	RJMP _0x206009C
_0x2060095:
_0x206009E:
	CALL SUBOPT_0x27
	CALL __DIVD21U
	MOV  R18,R30
	CPI  R18,10
	BRLO _0x20600A0
	SBRS R16,3
	RJMP _0x20600A1
	SUBI R18,-LOW(55)
	RJMP _0x20600A2
_0x20600A1:
	SUBI R18,-LOW(87)
_0x20600A2:
	RJMP _0x20600A3
_0x20600A0:
	SUBI R18,-LOW(48)
_0x20600A3:
	SBRC R16,4
	RJMP _0x20600A5
	CPI  R18,49
	BRSH _0x20600A7
	__GETD2S 16
	__CPD2N 0x1
	BRNE _0x20600A6
_0x20600A7:
	RJMP _0x20600A9
_0x20600A6:
	CP   R20,R19
	BRSH _0x2060114
	CP   R21,R19
	BRLO _0x20600AC
	SBRS R16,0
	RJMP _0x20600AD
_0x20600AC:
	RJMP _0x20600AB
_0x20600AD:
	LDI  R18,LOW(32)
	SBRS R16,7
	RJMP _0x20600AE
_0x2060114:
	LDI  R18,LOW(48)
_0x20600A9:
	ORI  R16,LOW(16)
	SBRS R16,2
	RJMP _0x20600AF
	CALL SUBOPT_0x26
	BREQ _0x20600B0
	SUBI R21,LOW(1)
_0x20600B0:
_0x20600AF:
_0x20600AE:
_0x20600A5:
	CALL SUBOPT_0x1B
	CPI  R21,0
	BREQ _0x20600B1
	SUBI R21,LOW(1)
_0x20600B1:
_0x20600AB:
	SUBI R19,LOW(1)
	CALL SUBOPT_0x27
	CALL __MODD21U
	CALL SUBOPT_0x20
	LDD  R30,Y+20
	__GETD2S 16
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __DIVD21U
	CALL SUBOPT_0x25
	__GETD1S 16
	CALL __CPD10
	BREQ _0x206009F
	RJMP _0x206009E
_0x206009F:
_0x206009C:
	SBRS R16,0
	RJMP _0x20600B2
_0x20600B3:
	CPI  R21,0
	BREQ _0x20600B5
	SUBI R21,LOW(1)
	LDI  R30,LOW(32)
	ST   -Y,R30
	CALL SUBOPT_0x1E
	RJMP _0x20600B3
_0x20600B5:
_0x20600B2:
_0x20600B6:
_0x2060054:
_0x2060112:
	LDI  R17,LOW(0)
_0x2060035:
	RJMP _0x2060030
_0x2060032:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	CALL __GETW1P
	CALL __LOADLOCR6
	ADIW R28,63
	ADIW R28,31
	RET
_sprintf:
	PUSH R15
	MOV  R15,R24
	SBIW R28,6
	CALL __SAVELOCR4
	CALL SUBOPT_0x28
	SBIW R30,0
	BRNE _0x20600B7
	LDI  R30,LOW(65535)
	LDI  R31,HIGH(65535)
	RJMP _0x20A0002
_0x20600B7:
	MOVW R26,R28
	ADIW R26,6
	CALL __ADDW2R15
	MOVW R16,R26
	CALL SUBOPT_0x28
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R30,LOW(0)
	STD  Y+8,R30
	STD  Y+8+1,R30
	MOVW R26,R28
	ADIW R26,10
	CALL __ADDW2R15
	CALL __GETW1P
	ST   -Y,R31
	ST   -Y,R30
	ST   -Y,R17
	ST   -Y,R16
	LDI  R30,LOW(_put_buff_G103)
	LDI  R31,HIGH(_put_buff_G103)
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,10
	ST   -Y,R31
	ST   -Y,R30
	RCALL __print_G103
	MOVW R18,R30
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LDI  R30,LOW(0)
	ST   X,R30
	MOVW R30,R18
_0x20A0002:
	CALL __LOADLOCR4
	ADIW R28,10
	POP  R15
	RET

	.CSEG
_ftrunc:
   ldd  r23,y+3
   ldd  r22,y+2
   ldd  r31,y+1
   ld   r30,y
   bst  r23,7
   lsl  r23
   sbrc r22,7
   sbr  r23,1
   mov  r25,r23
   subi r25,0x7e
   breq __ftrunc0
   brcs __ftrunc0
   cpi  r25,24
   brsh __ftrunc1
   clr  r26
   clr  r27
   clr  r24
__ftrunc2:
   sec
   ror  r24
   ror  r27
   ror  r26
   dec  r25
   brne __ftrunc2
   and  r30,r26
   and  r31,r27
   and  r22,r24
   rjmp __ftrunc1
__ftrunc0:
   clt
   clr  r23
   clr  r30
   clr  r31
   clr  r22
__ftrunc1:
   cbr  r22,0x80
   lsr  r23
   brcc __ftrunc3
   sbr  r22,0x80
__ftrunc3:
   bld  r23,7
   ld   r26,y+
   ld   r27,y+
   ld   r24,y+
   ld   r25,y+
   cp   r30,r26
   cpc  r31,r27
   cpc  r22,r24
   cpc  r23,r25
   bst  r25,7
   ret
_floor:
	RCALL SUBOPT_0x29
	CALL __PUTPARD1
	CALL _ftrunc
	CALL __PUTD1S0
    brne __floor1
__floor0:
	RCALL SUBOPT_0x29
	RJMP _0x20A0001
__floor1:
    brtc __floor0
	RCALL SUBOPT_0x29
	__GETD2N 0x3F800000
	CALL __SUBF12
_0x20A0001:
	ADIW R28,4
	RET

	.ESEG
_FlagSetTime:
	.DB  0x1

	.DSEG
__seed_G102:
	.BYTE 0x4

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x0:
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x1:
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x2:
	ST   -Y,R30
	CALL _LCD16X2_Send4Bit
	JMP  _LCD16X2_Enable

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x3:
	LDI  R30,LOW(5)
	LDI  R31,HIGH(5)
	RJMP SUBOPT_0x1

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x4:
	CALL _I2CSOFT_Start
	LDI  R30,LOW(208)
	ST   -Y,R30
	JMP  _I2CSOFT_WriteData

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x5:
	SBI  0x15,0
	__DELAY_USB 13
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x6:
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x7:
	ST   -Y,R31
	ST   -Y,R30
	JMP  _strcpyf

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x8:
	__PUTD1S 9
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x9:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	ADIW R26,1
	STD  Y+6,R26
	STD  Y+6+1,R27
	SBIW R26,1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0xA:
	__GETD2S 2
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0xB:
	__GETD1N 0x3DCCCCCD
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0xC:
	__PUTD1S 2
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0xD:
	__GETD1S 2
	__GETD2S 9
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0xE:
	__GETD1N 0x41200000
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0xF:
	__GETD2N 0x3F000000
	CALL __ADDF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x10:
	MOV  R30,R16
	SUBI R30,-LOW(48)
	ST   X,R30
	MOV  R30,R16
	LDI  R31,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x11:
	__GETD2S 9
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x12:
	CALL __SWAPD12
	CALL __SUBF12
	RJMP SUBOPT_0x8

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x13:
	LD   R30,X+
	LD   R31,X+
	ADIW R30,1
	ST   -X,R31
	ST   -X,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x14:
	__GETD2S 4
	RJMP SUBOPT_0xE

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x15:
	__PUTD1S 4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0x16:
	__GETD1S 4
	__GETD2S 12
	CALL __CMPF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x17:
	__GETD2S 12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x18:
	__PUTD1S 12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x19:
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	ADIW R26,1
	STD  Y+8,R26
	STD  Y+8+1,R27
	SBIW R26,1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x1A:
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ADIW R30,1
	STD  Y+8,R30
	STD  Y+8+1,R31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0x1B:
	ST   -Y,R18
	LDD  R30,Y+7
	LDD  R31,Y+7+1
	ST   -Y,R31
	ST   -Y,R30
	LDD  R30,Y+11
	LDD  R31,Y+11+1
	ICALL
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 8 TIMES, CODE SIZE REDUCTION:25 WORDS
SUBOPT_0x1C:
	__GETW1SX 90
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0x1D:
	SBIW R30,4
	__PUTW1SX 90
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:12 WORDS
SUBOPT_0x1E:
	LDD  R30,Y+7
	LDD  R31,Y+7+1
	ST   -Y,R31
	ST   -Y,R30
	LDD  R30,Y+11
	LDD  R31,Y+11+1
	ICALL
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:17 WORDS
SUBOPT_0x1F:
	__GETW2SX 90
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x20:
	__PUTD1S 10
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x21:
	RCALL SUBOPT_0x1C
	RJMP SUBOPT_0x1D

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x22:
	__GETD1S 10
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x23:
	STD  Y+14,R30
	STD  Y+14+1,R31
	ST   -Y,R31
	ST   -Y,R30
	CALL _strlen
	MOV  R17,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x24:
	RCALL SUBOPT_0x1F
	ADIW R26,4
	CALL __GETW1P
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x25:
	__PUTD1S 16
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:14 WORDS
SUBOPT_0x26:
	ANDI R16,LOW(251)
	LDD  R30,Y+21
	ST   -Y,R30
	__GETW1SX 87
	ST   -Y,R31
	ST   -Y,R30
	__GETW1SX 91
	ICALL
	CPI  R21,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x27:
	__GETD1S 16
	__GETD2S 10
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x28:
	MOVW R26,R28
	ADIW R26,12
	CALL __ADDW2R15
	CALL __GETW1P
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x29:
	CALL __GETD1S0
	RET


	.CSEG
_delay_ms:
	ld   r30,y+
	ld   r31,y+
	adiw r30,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0x7D0
	wdr
	sbiw r30,1
	brne __delay_ms0
__delay_ms1:
	ret

__ANEGF1:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __ANEGF10
	SUBI R23,0x80
__ANEGF10:
	RET

__ROUND_REPACK:
	TST  R21
	BRPL __REPACK
	CPI  R21,0x80
	BRNE __ROUND_REPACK0
	SBRS R30,0
	RJMP __REPACK
__ROUND_REPACK0:
	ADIW R30,1
	ADC  R22,R25
	ADC  R23,R25
	BRVS __REPACK1

__REPACK:
	LDI  R21,0x80
	EOR  R21,R23
	BRNE __REPACK0
	PUSH R21
	RJMP __ZERORES
__REPACK0:
	CPI  R21,0xFF
	BREQ __REPACK1
	LSL  R22
	LSL  R0
	ROR  R21
	ROR  R22
	MOV  R23,R21
	RET
__REPACK1:
	PUSH R21
	TST  R0
	BRMI __REPACK2
	RJMP __MAXRES
__REPACK2:
	RJMP __MINRES

__UNPACK:
	LDI  R21,0x80
	MOV  R1,R25
	AND  R1,R21
	LSL  R24
	ROL  R25
	EOR  R25,R21
	LSL  R21
	ROR  R24

__UNPACK1:
	LDI  R21,0x80
	MOV  R0,R23
	AND  R0,R21
	LSL  R22
	ROL  R23
	EOR  R23,R21
	LSL  R21
	ROR  R22
	RET

__CFD1U:
	SET
	RJMP __CFD1U0
__CFD1:
	CLT
__CFD1U0:
	PUSH R21
	RCALL __UNPACK1
	CPI  R23,0x80
	BRLO __CFD10
	CPI  R23,0xFF
	BRCC __CFD10
	RJMP __ZERORES
__CFD10:
	LDI  R21,22
	SUB  R21,R23
	BRPL __CFD11
	NEG  R21
	CPI  R21,8
	BRTC __CFD19
	CPI  R21,9
__CFD19:
	BRLO __CFD17
	SER  R30
	SER  R31
	SER  R22
	LDI  R23,0x7F
	BLD  R23,7
	RJMP __CFD15
__CFD17:
	CLR  R23
	TST  R21
	BREQ __CFD15
__CFD18:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	DEC  R21
	BRNE __CFD18
	RJMP __CFD15
__CFD11:
	CLR  R23
__CFD12:
	CPI  R21,8
	BRLO __CFD13
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R23
	SUBI R21,8
	RJMP __CFD12
__CFD13:
	TST  R21
	BREQ __CFD15
__CFD14:
	LSR  R23
	ROR  R22
	ROR  R31
	ROR  R30
	DEC  R21
	BRNE __CFD14
__CFD15:
	TST  R0
	BRPL __CFD16
	RCALL __ANEGD1
__CFD16:
	POP  R21
	RET

__CDF1U:
	SET
	RJMP __CDF1U0
__CDF1:
	CLT
__CDF1U0:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __CDF10
	CLR  R0
	BRTS __CDF11
	TST  R23
	BRPL __CDF11
	COM  R0
	RCALL __ANEGD1
__CDF11:
	MOV  R1,R23
	LDI  R23,30
	TST  R1
__CDF12:
	BRMI __CDF13
	DEC  R23
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R1
	RJMP __CDF12
__CDF13:
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R1
	PUSH R21
	RCALL __REPACK
	POP  R21
__CDF10:
	RET

__SWAPACC:
	PUSH R20
	MOVW R20,R30
	MOVW R30,R26
	MOVW R26,R20
	MOVW R20,R22
	MOVW R22,R24
	MOVW R24,R20
	MOV  R20,R0
	MOV  R0,R1
	MOV  R1,R20
	POP  R20
	RET

__UADD12:
	ADD  R30,R26
	ADC  R31,R27
	ADC  R22,R24
	RET

__NEGMAN1:
	COM  R30
	COM  R31
	COM  R22
	SUBI R30,-1
	SBCI R31,-1
	SBCI R22,-1
	RET

__SUBF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129
	LDI  R21,0x80
	EOR  R1,R21

	RJMP __ADDF120

__ADDF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129

__ADDF120:
	CPI  R23,0x80
	BREQ __ADDF128
__ADDF121:
	MOV  R21,R23
	SUB  R21,R25
	BRVS __ADDF1211
	BRPL __ADDF122
	RCALL __SWAPACC
	RJMP __ADDF121
__ADDF122:
	CPI  R21,24
	BRLO __ADDF123
	CLR  R26
	CLR  R27
	CLR  R24
__ADDF123:
	CPI  R21,8
	BRLO __ADDF124
	MOV  R26,R27
	MOV  R27,R24
	CLR  R24
	SUBI R21,8
	RJMP __ADDF123
__ADDF124:
	TST  R21
	BREQ __ADDF126
__ADDF125:
	LSR  R24
	ROR  R27
	ROR  R26
	DEC  R21
	BRNE __ADDF125
__ADDF126:
	MOV  R21,R0
	EOR  R21,R1
	BRMI __ADDF127
	RCALL __UADD12
	BRCC __ADDF129
	ROR  R22
	ROR  R31
	ROR  R30
	INC  R23
	BRVC __ADDF129
	RJMP __MAXRES
__ADDF128:
	RCALL __SWAPACC
__ADDF129:
	RCALL __REPACK
	POP  R21
	RET
__ADDF1211:
	BRCC __ADDF128
	RJMP __ADDF129
__ADDF127:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	BREQ __ZERORES
	BRCC __ADDF1210
	COM  R0
	RCALL __NEGMAN1
__ADDF1210:
	TST  R22
	BRMI __ADDF129
	LSL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVC __ADDF1210

__ZERORES:
	CLR  R30
	CLR  R31
	CLR  R22
	CLR  R23
	POP  R21
	RET

__MINRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	SER  R23
	POP  R21
	RET

__MAXRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	LDI  R23,0x7F
	POP  R21
	RET

__MULF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BREQ __ZERORES
	CPI  R25,0x80
	BREQ __ZERORES
	EOR  R0,R1
	SEC
	ADC  R23,R25
	BRVC __MULF124
	BRLT __ZERORES
__MULF125:
	TST  R0
	BRMI __MINRES
	RJMP __MAXRES
__MULF124:
	PUSH R0
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R17
	CLR  R18
	CLR  R25
	MUL  R22,R24
	MOVW R20,R0
	MUL  R24,R31
	MOV  R19,R0
	ADD  R20,R1
	ADC  R21,R25
	MUL  R22,R27
	ADD  R19,R0
	ADC  R20,R1
	ADC  R21,R25
	MUL  R24,R30
	RCALL __MULF126
	MUL  R27,R31
	RCALL __MULF126
	MUL  R22,R26
	RCALL __MULF126
	MUL  R27,R30
	RCALL __MULF127
	MUL  R26,R31
	RCALL __MULF127
	MUL  R26,R30
	ADD  R17,R1
	ADC  R18,R25
	ADC  R19,R25
	ADC  R20,R25
	ADC  R21,R25
	MOV  R30,R19
	MOV  R31,R20
	MOV  R22,R21
	MOV  R21,R18
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	POP  R0
	TST  R22
	BRMI __MULF122
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	RJMP __MULF123
__MULF122:
	INC  R23
	BRVS __MULF125
__MULF123:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__MULF127:
	ADD  R17,R0
	ADC  R18,R1
	ADC  R19,R25
	RJMP __MULF128
__MULF126:
	ADD  R18,R0
	ADC  R19,R1
__MULF128:
	ADC  R20,R25
	ADC  R21,R25
	RET

__DIVF21:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BRNE __DIVF210
	TST  R1
__DIVF211:
	BRPL __DIVF219
	RJMP __MINRES
__DIVF219:
	RJMP __MAXRES
__DIVF210:
	CPI  R25,0x80
	BRNE __DIVF218
__DIVF217:
	RJMP __ZERORES
__DIVF218:
	EOR  R0,R1
	SEC
	SBC  R25,R23
	BRVC __DIVF216
	BRLT __DIVF217
	TST  R0
	RJMP __DIVF211
__DIVF216:
	MOV  R23,R25
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R1
	CLR  R17
	CLR  R18
	CLR  R19
	CLR  R20
	CLR  R21
	LDI  R25,32
__DIVF212:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R20,R17
	BRLO __DIVF213
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R20,R17
	SEC
	RJMP __DIVF214
__DIVF213:
	CLC
__DIVF214:
	ROL  R21
	ROL  R18
	ROL  R19
	ROL  R1
	ROL  R26
	ROL  R27
	ROL  R24
	ROL  R20
	DEC  R25
	BRNE __DIVF212
	MOVW R30,R18
	MOV  R22,R1
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	TST  R22
	BRMI __DIVF215
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVS __DIVF217
__DIVF215:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__CMPF12:
	TST  R25
	BRMI __CMPF120
	TST  R23
	BRMI __CMPF121
	CP   R25,R23
	BRLO __CMPF122
	BRNE __CMPF121
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	BRLO __CMPF122
	BREQ __CMPF123
__CMPF121:
	CLZ
	CLC
	RET
__CMPF122:
	CLZ
	SEC
	RET
__CMPF123:
	SEZ
	CLC
	RET
__CMPF120:
	TST  R23
	BRPL __CMPF122
	CP   R25,R23
	BRLO __CMPF121
	BRNE __CMPF122
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	BRLO __CMPF122
	BREQ __CMPF123
	RJMP __CMPF121

__ADDW2R15:
	CLR  R0
	ADD  R26,R15
	ADC  R27,R0
	RET

__ANEGW1:
	NEG  R31
	NEG  R30
	SBCI R31,0
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__ASRW4:
	ASR  R31
	ROR  R30
__ASRW3:
	ASR  R31
	ROR  R30
__ASRW2:
	ASR  R31
	ROR  R30
	ASR  R31
	ROR  R30
	RET

__CBD1:
	MOV  R31,R30
	ADD  R31,R31
	SBC  R31,R31
	MOV  R22,R31
	MOV  R23,R31
	RET

__CWD1:
	MOV  R22,R31
	ADD  R22,R22
	SBC  R22,R22
	MOV  R23,R22
	RET

__EQB12:
	CP   R30,R26
	LDI  R30,1
	BREQ __EQB12T
	CLR  R30
__EQB12T:
	RET

__DIVB21U:
	CLR  R0
	LDI  R25,8
__DIVB21U1:
	LSL  R26
	ROL  R0
	SUB  R0,R30
	BRCC __DIVB21U2
	ADD  R0,R30
	RJMP __DIVB21U3
__DIVB21U2:
	SBR  R26,1
__DIVB21U3:
	DEC  R25
	BRNE __DIVB21U1
	MOV  R30,R26
	MOV  R26,R0
	RET

__DIVB21:
	RCALL __CHKSIGNB
	RCALL __DIVB21U
	BRTC __DIVB211
	NEG  R30
__DIVB211:
	RET

__DIVW21U:
	CLR  R0
	CLR  R1
	LDI  R25,16
__DIVW21U1:
	LSL  R26
	ROL  R27
	ROL  R0
	ROL  R1
	SUB  R0,R30
	SBC  R1,R31
	BRCC __DIVW21U2
	ADD  R0,R30
	ADC  R1,R31
	RJMP __DIVW21U3
__DIVW21U2:
	SBR  R26,1
__DIVW21U3:
	DEC  R25
	BRNE __DIVW21U1
	MOVW R30,R26
	MOVW R26,R0
	RET

__DIVW21:
	RCALL __CHKSIGNW
	RCALL __DIVW21U
	BRTC __DIVW211
	RCALL __ANEGW1
__DIVW211:
	RET

__DIVD21U:
	PUSH R19
	PUSH R20
	PUSH R21
	CLR  R0
	CLR  R1
	CLR  R20
	CLR  R21
	LDI  R19,32
__DIVD21U1:
	LSL  R26
	ROL  R27
	ROL  R24
	ROL  R25
	ROL  R0
	ROL  R1
	ROL  R20
	ROL  R21
	SUB  R0,R30
	SBC  R1,R31
	SBC  R20,R22
	SBC  R21,R23
	BRCC __DIVD21U2
	ADD  R0,R30
	ADC  R1,R31
	ADC  R20,R22
	ADC  R21,R23
	RJMP __DIVD21U3
__DIVD21U2:
	SBR  R26,1
__DIVD21U3:
	DEC  R19
	BRNE __DIVD21U1
	MOVW R30,R26
	MOVW R22,R24
	MOVW R26,R0
	MOVW R24,R20
	POP  R21
	POP  R20
	POP  R19
	RET

__MODB21:
	CLT
	SBRS R26,7
	RJMP __MODB211
	NEG  R26
	SET
__MODB211:
	SBRC R30,7
	NEG  R30
	RCALL __DIVB21U
	MOV  R30,R26
	BRTC __MODB212
	NEG  R30
__MODB212:
	RET

__MODW21:
	CLT
	SBRS R27,7
	RJMP __MODW211
	COM  R26
	COM  R27
	ADIW R26,1
	SET
__MODW211:
	SBRC R31,7
	RCALL __ANEGW1
	RCALL __DIVW21U
	MOVW R30,R26
	BRTC __MODW212
	RCALL __ANEGW1
__MODW212:
	RET

__MODD21U:
	RCALL __DIVD21U
	MOVW R30,R26
	MOVW R22,R24
	RET

__CHKSIGNB:
	CLT
	SBRS R30,7
	RJMP __CHKSB1
	NEG  R30
	SET
__CHKSB1:
	SBRS R26,7
	RJMP __CHKSB2
	NEG  R26
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSB2:
	RET

__CHKSIGNW:
	CLT
	SBRS R31,7
	RJMP __CHKSW1
	RCALL __ANEGW1
	SET
__CHKSW1:
	SBRS R27,7
	RJMP __CHKSW2
	COM  R26
	COM  R27
	ADIW R26,1
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSW2:
	RET

__GETW1P:
	LD   R30,X+
	LD   R31,X
	SBIW R26,1
	RET

__GETD1P:
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X
	SBIW R26,3
	RET

__GETD1S0:
	LD   R30,Y
	LDD  R31,Y+1
	LDD  R22,Y+2
	LDD  R23,Y+3
	RET

__PUTD1S0:
	ST   Y,R30
	STD  Y+1,R31
	STD  Y+2,R22
	STD  Y+3,R23
	RET

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__SWAPD12:
	MOV  R1,R24
	MOV  R24,R22
	MOV  R22,R1
	MOV  R1,R25
	MOV  R25,R23
	MOV  R23,R1

__SWAPW12:
	MOV  R1,R27
	MOV  R27,R31
	MOV  R31,R1

__SWAPB12:
	MOV  R1,R26
	MOV  R26,R30
	MOV  R30,R1
	RET

__EEPROMRDB:
	SBIC EECR,EEWE
	RJMP __EEPROMRDB
	PUSH R31
	IN   R31,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R30,EEDR
	OUT  SREG,R31
	POP  R31
	RET

__EEPROMWRB:
	SBIS EECR,EEWE
	RJMP __EEPROMWRB1
	WDR
	RJMP __EEPROMWRB
__EEPROMWRB1:
	IN   R25,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R24,EEDR
	CP   R30,R24
	BREQ __EEPROMWRB0
	OUT  EEDR,R30
	SBI  EECR,EEMWE
	SBI  EECR,EEWE
__EEPROMWRB0:
	OUT  SREG,R25
	RET

__CPD10:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	RET

__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

;END OF CODE MARKER
__END_OF_CODE:
