;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic12f675.c"
	list	p=12f675
	radix dec
	include "p12f675.inc"
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
	global	_ANSEL_bits
	global	_CMCON_bits
	global	_EECON1_bits
	global	_GPIO_bits
	global	_INTCON_bits
	global	_IOC_bits
	global	_IOCB_bits
	global	_OPTION_REG_bits
	global	_OSCCAL_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_TRISIO_bits
	global	_VRCON_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_GPIO
	global	_PCLATH
	global	_INTCON
	global	_PIR1
	global	_TMR1L
	global	_TMR1H
	global	_T1CON
	global	_CMCON
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISIO
	global	_PIE1
	global	_PCON
	global	_OSCCAL
	global	_WPU
	global	_IOC
	global	_IOCB
	global	_VRCON
	global	_EEDATA
	global	_EEDAT
	global	_EEADR
	global	_EECON1
	global	_EECON2
	global	_ADRESL
	global	_ANSEL

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic12f675_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic12f675_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic12f675_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic12f675_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic12f675_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic12f675_5	udata_ovr	0x0005
_GPIO_bits
_GPIO
	res	1
UD_abs_pic12f675_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic12f675_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic12f675_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic12f675_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic12f675_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic12f675_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic12f675_19	udata_ovr	0x0019
_CMCON_bits
_CMCON
	res	1
UD_abs_pic12f675_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic12f675_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic12f675_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic12f675_85	udata_ovr	0x0085
_TRISIO_bits
_TRISIO
	res	1
UD_abs_pic12f675_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic12f675_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic12f675_90	udata_ovr	0x0090
_OSCCAL_bits
_OSCCAL
	res	1
UD_abs_pic12f675_95	udata_ovr	0x0095
_WPU
	res	1
UD_abs_pic12f675_96	udata_ovr	0x0096
_IOC_bits
_IOCB_bits
_IOC
_IOCB
	res	1
UD_abs_pic12f675_99	udata_ovr	0x0099
_VRCON_bits
_VRCON
	res	1
UD_abs_pic12f675_9a	udata_ovr	0x009a
_EEDATA
_EEDAT
	res	1
UD_abs_pic12f675_9b	udata_ovr	0x009b
_EEADR
	res	1
UD_abs_pic12f675_9c	udata_ovr	0x009c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic12f675_9d	udata_ovr	0x009d
_EECON2
	res	1
UD_abs_pic12f675_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic12f675_9f	udata_ovr	0x009f
_ANSEL_bits
_ANSEL
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
code_pic12f675	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
