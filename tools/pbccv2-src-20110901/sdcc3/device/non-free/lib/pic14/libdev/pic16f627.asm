;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16f627.c"
	list	p=16f627
	radix dec
	include "p16f627.inc"
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
	global	_CMCON_bits
	global	_EECON1_bits
	global	_INTCON_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_RCSTA_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TXSTA_bits
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
	global	_TMR1L
	global	_TMR1H
	global	_T1CON
	global	_TMR2
	global	_T2CON
	global	_CCPR1L
	global	_CCPR1H
	global	_CCP1CON
	global	_RCSTA
	global	_TXREG
	global	_RCREG
	global	_CMCON
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_PIE1
	global	_PCON
	global	_PR2
	global	_TXSTA
	global	_SPBRG
	global	_EEDATA
	global	_EEADR
	global	_EECON1
	global	_EECON2
	global	_VRCON

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16f627_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16f627_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16f627_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16f627_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16f627_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16f627_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16f627_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16f627_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16f627_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16f627_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16f627_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16f627_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16f627_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16f627_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16f627_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16f627_15	udata_ovr	0x0015
_CCPR1L
	res	1
UD_abs_pic16f627_16	udata_ovr	0x0016
_CCPR1H
	res	1
UD_abs_pic16f627_17	udata_ovr	0x0017
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16f627_18	udata_ovr	0x0018
_RCSTA_bits
_RCSTA
	res	1
UD_abs_pic16f627_19	udata_ovr	0x0019
_TXREG
	res	1
UD_abs_pic16f627_1a	udata_ovr	0x001a
_RCREG
	res	1
UD_abs_pic16f627_1f	udata_ovr	0x001f
_CMCON_bits
_CMCON
	res	1
UD_abs_pic16f627_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16f627_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16f627_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16f627_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16f627_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16f627_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16f627_98	udata_ovr	0x0098
_TXSTA_bits
_TXSTA
	res	1
UD_abs_pic16f627_99	udata_ovr	0x0099
_SPBRG
	res	1
UD_abs_pic16f627_9a	udata_ovr	0x009a
_EEDATA
	res	1
UD_abs_pic16f627_9b	udata_ovr	0x009b
_EEADR
	res	1
UD_abs_pic16f627_9c	udata_ovr	0x009c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic16f627_9d	udata_ovr	0x009d
_EECON2
	res	1
UD_abs_pic16f627_9f	udata_ovr	0x009f
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
code_pic16f627	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
