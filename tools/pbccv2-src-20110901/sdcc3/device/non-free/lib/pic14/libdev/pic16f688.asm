;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16f688.c"
	list	p=16f688
	radix dec
	include "p16f688.inc"
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
	global	_ANSEL_bits
	global	_BAUDCTL_bits
	global	_CMCON0_bits
	global	_CMCON1_bits
	global	_EECON1_bits
	global	_INTCON_bits
	global	_IOC_bits
	global	_IOCA_bits
	global	_OPTION_REG_bits
	global	_OSCCON_bits
	global	_OSCTUNE_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PORTA_bits
	global	_PORTC_bits
	global	_RCSTA_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_TRISA_bits
	global	_TRISC_bits
	global	_TXSTA_bits
	global	_VRCON_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_PORTA
	global	_PORTC
	global	_PCLATH
	global	_INTCON
	global	_PIR1
	global	_TMR1L
	global	_TMR1H
	global	_T1CON
	global	_BAUDCTL
	global	_SPBRGH
	global	_SPBRG
	global	_RCREG
	global	_TXREG
	global	_TXSTA
	global	_RCSTA
	global	_WDTCON
	global	_CMCON0
	global	_CMCON1
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISC
	global	_PIE1
	global	_PCON
	global	_OSCCON
	global	_OSCTUNE
	global	_ANSEL
	global	_WPU
	global	_WPUA
	global	_IOC
	global	_IOCA
	global	_EEDATH
	global	_EEADRH
	global	_VRCON
	global	_EEDAT
	global	_EEDATA
	global	_EEADR
	global	_EECON1
	global	_EECON2
	global	_ADRESL
	global	_ADCON1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16f688_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16f688_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16f688_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16f688_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16f688_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16f688_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16f688_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16f688_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16f688_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16f688_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16f688_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16f688_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16f688_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16f688_11	udata_ovr	0x0011
_BAUDCTL_bits
_BAUDCTL
	res	1
UD_abs_pic16f688_12	udata_ovr	0x0012
_SPBRGH
	res	1
UD_abs_pic16f688_13	udata_ovr	0x0013
_SPBRG
	res	1
UD_abs_pic16f688_14	udata_ovr	0x0014
_RCREG
	res	1
UD_abs_pic16f688_15	udata_ovr	0x0015
_TXREG
	res	1
UD_abs_pic16f688_16	udata_ovr	0x0016
_TXSTA_bits
_TXSTA
	res	1
UD_abs_pic16f688_17	udata_ovr	0x0017
_RCSTA_bits
_RCSTA
	res	1
UD_abs_pic16f688_18	udata_ovr	0x0018
_WDTCON
	res	1
UD_abs_pic16f688_19	udata_ovr	0x0019
_CMCON0_bits
_CMCON0
	res	1
UD_abs_pic16f688_1a	udata_ovr	0x001a
_CMCON1_bits
_CMCON1
	res	1
UD_abs_pic16f688_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic16f688_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16f688_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16f688_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16f688_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16f688_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16f688_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16f688_8f	udata_ovr	0x008f
_OSCCON_bits
_OSCCON
	res	1
UD_abs_pic16f688_90	udata_ovr	0x0090
_OSCTUNE_bits
_OSCTUNE
	res	1
UD_abs_pic16f688_91	udata_ovr	0x0091
_ANSEL_bits
_ANSEL
	res	1
UD_abs_pic16f688_95	udata_ovr	0x0095
_WPU
_WPUA
	res	1
UD_abs_pic16f688_96	udata_ovr	0x0096
_IOC_bits
_IOCA_bits
_IOC
_IOCA
	res	1
UD_abs_pic16f688_97	udata_ovr	0x0097
_EEDATH
	res	1
UD_abs_pic16f688_98	udata_ovr	0x0098
_EEADRH
	res	1
UD_abs_pic16f688_99	udata_ovr	0x0099
_VRCON_bits
_VRCON
	res	1
UD_abs_pic16f688_9a	udata_ovr	0x009a
_EEDAT
_EEDATA
	res	1
UD_abs_pic16f688_9b	udata_ovr	0x009b
_EEADR
	res	1
UD_abs_pic16f688_9c	udata_ovr	0x009c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic16f688_9d	udata_ovr	0x009d
_EECON2
	res	1
UD_abs_pic16f688_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic16f688_9f	udata_ovr	0x009f
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
code_pic16f688	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
