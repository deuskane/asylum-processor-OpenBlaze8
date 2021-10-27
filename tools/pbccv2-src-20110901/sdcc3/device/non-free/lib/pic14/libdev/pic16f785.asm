;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:12 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16f785.c"
	list	p=16f785
	radix dec
	include "p16f785.inc"
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
	global	_ANSEL1_bits
	global	_CCP1CON_bits
	global	_CM1CON0_bits
	global	_CM2CON0_bits
	global	_CM2CON1_bits
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
	global	_PORTB_bits
	global	_PORTC_bits
	global	_PWMCLK_bits
	global	_PWMCON0_bits
	global	_PWMCON1_bits
	global	_REFCON_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TRISC_bits
	global	_VRCON_bits
	global	_WDTCON_bits
	global	_WPUA_bits
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
	global	_CCPR1L
	global	_CCPR1H
	global	_CCP1CON
	global	_WDTCON
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_TRISC
	global	_PIE1
	global	_PCON
	global	_OSCCON
	global	_OSCTUNE
	global	_ANSEL
	global	_ANSEL0
	global	_PR2
	global	_ANSEL1
	global	_WPU
	global	_WPUA
	global	_IOC
	global	_IOCA
	global	_REFCON
	global	_VRCON
	global	_EEDAT
	global	_EEDATA
	global	_EEADR
	global	_EECON1
	global	_EECON2
	global	_ADRESL
	global	_ADCON1
	global	_PWMCON1
	global	_PWMCON0
	global	_PWMCLK
	global	_PWMPH1
	global	_PWMPH2
	global	_CM1CON0
	global	_CM2CON0
	global	_CM2CON1
	global	_OPA1CON
	global	_OPA2CON

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16f785_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16f785_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16f785_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16f785_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16f785_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16f785_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16f785_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16f785_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16f785_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16f785_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16f785_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16f785_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16f785_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16f785_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16f785_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16f785_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16f785_13	udata_ovr	0x0013
_CCPR1L
	res	1
UD_abs_pic16f785_14	udata_ovr	0x0014
_CCPR1H
	res	1
UD_abs_pic16f785_15	udata_ovr	0x0015
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16f785_18	udata_ovr	0x0018
_WDTCON_bits
_WDTCON
	res	1
UD_abs_pic16f785_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic16f785_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16f785_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16f785_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16f785_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16f785_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16f785_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16f785_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16f785_8f	udata_ovr	0x008f
_OSCCON_bits
_OSCCON
	res	1
UD_abs_pic16f785_90	udata_ovr	0x0090
_OSCTUNE_bits
_OSCTUNE
	res	1
UD_abs_pic16f785_91	udata_ovr	0x0091
_ANSEL
_ANSEL0
	res	1
UD_abs_pic16f785_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16f785_93	udata_ovr	0x0093
_ANSEL1_bits
_ANSEL1
	res	1
UD_abs_pic16f785_95	udata_ovr	0x0095
_WPUA_bits
_WPU
_WPUA
	res	1
UD_abs_pic16f785_96	udata_ovr	0x0096
_IOC_bits
_IOCA_bits
_IOC
_IOCA
	res	1
UD_abs_pic16f785_98	udata_ovr	0x0098
_REFCON_bits
_REFCON
	res	1
UD_abs_pic16f785_99	udata_ovr	0x0099
_VRCON_bits
_VRCON
	res	1
UD_abs_pic16f785_9a	udata_ovr	0x009a
_EEDAT
_EEDATA
	res	1
UD_abs_pic16f785_9b	udata_ovr	0x009b
_EEADR
	res	1
UD_abs_pic16f785_9c	udata_ovr	0x009c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic16f785_9d	udata_ovr	0x009d
_EECON2
	res	1
UD_abs_pic16f785_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic16f785_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16f785_110	udata_ovr	0x0110
_PWMCON1_bits
_PWMCON1
	res	1
UD_abs_pic16f785_111	udata_ovr	0x0111
_PWMCON0_bits
_PWMCON0
	res	1
UD_abs_pic16f785_112	udata_ovr	0x0112
_PWMCLK_bits
_PWMCLK
	res	1
UD_abs_pic16f785_113	udata_ovr	0x0113
_PWMPH1
	res	1
UD_abs_pic16f785_114	udata_ovr	0x0114
_PWMPH2
	res	1
UD_abs_pic16f785_119	udata_ovr	0x0119
_CM1CON0_bits
_CM1CON0
	res	1
UD_abs_pic16f785_11a	udata_ovr	0x011a
_CM2CON0_bits
_CM2CON0
	res	1
UD_abs_pic16f785_11b	udata_ovr	0x011b
_CM2CON1_bits
_CM2CON1
	res	1
UD_abs_pic16f785_11c	udata_ovr	0x011c
_OPA1CON
	res	1
UD_abs_pic16f785_11d	udata_ovr	0x011d
_OPA2CON
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
code_pic16f785	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
