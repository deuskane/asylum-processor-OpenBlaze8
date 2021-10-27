;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 21 2010) (Linux)
; This file was generated Sun Nov 21 16:03:13 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"pic16f914.c"
	list	p=16f914
	radix dec
	include "p16f914.inc"
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
	global	_CCP1CON_bits
	global	_CCP2CON_bits
	global	_CMCON0_bits
	global	_CMCON1_bits
	global	_EEADRH_bits
	global	_EEADRL_bits
	global	_EECON1_bits
	global	_INTCON_bits
	global	_IOC_bits
	global	_IOCB_bits
	global	_LCDCON_bits
	global	_LCDDATA0_bits
	global	_LCDDATA1_bits
	global	_LCDDATA10_bits
	global	_LCDDATA11_bits
	global	_LCDDATA2_bits
	global	_LCDDATA3_bits
	global	_LCDDATA4_bits
	global	_LCDDATA5_bits
	global	_LCDDATA6_bits
	global	_LCDDATA7_bits
	global	_LCDDATA8_bits
	global	_LCDDATA9_bits
	global	_LCDPS_bits
	global	_LCDSE0_bits
	global	_LCDSE1_bits
	global	_LCDSE2_bits
	global	_LVDCON_bits
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
	global	_PORTD_bits
	global	_PORTE_bits
	global	_RCSTA_bits
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
	global	_TXSTA_bits
	global	_VRCON_bits
	global	_WDTCON_bits
	global	_WPU_bits
	global	_WPUB_bits
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
	global	_SSPBUF
	global	_SSPCON
	global	_CCPR1L
	global	_CCPR1H
	global	_CCP1CON
	global	_RCSTA
	global	_TXREG
	global	_RCREG
	global	_CCPR2L
	global	_CCPR2H
	global	_CCP2CON
	global	_ADRESH
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
	global	_OSCCON
	global	_OSCTUNE
	global	_ANSEL
	global	_PR2
	global	_SSPADD
	global	_SSPSTAT
	global	_WPUB
	global	_WPU
	global	_IOCB
	global	_IOC
	global	_CMCON1
	global	_TXSTA
	global	_SPBRG
	global	_CMCON0
	global	_VRCON
	global	_ADRESL
	global	_ADCON1
	global	_WDTCON
	global	_LCDCON
	global	_LCDPS
	global	_LVDCON
	global	_EEDATL
	global	_EEADRL
	global	_EEDATH
	global	_EEADRH
	global	_LCDDATA0
	global	_LCDDATA1
	global	_LCDDATA2
	global	_LCDDATA3
	global	_LCDDATA4
	global	_LCDDATA5
	global	_LCDDATA6
	global	_LCDDATA7
	global	_LCDDATA8
	global	_LCDDATA9
	global	_LCDDATA10
	global	_LCDDATA11
	global	_LCDSE0
	global	_LCDSE1
	global	_LCDSE2
	global	_EECON1
	global	_EECON2

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
UD_abs_pic16f914_0	udata_ovr	0x0000
_INDF
	res	1
UD_abs_pic16f914_1	udata_ovr	0x0001
_TMR0
	res	1
UD_abs_pic16f914_2	udata_ovr	0x0002
_PCL
	res	1
UD_abs_pic16f914_3	udata_ovr	0x0003
_STATUS_bits
_STATUS
	res	1
UD_abs_pic16f914_4	udata_ovr	0x0004
_FSR
	res	1
UD_abs_pic16f914_5	udata_ovr	0x0005
_PORTA_bits
_PORTA
	res	1
UD_abs_pic16f914_6	udata_ovr	0x0006
_PORTB_bits
_PORTB
	res	1
UD_abs_pic16f914_7	udata_ovr	0x0007
_PORTC_bits
_PORTC
	res	1
UD_abs_pic16f914_8	udata_ovr	0x0008
_PORTD_bits
_PORTD
	res	1
UD_abs_pic16f914_9	udata_ovr	0x0009
_PORTE_bits
_PORTE
	res	1
UD_abs_pic16f914_a	udata_ovr	0x000a
_PCLATH
	res	1
UD_abs_pic16f914_b	udata_ovr	0x000b
_INTCON_bits
_INTCON
	res	1
UD_abs_pic16f914_c	udata_ovr	0x000c
_PIR1_bits
_PIR1
	res	1
UD_abs_pic16f914_d	udata_ovr	0x000d
_PIR2_bits
_PIR2
	res	1
UD_abs_pic16f914_e	udata_ovr	0x000e
_TMR1L
	res	1
UD_abs_pic16f914_f	udata_ovr	0x000f
_TMR1H
	res	1
UD_abs_pic16f914_10	udata_ovr	0x0010
_T1CON_bits
_T1CON
	res	1
UD_abs_pic16f914_11	udata_ovr	0x0011
_TMR2
	res	1
UD_abs_pic16f914_12	udata_ovr	0x0012
_T2CON_bits
_T2CON
	res	1
UD_abs_pic16f914_13	udata_ovr	0x0013
_SSPBUF
	res	1
UD_abs_pic16f914_14	udata_ovr	0x0014
_SSPCON_bits
_SSPCON
	res	1
UD_abs_pic16f914_15	udata_ovr	0x0015
_CCPR1L
	res	1
UD_abs_pic16f914_16	udata_ovr	0x0016
_CCPR1H
	res	1
UD_abs_pic16f914_17	udata_ovr	0x0017
_CCP1CON_bits
_CCP1CON
	res	1
UD_abs_pic16f914_18	udata_ovr	0x0018
_RCSTA_bits
_RCSTA
	res	1
UD_abs_pic16f914_19	udata_ovr	0x0019
_TXREG
	res	1
UD_abs_pic16f914_1a	udata_ovr	0x001a
_RCREG
	res	1
UD_abs_pic16f914_1b	udata_ovr	0x001b
_CCPR2L
	res	1
UD_abs_pic16f914_1c	udata_ovr	0x001c
_CCPR2H
	res	1
UD_abs_pic16f914_1d	udata_ovr	0x001d
_CCP2CON_bits
_CCP2CON
	res	1
UD_abs_pic16f914_1e	udata_ovr	0x001e
_ADRESH
	res	1
UD_abs_pic16f914_1f	udata_ovr	0x001f
_ADCON0_bits
_ADCON0
	res	1
UD_abs_pic16f914_81	udata_ovr	0x0081
_OPTION_REG_bits
_OPTION_REG
	res	1
UD_abs_pic16f914_85	udata_ovr	0x0085
_TRISA_bits
_TRISA
	res	1
UD_abs_pic16f914_86	udata_ovr	0x0086
_TRISB_bits
_TRISB
	res	1
UD_abs_pic16f914_87	udata_ovr	0x0087
_TRISC_bits
_TRISC
	res	1
UD_abs_pic16f914_88	udata_ovr	0x0088
_TRISD_bits
_TRISD
	res	1
UD_abs_pic16f914_89	udata_ovr	0x0089
_TRISE_bits
_TRISE
	res	1
UD_abs_pic16f914_8c	udata_ovr	0x008c
_PIE1_bits
_PIE1
	res	1
UD_abs_pic16f914_8d	udata_ovr	0x008d
_PIE2_bits
_PIE2
	res	1
UD_abs_pic16f914_8e	udata_ovr	0x008e
_PCON_bits
_PCON
	res	1
UD_abs_pic16f914_8f	udata_ovr	0x008f
_OSCCON_bits
_OSCCON
	res	1
UD_abs_pic16f914_90	udata_ovr	0x0090
_OSCTUNE_bits
_OSCTUNE
	res	1
UD_abs_pic16f914_91	udata_ovr	0x0091
_ANSEL_bits
_ANSEL
	res	1
UD_abs_pic16f914_92	udata_ovr	0x0092
_PR2
	res	1
UD_abs_pic16f914_93	udata_ovr	0x0093
_SSPADD
	res	1
UD_abs_pic16f914_94	udata_ovr	0x0094
_SSPSTAT_bits
_SSPSTAT
	res	1
UD_abs_pic16f914_95	udata_ovr	0x0095
_WPU_bits
_WPUB_bits
_WPUB
_WPU
	res	1
UD_abs_pic16f914_96	udata_ovr	0x0096
_IOC_bits
_IOCB_bits
_IOCB
_IOC
	res	1
UD_abs_pic16f914_97	udata_ovr	0x0097
_CMCON1_bits
_CMCON1
	res	1
UD_abs_pic16f914_98	udata_ovr	0x0098
_TXSTA_bits
_TXSTA
	res	1
UD_abs_pic16f914_99	udata_ovr	0x0099
_SPBRG
	res	1
UD_abs_pic16f914_9c	udata_ovr	0x009c
_CMCON0_bits
_CMCON0
	res	1
UD_abs_pic16f914_9d	udata_ovr	0x009d
_VRCON_bits
_VRCON
	res	1
UD_abs_pic16f914_9e	udata_ovr	0x009e
_ADRESL
	res	1
UD_abs_pic16f914_9f	udata_ovr	0x009f
_ADCON1_bits
_ADCON1
	res	1
UD_abs_pic16f914_105	udata_ovr	0x0105
_WDTCON_bits
_WDTCON
	res	1
UD_abs_pic16f914_107	udata_ovr	0x0107
_LCDCON_bits
_LCDCON
	res	1
UD_abs_pic16f914_108	udata_ovr	0x0108
_LCDPS_bits
_LCDPS
	res	1
UD_abs_pic16f914_109	udata_ovr	0x0109
_LVDCON_bits
_LVDCON
	res	1
UD_abs_pic16f914_10c	udata_ovr	0x010c
_EEDATL
	res	1
UD_abs_pic16f914_10d	udata_ovr	0x010d
_EEADRL_bits
_EEADRL
	res	1
UD_abs_pic16f914_10e	udata_ovr	0x010e
_EEDATH
	res	1
UD_abs_pic16f914_10f	udata_ovr	0x010f
_EEADRH_bits
_EEADRH
	res	1
UD_abs_pic16f914_110	udata_ovr	0x0110
_LCDDATA0_bits
_LCDDATA0
	res	1
UD_abs_pic16f914_111	udata_ovr	0x0111
_LCDDATA1_bits
_LCDDATA1
	res	1
UD_abs_pic16f914_112	udata_ovr	0x0112
_LCDDATA2_bits
_LCDDATA2
	res	1
UD_abs_pic16f914_113	udata_ovr	0x0113
_LCDDATA3_bits
_LCDDATA3
	res	1
UD_abs_pic16f914_114	udata_ovr	0x0114
_LCDDATA4_bits
_LCDDATA4
	res	1
UD_abs_pic16f914_115	udata_ovr	0x0115
_LCDDATA5_bits
_LCDDATA5
	res	1
UD_abs_pic16f914_116	udata_ovr	0x0116
_LCDDATA6_bits
_LCDDATA6
	res	1
UD_abs_pic16f914_117	udata_ovr	0x0117
_LCDDATA7_bits
_LCDDATA7
	res	1
UD_abs_pic16f914_118	udata_ovr	0x0118
_LCDDATA8_bits
_LCDDATA8
	res	1
UD_abs_pic16f914_119	udata_ovr	0x0119
_LCDDATA9_bits
_LCDDATA9
	res	1
UD_abs_pic16f914_11a	udata_ovr	0x011a
_LCDDATA10_bits
_LCDDATA10
	res	1
UD_abs_pic16f914_11b	udata_ovr	0x011b
_LCDDATA11_bits
_LCDDATA11
	res	1
UD_abs_pic16f914_11c	udata_ovr	0x011c
_LCDSE0_bits
_LCDSE0
	res	1
UD_abs_pic16f914_11d	udata_ovr	0x011d
_LCDSE1_bits
_LCDSE1
	res	1
UD_abs_pic16f914_11e	udata_ovr	0x011e
_LCDSE2_bits
_LCDSE2
	res	1
UD_abs_pic16f914_18c	udata_ovr	0x018c
_EECON1_bits
_EECON1
	res	1
UD_abs_pic16f914_18d	udata_ovr	0x018d
_EECON2
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
code_pic16f914	code

;	code size estimation:
;	    0+    0 =     0 instructions (    0 byte)

	end
