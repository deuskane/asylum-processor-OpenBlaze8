;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16c781.c"
	list	p=16c781
	radix dec
	include "p16c781.inc"
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
	global	_CALCON_bits
	global	_CM1CON0_bits
	global	_CM2CON0_bits
	global	_CM2CON1_bits
	global	_DACON0_bits
	global	_INTCON_bits
	global	_LVDCON_bits
	global	_OPACON_bits
	global	_OPTION_REG_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIR1_bits
	global	_PMCON1_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_PSMCCON0_bits
	global	_PSMCCON1_bits
	global	_REFCON_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
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
	global	_ADRES
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_PIE1
	global	_PCON
	global	_WPUB
	global	_IOCB
	global	_REFCON
	global	_LVDCON
	global	_ANSEL
	global	_ADCON1
	global	_PMDATL
	global	_PMADRL
	global	_PMDATH
	global	_PMADRH
	global	_CALCON
	global	_PSMCCON0
	global	_PSMCCON1
	global	_CM1CON0
	global	_CM2CON0
	global	_CM2CON1
	global	_OPACON
	global	_DAC
	global	_DACON0
	global	_PMCON1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16c781_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16c781_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16c781_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16c781_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16c781_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16c781_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16c781_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16c781_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16c781_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16c781_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16c781_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16c781_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16c781_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16c781_1e	udata_ovr	0x001e
_ADRES
	res	1
UD_abs_pic16c781_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16c781_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16c781_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16c781_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16c781_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16c781_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16c781_95	udata_ovr	0x0095
_WPUB
	res	1
UD_abs_pic16c781_96	udata_ovr	0x0096
_IOCB
	res	1
UD_abs_pic16c781_9b	udata_ovr	0x009b
_REFCON_bits
_REFCON
	res	1
UD_abs_pic16c781_9c	udata_ovr	0x009c
_LVDCON_bits
_LVDCON
	res	1
UD_abs_pic16c781_9d	udata_ovr	0x009d
_ANSEL
	res	1
UD_abs_pic16c781_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16c781_10c	udata_ovr	0x010c
_PMDATL
	res	1
UD_abs_pic16c781_10d	udata_ovr	0x010d
_PMADRL
	res	1
UD_abs_pic16c781_10e	udata_ovr	0x010e
_PMDATH
	res	1
UD_abs_pic16c781_10f	udata_ovr	0x010f
_PMADRH
	res	1
UD_abs_pic16c781_110	udata_ovr	0x0110
_CALCON_bits
_CALCON
	res	1
UD_abs_pic16c781_111	udata_ovr	0x0111
_PSMCCON0_bits
_PSMCCON0
	res	1
UD_abs_pic16c781_112	udata_ovr	0x0112
_PSMCCON1_bits
_PSMCCON1
	res	1
UD_abs_pic16c781_119	udata_ovr	0x0119
_CM1CON0_bits
_CM1CON0
	res	1
UD_abs_pic16c781_11a	udata_ovr	0x011a
_CM2CON0_bits
_CM2CON0
	res	1
UD_abs_pic16c781_11b	udata_ovr	0x011b
_CM2CON1_bits
_CM2CON1
	res	1
UD_abs_pic16c781_11c	udata_ovr	0x011c
_OPACON_bits
_OPACON
	res	1
UD_abs_pic16c781_11e	udata_ovr	0x011e
_DAC
	res	1
UD_abs_pic16c781_11f	udata_ovr	0x011f
_DACON0_bits
_DACON0
	res	1
UD_abs_pic16c781_18c	udata_ovr	0x018c
_PMCON1_bits
_PMCON1
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
code_pic16c781	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
