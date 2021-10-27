;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:11 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16f687.c"
	list	p=16f687
	radix dec
	include "p16f687.inc"
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
	global	_ANSELH_bits
	global	_BAUDCTL_bits
	global	_CM1CON0_bits
	global	_CM2CON0_bits
	global	_CM2CON1_bits
	global	_EECON1_bits
	global	_INTCON_bits
	global	_IOC_bits
	global	_IOCA_bits
	global	_IOCB_bits
	global	_OPTION_REG_bits
	global	_OSCCON_bits
	global	_OSCTUNE_bits
	global	_PCON_bits
	global	_PIE1_bits
	global	_PIE2_bits
	global	_PIR1_bits
	global	_PIR2_bits
	global	_PORTA_bits
	global	_PORTB_bits
	global	_PORTC_bits
	global	_RCSTA_bits
	global	_SPBRG_bits
	global	_SPBRGH_bits
	global	_SRCON_bits
	global	_SSPCON_bits
	global	_SSPSTAT_bits
	global	_STATUS_bits
	global	_T1CON_bits
	global	_TRISA_bits
	global	_TRISB_bits
	global	_TRISC_bits
	global	_TXSTA_bits
	global	_VRCON_bits
	global	_WDTCON_bits
	global	_WPUA_bits
	global	_WPUB_bits
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
	global	_PIR2
	global	_TMR1L
	global	_TMR1H
	global	_T1CON
	global	_SSPBUF
	global	_SSPCON
	global	_RCSTA
	global	_TXREG
	global	_RCREG
	global	_ADRESH
	global	_ADCON0
	global	_OPTION_REG
	global	_TRISA
	global	_TRISB
	global	_TRISC
	global	_PIE1
	global	_PIE2
	global	_PCON
	global	_OSCCON
	global	_OSCTUNE
	global	_SSPADD
	global	_MSK
	global	_SSPMSK
	global	_SSPSTAT
	global	_WPU
	global	_WPUA
	global	_IOC
	global	_IOCA
	global	_WDTCON
	global	_TXSTA
	global	_SPBRG
	global	_SPBRGH
	global	_BAUDCTL
	global	_ADRESL
	global	_ADCON1
	global	_EEDAT
	global	_EEDATA
	global	_EEADR
	global	_EEDATH
	global	_EEADRH
	global	_WPUB
	global	_IOCB
	global	_VRCON
	global	_CM1CON0
	global	_CM2CON0
	global	_CM2CON1
	global	_ANSEL
	global	_ANSELH
	global	_EECON1
	global	_EECON2
	global	_SRCON

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16f687_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16f687_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16f687_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16f687_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16f687_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16f687_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16f687_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16f687_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16f687_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16f687_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16f687_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16f687_d	udata_ovr	0x000d
_PIR2_bits
_PIR2
	res	1
UD_abs_pic16f687_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16f687_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16f687_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16f687_13	udata_ovr	0x0013
_SSPBUF
	res	1
UD_abs_pic16f687_14	udata_ovr	0x0014
_SSPCON_bits
_SSPCON
	res	1
UD_abs_pic16f687_18	udata_ovr	0x0018
_RCSTA_bits
_RCSTA
	res	1
UD_abs_pic16f687_19	udata_ovr	0x0019
_TXREG
	res	1
UD_abs_pic16f687_1a	udata_ovr	0x001a
_RCREG
	res	1
UD_abs_pic16f687_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic16f687_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16f687_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16f687_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16f687_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16f687_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16f687_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16f687_8d	udata_ovr	0x008d
_PIE2_bits
_PIE2
	res	1
UD_abs_pic16f687_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16f687_8f	udata_ovr	0x008f
_OSCCON_bits
_OSCCON
	res	1
UD_abs_pic16f687_90	udata_ovr	0x0090
_OSCTUNE_bits
_OSCTUNE
	res	1
UD_abs_pic16f687_93	udata_ovr	0x0093
_SSPADD
_MSK
_SSPMSK
	res	1
UD_abs_pic16f687_94	udata_ovr	0x0094
_SSPSTAT_bits
_SSPSTAT
	res	1
UD_abs_pic16f687_95	udata_ovr	0x0095
_WPUA_bits
_WPU
_WPUA
	res	1
UD_abs_pic16f687_96	udata_ovr	0x0096
_IOC_bits
_IOCA_bits
_IOC
_IOCA
	res	1
UD_abs_pic16f687_97	udata_ovr	0x0097
_WDTCON_bits
_WDTCON
	res	1
UD_abs_pic16f687_98	udata_ovr	0x0098
_TXSTA_bits
_TXSTA
	res	1
UD_abs_pic16f687_99	udata_ovr	0x0099
_SPBRG_bits
_SPBRG
	res	1
UD_abs_pic16f687_9a	udata_ovr	0x009a
_SPBRGH_bits
_SPBRGH
	res	1
UD_abs_pic16f687_9b	udata_ovr	0x009b
_BAUDCTL_bits
_BAUDCTL
	res	1
UD_abs_pic16f687_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic16f687_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16f687_10c	udata_ovr	0x010c
_EEDAT
_EEDATA
	res	1
UD_abs_pic16f687_10d	udata_ovr	0x010d
_EEADR
	res	1
UD_abs_pic16f687_10e	udata_ovr	0x010e
_EEDATH
	res	1
UD_abs_pic16f687_10f	udata_ovr	0x010f
_EEADRH
	res	1
UD_abs_pic16f687_115	udata_ovr	0x0115
_WPUB_bits
_WPUB
	res	1
UD_abs_pic16f687_116	udata_ovr	0x0116
_IOCB_bits
_IOCB
	res	1
UD_abs_pic16f687_118	udata_ovr	0x0118
_VRCON_bits
_VRCON
	res	1
UD_abs_pic16f687_119	udata_ovr	0x0119
_CM1CON0_bits
_CM1CON0
	res	1
UD_abs_pic16f687_11a	udata_ovr	0x011a
_CM2CON0_bits
_CM2CON0
	res	1
UD_abs_pic16f687_11b	udata_ovr	0x011b
_CM2CON1_bits
_CM2CON1
	res	1
UD_abs_pic16f687_11e	udata_ovr	0x011e
_ANSEL_bits
_ANSEL
	res	1
UD_abs_pic16f687_11f	udata_ovr	0x011f
_ANSELH_bits
_ANSELH
	res	1
UD_abs_pic16f687_18c	udata_ovr	0x018c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic16f687_18d	udata_ovr	0x018d
_EECON2
	res	1
UD_abs_pic16f687_19e	udata_ovr	0x019e
_SRCON_bits
_SRCON
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
code_pic16f687	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
