;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c433.c"
	list	p=16c433
	radix dec
	include "p16c433.inc"
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
	global	_ADCON0_bits
	global	_ADCON1_bits
	global	_INTCON_bits
	global	_OPTION_REG_bits
	global	_OSCCAL_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_STATUS_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_GPIO
	global	_PCLATH
	global	_INTCON
	global	_PIR1
	global	_ADRES
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISIO
	global	_PIE1
	global	_PCON
	global	_OSCCAL
	global	_ADCON1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c433_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c433_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c433_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c433_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c433_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c433_5	udata_ovr	0x0005
_GPIO
	res	1
UD_abs_pic16c433_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c433_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c433_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c433_1e	udata_ovr	0x001e
_ADRES
	res	1
UD_abs_pic16c433_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16c433_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c433_85	udata_ovr	0x0085
_TRISIO
	res	1
UD_abs_pic16c433_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c433_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c433_8f	udata_ovr	0x008f
_OSCCAL_bits
_OSCCAL
	res	1
UD_abs_pic16c433_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
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
code_pic16c433	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
