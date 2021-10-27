/*------------------------------------------------------------------------
ralloc.c - source file for register allocation. (XILINX PICOBLAZE) specific

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

#include "common.h"
#include "ralloc.h"
#include "gen.h"

//#define SYMBOL_IN_REG(reg)      validateOpType(reg->currOper, "OP_SYMBOL", #op, SYMBOL, __FILE__, __LINE__)->operand.symOperand
#define SYMBOL_IN_REG(reg)  OP_SYMBOL(reg.currOper)
#define RCV ic->op == RECEIVE
#define GLOBORVOLATIL(x) (IS_OP_GLOBAL(x) || IS_OP_VOLATILE(x))
#define IS_ENDLABEL(x) x->op == LABEL && strstr( IC_LABEL(x)->name, "_ifend_")

#define SKIP_IC5(x) (x->op == CALL        	||	\
		     x->op == RETURN	        ||	\
                     x->op == ENDFUNCTION       ||	\
                     x->op == FUNCTION   	||	\
                     x->op == SEND   		||	\
                     x->op == RECEIVE )


#define SKIP_NO_OP(x)  (x->op == GOTO         ||    \
                        x->op == LABEL        ||    \
                        x->op == FUNCTION     ||    \
                        x->op == INLINEASM    ||    \
			x->op == JUMPTABLE    ||    \
			x->op == IFX          ||    \
			x->op == CALL         ||    \
			x->op == PCALL        ||    \
			x->op == ARRAYINIT    ||    \
                        x->op == CRITICAL     ||    \
                        x->op == ENDCRITICAL  ||    \
			x->op == ENDFUNCTION  )

extern void genPBLAZECode(iCode *);
extern unsigned fPBLAZEReturnSize;
extern void emitStore(char *r, int mem);
extern void emitFetch(char *r, int mem);

/* Global data */
static struct {
    bitVect *regAssigned;
    bitVect *funcrUsed;         /* registers used in a function */
    int stackExtend;
    int dataExtend;
} _G;

/* Shared with gen.c */
int pblaze_ptrRegReq;           /* pointer register required */

int gInit = 0;

/* PBLAZE registers */
regs regsPBLAZE[] = {
    {REG_GPR, S0_IDX, "s0", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S1_IDX, "s1", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S2_IDX, "s2", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S3_IDX, "s3", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S4_IDX, "s4", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S5_IDX, "s5", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S6_IDX, "s6", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S7_IDX, "s7", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S8_IDX, "s8", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, S9_IDX, "s9", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, SA_IDX, "sA", NULL, 0, 0, SAME_VAL, 1, 0},
    {REG_GPR, SB_IDX, "sB", NULL, 0, 0, SAME_VAL, 1, 1},
    {REG_GPR, SC_IDX, "sC", NULL, 0, 0, SAME_VAL, 1, 1},
    {REG_GPR, SD_IDX, "sD", NULL, 0, 0, SAME_VAL, 1, 1},
    {REG_GPR, SE_IDX, "sE", NULL, 0, 0, SAME_VAL, 1, 1},
    {REG_GPR, SF_IDX, "sF", NULL, 0, 0, SAME_VAL, 0, 1},
};



int pblaze_nRegs = PBLAZENREGS - SEND_REG_COUNT - 1;    // avaiable regs
int pblaze_totalRegs = PBLAZENREGS;     // total regs
int pblaze_fReg = 0;            /* first allocatable register */

// temp regs counter
int ctr = 0;

memMap memPBLAZE[MEMSIZE];


void printRegs(void)
{

    int i;

    printf("==============PicoBlaze=Registers=============\n");

    for (i = 0; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].isFree == 0 && regsPBLAZE[i].currOper) {
            printf("%s ->\t %s:%d\n", regsPBLAZE[i].name, SYMBOL_IN_REG(regsPBLAZE[i])->name, regsPBLAZE[i].offset);

        } else if (regsPBLAZE[i].isReserved == 1 && regsPBLAZE[i].currOper)
            //printf("%s ->\t %s\n", regsPBLAZE[i].name, "reserved");
            printf("%sR ->\t %s:%d\n", regsPBLAZE[i].name, SYMBOL_IN_REG(regsPBLAZE[i])->name, regsPBLAZE[i].offset);
    }
    printf("==============================================\n\n");
}


void printMemory(void)
{

    int i;

    printf("==============PicoBlaze=Memory================\n");

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].isFree == 0 && memPBLAZE[i].currOper) {
            printf("%d ->\t %s:%d\n", memPBLAZE[i].addr, SYMBOL_IN_REG(memPBLAZE[i])->name, memPBLAZE[i].offset);

        }
    }
    printf("==============================================\n\n");
}

/*-----------------------------------------------------------------*/
/* Prints constants name depending on the selected dialect         */
/*-----------------------------------------------------------------*/
void printConstants(FILE * of)
{
    int i;
    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].isFree == 0 && memPBLAZE[i].currOper && IS_OP_GLOBAL(memPBLAZE[i].currOper)) {
            if (pblaze_options.dialect && getSize(operandType(memPBLAZE[i].currOper)) == 1)
                fprintf(of, "\tCONSTANT\t%s, %02x\n", SYMBOL_IN_REG(memPBLAZE[i])->rname, i);
            else if (pblaze_options.dialect)
                fprintf(of, "\tCONSTANT\t%s_%d, %02x\n", SYMBOL_IN_REG(memPBLAZE[i])->rname, memPBLAZE[i].offset, i);
            else if (getSize(operandType(memPBLAZE[i].currOper)) == 1)
                fprintf(of, "\t%s\tEQU $%02x\n", SYMBOL_IN_REG(memPBLAZE[i])->rname, i);
            else
                fprintf(of, "\t%s_%d\tEQU $%02x\n", SYMBOL_IN_REG(memPBLAZE[i])->rname, memPBLAZE[i].offset, i);
        }
    }
    fprintf(of, "\n");
}

/*-----------------------------------------------------------------*/
/* operName - returns a memory name or a memory adress             */
/*-----------------------------------------------------------------*/
char *operName(int addr)
{
    char *s = buffer;
    if (memPBLAZE[addr].isFree || !IS_OP_GLOBAL(memPBLAZE[addr].currOper))
        sprintf(s, "%s%02x", pblaze_options.dialect ? "" : "$", addr);
    else if (getSize(operandType(memPBLAZE[addr].currOper)) == 1)
        sprintf(s, "%s", SYMBOL_IN_REG(memPBLAZE[addr])->rname);
    else
        sprintf(s, "%s_%d", SYMBOL_IN_REG(memPBLAZE[addr])->rname, memPBLAZE[addr].offset);
    return Safe_strdup(s);
}

/*-----------------------------------------------------------------*/
/* pblaze_regWithIdx - returns pointer to register with index number*/
/*-----------------------------------------------------------------*/
regs *pblaze_regWithIdx(int idx)
{
    int i;

    for (i = 0; i < pblaze_totalRegs; i++)
        if (regsPBLAZE[i].rIdx == idx)
            return &regsPBLAZE[i];

    werror(E_INTERNAL_ERROR, __FILE__, __LINE__, "regWithIdx not found");
    exit(1);
}

/*-----------------------------------------------------------------*/
/* check for memory collisions (between data part and the stack    */
/*-----------------------------------------------------------------*/
void staticMemoryCheck(int t)
{
    static int top = MEMSIZE - 1;
    if (t >= 0 && t < MEMSIZE)
        top = t;

    if (!memPBLAZE[top].isFree || memPBLAZE[top].currOper) {
        fprintf(stderr, "pblaze port error: not enough memory\n");
        exit(0);
    }

}

/*-----------------------------------------------------------------*/
/* Init stack                                                      */
/*-----------------------------------------------------------------*/
void initPBLAZEStack(void)
{
    // top of the stack pointer
    regs *rStack;
    //pblaze_nRegs = 15;
    rStack = pblaze_regWithIdx(SF_IDX);
    rStack->currOper = NULL;
    rStack->isFree = 0;
    rStack->isReserved = 1;

}

/*-----------------------------------------------------------------*/
/* firstFreeReg - returns first free register                      */
/*-----------------------------------------------------------------*/
static regs *firstFreeReg(void)
{
    int i;

    for (i = 0; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].isFree == 1 && regsPBLAZE[i].isReserved == 0)
            return &regsPBLAZE[i];
    }

    return NULL;
}

/*-----------------------------------------------------------------*/
/* firstFreeMem - returns first free register                      */
/*-----------------------------------------------------------------*/
memMap *firstFreeMem(void)
{
    int i;

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].isFree == 1)
            return &memPBLAZE[i];
    }

    return NULL;
}

/*-----------------------------------------------------------------*/
/* isOpInReg - test if operand is in registers                  */
/*-----------------------------------------------------------------*/
int isOpInReg(operand * op)
{
    int i, found = 0;

    if (!op)
        return 0;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].currOper && pblaze_operandsEqu(op, regsPBLAZE[i].currOper)) {
            found++;
        }
    }

    return found;
}


/*-----------------------------------------------------------------*/
/* isOffsetInReg - test if operand's offset is in registers         */
/*-----------------------------------------------------------------*/
regs *isOffsetInReg(operand * op, int offset)
{
    int i;

    if (!op)
        return NULL;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].currOper && pblaze_operandsEqu(op, regsPBLAZE[i].currOper) && regsPBLAZE[i].offset == offset) {
            return &regsPBLAZE[i];
        }
    }

    return NULL;
}

/*-----------------------------------------------------------------*/
/* isOffsetInMem - test if operand's offset is in the memory        */
/* returns pointer into memory                                     */
/*-----------------------------------------------------------------*/
memMap *isOffsetInMem(operand * op, int offset)
{
    int i;
    if (op == NULL || op->type != SYMBOL)
        return NULL;

    if (!op)
        return NULL;

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].currOper && pblaze_operandsEqu(op, memPBLAZE[i].currOper)) {
            if (memPBLAZE[i].offset == offset)
                return &memPBLAZE[i];
        }
    }

    return NULL;
}

/*-----------------------------------------------------------------*/
/* isOpInMem - test if symbol is in the memory                     */
/* returns pointer into memory                                     */
/*-----------------------------------------------------------------*/
memMap *isOpInMem(operand * op)
{
    int i, size, found = 0;
    memMap *m = NULL;
    if (op == NULL || op->type != SYMBOL)
        return NULL;

    symbol *s = OP_SYMBOL(op);

    if (!op)
        return NULL;

    size = getSize(s->type);

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].currOper && pblaze_operandsEqu(op, memPBLAZE[i].currOper)) {
            found++;
            if (m == NULL)
                m = &memPBLAZE[i];
        }
    }

    if (found == size)
        return m;
    return NULL;

}

/*-----------------------------------------------------------------*/
/* lockReg - set a register as reserved                            */
/*-----------------------------------------------------------------*/
void lockReg(regs * r)
{
    r->isReserved = 1;
}

/*-----------------------------------------------------------------*/
/* unlockReg - unset a register as reserved                            */
/*-----------------------------------------------------------------*/
void unlockReg(regs * r)
{
    if (r->rIdx < pblaze_nRegs)
        r->isReserved = 0;
}

/*-----------------------------------------------------------------*/
/* freeReg - frees a register                                      */
/*-----------------------------------------------------------------*/
static void freeReg(regs * reg)
{
    if (reg) {
        reg->isFree = 1;
        reg->currOper = NULL;
        reg->offset = 0;
        reg->ptrOffset = 0;
        reg->isReserved = 0;
        reg->changed = SAME_VAL;
    }
}

/*-----------------------------------------------------------------*/
/* freeMem - frees a memory cell                                   */
/*-----------------------------------------------------------------*/
static void freeMem(memMap * mem)
{
    if (mem) {
        mem->currOper = NULL;
        mem->offset = 0;
        mem->ptrOffset = 0;
        mem->nextPart = -1;
        mem->reserved = 0;
        mem->isGlobal = 0;
        mem->isFree = 1;
        mem->isOnlyInMem = 0;
    }
}

/*-----------------------------------------------------------------*/
/* initPBLAZEMem - init PicoBlaze memory                                     */
/*-----------------------------------------------------------------*/
void initPBLAZEMem(void)
{
    int i;
    for (i = 0; i < MEMSIZE; i++) {

        memPBLAZE[i].addr = i;
        memPBLAZE[i].currOper = NULL;
        memPBLAZE[i].offset = 0;
        memPBLAZE[i].ptrOffset = 0;
        memPBLAZE[i].nextPart = -1;
        memPBLAZE[i].reserved = 0;
        memPBLAZE[i].isGlobal = 0;
        memPBLAZE[i].isFree = 1;
        memPBLAZE[i].isOnlyInMem = 0;

    }
}

/*-----------------------------------------------------------------*/
/* freeOpFromReg - frees an operand from registers                 */
/*-----------------------------------------------------------------*/
void freeOpFromReg(operand * op)
{
    int i, size;
    symbol *s;
    regs *rtmp;

    if (!op)
        return;

    s = OP_SYMBOL(op);
    size = getSize(operandType(op));

    for (i = 0; i < size; i++) {
        if (s->regs[i]) {
            rtmp = s->regs[i];
            s->regs[i] = NULL;
            freeReg(rtmp);
        }
    }
    s->nRegs = 0;
}

/*-----------------------------------------------------------------*/
/* freeOffsetFromReg - frees an operand offset from registers      */
/*-----------------------------------------------------------------*/
void freeOffsetFromReg(operand * op, int offset)
{
    if (!op)
        return;

    symbol *s = OP_SYMBOL(op);
    regs *rtmp;

    if (s->regs[offset]) {
        rtmp = s->regs[offset];
        s->regs[offset] = NULL;
        freeReg(rtmp);
    }
}

/*-----------------------------------------------------------------*/
/* freeOpFromMem - frees an operand from the memory                */
/*-----------------------------------------------------------------*/
void freeOpFromMem(operand * op)
{
    int i;

    if (!op)
        return;

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].currOper == op) {
            freeMem(&memPBLAZE[i]);
        }
    }
}

/*-----------------------------------------------------------------*/
/* freeOffsetFromMem - frees an operand offset from the memory     */
/*-----------------------------------------------------------------*/
void freeOffsetFromMem(operand * op, int offset)
{
    int i;

    if (!op)
        return;

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].currOper && pblaze_operandsEqu(op, memPBLAZE[i].currOper) && memPBLAZE[i].offset == offset) {
            freeMem(&memPBLAZE[i]);
        }
    }
}


/*-----------------------------------------------------------------*/
/* freeOperand - frees an operand                                  */
/*-----------------------------------------------------------------*/
void freeOperand(operand * op)
{
    freeOpFromReg(op);
    freeOpFromMem(op);
}

/*-----------------------------------------------------------------*/
/* nFreeRegs - returns number of free registers                    */
/*-----------------------------------------------------------------*/
static int nFreeRegs(void)
{
    int i;
    int nfr = 0;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++)
        if (regsPBLAZE[i].isFree && regsPBLAZE[i].isReserved == 0)
            nfr++;
    return nfr;
}

/*-----------------------------------------------------------------*/
/* resetRegs - clear GP registers                                  */
/*-----------------------------------------------------------------*/
void resetRegs(void)
{
    int i;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (!regsPBLAZE[i].isReserved)
            freeReg(&regsPBLAZE[i]);
    }
}

/*-----------------------------------------------------------------*/
/* clearUnusedOpFromReg - remove old operands from the registers   */
/*-----------------------------------------------------------------*/
int clearUnusedOpFromReg(iCode * ic)
{
    int position, freed = 0, i = 0;
    if (!ic)
        return 0;

    position = ic->seq;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].isFree == 0 && regsPBLAZE[i].isReserved == 0 && regsPBLAZE[i].currOper &&
            !isOpVolatile(regsPBLAZE[i].currOper) && OP_LIVETO(regsPBLAZE[i].currOper) < position) {
            if (!IS_OP_GLOBAL(regsPBLAZE[i].currOper) && OP_LIVEFROM(regsPBLAZE[i].currOper) > 0) {
                freeOpFromReg(regsPBLAZE[i].currOper);
                if (i >= SEND_REG_FIRST)
                    regsPBLAZE[i].isReserved = 1;
                freed++;
            }
        }
    }

    return freed;
}

/*-----------------------------------------------------------------*/
/* clearUnusedOpFromMem - remove old operands from the memory   */
/*-----------------------------------------------------------------*/
int clearUnusedOpFromMem(iCode * ic)
{
    int position, freed = 0, i = 0;
    if (!ic)
        return 0;

    position = ic->seq;
    for (i = 0; i < MEMSIZE; i++) {

        if (memPBLAZE[i].isFree == 0 && memPBLAZE[i].currOper && !IS_OP_GLOBAL(memPBLAZE[i].currOper) &&
            OP_LIVETO(memPBLAZE[i].currOper) != 0 && OP_LIVETO(memPBLAZE[i].currOper) < position) {

            freeMem(&memPBLAZE[i]);
            freed++;
        }
    }

    return freed;
}

/*-----------------------------------------------------------------*/
/* clearMemEndFunc - clear memory at the end of a current function */
/*-----------------------------------------------------------------*/
void clearMemEndFunc(void)
{
    int i;

    for (i = 0; i < MEMSIZE; i++) {

        if (memPBLAZE[i].isFree == 0 && memPBLAZE[i].currOper && !IS_OP_GLOBAL(memPBLAZE[i].currOper)) {
            freeMem(&memPBLAZE[i]);
        }
    }
}

/*-----------------------------------------------------------------*/
/* getMemoryBlock - return last memory cell number with current size */
/*-----------------------------------------------------------------*/
int getMemoryBlock(int size)
{
    int i, count = 0;

    for (i = 0; i < MEMSIZE; i++) {
        if (memPBLAZE[i].isFree == 1 && memPBLAZE[i].isGlobal == 0) {
            count++;
            if (size <= count)
                return i;
        } else {
            count = 0;
        }
    }

    //werror (E_INTERNAL_ERROR, __FILE__, __LINE__, "cannot allocate memory for a global variable");
    fprintf(stderr, "%s:%d: pblaze port error: cannot allocate memory for a global variable\n", __FILE__, __LINE__);
    exit(1);
    return -1;
}


/*-----------------------------------------------------------------*/
/* set operand in registers as reserved                            */
/*-----------------------------------------------------------------*/
void setReserved(operand * oper)
{
    int size, i;

    if (oper->type != SYMBOL)
        return;

    symbol *s = OP_SYMBOL(oper);
    size = getSize(s->type);

    if (s->nRegs == 0)
        return;

    for (i = 0; i < size; i++) {

        s->regs[i]->isReserved = 1;

    }
}

/*-----------------------------------------------------------------*/
/* unset operand in registers as reserved                          */
/*-----------------------------------------------------------------*/
void unSetReserved(operand * oper)
{
    int size, i;

    if (oper->type != SYMBOL)
        return;

    symbol *s = OP_SYMBOL(oper);
    size = getSize(s->type);

    if (s->nRegs == 0)
        return;

    for (i = 0; i < size; i++) {
        if (s->regs[i]->rIdx < pblaze_nRegs)
            s->regs[i]->isReserved = 0;

    }
}

/*-----------------------------------------------------------------*/
/* allocOpInMem - alloc operand in the memory                      */
/*-----------------------------------------------------------------*/
void allocOpInMem(operand * op)
{
    int size, i, pos, next = -1;
    memMap *m;

    if (isOpInMem(op))
        return;

    size = getSize(operandType(op));
    pos = getMemoryBlock(size);

    for (i = 0; i < size; i++) {
        m = &memPBLAZE[pos];
        m->currOper = op;
        m->isFree = 0;
        m->isGlobal = IS_OP_GLOBAL(op);
        m->offset = i;
        m->ptrOffset = 0;
        m->nextPart = next;
        next = pos--;
    }

}



/*-----------------------------------------------------------------*/
/* moveOpToMem - move operand from registers to memory             */
/*-----------------------------------------------------------------*/
void moveOpToMem(operand * op)
{
    if (!op) {
        return;
    }

    int size, i, next = -1;
    memMap *m, *t;
    symbol *s = OP_SYMBOL(op);

    size = getSize(s->type);

    for (i = size - 1; i >= 0; i--) {
        /* this offset is in the memory */
        if (s->regs[i] == NULL && (t = isOffsetInMem(op, i)) != NULL) {
            next = t->addr;
        }
        /* offset is in the registers */
        else if (s->regs[i]) {
            // try to get a pointer, if it is a global variable
            if (IS_OP_GLOBAL(op) && (m = isOffsetInMem(op, i)) != NULL) {
            } else
                m = firstFreeMem();

            if (!m) {
                fprintf(stderr, "%s:%d: pblaze port error: not enough memory\n", __FILE__, __LINE__);
                exit(1);
            }
            //emitcode ("STORE", "%s, %02x", s->regs[i]->name , m->addr );
            emitStore(s->regs[i]->name, m->addr);

            m->currOper = op;
            m->isFree = 0;
            m->isGlobal = IS_OP_GLOBAL(op);
            m->offset = i;
            m->ptrOffset = s->regs[i]->ptrOffset;
            m->nextPart = next;
            next = m->addr;
        }
    }

    freeOpFromReg(op);
}

/*-----------------------------------------------------------------*/
/* moveOffsetToMem - move operand's offset from registers to memory*/
/*-----------------------------------------------------------------*/
void moveOffsetToMem(operand * op, int offset)
{
    if (!op) {
        return;
    }

    memMap *m, *t;
    symbol *s = OP_SYMBOL(op);

    // move all registers if it is a global operand
    if (IS_OP_GLOBAL(op))
        moveOpToMem(op);

    // not a global operand
    else if (offset >= 0 && s->regs[offset] != NULL) {
        m = isOffsetInMem(op, offset);
        if (!m)
            m = firstFreeMem();

        if (!m) {
            fprintf(stderr, "%s:%d: pblaze port error: not enough memory\n", __FILE__, __LINE__);
            exit(1);
        }
        //emitcode ("STORE", "%s, %02x", s->regs[offset]->name , m->addr );
        emitStore(s->regs[offset]->name, m->addr);

        m->currOper = op;
        m->isFree = 0;
        m->isGlobal = IS_OP_GLOBAL(op);
        m->offset = offset;
        m->ptrOffset = s->regs[offset]->ptrOffset;
        t = isOffsetInMem(op, offset + 1);
        if (t == NULL)
            m->nextPart = -1;
        else
            m->nextPart = t->addr;

        // free operand's offset
        freeOffsetFromReg(op, offset);
    }
}


/*-----------------------------------------------------------------*/
/* bitVectRemainRegs - returns sum of a bit values                 */
/*-----------------------------------------------------------------*/
int bitVectRemainRegs(bitVect * bv)
{
    int i, c = 0;

    if (!bv)
        return 0;

    for (i = 0; i < bv->size; i++)
        c += bitVectBitValue(bv, i);
    return c;
}


/*-----------------------------------------------------------------*/
/* firstIC5 - returns iCode of the first instruction from IC5 instr*/
/*-----------------------------------------------------------------*/
iCode *firstIC5(iCode * ic)
{
    iCode *tic;
    if (!ic)
        return NULL;

    tic = ic;
    while (tic) {
        if (SKIP_IC5(tic))
            break;

        tic = tic->next;
    }
    return tic;
}

/*-----------------------------------------------------------------*/
/* blockStart - returns iCode of the start of a block              */
/*-----------------------------------------------------------------*/
iCode *blockStart(iCode * ic)
{
    iCode *tic;
    if (!ic)
        return NULL;

    tic = ic;
    while (tic->prev) {
        if (SKIP_IC2(tic->prev) || tic->prev->op == IFX)
            break;

        tic = tic->prev;
    }
    return tic;
}

/*-----------------------------------------------------------------*/
/* blockEnd - returns iCode of the end of a block              */
/*-----------------------------------------------------------------*/
iCode *blockEnd(iCode * ic)
{
    iCode *tic;
    if (!ic)
        return NULL;

    tic = ic;
    while (tic->next) {
        if (SKIP_IC2(tic->next) || tic->next->op == IFX)
            break;

        tic = tic->next;
    }
    return tic;
}

/*-----------------------------------------------------------------*/
/* assignOptTest - checking whether the assignment can be optimized*/
/* there can be some conflict in IFX                               */
/*-----------------------------------------------------------------*/
int testIFXConflict(iCode * lic, operand * to)
{
    iCode *ic, *ifxs, *ifxe;
    short isIFX = 0;
    short isIFEND = 0;
    short isAssign = 0;
    short isGoto = 0;

    if (!lic)
        return 1;

    /* check whether we are nested in ifx */
    for (ic = lic; ic; ic = ic->prev) {

        if (ic->op == IFX) {
            isIFX = 1;
            ifxs = ic;
            break;
        } else if (IS_ENDLABEL(ic))
            break;
    }

    if (!isIFX)
        return 1;

    /* find end of the current IFX */
    for (ic = lic->next; ic; ic = ic->next) {
        if (IS_ENDLABEL(ic)) {
            isIFEND = 1;
            ifxe = ic;
            break;
        }
    }

    if (!isIFEND)
        return 0;

    /* find assing conflicts (forward) */
    for (ic = lic->next; ic && ic != ifxe; ic = ic->next) {
        if (ic->op == GOTO)
            isGoto = 1;
        else if (!SKIP_NO_OP(ic) && isGoto) {
            if (IC_RESULT(ic) && pblaze_operandsEqu(to, IC_RESULT(ic)))
                return 0;
            else if (IC_RIGHT(ic) && pblaze_operandsEqu(to, IC_RIGHT(ic)))
                return 0;
            else if (IC_LEFT(ic) && pblaze_operandsEqu(to, IC_LEFT(ic)))
                return 0;
        }
    }

    isGoto = 0;

    /* find assing conflicts (backward) */
    for (ic = lic; ic && ic != ifxs; ic = ic->prev) {
        if (ic->op == GOTO)
            isGoto = 1;
        else if (IS_ENDLABEL(ic))
            break;
        else if (!SKIP_NO_OP(ic) && isGoto) {
            if (IC_RESULT(ic) && pblaze_operandsEqu(to, IC_RESULT(ic)))
                return 0;
            else if (IC_RIGHT(ic) && pblaze_operandsEqu(to, IC_RIGHT(ic)))
                return 0;
            else if (IC_LEFT(ic) && pblaze_operandsEqu(to, IC_LEFT(ic)))
                return 0;
        }
    }

    return 1;
}


/*-----------------------------------------------------------------*/
/* testOperand - LRU operands testing                              */
/*-----------------------------------------------------------------*/
void testOperand(operand * op, int free, bitVect * rUse)
{
    int sizeInReg, remainOp, size, j;
    regs *r;

    if (!op)
        return;

    sizeInReg = isOpInReg(op);
    remainOp = bitVectRemainRegs(rUse);

    if (sizeInReg > 0 && remainOp - sizeInReg >= free) {
        size = getSize(operandType(op));

        for (j = 0; j < size; j++) {
            r = isOffsetInReg(op, j);
            if (r) {
                bitVectUnSetBit(rUse, r->rIdx);
            }
        }

    }
}

int isUsedInCurrentInstr(iCode * ic, operand * op)
{
    int res = 0;

    if (IC_LEFT(ic) != NULL && pblaze_operandsEqu(IC_LEFT(ic), op)) {
        res = 1;
    }

    else if (IC_RIGHT(ic) != NULL && pblaze_operandsEqu(IC_RIGHT(ic), op)) {
        res = 1;
    }

    else if (IC_RESULT(ic) != NULL && pblaze_operandsEqu(IC_RESULT(ic), op)) {
        res = 1;
    }

    return res;
}

/*-----------------------------------------------------------------*/
/* spillRegsIntoMem - move LRU operand into memory                */
/*-----------------------------------------------------------------*/
int spillRegsIntoMem(iCode * lic, operand * op, int offset, int free)
{
    iCode *ic, *tic;
    bitVect *rUse;
    int remainOp, i, bStart;

    if (!lic)
        return -1;
    if (free <= 0)
        return 0;

    // bit vector of used registers
    rUse = newBitVect(pblaze_nRegs);

    tic = blockStart(lic);
    if (tic)
        bStart = tic->seq;
    else
        bStart = lic->seq;

    // set vector bits corresponding to used / free registers
    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].isReserved == 1 || regsPBLAZE[i].isFree == 1 || (bStart > OP_LIVEFROM(regsPBLAZE[i].currOper))
            || (isUsedInCurrentInstr(lic, regsPBLAZE[i].currOper) && regsPBLAZE[i].offset == offset)) {
            bitVectUnSetBit(rUse, i);
        } else {
            bitVectSetBit(rUse, i);
        }
    }

    if (bitVectRemainRegs(rUse) == 0) {
        return 1;
    }
    // get LRU operand
    for (ic = lic; ic; ic = ic->next) {

        if (!SKIP_NO_OP(ic)) {

            if (IC_LEFT(ic) != NULL) {
                testOperand(IC_LEFT(ic), free, rUse);
            }

            if (IC_RIGHT(ic) != NULL) {
                testOperand(IC_RIGHT(ic), free, rUse);
            }

            if (IC_RESULT(ic) != NULL) {
                testOperand(IC_RESULT(ic), free, rUse);
            }

        }

        remainOp = bitVectRemainRegs(rUse);

        if (remainOp == free)
            break;
    }

    // try to move global variable first
    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (bitVectBitValue(rUse, i) && IS_OP_GLOBAL(regsPBLAZE[i].currOper) && free > nFreeRegs()) {
            moveOpToMem(regsPBLAZE[i].currOper);
        }
    }

    // move LRU temp variable into memory
    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (bitVectBitValue(rUse, i) && free > nFreeRegs()) {
            moveOffsetToMem(regsPBLAZE[i].currOper, regsPBLAZE[i].offset);
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // second selection phase - operand with no assignment conflict (inside IF-ELSE condition)
    if (remainOp == free)
        return 0;

    /*

       // set vector bits corresponding to used / free registers
       for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
       if( regsPBLAZE[i].isReserved == 1 || regsPBLAZE[i].isFree == 1 ) {
       bitVectUnSetBit(rUse,i);
       }
       else {
       bitVectSetBit(rUse,i);
       }
       }

       for (ic = lic; ic; ic = ic->next) {

       if( !SKIP_NO_OP(ic) ) {

       if(IC_LEFT(ic) != NULL && isOpInReg(IC_LEFT(ic)) && !testIFXConflict(ic, IC_LEFT(ic)) ) {
       testOperand(IC_LEFT(ic), 0, rUse);
       }

       if(IC_RIGHT(ic) != NULL && isOpInReg(IC_RIGHT(ic)) && !testIFXConflict(ic, IC_RIGHT(ic)) ) {
       testOperand(IC_RIGHT(ic), 0, rUse);
       }

       if(IC_RESULT(ic) != NULL && isOpInReg(IC_RESULT(ic)) && !testIFXConflict(ic, IC_RESULT(ic)) ) {
       testOperand(IC_RESULT(ic), 0, rUse);
       }

       }
       }

       // move LRU temp variable into memory
       for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
       if(bitVectBitValue(rUse,i) &&  free > nFreeRegs() ) {
       moveOffsetToMem (regsPBLAZE[i].currOper, regsPBLAZE[i].offset);
       }
       }  

       remainOp = bitVectRemainRegs(rUse);

     */

    if (nFreeRegs() < free) {
        return 1;
    }

    return 0;
}

/*-----------------------------------------------------------------*/
/* globalChanged - global value changed                            */
/*-----------------------------------------------------------------*/
void globalChanged(operand * op, short c)
{
    int i, size;

    if (!op)
        return;

    size = getSize(operandType(op));

    for (i = 0; i < size; i++) {
        if (OP_SYMBOL(op)->regs[i]) {
            OP_SYMBOL(op)->regs[i]->changed = c;
        }
    }

}

/*-----------------------------------------------------------------*/
/* freeGlobalsFromReg - move globals into the memory if changed    */
/*-----------------------------------------------------------------*/
void freeGlobalsFromReg(void)
{
    int i;

    for (i = pblaze_fReg; i < pblaze_nRegs; i++) {
        if (regsPBLAZE[i].currOper && IS_OP_GLOBAL(regsPBLAZE[i].currOper)) {
            if (regsPBLAZE[i].changed == IN_REG) {
                moveOpToMem(regsPBLAZE[i].currOper);
            } else
                freeOpFromReg(regsPBLAZE[i].currOper);
        }
    }


}

/*-----------------------------------------------------------------*/
/* getReg - returns pointer to a free register                     */
/*-----------------------------------------------------------------*/
regs *getReg(iCode * ic)
{
    regs *rtmp;

    clearUnusedOpFromReg(ic);

    rtmp = firstFreeReg();
    if (rtmp) {
        /* callee saves */
        if (isCalleesaves()) {
            if (!isRegUsed(rtmp->rIdx)) {
                pushStack(rtmp->rIdx, 0);
            }
            setRegUsed(rtmp->rIdx);
        }

        return rtmp;
    } else {
        rtmp = pblaze_regWithIdx(pblaze_nRegs + ctr);

        ctr++;
        if (ctr >= SEND_REG_COUNT)
            ctr = 0;

        return rtmp;
    }
    return NULL;
}

/*-----------------------------------------------------------------*/
/* getTempReg - returns pointer to a next temp register            */
/*-----------------------------------------------------------------*/
regs *getTempReg(void)
{
    regs *rtmp;
    rtmp = pblaze_regWithIdx(pblaze_nRegs + ctr);

    ctr++;
    if (ctr >= SEND_REG_COUNT)
        ctr = 0;

    return rtmp;
}

/*-----------------------------------------------------------------*/
/* getRegOper - returns pointer to a free register                     */
/*-----------------------------------------------------------------*/
regs *getRegOper(iCode * ic, operand * op, int offset)
{
    regs *rtmp;

    clearUnusedOpFromReg(ic);
    if (nFreeRegs() == 0) {

        spillRegsIntoMem(ic, op, offset, 1);

    }

    rtmp = firstFreeReg();
    if (rtmp) {
        /* callee saves */
        if (isCalleesaves()) {
            if (!isRegUsed(rtmp->rIdx)) {
                pushStack(rtmp->rIdx, 0);
            }
            setRegUsed(rtmp->rIdx);
        }

        return rtmp;
    } else {
        rtmp = pblaze_regWithIdx(pblaze_nRegs + ctr);

        ctr++;
        if (ctr >= SEND_REG_COUNT)
            ctr = 0;

        return rtmp;
    }
    return NULL;
}


/*-----------------------------------------------------------------*/
/* assignOptTest - checking whether the assignment can be optimized*/
/* there can be some conflict in IFX                               */
/*-----------------------------------------------------------------*/
int assignOptTest(iCode * lic, operand * to)
{
    iCode *ic, *ifxs, *ifxe;
    short isIFX = 0;
    short isIFEND = 0;
    short isAssign = 0;
    short isGoto = 0;

    if (!lic)
        return 1;

    /* check whether we are nested in ifx */
    for (ic = lic; ic; ic = ic->prev) {

        if (ic->op == IFX) {
            isIFX = 1;
            ifxs = ic;
            break;
        } else if (IS_ENDLABEL(ic))
            break;
    }

    if (!isIFX)
        return 1;

    /* find end of the current IFX */
    for (ic = lic->next; ic; ic = ic->next) {
        if (IS_ENDLABEL(ic)) {
            isIFEND = 1;
            ifxe = ic;
            break;
        }
    }

    if (!isIFEND)
        return 0;

    /* find assing conflicts (forward) */
    for (ic = lic->next; ic && ic != ifxe; ic = ic->next) {
        if (ic->op == GOTO)
            isGoto = 1;
        else if (ic->op == '=' && isGoto && pblaze_operandsEqu(to, IC_RESULT(ic))) {
            return 0;
        }
    }

    isGoto = 0;

    /* find assing conflicts (backward) */
    for (ic = lic; ic && ic != ifxs; ic = ic->prev) {
        if (ic->op == GOTO)
            isGoto = 1;
        else if (IS_ENDLABEL(ic))
            break;
        else if (ic->op == '=' && isGoto && pblaze_operandsEqu(to, IC_RESULT(ic))) {
            return 0;
        }
    }

    return 1;
}

/*-----------------------------------------------------------------*/
/* assignOpt - assign optimalization                               */
/*-----------------------------------------------------------------*/
void assignOpt(iCode * ic, operand * to, operand * from)
{
    int size, nReg, i;
    regs *rtmp;
    memMap *mem;

    if (IS_OP_GLOBAL(to))
        freeOpFromReg(to);
    else
        freeOperand(to);

    size = getSize(operandType(to));
    nReg = getSize(operandType(from));
    OP_SYMBOL(to)->nRegs = size;

    if (nReg == 0) {
        return;
    }

    for (i = 0; i < size; i++) {

        rtmp = OP_SYMBOL(from)->regs[i];
        if (!rtmp) {
            mem = isOffsetInMem(from, i);
            if (mem != NULL)
                mem->currOper = to;
            else {
                //exit (1);
                rtmp = getReg(ic);
                if (rtmp->rIdx < pblaze_nRegs) {
                    rtmp->isFree = 0;
                    rtmp->offset = i;
                    //emitLoadNumb(rtmp->name, 0);
                }
            }
        }
        OP_SYMBOL(to)->regs[i] = rtmp;
        if (rtmp) {
            rtmp->currOper = to;
        }
        OP_SYMBOL(from)->regs[i] = NULL;
    }

    for (i = size; i < nReg; i++) {
        rtmp = OP_SYMBOL(from)->regs[i];
        freeReg(rtmp);
        OP_SYMBOL(from)->regs[i] = NULL;
    }

    OP_SYMBOL(from)->nRegs = 0;
}



/*-----------------------------------------------------------------*/
/* aopGetReg - assign an operand's offset into registers if necessary*/
/*             and returns that register                           */
/*-----------------------------------------------------------------*/
regs *aopGetReg(iCode * ic, operand * op, int offset)
{
    regs *rs;
    int size;
    memMap *mem, *mtmp;
    regs *rtmp;

    // symbol only
    if (op->type == SYMBOL) {
        size = getSize(OP_SYMBOL(op)->type);
        if (offset >= size)
            return NULL;

        /* operand is already in the registers */
        if (OP_SYMBOL(op)->regs[offset] != NULL && OP_SYMBOL(op)->regs[offset]->rIdx < pblaze_nRegs) {
            rs = OP_SYMBOL(op)->regs[offset];
            return rs;
        }
        // operand is in the memory
        else if ((mem = isOffsetInMem(op, offset)) != NULL) {

            // get a register for the operand
            if (mem->isOnlyInMem)
                rtmp = getTempReg();
            else {
                rtmp = getRegOper(ic, op, offset);
                rtmp->ptrOffset = mem->ptrOffset;
            }

            // no free registers, make this offset being pernament in the memory
            if (rtmp->rIdx >= pblaze_nRegs && !IS_OP_GLOBALVOLATILE(op)) {
                mem->isOnlyInMem = 1;
                OP_SYMBOL(op)->regs[offset] = rtmp;
            }

            if (mem->isOnlyInMem == 0) {
                rtmp->isFree = 0;
                rtmp->currOper = op;
                rtmp->offset = offset;

                OP_SYMBOL(op)->regs[offset] = rtmp;
            }
            // load operand from the memory into registers
            if (((ic->prev || ic->next)))
                emitFetch(rtmp->name, mem->addr);

            // clear memory, if its a temporary variable
            //if( !IS_OP_GLOBAL(op) )  IS_ITEMP(op) && OP_LIVETO(op) != 0
            if (!IS_OP_GLOBAL(op) && OP_LIVETO(op) != 0 && mem->isOnlyInMem == 0)
                freeOffsetFromMem(op, offset);

            return rtmp;
        }
        // not in registers or the memory
        else {
            rtmp = getRegOper(ic, op, offset);

            // enought free registers
            if (rtmp->rIdx < pblaze_nRegs) {
                rtmp->isFree = 0;
                rtmp->currOper = op;
                rtmp->offset = offset;
                rtmp->ptrOffset = 0;

                OP_SYMBOL(op)->regs[offset] = rtmp;
                OP_SYMBOL(op)->nRegs = size;

            }
            // not enought free registers - use memory for storing the operand
            else {
                mem = firstFreeMem();
                if (!mem) {
                    fprintf(stderr, "%s:%d: pblaze port error: not enough memory\n", __FILE__, __LINE__);
                    exit(1);
                }

                OP_SYMBOL(op)->nRegs = size;
                OP_SYMBOL(op)->regs[offset] = rtmp;
                mem->currOper = op;
                mem->offset = offset;
                mem->ptrOffset = 0;
                mem->isOnlyInMem = 1;
                mem->isFree = 0;
                mem->isGlobal = IS_OP_GLOBAL(op);

                mtmp = isOffsetInMem(op, offset + 1);
                mem->nextPart = mtmp == NULL ? -1 : mtmp->addr;
                mtmp = isOffsetInMem(op, offset - 1);
                if (mtmp)
                    mtmp->nextPart = mem->addr;

            }

            rs = rtmp;
            return rs;
        }
    }
    return NULL;
}

/*-----------------------------------------------------------------*/
/* aopGetRegName - assign an operand's offset into registers       */
/*             if necessary and returns that register's name       */
/*-----------------------------------------------------------------*/
char *aopGetRegName(iCode * ic, operand * op, int offset)
{
    regs *rs;
    rs = aopGetReg(ic, op, offset);
    return rs != NULL ? rs->name : NULL;
}

/*-----------------------------------------------------------------*/
/* aopUpdateOpInMeme - save value of operand which is pernamently  */
/*             in the memory (due to no free registers )           */
/*-----------------------------------------------------------------*/
void aopUpdateOpInMem(iCode * ic, operand * op, int offset)
{
    memMap *mem;

    mem = isOffsetInMem(op, offset);

    if (mem && mem->isOnlyInMem == 1 && OP_SYMBOL(op) && OP_SYMBOL(op)->regs[offset] != NULL
        && !IS_OP_GLOBALVOLATILE(op)) {
        emitStore(OP_SYMBOL(op)->regs[offset]->name, mem->addr);
        OP_SYMBOL(op)->regs[offset] = NULL;
    }
}

/*-----------------------------------------------------------------*/
/* aopMoveReg - move register to an operand                        */
/*-----------------------------------------------------------------*/
void aopMoveReg(iCode * ic, operand * result, regs * rFrom, int offset)
{
    memMap *mem;
    regs *reg;

    if (result->type == SYMBOL) {
        if (rFrom->rIdx >= pblaze_nRegs) {
            mem = isOffsetInMem(result, offset);

            if ((mem && mem->isOnlyInMem == 1) || (mem && !isOffsetInReg(result, offset))) {
                emitStore(rFrom->name, mem->addr);
            } else {
                reg = aopGetReg(ic, result, offset);
                if (reg->rIdx >= pblaze_nRegs) {
                    emitLoad(reg->name, rFrom->name);
                    aopUpdateOpInMem(ic, result, offset);
                } else {
                    emitLoad(reg->name, rFrom->name);
                }

            }
        } else {
            if (rFrom->currOper && IS_SYMOP(rFrom->currOper))
                OP_SYMBOL(rFrom->currOper)->regs[rFrom->offset] = NULL;

            mem = isOffsetInMem(result, offset);
            if (mem && mem->isOnlyInMem == 1) {
                emitStore(rFrom->name, mem->addr);
            } else {
                rFrom->isFree = 0;
                rFrom->currOper = result;
                rFrom->offset = offset;
                rFrom->ptrOffset = 0;

                OP_SYMBOL(result)->regs[offset] = rFrom;
            }
        }
    }
}

/*-----------------------------------------------------------------*/
/* aopPutReg                                                       */
/*-----------------------------------------------------------------*/
void aopPutReg(iCode * ic, operand * result, regs * rFrom, int offset)
{
    regs *res;
    memMap *mem;

    if (result->type == SYMBOL) {

        if (IS_OP_GLOBALVOLATILE(result) || (result->isaddr && LOCAL_POINTER)) {
            mem = isOffsetInMem(result, offset);
            if (mem)
                emitStore(rFrom->name, mem->addr);
            else
                fprintf(stderr, "%s:%d: pblaze port warning: operand %s is not in the memory\n", __FILE__, __LINE__,
                        OP_SYMBOL(result)->name);
        }

        else if (IS_OP_GLOBAL(result)) {
            lockReg(rFrom);
            mem = isOffsetInMem(result, offset);
            if (mem && mem->isOnlyInMem == 1) {
                emitStore(rFrom->name, mem->addr);
                return;
            }

            res = aopGetReg(ic, result, offset);
            if (res->rIdx >= pblaze_nRegs && mem) {
                emitStore(rFrom->name, mem->addr);
            } else
                emitLoad(res->name, rFrom->name);
            unlockReg(rFrom);
        }
        /* result is a pointer into memory */
        else if (POINTER_SET(ic)) {
            if(isInOutRef(result)) {
                pblaze_emitcodeOutput(ic, rFrom->name, result);
            }
            else {
                res = aopGetReg(ic, result, 0);

                /* move value into a pointed memory */
                emitStoreReg(rFrom->name, res->name);
                res->ptrOffset = offset;
            }
        }
        /* normal operation */
        else {
            /* temporarly source register (unassigned to any operand) */
            if (rFrom->isReserved == 1 && SEND_REG_FIRST > rFrom->rIdx && !rFrom->currOper) {
                aopMoveReg(ic, result, rFrom, offset);
            } else {
                res = aopGetReg(ic, result, offset);
                mem = isOffsetInMem(result, offset);
                /* operand only in memory */
                if (mem && mem->isOnlyInMem && rFrom->rIdx >= pblaze_nRegs) {
                    emitStore(rFrom->name, mem->addr);
                }
                /* normal operation */
                else {
                    if (strcmp(res->name, rFrom->name) != 0)
                        emitLoad(res->name, rFrom->name);
                    aopUpdateOpInMem(ic, result, offset);
                }
            }
        }
    }
}

/*-----------------------------------------------------------------*/
/* aopPutVal                                                      */
/*-----------------------------------------------------------------*/
void aopPutVal(iCode * ic, operand * result, char *val, int offset)
{
    regs *rtmp, *res;
    memMap *mem;

    if (result->type == SYMBOL) {

        if (IS_OP_GLOBALVOLATILE(result) || (result->isaddr && LOCAL_POINTER)) {
            mem = isOffsetInMem(result, offset);
            if (mem) {
                rtmp = getReg(ic);
                lockReg(rtmp);
                emitLoad(rtmp->name, val);
                emitStore(rtmp->name, mem->addr);
                unlockReg(rtmp);
            } else
                fprintf(stderr, "%s:%d: pblaze port warning: operand %s is not in the memory\n", __FILE__, __LINE__,
                        OP_SYMBOL(result)->name);
        }

        else if (IS_OP_GLOBAL(result)) {
            res = aopGetReg(ic, result, offset);
            emitLoad(res->name, val);

            if (res->rIdx >= pblaze_nRegs) {
                mem = isOffsetInMem(result, offset);
                if (mem && mem->isOnlyInMem == 1) {
                    emitStore(res->name, mem->addr);
                }
            }

        }

        /* result is a pointer into memory */
        else if (POINTER_SET(ic)) {
            
            if(isInOutRef(result)) {
                rtmp = getReg(ic);
                emitLoad(rtmp->name, val);
                pblaze_emitcodeOutput(ic, rtmp->name, result);
            }
            else {
                res = aopGetReg(ic, result, 0);

                /* move value into a pointed memory */
                rtmp = getReg(ic);
                emitLoad(rtmp->name, val);
                emitStoreReg(rtmp->name, res->name);
                res->ptrOffset = offset;
            }
        }
        /* basic load into a register */
        else {
            res = aopGetReg(ic, result, offset);

            emitLoad(res->name, val);
            aopUpdateOpInMem(ic, result, offset);
        }

    }
    //Safe_free(val);
}

/*-----------------------------------------------------------------*/
/* findAndAllocGlobals - alloc memory for global variables         */
/*-----------------------------------------------------------------*/
static void findAndAllocGlobals(iCode * lic)
{
    iCode *ic;
    operand *op;

    if (!lic)
        return;

    for (ic = lic; ic; ic = ic->next) {
        if (!SKIP_NO_OP(ic)) {

            if (IC_LEFT(ic) && (IS_OP_GLOBAL(IC_LEFT(ic)))) {
                op = IC_LEFT(ic);;
                if (!IS_FUNC(OP_SYM_TYPE(op)) && !isOpInMem(op))
                    allocOpInMem(op);
            }

            if (IC_RIGHT(ic) && (IS_OP_GLOBAL(IC_RIGHT(ic)))) {
                op = IC_RIGHT(ic);
                if (!IS_FUNC(OP_SYM_TYPE(op)) && !isOpInMem(op))
                    allocOpInMem(op);
            }

            if (IC_RESULT(ic) && (IS_OP_GLOBAL(IC_RESULT(ic)))) {
                op = IC_RESULT(ic);
                if (!IS_FUNC(OP_SYM_TYPE(op)) && !isOpInMem(op))
                    allocOpInMem(op);
            }
        }
    }

}

/*-----------------------------------------------------------------*/
/* findIndirectOperands - alloc memory for arrays or pointed operands*/
/*-----------------------------------------------------------------*/
static void findIndirectOperands(iCode * lic)
{
    iCode *ic;
    operand *op;

    if (!lic)
        return;

    for (ic = lic; ic; ic = ic->next) {

        if (!SKIP_NO_OP(ic)) {

            // indirect address
            if (IC_RESULT(ic) && IC_RESULT(ic)->isaddr && !IS_OP_GLOBAL(IC_RESULT(ic)) &&
                !isOpVolatile(IC_RESULT(ic)) && OP_LIVEFROM(IC_RESULT(ic)) == 0 && OP_LIVETO(IC_RESULT(ic)) == 0) {
                op = IC_RESULT(ic);
                if (!IS_FUNC(OP_SYM_TYPE(op)) && !isOpInMem(op))
                    allocOpInMem(op);
            }

            if (IC_LEFT(ic) && IS_SYMOP(IC_LEFT(ic)) && !isOpVolatile(IC_LEFT(ic)) &&
                (IS_ARRAY(OP_SYM_TYPE(IC_LEFT(ic))) || IS_STRUCT(OP_SYM_TYPE(IC_LEFT(ic)))
                 || IS_TYPEDEF(OP_SYM_TYPE(IC_LEFT(ic))) || (IC_LEFT(ic)->isaddr && !IS_ITEMP(IC_LEFT(ic))))) {
                op = IC_LEFT(ic);
                if (!IS_FUNC(OP_SYM_TYPE(op)) && !isOpInMem(op))
                    allocOpInMem(op);

            }
        }
    }

}

/*-----------------------------------------------------------------*/
/* pblaze_genCodeLoop                                              */
/*-----------------------------------------------------------------*/
void pblaze_genCodeLoop(void)
{
    ebbIndex *ebbi;
    eBBlock **ebbs;
    int count;
    iCode *ic;

    _G_glueCalled = 1;
    pblaze_interrupt = NULL;

    if (_G_codeSet) {

        // optimalization phase
        for (ebbi = setFirstItem(_G_codeSet); ebbi; ebbi = setNextItem(_G_codeSet)) {
            ebbs = ebbi->bbOrder;
            count = ebbi->count;

            /* now get back the chain */
            //ic = iCodeLabelOptimize (iCodeFromeBBlock (ebbs, count));
            ic = iCodeFromeBBlock(ebbs, count);
            findAndAllocGlobals(ic);
        }

        // code generation phase
        for (ebbi = setFirstItem(_G_codeSet); ebbi; ebbi = setNextItem(_G_codeSet)) {
            ebbs = ebbi->bbOrder;
            count = ebbi->count;

            setToNull((void *) &_G.funcrUsed);
            /* now get back the chain */
            ic = iCodeFromeBBlock(ebbs, count);

            findIndirectOperands(ic);
            //resetRegs ();

            genPBLAZECode(ic);
            resetRegs();
        }
    }

}



/*-----------------------------------------------------------------*/
/* assignRegisters                                                 */
/*-----------------------------------------------------------------*/
void pblaze_assignRegisters(ebbIndex * ebbi)
{
    eBBlock **ebbs = ebbi->bbOrder;
    int count = ebbi->count;
    iCode *ic;

    if (gInit == 0) {
        gInit = 1;
        initPBLAZEMem();
    }
    //doOverlays (ebbs, count);
    //iCodeLabelOptimize(iCodeFromeBBlock (ebbs, count) );

    if (!_G_glueCalled) {
        addSet(&_G_codeSet, ebbi);

    } else {


        setToNull((void *) &_G.funcrUsed);

        /* now get back the chain */
        //ic = iCodeLabelOptimize (iCodeFromeBBlock (ebbs, count));
        ic = iCodeFromeBBlock(ebbs, count);

        //findAndAllocGlobals(ic);

        genPBLAZECode(ic);
    }
    return;
}
