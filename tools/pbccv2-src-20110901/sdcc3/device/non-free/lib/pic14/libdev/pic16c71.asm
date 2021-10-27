;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c71.c"
	list	p=16c71
	radix dec
	include "p16c71.inc"
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
	global	_PORTA_bits
	global	_PORTB_bits
	global	_STATUS_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_PORTA
	global	_PORTB
	global	_ADCON0
	global	_ADRES
	global	_PCLATH
	global	_INTCON
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_ADCON1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c71_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c71_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c71_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c71_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c71_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c71_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c71_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c71_8	udata_ovr	0x0008
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16c71_9	udata_ovr	0x0009
_ADRES
	res	1
UD_abs_pic16c71_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c71_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c71_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c71_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16c71_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c71_88	udata_ovr	0x0088
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
code_pic16c71	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
