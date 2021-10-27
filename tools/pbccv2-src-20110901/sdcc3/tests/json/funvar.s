;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 27 2010) (CYGWIN)
; This file was generated Sun Nov 28 11:03:48 2010
;--------------------------------------------------------
	.module funvar
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _test
	.globl _globvar
;--------------------------------------------------------
;  ram data
;--------------------------------------------------------
	.area DSEG
;--------------------------------------------------------
; overlayable items in  ram 
;--------------------------------------------------------
	.area OSEG
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG	(DATA)
__start__stack:
	.ds	1

;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
	;	funvar.c 3
	;	funvar.c 5
	L00001:
	;	funvar.c 8
	;	funvar.c 10
	L00001:
	;	funvar.c 1
	load	s0, 0d
	.area GSFINAL
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	lcall	_main
;	return from main will lock up
	sjmp .
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG
	;	funvar.c 3
	;	funvar.c 5
	L00001:
	;	funvar.c 3
	;	funvar.c 5
	L00001:
	;	funvar.c 8
	;	funvar.c 10
	L00001:
	.area CSEG
	.area CONST   (CODE)
	.area CABS    (ABS,CODE)
