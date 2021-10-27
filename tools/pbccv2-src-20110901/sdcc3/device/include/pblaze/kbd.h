/*
 * kbd.h - Keyboarch (16 keys) peripheral functions header file for FITKit
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
*/

#ifndef __KBD_H__
#define __KBD_H__

#include "delay.h"
#include "port.h"

#define port_kb_low  60
#define port_kb_high 61

#define CHAR_SPACE  0x20
#define CHAR_0      0x30
#define CHAR_1      0x31
#define CHAR_2      0x32
#define CHAR_3      0x33
#define CHAR_4      0x34
#define CHAR_5      0x35
#define CHAR_6      0x36
#define CHAR_7      0x37
#define CHAR_8      0x38
#define CHAR_9      0x39
#define CHAR_A      0x41
#define CHAR_B      0x42
#define CHAR_C      0x43
#define CHAR_D      0x44
#define CHAR_STAR   0x2A
#define CHAR_HASH   0x23

#define ASM_CHAR_SPACE  20
#define ASM_CHAR_0      30
#define ASM_CHAR_1      31
#define ASM_CHAR_2      32
#define ASM_CHAR_3      33
#define ASM_CHAR_4      34
#define ASM_CHAR_5      35
#define ASM_CHAR_6      36
#define ASM_CHAR_7      37
#define ASM_CHAR_8      38
#define ASM_CHAR_9      39
#define ASM_CHAR_A      41
#define ASM_CHAR_B      42
#define ASM_CHAR_C      43
#define ASM_CHAR_D      44
#define ASM_CHAR_STAR   2A
#define ASM_CHAR_HASH   23


unsigned char readkey()
{
      volatile unsigned char key = 0;
      __asm
       INPUT _key, port_kb_low
xch1:
       SRA  _key
       JUMP NC, xch4
       LOAD _key, ASM_CHAR_1
       JUMP xchno

xch4:
       SRA  _key
       JUMP NC, xch7
       LOAD _key, ASM_CHAR_4
       JUMP xchno

xch7:
       SRA  _key
       JUMP NC, xchs
       LOAD _key, ASM_CHAR_7
       JUMP xchno

xchs:
       SRA  _key
       JUMP NC, xch2
       LOAD _key, ASM_CHAR_STAR
       JUMP xchno

xch2:
       SRA  _key
       JUMP NC, xch5
       LOAD _key, ASM_CHAR_2
       JUMP xchno

xch5:
       SRA  _key
       JUMP NC, xch8
       LOAD _key, ASM_CHAR_5
       JUMP xchno

xch8:
       SRA  _key
       JUMP NC, xch0
       LOAD _key, ASM_CHAR_8
       JUMP xchno

xch0:
       SRA  _key
       JUMP NC, xch3
       LOAD _key, ASM_CHAR_0
       JUMP xchno

xch3:
       INPUT _key, port_kb_high
       SRA  _key
       JUMP NC, xch6
       LOAD _key, ASM_CHAR_3
       JUMP xchno

xch6:
       SRA  _key
       JUMP NC, xch9
       LOAD _key, ASM_CHAR_6
       JUMP xchno

xch9:
       SRA  _key
       JUMP NC, xchm
       LOAD _key, ASM_CHAR_9
       JUMP xchno

xchm:
       SRA  _key
       JUMP NC, xcha
       LOAD _key, ASM_CHAR_HASH
       JUMP xchno

xcha:
       SRA  _key
       JUMP NC, xchb
       LOAD _key, ASM_CHAR_A
       JUMP xchno

xchb:
       SRA  _key
       JUMP NC, xchc
       LOAD _key, ASM_CHAR_B
       JUMP xchno

xchc:
       SRA  _key
       JUMP NC, xchd
       LOAD _key, ASM_CHAR_C
       JUMP xchno

xchd:
       SRA  _key
       JUMP NC, xchno
       LOAD _key, ASM_CHAR_D
   
xchno:
       
  __endasm;
  
  return key;
}








#endif