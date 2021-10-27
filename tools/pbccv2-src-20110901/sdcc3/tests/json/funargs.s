;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6064 (Nov 27 2010) (CYGWIN)
; This file was generated Sun Nov 28 10:56:27 2010
;--------------------------------------------------------
	.module funargs
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _f
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
	;	funargs.c 1
	;	funargs.c 3
	add	4, 5
	L00001:
	;	funargs.c 1
	;	funargs.c 3
	add	4, 5
	L00001:
	;	funargs.c 7
	;	funargs.c 9
	load	s0, 00
	L00008:
	L00001:
	;	funargs.c 10
	;	funargs.c 12
	add	4, 5
	;	funargs.c 13
	;	funargs.c 10
	add	4, 5
	L00005:
	.area CSEG
	.area CONST   (CODE)
	.area CABS    (ABS,CODE)
