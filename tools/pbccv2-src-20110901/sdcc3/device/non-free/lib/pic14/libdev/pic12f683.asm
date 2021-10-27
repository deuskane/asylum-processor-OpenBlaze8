;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:10 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic12f683.c"
	list	p=12f683
	radix dec
	include "p12f683.inc"
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
	global	_CCP1CON_bits
	global	_CMCON0_bits
	global	_CMCON1_bits
	global	_EECON1_bits
	global	_GPIO_bits
	global	_INTCON_bits
	global	_IOC_bits
	global	_IOCA_bits
	global	_OPTION_REG_bits
	global	_OSCCON_bits
	global	_OSCTUNE_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_VRCON_bits
	global	_WDTCON_bits
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
	global	_TMR2
	global	_T2CON
	global	_CCPR1L
	global	_CCPR1H
	global	_CCP1CON
	global	_WDTCON
	global	_CMCON0
	global	_CMCON1
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISIO
	global	_PIE1
	global	_PCON
	global	_OSCCON
	global	_OSCTUNE
	global	_PR2
	global	_WPU
	global	_WPUA
	global	_IOC
	global	_IOCA
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
UD_abs_pic12f683_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic12f683_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic12f683_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic12f683_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic12f683_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic12f683_5	udata_ovr	0x0005
_GPIO_bits
_GPIO
	res	1
UD_abs_pic12f683_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic12f683_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic12f683_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic12f683_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic12f683_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic12f683_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic12f683_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic12f683_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic12f683_13	udata_ovr	0x0013
_CCPR1L
	res	1
UD_abs_pic12f683_14	udata_ovr	0x0014
_CCPR1H
	res	1
UD_abs_pic12f683_15	udata_ovr	0x0015
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic12f683_18	udata_ovr	0x0018
_WDTCON_bits
_WDTCON
	res	1
UD_abs_pic12f683_19	udata_ovr	0x0019
_CMCON0_bits
_CMCON0
	res	1
UD_abs_pic12f683_1a	udata_ovr	0x001a
_CMCON1_bits
_CMCON1
	res	1
UD_abs_pic12f683_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic12f683_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic12f683_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic12f683_85	udata_ovr	0x0085
_TRISIO
	res	1
UD_abs_pic12f683_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic12f683_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic12f683_8f	udata_ovr	0x008f
_OSCCON_bits
_OSCCON
	res	1
UD_abs_pic12f683_90	udata_ovr	0x0090
_OSCTUNE_bits
_OSCTUNE
	res	1
UD_abs_pic12f683_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic12f683_95	udata_ovr	0x0095
_WPU
_WPUA
	res	1
UD_abs_pic12f683_96	udata_ovr	0x0096
_IOC_bits
_IOCA_bits
_IOC
_IOCA
	res	1
UD_abs_pic12f683_99	udata_ovr	0x0099
_VRCON_bits
_VRCON
	res	1
UD_abs_pic12f683_9a	udata_ovr	0x009a
_EEDATA
_EEDAT
	res	1
UD_abs_pic12f683_9b	udata_ovr	0x009b
_EEADR
	res	1
UD_abs_pic12f683_9c	udata_ovr	0x009c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic12f683_9d	udata_ovr	0x009d
_EECON2
	res	1
UD_abs_pic12f683_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic12f683_9f	udata_ovr	0x009f
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
code_pic12f683	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
