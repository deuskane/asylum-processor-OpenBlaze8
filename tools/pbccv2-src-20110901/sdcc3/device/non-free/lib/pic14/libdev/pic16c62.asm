;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c62.c"
	list	p=16c62
	radix dec
	include "p16c62.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------

	extern PSAVE
	extern SSAVE
	extern WSAVE
	extern STK12
	extern STK11
	extern STK10
	extern STK09
	extern STK08
	extern STK07
	extern STK06
	extern STK05
	extern STK04
	extern STK03
	extern STK02
	extern STK01
	extern STK00
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_CCP1CON_bits
	global	_INTCON_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_PORTC_bits
	global	_SSPCON_bits
	global	_SSPSTAT_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TRISC_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_PORTA
	global	_PORTB
	global	_PORTC
	global	_PCLATH
	global	_INTCON
	global	_PIR1
	global	_TMR1L
	global	_TMR1H
	global	_T1CON
	global	_TMR2
	global	_T2CON
	global	_SSPBUF
	global	_SSPCON
	global	_CCPR1L
	global	_CCPR1H
	global	_CCP1CON
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_TRISC
	global	_PIE1
	global	_PCON
	global	_PR2
	global	_SSPADD
	global	_SSPSTAT

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c62_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c62_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c62_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c62_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c62_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c62_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c62_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c62_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16c62_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c62_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c62_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c62_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16c62_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16c62_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16c62_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16c62_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16c62_13	udata_ovr	0x0013
_SSPBUF
	res	1
UD_abs_pic16c62_14	udata_ovr	0x0014
_SSPCON_bits
_SSPCON
	res	1
UD_abs_pic16c62_15	udata_ovr	0x0015
_CCPR1L
	res	1
UD_abs_pic16c62_16	udata_ovr	0x0016
_CCPR1H
	res	1
UD_abs_pic16c62_17	udata_ovr	0x0017
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16c62_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c62_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16c62_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c62_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16c62_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c62_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c62_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16c62_93	udata_ovr	0x0093
_SSPADD
	res	1
UD_abs_pic16c62_94	udata_ovr	0x0094
_SSPSTAT_bits
_SSPSTAT
	res	1
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_pic16c62	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
