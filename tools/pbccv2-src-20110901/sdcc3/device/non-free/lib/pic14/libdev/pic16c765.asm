;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c765.c"
	list	p=16c765
	radix dec
	include "p16c765.inc"
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
	global	_CCP2CON_bits
	global	_INTCON_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIE2_bits
	global	_PIR1_bits
	global	_PIR2_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_PORTC_bits
	global	_PORTD_bits
	global	_PORTE_bits
	global	_RCSTA_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_T2CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TRISC_bits
	global	_TRISD_bits
	global	_TRISE_bits
	global	_TXSTA_bits
	global	_UCTRL_bits
	global	_UEIE_bits
	global	_UEP0_bits
	global	_UIE_bits
	global	_USTAT_bits
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
	global	_PIR2
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
	global	_CCPR2L
	global	_CCPR2H
	global	_CCP2CON
	global	_ADRES
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_TRISC
	global	_TRISD
	global	_TRISE
	global	_PIE1
	global	_PIE2
	global	_PCON
	global	_PR2
	global	_TXSTA
	global	_SPBRG
	global	_ADCON1
	global	_UIR
	global	_UIE
	global	_UEIR
	global	_UEIE
	global	_USTAT
	global	_UCTRL
	global	_UADDR
	global	_USWSTAT
	global	_UEP0
	global	_UEP1
	global	_UEP2
	global	_BD0OST
	global	_BD0OBC
	global	_BD0OAL
	global	_BD0IST
	global	_BD0IBC
	global	_BD0IAL
	global	_BD1OST
	global	_BD1OBC
	global	_BD1OAL
	global	_BD1IST
	global	_BD1IBC
	global	_BD1IAL
	global	_BD2OST
	global	_BD2OBC
	global	_BD2OAL
	global	_BD2IST
	global	_BD2IBC
	global	_BD2IAL

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c765_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c765_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c765_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c765_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c765_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c765_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c765_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c765_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16c765_8	udata_ovr	0x0008
_PORTD_bits
_PORTD
	res	1
UD_abs_pic16c765_9	udata_ovr	0x0009
_PORTE_bits
_PORTE
	res	1
UD_abs_pic16c765_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c765_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c765_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c765_d	udata_ovr	0x000d
_PIR2_bits
_PIR2
	res	1
UD_abs_pic16c765_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16c765_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16c765_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16c765_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16c765_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16c765_15	udata_ovr	0x0015
_CCPR1L
	res	1
UD_abs_pic16c765_16	udata_ovr	0x0016
_CCPR1H
	res	1
UD_abs_pic16c765_17	udata_ovr	0x0017
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16c765_18	udata_ovr	0x0018
_RCSTA_bits
_RCSTA
	res	1
UD_abs_pic16c765_19	udata_ovr	0x0019
_TXREG
	res	1
UD_abs_pic16c765_1a	udata_ovr	0x001a
_RCREG
	res	1
UD_abs_pic16c765_1b	udata_ovr	0x001b
_CCPR2L
	res	1
UD_abs_pic16c765_1c	udata_ovr	0x001c
_CCPR2H
	res	1
UD_abs_pic16c765_1d	udata_ovr	0x001d
_CCP2CON_bits
_CCP2CON
	res	1
UD_abs_pic16c765_1e	udata_ovr	0x001e
_ADRES
	res	1
UD_abs_pic16c765_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16c765_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c765_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16c765_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c765_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16c765_88	udata_ovr	0x0088
_TRISD_bits
_TRISD
	res	1
UD_abs_pic16c765_89	udata_ovr	0x0089
_TRISE_bits
_TRISE
	res	1
UD_abs_pic16c765_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c765_8d	udata_ovr	0x008d
_PIE2_bits
_PIE2
	res	1
UD_abs_pic16c765_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c765_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16c765_98	udata_ovr	0x0098
_TXSTA_bits
_TXSTA
	res	1
UD_abs_pic16c765_99	udata_ovr	0x0099
_SPBRG
	res	1
UD_abs_pic16c765_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16c765_190	udata_ovr	0x0190
_UIR
	res	1
UD_abs_pic16c765_191	udata_ovr	0x0191
_UIE_bits
_UIE
	res	1
UD_abs_pic16c765_192	udata_ovr	0x0192
_UEIR
	res	1
UD_abs_pic16c765_193	udata_ovr	0x0193
_UEIE_bits
_UEIE
	res	1
UD_abs_pic16c765_194	udata_ovr	0x0194
_USTAT_bits
_USTAT
	res	1
UD_abs_pic16c765_195	udata_ovr	0x0195
_UCTRL_bits
_UCTRL
	res	1
UD_abs_pic16c765_196	udata_ovr	0x0196
_UADDR
	res	1
UD_abs_pic16c765_197	udata_ovr	0x0197
_USWSTAT
	res	1
UD_abs_pic16c765_198	udata_ovr	0x0198
_UEP0_bits
_UEP0
	res	1
UD_abs_pic16c765_199	udata_ovr	0x0199
_UEP1
	res	1
UD_abs_pic16c765_19a	udata_ovr	0x019a
_UEP2
	res	1
UD_abs_pic16c765_1a0	udata_ovr	0x01a0
_BD0OST
	res	1
UD_abs_pic16c765_1a1	udata_ovr	0x01a1
_BD0OBC
	res	1
UD_abs_pic16c765_1a2	udata_ovr	0x01a2
_BD0OAL
	res	1
UD_abs_pic16c765_1a4	udata_ovr	0x01a4
_BD0IST
	res	1
UD_abs_pic16c765_1a5	udata_ovr	0x01a5
_BD0IBC
	res	1
UD_abs_pic16c765_1a6	udata_ovr	0x01a6
_BD0IAL
	res	1
UD_abs_pic16c765_1a8	udata_ovr	0x01a8
_BD1OST
	res	1
UD_abs_pic16c765_1a9	udata_ovr	0x01a9
_BD1OBC
	res	1
UD_abs_pic16c765_1aa	udata_ovr	0x01aa
_BD1OAL
	res	1
UD_abs_pic16c765_1ac	udata_ovr	0x01ac
_BD1IST
	res	1
UD_abs_pic16c765_1ad	udata_ovr	0x01ad
_BD1IBC
	res	1
UD_abs_pic16c765_1ae	udata_ovr	0x01ae
_BD1IAL
	res	1
UD_abs_pic16c765_1b0	udata_ovr	0x01b0
_BD2OST
	res	1
UD_abs_pic16c765_1b1	udata_ovr	0x01b1
_BD2OBC
	res	1
UD_abs_pic16c765_1b2	udata_ovr	0x01b2
_BD2OAL
	res	1
UD_abs_pic16c765_1b4	udata_ovr	0x01b4
_BD2IST
	res	1
UD_abs_pic16c765_1b5	udata_ovr	0x01b5
_BD2IBC
	res	1
UD_abs_pic16c765_1b6	udata_ovr	0x01b6
_BD2IAL
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
code_pic16c765	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
