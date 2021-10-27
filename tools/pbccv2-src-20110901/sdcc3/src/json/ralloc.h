/*-------------------------------------------------------------------------
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   
   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!  
-------------------------------------------------------------------------*/
#ifndef _JSON_SDCCRALLOC_H
#define _JSON_SDCCRALLOC_H

#include "SDCCicode.h"
#include "SDCCBBlock.h"


enum
  {
    S0_IDX = 0,
    S1_IDX, S2_IDX, S3_IDX, S4_IDX, 
    S5_IDX, S6_IDX, S7_IDX, S8_IDX, 
    S9_IDX, SA_IDX, SB_IDX, SC_IDX,
    SD_IDX, SE_IDX, SF_IDX
  };


#define REG_PTR 0x01
#define REG_GPR 0x02	/* general purpose registers*/


/* definition for the registers */
typedef struct regs
  {
    short type;			/* PicoBlaze have only REG_GPR */
    short rIdx;			/* index into register table */
    char *name;			/* name */
    symbol *currSymbol;		/* current symbol in the register */
    short offset;		/* offset of the operand (if larger than 1B) */
    unsigned isFree:1;		/* is currently unassigned  */
  }
regs;
extern regs regsJSON[];

//void assignReg (operand * op);

regs *json_regWithIdx (int);

#endif
