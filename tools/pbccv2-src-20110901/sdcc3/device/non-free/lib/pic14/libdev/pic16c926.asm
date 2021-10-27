;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c926.c"
	list	p=16c926
	radix dec
	include "p16c926.inc"
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
	global	_CCP1CON_bits
	global	_INTCON_bits
	global	_LCDCON_bits
	global	_LCDPS_bits
	global	_LCDSE_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PMCON1_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_PORTC_bits
	global	_PORTD_bits
	global	_PORTE_bits
	global	_SSPCON_bits
	global	_SSPSTAT_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TRISC_bits
	global	_TRISD_bits
	global	_TRISE_bits
	global	_INDF
	global	_TMR0
	global	_PCL
	global	_STATUS
	global	_FSR
	global	_PORTA
	global	_PORTB
	global	_PORTC
	global	_PORTD
	global	_PORTE
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
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_TRISC
	global	_TRISD
	global	_TRISE
	global	_PIE1
	global	_PCON
	global	_PR2
	global	_SSPADD
	global	_SSPSTAT
	global	_ADRESL
	global	_ADCON1
	global	_PORTF
	global	_PORTG
	global	_PMCON1
	global	_LCDSE
	global	_LCDPS
	global	_LCDCON
	global	_LCDD00
	global	_LCDD01
	global	_LCDD02
	global	_LCDD03
	global	_LCDD04
	global	_LCDD05
	global	_LCDD06
	global	_LCDD07
	global	_LCDD08
	global	_LCDD09
	global	_LCDD10
	global	_LCDD11
	global	_LCDD12
	global	_LCDD13
	global	_LCDD14
	global	_LCDD15
	global	_TRISF
	global	_TRISG
	global	_PMDATA
	global	_PMDATH
	global	_PMADR
	global	_PMADRH

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c926_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c926_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c926_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c926_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c926_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c926_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c926_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c926_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16c926_8	udata_ovr	0x0008
_PORTD_bits
_PORTD
	res	1
UD_abs_pic16c926_9	udata_ovr	0x0009
_PORTE_bits
_PORTE
	res	1
UD_abs_pic16c926_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c926_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c926_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c926_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16c926_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16c926_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16c926_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16c926_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16c926_13	udata_ovr	0x0013
_SSPBUF
	res	1
UD_abs_pic16c926_14	udata_ovr	0x0014
_SSPCON_bits
_SSPCON
	res	1
UD_abs_pic16c926_15	udata_ovr	0x0015
_CCPR1L
	res	1
UD_abs_pic16c926_16	udata_ovr	0x0016
_CCPR1H
	res	1
UD_abs_pic16c926_17	udata_ovr	0x0017
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16c926_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic16c926_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16c926_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c926_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16c926_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c926_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16c926_88	udata_ovr	0x0088
_TRISD_bits
_TRISD
	res	1
UD_abs_pic16c926_89	udata_ovr	0x0089
_TRISE_bits
_TRISE
	res	1
UD_abs_pic16c926_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c926_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c926_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16c926_93	udata_ovr	0x0093
_SSPADD
	res	1
UD_abs_pic16c926_94	udata_ovr	0x0094
_SSPSTAT_bits
_SSPSTAT
	res	1
UD_abs_pic16c926_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic16c926_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16c926_107	udata_ovr	0x0107
_PORTF
	res	1
UD_abs_pic16c926_108	udata_ovr	0x0108
_PORTG
	res	1
UD_abs_pic16c926_10c	udata_ovr	0x010c
_PMCON1_bits
_PMCON1
	res	1
UD_abs_pic16c926_10d	udata_ovr	0x010d
_LCDSE_bits
_LCDSE
	res	1
UD_abs_pic16c926_10e	udata_ovr	0x010e
_LCDPS_bits
_LCDPS
	res	1
UD_abs_pic16c926_10f	udata_ovr	0x010f
_LCDCON_bits
_LCDCON
	res	1
UD_abs_pic16c926_110	udata_ovr	0x0110
_LCDD00
	res	1
UD_abs_pic16c926_111	udata_ovr	0x0111
_LCDD01
	res	1
UD_abs_pic16c926_112	udata_ovr	0x0112
_LCDD02
	res	1
UD_abs_pic16c926_113	udata_ovr	0x0113
_LCDD03
	res	1
UD_abs_pic16c926_114	udata_ovr	0x0114
_LCDD04
	res	1
UD_abs_pic16c926_115	udata_ovr	0x0115
_LCDD05
	res	1
UD_abs_pic16c926_116	udata_ovr	0x0116
_LCDD06
	res	1
UD_abs_pic16c926_117	udata_ovr	0x0117
_LCDD07
	res	1
UD_abs_pic16c926_118	udata_ovr	0x0118
_LCDD08
	res	1
UD_abs_pic16c926_119	udata_ovr	0x0119
_LCDD09
	res	1
UD_abs_pic16c926_11a	udata_ovr	0x011a
_LCDD10
	res	1
UD_abs_pic16c926_11b	udata_ovr	0x011b
_LCDD11
	res	1
UD_abs_pic16c926_11c	udata_ovr	0x011c
_LCDD12
	res	1
UD_abs_pic16c926_11d	udata_ovr	0x011d
_LCDD13
	res	1
UD_abs_pic16c926_11e	udata_ovr	0x011e
_LCDD14
	res	1
UD_abs_pic16c926_11f	udata_ovr	0x011f
_LCDD15
	res	1
UD_abs_pic16c926_187	udata_ovr	0x0187
_TRISF
	res	1
UD_abs_pic16c926_188	udata_ovr	0x0188
_TRISG
	res	1
UD_abs_pic16c926_18c	udata_ovr	0x018c
_PMDATA
	res	1
UD_abs_pic16c926_18d	udata_ovr	0x018d
_PMDATH
	res	1
UD_abs_pic16c926_18e	udata_ovr	0x018e
_PMADR
	res	1
UD_abs_pic16c926_18f	udata_ovr	0x018f
_PMADRH
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
code_pic16c926	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
