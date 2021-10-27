/*-------------------------------------------------------------------------
gen.h - header file for code generation for XILINX PICOBLAZE

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

#ifndef SDCCGENPBLAZE_H
#define SDCCGENPBLAZE_H

#include "main.h"

#define GLOB_ASSIGN (ic->next == NULL && ic->prev == NULL)
#define IS_OP_GLOBALVOLATILE(x)	(IS_OP_GLOBAL( x ) && isOpVolatile( x ))
#define LOCAL_POINTER (!IS_OP_GLOBAL(result) && !isOpVolatile(result) && OP_LIVEFROM(result) == 0 && OP_LIVETO(result) == 0)
#define ASSIGN_OPT(x,y) 	( !IS_OP_GLOBAL( y ) && \
				!IS_OP_VOLATILE(x) && !IS_OP_VOLATILE(y) && \
				OP_LIVETO(y) != 0 && ic->seq >= OP_LIVETO(y))


#define MULUSCHAR "_muluchar"
#define MULSCHAR "_mulschar"
#define MULINT "_mulint"
#define MULLONG "_mullong"
#define DIVSCHAR "_divschar"
#define DIVUSCHAR "_divuchar"
#define DIVSINT "_divsint"
#define DIVUSINT "_divuint"
#define DIVSLONG "_divslong"
#define DIVUSLONG "_divulong"
#define MODSCHAR "_modschar"
#define MODUSCHAR "_moduchar"
#define MODSINT "_modsint"
#define MODUSINT "_moduint"
#define MODSLONG "_modslong"
#define MODUSLONG "_modulong"


enum {
    AOP_LIT = 1,
    AOP_REG, AOP_DIR,
    AOP_STK, AOP_STR
};

/* type asmop : a homogenised type for 
   all the different spaces an operand can be
   in */
typedef struct asmop {

    short type;                 /* can have values
                                   AOP_LIT    -  operand is a literal value
                                   AOP_REG    -  must be loaded into a register
                                   AOP_DIR    -  direct just a name   

                                 */
    short coff;                 /* current offset */
    short size;                 /* total size */
    unsigned freed:1;           /* already freed    */
    union {
        value *aop_lit;         /* if literal */
        regs *aop_reg[4];       /* array of registers */
        char *aop_dir;          /* if direct  */
    } aopu;
} asmop;


typedef struct inOutStruct {
    char *name;                 /* IN/OUT operand name */
    operand *tempOper;
    int liveFrom;
    int liveTo;
    short isNumOffset;          /* port address given as a number or an operand */
    unsigned long numOffset;    /* port address given as a number */
    operand *regOffset;         /* port address given as an indirect operand */
} inOutStruct_t;

void testOp(operand * oper);

void genPBLAZECode(iCode *);
void pblaze_emitDebuggerSymbol(const char *);
bool pblaze_operandsEqu(operand * op1, operand * op2);
int isOpVolatile(operand * oper);
void setRegUsed(int r);
int isRegUsed(int r);
short isCalleesaves(void);
void pushStack(int rdx, int c);

void emitStore(char *r, int mem);
void emitStoreReg(char *r, char *adr);
void emitFetch(char *r, int mem);
void emitLoadNumb(char *r, int val);
void emitLoad(char *l, char *r);
void emitcodeADD(char *l, int val);
void emitcodeSUB(char *l, int val);

int isInOutRef(operand * oper);
void pblaze_emitcodeOutput(iCode * ic, char *source, operand * to);

void genMulDivFunc(FILE * of);

void genMultChar(FILE * of);
void genMultUnsignedChar(FILE * of);
void genMultInt(FILE * of);
void genMultLong(FILE * of);
void genDivChar(FILE * of);
void genDivUnsignedChar(FILE * of);
void genModChar(FILE * of);
void genModUnsignedChar(FILE * of);
void genDivInt(FILE * of);
void genDivUnsignedInt(FILE * of);
void genModInt(FILE * of);
void genModUnsignedInt(FILE * of);
void genDivLong(FILE * of);
void genDivUnsignedLong(FILE * of);
void genModLong(FILE * of);
void genModUnsignedLong(FILE * of);
#endif
