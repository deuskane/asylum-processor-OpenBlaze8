#ifndef __PORT_H__
#define __PORT_H__

#define MIN_PAUSE 10

#include "delay.h"
/*
 * port.h - port communication functions header file
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
*/
void __port_write(unsigned char, unsigned char);
unsigned char __port_read(volatile unsigned char);

void __port_write(unsigned char port, unsigned char arg) 
{ 
	unsigned volatile char p;
	unsigned volatile char a;
	p = port;
	a = arg;
  __asm 
     OUTPUT _a, _p
  __endasm;
  delay(MIN_PAUSE);
}

unsigned char __port_read(volatile unsigned char port) 
{ 
  volatile unsigned char d = 0;
  volatile unsigned char p = port;
  __asm 
     INPUT _d, _p
  __endasm;
  delay(MIN_PAUSE);
  return d;
}

#endif