/*-------------------------------------------------------------------------
ralloc.h - source file for register allocation. (XILINX PICOBLAZE) specific

Author: 
    Jakub Hornik, xhorni00<at>stud.fit.vutbr.cz
Master Thesis Project:
    Compiler Back-End of Subset of Language C for 8-Bit Processor
Date:
    2011
    
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
#include "SDCCicode.h"
#include "SDCCBBlock.h"
#ifndef PBLAZERALLOC_H
#define PBLAZERALLOC_H

enum {
    S0_IDX = 0,
    S1_IDX, S2_IDX, S3_IDX, S4_IDX,
    S5_IDX, S6_IDX, S7_IDX, S8_IDX,
    S9_IDX, SA_IDX, SB_IDX, SC_IDX,
    SD_IDX, SE_IDX, SF_IDX
};

enum {
    SAME_VAL = 0,
    IN_REG,
    IN_MEM
};


#define REG_PTR 0x01
#define REG_GPR 0x02            /* general purpose registers */

/* definition of the stack size and the stack bottom */
#define PBLAZE_STACK_SIZE 32
#define PBLAZE_STACK_BOTTOM 0x3F

/* first register used in send/receive function passing */
#define SEND_REG_FIRST SB_IDX
/* number of send/receive registers */
#define SEND_REG_COUNT 4

/* PicoBlaze's data memory size */
#define MEMSIZE 64
#define PBLAZENREGS 16

static set *_G_codeSet;
static int _G_glueCalled = 0;

/* definition for the registers */
typedef struct regs {
    short type;                 /* PicoBlaze have only REG_GPR */
    short rIdx;                 /* index into register table */
    char *name;                 /* name */
    operand *currOper;          /* current operand in the register */
    short offset;               /* offset of the operand  */
    short ptrOffset;            /* offset of the current pointer */
    short changed;              /* global variable is actual in the register */
    unsigned isFree:1;          /* is currently unassigned  */
    unsigned isReserved:1;      /* is reserved  */
} regs;



/* definition for the memory */
typedef struct memMap {
    unsigned int addr;          /* address of the memory cell */
    operand *currOper;          /* current operand in the register */
    short offset;               /* offset of the operand (if larger than 1B) */
    short ptrOffset;            /* offset of the current pointer */
    short nextPart;             /* index into memory with next part of the operand */
    unsigned reserved:1;        /* is reserved  */
    unsigned isGlobal:1;        /* contains global value  */
    unsigned isFree:1;          /* is currently free  */
    unsigned isOnlyInMem:1;     /* temporary variable which is only in the memory due to no avaiable registers  */
} memMap;

extern regs regsPBLAZE[];
extern memMap memPBLAZE[];

void staticMemoryCheck(int top);

char *aopGetRegName(iCode * ic, operand * op, int offset);
regs *aopGetReg(iCode * ic, operand * op, int offset);
void aopPutReg(iCode * ic, operand * result, regs * rFrom, int offset);
void aopPutVal(iCode * ic, operand * result, char *val, int offset);
void aopMoveReg(iCode * ic, operand * result, regs * rFrom, int offset);
void aopUpdateOpInMem(iCode * ic, operand * op, int offset);

regs *getReg(iCode * ic);

int isOpInReg(operand * op);
regs *isOffsetInReg(operand * op, int offset);

memMap *isOpInMem(operand * op);
memMap *isOffsetInMem(operand * op, int offset);

void assignOpt(iCode * ic, operand * to, operand * from);
int assignOptTest(iCode * lic, operand * to);

int clearUnusedOpFromReg(iCode * ic);
int clearUnusedOpFromMem(iCode * ic);
void clearMemEndFunc(void);
void globalChanged(operand * op, short c);
void freeGlobalsFromReg(void);
void allocOpInMem(operand * op);
void freeOpFromReg(operand * op);
memMap *firstFreeMem(void);
void moveOpToMem(operand * op);

void printRegs(void);
void printMemory(void);
void printConstants(FILE * of);
char *operName(int addr);

void setReserved(operand * oper);
void unSetReserved(operand * oper);
void unlockReg(regs * r);
void lockReg(regs * r);

regs *pblaze_regWithIdx(int);
void pblaze_genCodeLoop(void);

#endif
