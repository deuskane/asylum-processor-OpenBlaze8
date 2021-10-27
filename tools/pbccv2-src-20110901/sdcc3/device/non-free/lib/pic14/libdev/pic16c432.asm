;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c432.c"
	list	p=16c432
	radix dec
	include "p16c432.inc"
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
	global	_CMCON_bits
	global	_INTCON_bits
	global	_LINPRT_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_STATUS_bits
	global	_TRISB_bits
	global	_VRCON_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_PORTA
	global	_PORTB
	global	_PCLATH
	global	_INTCON
	global	_PIR1
	global	_CMCON
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_PIE1
	global	_PCON
	global	_LINPRT
	global	_VRCON

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c432_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c432_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c432_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c432_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c432_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c432_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c432_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c432_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c432_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c432_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c432_1f	udata_ovr	0x001f
_CMCON_bits
_CMCON
	res	1
UD_abs_pic16c432_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c432_85	udata_ovr	0x0085
_TRISA
	res	1
UD_abs_pic16c432_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c432_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c432_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c432_90	udata_ovr	0x0090
_LINPRT_bits
_LINPRT
	res	1
UD_abs_pic16c432_9f	udata_ovr	0x009f
_VRCON_bits
_VRCON
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
code_pic16c432	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
