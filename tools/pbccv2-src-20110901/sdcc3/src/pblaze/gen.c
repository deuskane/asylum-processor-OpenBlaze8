/*-------------------------------------------------------------------------
gen.c - source file for code generation for XILINX PICOBLAZE

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

#define D(x) do if (options.verboseAsm) {x;} while(0)
#define LBL_KEY(x) x->key+100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SDCCglobl.h"
#include "newalloc.h"

#include "common.h"
#include "SDCCpeeph.h"
#include "ralloc.h"
#include "gen.h"

static struct {
    short onStack;
    short inLine;
    short debugLine;
    short isCalleSaves;
    short ptrOff;
    set *sendSet;
    set *inOutSet;
    bitVect *rUsedVect;
    iCode *current_iCode;
} _G;


static struct {
    short mschar;
    short muschar;
    short mint;
    short mlong;
    short dschar;
    short duschar;
    short modschar;
    short moduschar;
    short dsint;
    short dusint;
    short modsint;
    short modusint;
    short dslong;
    short duslong;
    short modslong;
    short moduslong;
} _GFunc;

extern int allocInfo;
extern int pblaze_ptrRegReq;
extern int pblaze_nRegs;
extern struct dbuf_s *codeOutBuf;

/* function return value registers - shared with send/receive */
char *fReturnPBLAZE[] = { "sB", "sC", "sD", "sE" };

unsigned fPBLAZEReturnSize = 4; /* shared with ralloc.c */
char **fPBLAZEReturn = fReturnPBLAZE;
char buffValP[64];
char *buffVal = buffValP;

static lineNode *lineHead = NULL;
static lineNode *lineCurr = NULL;

static int recvCnt = 0;
short initGen = 0;

/*-----------------------------------------------------------------*/
/* pblaze_emitcode - writes the code into a file                   */
/*-----------------------------------------------------------------*/
static void pblaze_emitcode(char *inst, char *fmt, ...)
{
    va_list ap;
    char lb[INITIAL_INLINEASM];
    char *lbp = lb;

    va_start(ap, fmt);

    if (inst && *inst) {
        if (fmt && *fmt)
            sprintf(lb, "%s\t", inst);
        else
            sprintf(lb, "%s", inst);
        vsprintf(lb + (strlen(lb)), fmt, ap);
    } else
        vsprintf(lb, fmt, ap);

    while (isspace((unsigned char) *lbp))
        lbp++;

    if (lbp && *lbp)
        lineCurr = (lineCurr ? connectLine(lineCurr, newLineNode(lb)) : (lineHead = newLineNode(lb)));
    lineCurr->isInline = _G.inLine;
    lineCurr->isDebug = _G.debugLine;
    lineCurr->ic = _G.current_iCode;
    va_end(ap);
}

/*-----------------------------------------------------------------*/
/* dialectNum-convert a number to a string with the correct dialect */
/*-----------------------------------------------------------------*/
char *dialectNum(int num)
{
    char *s = buffVal;
    sprintf(s, "%s%02x", pblaze_options.dialect ? "" : "$", num);
    return Safe_strdup(s);
}


/*-----------------------------------------------------------------*/
/* addInOutRef - mark oper as IN/OUT pointer with given offset     */
/*-----------------------------------------------------------------*/
void addInOutRef(operand * oper, operand * offset)
{
    unsigned long lit = 0L;
    inOutStruct_t *tmpInOut = Safe_alloc(sizeof(inOutStruct_t));

    tmpInOut->name = Safe_strdup(OP_SYMBOL(oper)->name);
    tmpInOut->tempOper = oper;
    tmpInOut->liveFrom = OP_LIVEFROM(oper);
    tmpInOut->liveTo = OP_LIVETO(oper);

    if (!offset) {
        tmpInOut->isNumOffset = 1;
        tmpInOut->regOffset = NULL;
        tmpInOut->numOffset = 0L;

    } else if (isOperandLiteral(offset)) {
        lit = ulFromVal(OP_VALUE(offset));
        tmpInOut->isNumOffset = 1;
        tmpInOut->regOffset = NULL;
        tmpInOut->numOffset = lit;
    } else {
        tmpInOut->isNumOffset = 0;
        tmpInOut->regOffset = offset;
    }
    addSet(&_G.inOutSet, tmpInOut);
}

/*-----------------------------------------------------------------*/
/* isInOutRef - test if the given operand is a IN/OUT pointer      */
/*-----------------------------------------------------------------*/
int isInOutRef(operand * oper)
{
    char *name = OP_SYMBOL(oper)->name;
    if (strcmp(pblaze_options.portKw, name) == 0)
        return 1;

    set *lp;

    for (lp = _G.inOutSet; lp; lp = lp->next) {
        inOutStruct_t *p = lp->item;
        if (strcmp(p->name, name) == 0)
            return 1;
    }
    return 0;
}

/*-----------------------------------------------------------------*/
/* getInOutRef - return io struct of the given operand             */
/*-----------------------------------------------------------------*/
inOutStruct_t *getInOutRef(operand * oper)
{
    char *name = OP_SYMBOL(oper)->name;
    set *lp;

    for (lp = _G.inOutSet; lp; lp = lp->next) {
        inOutStruct_t *p = lp->item;
        if (strcmp(p->name, name) == 0)
            break;
    }
    if (!lp)
        return NULL;

    return lp->item;
}

/*-------------------------------------------------------------------------*/
/* pblaze_emitcodeOutput - emit OUTPUT instruction with given params       */
/*-------------------------------------------------------------------------*/
void pblaze_emitcodeOutputNum(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("OUTPUT", "%s, %s", l, r);
    else
        pblaze_emitcode("OUT", "%s, %s", l, r);
}

/*-------------------------------------------------------------------------*/
/* pblaze_emitcodeOutput - emit OUTPUT instruction with given params       */
/*-------------------------------------------------------------------------*/
void pblaze_emitcodeOutputReg(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("OUTPUT", "%s, (%s)", l, r);
    else
        pblaze_emitcode("OUT", "%s, %s", l, r);
}

/*-------------------------------------------------------------------------*/
/* pblaze_emitcodeOutput - emit OUTPUT instruction with given params       */
/*-------------------------------------------------------------------------*/
void pblaze_emitcodeOutput(iCode * ic, char *source, operand * to)
{
    inOutStruct_t *tmp;
    tmp = getInOutRef(to);

    if (!tmp) {
        return;
    } else if (tmp->isNumOffset) {
        pblaze_emitcodeOutputNum(source, dialectNum((int) tmp->numOffset));
    } else {
        pblaze_emitcodeOutputReg(source, aopGetRegName(ic, tmp->regOffset, 0));
    }
}

/*-------------------------------------------------------------------------*/
/* pblaze_emitcodeInputNum - emit INPUT instruction with given params      */
/*-------------------------------------------------------------------------*/
void pblaze_emitcodeInputNum(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("INPUT", "%s, %s", l, r);
    else
        pblaze_emitcode("IN", "%s, %s", l, r);
}

/*-------------------------------------------------------------------------*/
/* pblaze_emitcodeInputReg - emit INPUT instruction with given params      */
/*-------------------------------------------------------------------------*/
void pblaze_emitcodeInputReg(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("INPUT", "%s, (%s)", l, r);
    else
        pblaze_emitcode("IN", "%s, %s", l, r);
}

/*-----------------------------------------------------------------*/
/* pblaze_emitcodeInput - emit INPUT instruction with given params */
/*-----------------------------------------------------------------*/
void pblaze_emitcodeInput(iCode * ic, operand * result, int resOffset, operand * from)
{
    inOutStruct_t *tmp;
    tmp = getInOutRef(from);

    if (!tmp) {
        return;
    } else if (tmp->isNumOffset) {
        pblaze_emitcodeInputNum(aopGetRegName(ic, result, resOffset), dialectNum((int) tmp->numOffset));
    } else {
        pblaze_emitcodeInputReg(aopGetRegName(ic, result, resOffset), aopGetRegName(ic, tmp->regOffset, 0));
    }
}


/*-----------------------------------------------------------------*/
/* emit functions                                                  */
/*-----------------------------------------------------------------*/
void pblaze_emitLabel(symbol * tlbl)
{
    pblaze_emitcode("", "_L%05d:", LBL_KEY(tlbl));
    lineCurr->isLabel = 1;
}

void pblaze_emitLabelC(symbol * tlbl)
{
    pblaze_emitcode("", "_LC%05d:", LBL_KEY(tlbl));
    lineCurr->isLabel = 1;
}

void pblaze_emitcodeADDCY(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("ADDCY", "%s, %s", l, r);
    else
        pblaze_emitcode("ADDC", "%s, %s", l, r);
}

void pblaze_emitcodeSUBCY(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("SUBCY", "%s, %s", l, r);
    else
        pblaze_emitcode("SUBC", "%s, %s", l, r);
}

void pblaze_emitcodeCompare(char *l, char *r)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("COMPARE", "%s, %s", l, r);
    else
        pblaze_emitcode("COMP", "%s, %s", l, r);
}

void pblaze_emitcodeStore(char *l, char *r)
{
    if (pblaze_options.dialect && r[0] == 's')
        pblaze_emitcode("STORE", "%s, (%s)", l, r);
    else
        pblaze_emitcode("STORE", "%s, %s", l, r);
}

void pblaze_emitcodeFetch(char *l, char *r)
{
    if (pblaze_options.dialect && r[0] == 's')
        pblaze_emitcode("FETCH", "%s, (%s)", l, r);
    else
        pblaze_emitcode("FETCH", "%s, %s", l, r);
}

/*-----------------------------------------------------------------*/
/* isOpVolatile - test if operand is volatile                      */
/*-----------------------------------------------------------------*/
int isOpVolatile(operand * oper)
{
    sym_link *type, *search;
    if (!oper || oper->type != SYMBOL || OP_LIVETO(oper) != 0)
        return 0;

    if (operandType(oper)) {
        for (type = operandType(oper); type && type->next; type = type->next);

        while (type) {

            if (IS_DECL(type) && DCL_PTR_VOLATILE(type))
                return 2;

            else if (!IS_DECL(type) && SPEC_VOLATILE(type))
                return 1;

            for (search = operandType(oper); search && search->next != type;)
                search = search->next;
            type = search;
        }

    }
    return 0;
}

// debug, test
void testOp(operand * oper)
{
    if (isOperandLiteral(oper)) {
        return;
    }
    printf("%s, rname:%s\t", OP_SYMBOL(oper)->name, OP_SYMBOL(oper)->rname);
    if (IS_OP_VOLATILE(oper)) {
        printf(" volatile, ");
    }

    if (oper->isaddr) {
        printf(" adress, ");
    }

    if (IS_OP_GLOBAL(oper)) {
        printf(" global, ");
    }

    if (IS_OP_POINTER(oper)) {
        printf(" pointer, ");
    }

    if (IS_OP_PARM(oper)) {
        printf(" parm, ");
    }

    if (IS_ITEMP(oper)) {
        printf(" itemp, ");
    }

    if (IS_PTR(OP_SYMBOL(oper)->type)) {
        printf(" is_ptr, ");
    }

    if (IS_VOLATILE(OP_SYMBOL(oper)->type)) {
        printf(" is_volatile, ");
    }

    if (IS_CODE(OP_SYMBOL(oper)->type)) {
        printf(" is_code, ");
    }

    if (IS_ABSOLUTE(OP_SYMBOL(oper)->type)) {
        printf(" is_absolute, ");
    }

    if (IS_REGISTER(OP_SYMBOL(oper)->type)) {
        printf(" is_register, ");
    }

    if (IS_STATIC(OP_SYMBOL(oper)->type)) {
        printf(" is_static, ");
    }

    if (IS_SYMOP(oper) && IS_ARRAY(OP_SYM_TYPE(oper))) {
        printf(" is_array, ");
    }

    if (IS_SYMOP(oper) && IS_STRUCT(OP_SYM_TYPE(oper))) {
        printf(" is_struct, ");
    }

    if (IS_SYMOP(oper) && IS_TYPEDEF(OP_SYM_TYPE(oper))) {
        printf(" is_typedef, ");
    }

    if (isOpVolatile(oper))
        printf(" isvolatile, ");

    printf("\n");

}


/*-----------------------------------------------------------------*/
/* pblaze_emitDebuggerSymbol - associate the current code location  */
/*   with a debugger symbol                                        */
/*-----------------------------------------------------------------*/
void pblaze_emitDebuggerSymbol(const char *debugSym)
{
    _G.debugLine = 1;
    pblaze_emitcode("", "%s ==.", debugSym);
    _G.debugLine = 0;
}


/*-----------------------------------------------------------------*/
/* valueOffset                                                     */
/*-----------------------------------------------------------------*/
unsigned int valueOffset(unsigned long lit, int offset)
{
    return ((lit >> (offset * 8)) & 0x0FFL);
}


/*-----------------------------------------------------------------*/
/* emit STORE and FETCH functions                                  */
/*-----------------------------------------------------------------*/
void emitStore(char *r, int mem)
{
    char *s;
    s = operName(mem);
    if (!s)
        pblaze_emitcode("STORE", "%s, %s%02x", r, pblaze_options.dialect ? "" : "$", mem);
    else
        pblaze_emitcode("STORE", "%s, %s", r, s);
}

void emitStoreReg(char *r, char *adr)
{
    if (pblaze_options.dialect)
        pblaze_emitcode("STORE", "%s, (%s)", r, adr);
    else
        pblaze_emitcode("STORE", "%s, %s", r, adr);
}

void emitFetch(char *r, int mem)
{
    char *s;
    s = operName(mem);
    if (!s)
        pblaze_emitcode("FETCH", "%s, %s%02x", r, pblaze_options.dialect ? "" : "$", mem);
    else
        pblaze_emitcode("FETCH", "%s, %s", r, s);
}

void emitLoadNumb(char *r, int val)
{
    pblaze_emitcode("LOAD", "%s, %s%02x", r, pblaze_options.dialect ? "" : "$", val);
}

void emitLoad(char *l, char *r)
{
    pblaze_emitcode("LOAD", "%s, %s", l, r);
}

void emitcodeADD(char *l, int val)
{
    pblaze_emitcode("ADD", "%s, %s%02x", l, pblaze_options.dialect ? "" : "$", val);
}

void emitcodeSUB(char *l, int val)
{
    pblaze_emitcode("SUB", "%s, %s%02x", l, pblaze_options.dialect ? "" : "$", val);
}



/*-----------------------------------------------------------------*/
/* bitVect functions                                               */
/*-----------------------------------------------------------------*/
void setRegUsed(int r)
{
    bitVectSetBit(_G.rUsedVect, r);
}

int isRegUsed(int r)
{
    return bitVectBitValue(_G.rUsedVect, r);
}

void clearBitVect(bitVect * bv)
{
    int i;
    for (i = 0; i < bv->size; i++)
        bitVectUnSetBit(bv, i);
}

short isCalleesaves(void)
{
    return _G.isCalleSaves;
}





/*-----------------------------------------------------------------*/
/* Push given register onto the stack                              */
/*-----------------------------------------------------------------*/
void pushStack(int rdx, int c)
{
    regs *rStack;
    rStack = pblaze_regWithIdx(rdx);
    pblaze_emitcodeStore(rStack->name, "sF");
    pblaze_emitcode("SUB", "sF, %s", dialectNum(1));

    _G.onStack++;

    staticMemoryCheck(MEMSIZE - _G.onStack - 1);
}

/*-----------------------------------------------------------------*/
/* Pop top of the the stack into given register                    */
/*-----------------------------------------------------------------*/
void popStack(int rdx, int c)
{
    regs *rStack;
    rStack = pblaze_regWithIdx(rdx);

    pblaze_emitcode("ADD", "sF, %s", dialectNum(1));
    pblaze_emitcodeFetch(rStack->name, "sF");

    _G.onStack--;
    staticMemoryCheck(MEMSIZE - _G.onStack - 1);
}


/*-----------------------------------------------------------------*/
/* regsInCommon - two operands have some registers in common       */
/*-----------------------------------------------------------------*/
static bool regsInCommon(operand * op1, operand * op2)
{
    symbol *sym1, *sym2;
    int i;

    /* if they have registers in common */
    if (!IS_SYMOP(op1) || !IS_SYMOP(op2))
        return FALSE;

    sym1 = OP_SYMBOL(op1);
    sym2 = OP_SYMBOL(op2);

    if (sym1->nRegs == 0 || sym2->nRegs == 0)
        return FALSE;

    for (i = 0; i < sym1->nRegs; i++) {
        int j;
        if (!sym1->regs[i])
            continue;

        for (j = 0; j < sym2->nRegs; j++) {
            if (!sym2->regs[j])
                continue;

            if (sym2->regs[j] == sym1->regs[i])
                return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------*/
/* pblaze_operandsEqu - equivalent                                        */
/*-----------------------------------------------------------------*/
bool pblaze_operandsEqu(operand * op1, operand * op2)
{
    symbol *sym1, *sym2;

    /* if they not symbols */
    if (!IS_SYMOP(op1) || !IS_SYMOP(op2))
        return FALSE;

    sym1 = OP_SYMBOL(op1);
    sym2 = OP_SYMBOL(op2);

    /* if they are the same */
    if (sym1 == sym2)
        return TRUE;

    if (strcmp(sym1->rname, sym2->rname) == 0)
        return TRUE;


    /* if left is a tmp & right is not */
    if (IS_ITEMP(op1) && !IS_ITEMP(op2) && sym1->isspilt && (sym1->usl.spillLoc == sym2))
        return TRUE;

    if (IS_ITEMP(op2) && !IS_ITEMP(op1) && sym2->isspilt && sym1->level > 0 && (sym2->usl.spillLoc == sym1))
        return TRUE;

    return FALSE;
}

/*-----------------------------------------------------------------*/
/* pointerSetOpt - optimization of assigning a value via a pointer */
/*-----------------------------------------------------------------*/
int pointerSetOpt(iCode * ic, int currOffset)
{
    iCode *aic, *pic, *lic;
    int pOffset, nOffset;

    if (!POINTER_SET(ic))
        return 0;

    if (!ic->next || !ic->next->next || !ic->prev)
        return 0;

    aic = ic->next;
    pic = aic->next;
    lic = ic->prev;

    /* previous offset of the pointer */
    if (pblaze_operandsEqu(IC_RESULT(ic), IC_RESULT(lic)) && OP_LIVETO(IC_RESULT(ic)) == ic->seq) {
        if (lic->op == '+' && isOperandLiteral(IC_RIGHT(lic))) {
            pOffset = (int) ulFromVal(OP_VALUE(IC_RIGHT(lic)));
        } else if (lic->op == ADDRESS_OF)
            pOffset = 0;
        else
            return 0;
    } else
        return 0;

    /* next offset of the pointer */
    if (aic->op == '+' && POINTER_SET(pic) && pblaze_operandsEqu(IC_RESULT(aic), IC_RESULT(pic))
        && OP_LIVETO(IC_RESULT(pic)) == ic->seq + 2) {
        if (isOperandLiteral(IC_RIGHT(aic))) {
            nOffset = (int) ulFromVal(OP_VALUE(IC_RIGHT(aic)));
        } else
            return 0;
    } else
        return 0;

    /* set pointer to the correct location */
    assignOpt(ic, IC_RESULT(aic), IC_RESULT(ic));
    pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, IC_RESULT(aic), 0), dialectNum(nOffset - pOffset - currOffset));
    aopUpdateOpInMem(ic, IC_RESULT(aic), 0);
    /* set next ADD instruction as generated */
    aic->generated = 1;

    return 1;
}

/*-----------------------------------------------------------------*/
/* Copy registers                                                  */
/*-----------------------------------------------------------------*/
void copyRegisters(iCode * ic, operand * opTo, operand * opFrom, int rFrom, int rTo)
{
    int i;
    int sizeT = getSize(operandType(opTo));

    for (i = rFrom; i <= rTo; i++) {
        aopPutReg(ic, opTo, aopGetReg(ic, opFrom, i), i);
    }
    for (; i < sizeT; i++) {
        aopPutVal(ic, opTo, dialectNum(0), i);
    }
}

/*-----------------------------------------------------------------*/
/* pblaze_assignResultValue -                                             */
/*-----------------------------------------------------------------*/
void pblaze_assignResultValue(iCode * ic, operand * oper)
{
    int i = 0;
    int size = getSize(operandType(oper));
    while (size--) {
        aopPutVal(ic, oper, fPBLAZEReturn[i], i);
        i++;
    }
}

/*-----------------------------------------------------------------*/
/* assignLiteral -                                             */
/*-----------------------------------------------------------------*/
void assignLiteral(operand * result, operand * literal, iCode * ic)
{
    int size, sizeR;
    unsigned long lit = 0L;
    int i;

    /* is a literal value */
    if (isOperandLiteral(literal)) {
        /* get value and size */
        lit = ulFromVal(OP_VALUE(literal));
        size = getSize(operandType(literal));
        sizeR = getSize(operandType(result));
        //size = sizeR > size ? size : sizeR;     

        if (IS_OP_GLOBAL(result)) {
            for (i = 0; i < size; i++) {
                aopPutVal(ic, result, dialectNum(valueOffset(lit, i)), i);
            }
        }

        else if (POINTER_SET(ic)) {

            if(isInOutRef(result) ){
                aopPutVal(ic, result, dialectNum(valueOffset(lit, 0)), 0);
                return;
            }
        
            for (i = 0; i < size; i++) {
                aopPutVal(ic, result, dialectNum(valueOffset(lit, size - i - 1)), i);

                if (i + 1 < size) {
                    pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));
                    aopUpdateOpInMem(ic, result, 0);
                }
            }
            /* pointer will be used later, return to the begining */
            if (!pointerSetOpt(ic, size - 1) && size > 1 && OP_LIVETO(result) > ic->seq) {
                pblaze_emitcode("SUB", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(size - 1));
                aopUpdateOpInMem(ic, result, 0);
            }
        } else {
            for (i = 0; i < size; i++) {
                aopPutVal(ic, result, dialectNum(valueOffset(lit, i)), i);
            }
        }
    }

}


/*-----------------------------------------------------------------*/
/* assignLiteralRegs -                                             */
/*-----------------------------------------------------------------*/
void assignLiteralRegs(int size, char **regs, operand * literal)
{
    unsigned long lit = 0L;
    int i;

    /* is a literal value */
    if (isOperandLiteral(literal)) {

        /* get value and size */
        lit = ulFromVal(OP_VALUE(literal));

        for (i = size - 1; i >= 0; i--) {
            pblaze_emitcode("LOAD", "%s, %s", regs[i], dialectNum(valueOffset(lit, i)));
        }
    }
}



/*-----------------------------------------------------------------*/
/* toBoolean - emit code for comparision                           */
/*-----------------------------------------------------------------*/
regs *toBoolean(iCode * ic, operand * oper)
{
    int size = getSize(operandType(oper));
    int offset = 1;
    regs *r;

    if (size == 1) {
        return aopGetReg(ic, oper, 0);
    }

    else {
        r = getReg(ic);
        lockReg(r);
        pblaze_emitcode("LOAD", "%s, %s", r->name, aopGetRegName(ic, oper, 0));

        while (--size) {
            pblaze_emitcode("OR", "%s, %s", r->name, aopGetRegName(ic, oper, offset));
            offset++;
        }
        unlockReg(r);
    }
    return r;
}

/*-----------------------------------------------------------------*/
/* genNot - generate code for ! operation                          */
/*-----------------------------------------------------------------*/
static void genNot(iCode * ic)
{
    operand *result, *left;
    regs *r;
    D(pblaze_emitcode(";", "genNot"));

    symbol *lbl = newiTempLabel(NULL);

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);

    /* fill the result with zeros */
    aopPutVal(ic, result, dialectNum(0), 0);

    r = toBoolean(ic, left);
    pblaze_emitcodeCompare(r->name, dialectNum(0));
    pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lbl));
    aopPutVal(ic, result, dialectNum(1), 0);
    pblaze_emitLabelC(lbl);
}




/*-----------------------------------------------------------------*/
/* genCpl - generate code for complement                           */
/*-----------------------------------------------------------------*/
static void genCpl(iCode * ic)
{
    int offset = 0;
    int size;
    operand *result, *left;

    D(pblaze_emitcode(";", "genCpl"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* the right symbol may ends at this position */
    if (ASSIGN_OPT(result, left) && assignOptTest(ic, IC_RESULT(ic))) {
        assignOpt(ic, result, left);
    } else {
        copyRegisters(ic, result, left, 0, size - 1);
    }

    while (size--) {
        pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, offset), dialectNum(255));
        aopUpdateOpInMem(ic, result, offset);
        offset++;
    }

}

/*-----------------------------------------------------------------*/
/* genUminus - unary minus code generation                         */
/*-----------------------------------------------------------------*/
static void genUminus(iCode * ic)
{
    operand *result, *left;
    int i, size;

    D(pblaze_emitcode(";", "genUminus"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* right symbol may ends at this position */
    if (ASSIGN_OPT(result, left) && assignOptTest(ic, IC_RESULT(ic))) {
        assignOpt(ic, result, left);
    } else {
        copyRegisters(ic, result, left, 0, size - 1);
    }

    /* invert bytes */
    for (i = 0; i < size; i++) {
        pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, i), dialectNum(255));
        aopUpdateOpInMem(ic, result, i);
    }

    /* add one */
    pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));
    aopUpdateOpInMem(ic, result, 0);
    for (i = 1; i < size; i++) {
        pblaze_emitcodeADDCY(aopGetRegName(ic, result, i), dialectNum(0));
        aopUpdateOpInMem(ic, result, i);
    }

}

/*-----------------------------------------------------------------*/
/* genIpush - genrate code for pushing                             */
/*-----------------------------------------------------------------*/
static void genIpush(iCode * ic)
{
    operand *left;
    int offset, size;
    unsigned long lit = 0L;
    regs *r;
    offset = 0;

    left = IC_LEFT(ic);
    size = getSize(operandType(left));

    D(pblaze_emitcode(";", "genIpush"));
    if (isOperandLiteral(left)) {

        /* get value */
        lit = ulFromVal(OP_VALUE(left));
        /* needs to be loaded into registers first -> get a free register */
        r = getReg(ic);

        while (size--) {
            /* first load into registers */
            pblaze_emitcode("LOAD", "%s, %s", r->name, dialectNum((unsigned int) ((lit >> (offset++ * 8)) & 0x0FFL)));
            /* push onto the stack */
            pushStack(r->rIdx, 1);
        }

    } else {

        while (size--) {
            pushStack(aopGetReg(ic, left, offset)->rIdx, 1);
            offset++;
        }
    }

}

/*-----------------------------------------------------------------*/
/* genIpop - recover the registers                                 */
/*-----------------------------------------------------------------*/
static void genIpop(iCode * ic)
{
    operand *left;
    int offset, size;

    left = IC_LEFT(ic);
    size = getSize(operandType(left));
    offset = size - 1;

    D(pblaze_emitcode(";", "genIpop"));

    if (isOperandLiteral(left)) {
        return;
    }

    while (size--) {
        popStack(aopGetReg(ic, left, offset)->rIdx, 1);
        offset--;
    }
}


/*-----------------------------------------------------------------*/
/* testFuncCall - check whether it should called the MUL or DIV func*/
/*-----------------------------------------------------------------*/
int testFuncCall(char *name)
{
    int start = S0_IDX;

    /* test if it is a mult or div function call */
    if (strcmp(name, MULUSCHAR) == 0) {
        _GFunc.muschar = 1;
        start = SB_IDX;
    } else if (strcmp(name, MULSCHAR) == 0) {
        _GFunc.mschar = 1;
        _GFunc.muschar = 1;
        start = SA_IDX;
    } else if (strcmp(name, MULINT) == 0) {
        _GFunc.mint = 1;
        start = S7_IDX;
    } else if (strcmp(name, MULLONG) == 0) {
        _GFunc.mlong = 1;
        start = S2_IDX;
    } else if (strcmp(name, DIVSCHAR) == 0) {
        _GFunc.dschar = 1;
        _GFunc.duschar = 1;
        start = SA_IDX;
    } else if (strcmp(name, DIVUSCHAR) == 0) {
        _GFunc.duschar = 1;
        start = SB_IDX;
    } else if (strcmp(name, DIVSINT) == 0) {
        _GFunc.dsint = 1;
        _GFunc.dusint = 1;
        start = S7_IDX;
    } else if (strcmp(name, DIVUSINT) == 0) {
        _GFunc.dusint = 1;
        start = S7_IDX;
    } else if (strcmp(name, DIVSLONG) == 0) {
        _GFunc.dslong = 1;
        _GFunc.duslong = 1;
        start = S2_IDX;
    } else if (strcmp(name, DIVUSLONG) == 0) {
        _GFunc.duslong = 1;
        start = S2_IDX;
    } else if (strcmp(name, MODSCHAR) == 0) {
        _GFunc.modschar = 1;
        _GFunc.dschar = 1;
        _GFunc.duschar = 1;
        start = SA_IDX;
    } else if (strcmp(name, MODUSCHAR) == 0) {
        _GFunc.moduschar = 1;
        _GFunc.duschar = 1;
        start = SB_IDX;
    } else if (strcmp(name, "_moduschar") == 0) {
        _GFunc.moduschar = 1;
        _GFunc.duschar = 1;
        start = SB_IDX;
    } else if (strcmp(name, MODSINT) == 0) {
        _GFunc.modsint = 1;
        _GFunc.dsint = 1;
        _GFunc.dusint = 1;
        start = S7_IDX;
    } else if (strcmp(name, MODUSINT) == 0) {
        _GFunc.modusint = 1;
        _GFunc.dusint = 1;
        start = S7_IDX;
    } else if (strcmp(name, MODSLONG) == 0) {
        _GFunc.modslong = 1;
        _GFunc.dslong = 1;
        _GFunc.duslong = 1;
        start = S2_IDX;
    } else if (strcmp(name, MODUSLONG) == 0) {
        _GFunc.moduslong = 1;
        _GFunc.duslong = 1;
        start = S2_IDX;
    }

    return start;
}

/*-----------------------------------------------------------------*/
/* genCall - generates a call statement                            */
/*-----------------------------------------------------------------*/
static void genCall(iCode * ic)
{
    int i, j;
    int size;
    regs *r;
    operand *sOp;
    iCode *sic;
    int rmax = SEND_REG_COUNT;
    int rfrst = SEND_REG_FIRST;
    int saveFrom;
    bitVect *rSaved;
    unsigned long lit = 0L;

    D(pblaze_emitcode(";", "genCall"));

    /* store globals. if changed */
    freeGlobalsFromReg();

    rSaved = newBitVect(pblaze_nRegs);

    /* test if its a multiply, div or mod call */
    saveFrom = testFuncCall(OP_SYMBOL(IC_LEFT(ic))->name);

    /* caller-saves, push used registers onto the stack */
    if (!_G.isCalleSaves && !IFFUNC_CALLEESAVES(OP_SYMBOL(IC_LEFT(ic))->type)) {
        for (i = S0_IDX; i <= SF_IDX; i++) {
            r = pblaze_regWithIdx(i);
            if (i >= saveFrom && r->isFree == 0 && r->isReserved == 0 && r->currOper
                && OP_LIVETO(r->currOper) > ic->seq) {
                pushStack(i, 1);
                // noted that the registers were moved to the stack
                bitVectSetBit(rSaved, i);
            } else if (i >= saveFrom && isOpVolatile(r->currOper) && !IS_OP_GLOBAL(r->currOper)) {
                pushStack(i, 1);
                bitVectSetBit(rSaved, i);
            } else
                bitVectUnSetBit(rSaved, i);
        }
    }
    /////////////////////////////////////////////////////

    /* if send set is not empty then assign */
    if (_G.sendSet) {
        D(pblaze_emitcode(";", "genSend"));
        _G.sendSet = reverseSet(_G.sendSet);
        // through all
        for (sic = setFirstItem(_G.sendSet); sic; sic = setNextItem(_G.sendSet)) {
            sOp = IC_LEFT(sic);
            size = getSize(operandType(sOp));

            // enough free registers for SEND
            if (size <= rmax) {
                rmax -= size;

                /* send operand is value */
                if (isOperandLiteral(sOp)) {
                    /* get value  */
                    lit = ulFromVal(OP_VALUE(sOp));
                    /* needs to be loaded into registers first */
                    for (j = 0; j < size; j++) {
                        pblaze_emitcode("LOAD", "%s, %s", pblaze_regWithIdx(rfrst)->name,
                                        dialectNum((unsigned int) ((lit >> ((j) * 8)) & 0x0FFL)));
                        rfrst++;
                    }
                }

                /* send operand is symbol */
                else {

                    for (i = 0; i < size; i++) {
                        pblaze_emitcode("LOAD", "%s, %s", pblaze_regWithIdx(rfrst)->name, aopGetRegName(sic, sOp, i));
                        rfrst++;
                    }
                }
                /* not enought free registers -> use stack */
            } else {
                /* send operand is value */
                if (isOperandLiteral(sOp)) {
                    regs *r;

                    /* get value */
                    lit = ulFromVal(OP_VALUE(sOp));
                    /* needs to be loaded into registers first -> get a free register */
                    r = getReg(ic);

                    for (j = 0; j < size; j++) {
                        /* first load into a register */
                        pblaze_emitcode("LOAD", "%s, %s", r->name,
                                        dialectNum((unsigned int) ((lit >> (j * 8)) & 0x0FFL)));
                        /* push onto the stack */
                        pushStack(r->rIdx, 1);
                    }
                }
                /* send operand is symbol */
                else {

                    for (i = 0; i < size; i++) {
                        /* push onto the stack */
                        if (aopGetReg(sic, sOp, i)) {
                            pushStack(OP_SYMBOL(sOp)->regs[i]->rIdx, 1);;
                        }
                    }

                }
                _G.onStack -= (size - 1);

            }
        }
        _G.sendSet = NULL;
    }
    ///////////////////////////////////////////////////////////////////

    /* make the call */
    pblaze_emitcode("CALL", "%s",
                    (OP_SYMBOL(IC_LEFT(ic))->rname[0] ? OP_SYMBOL(IC_LEFT(ic))->rname : OP_SYMBOL(IC_LEFT(ic))->name));

    /* test if it is a mult or div function call */
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MULUSCHAR) == 0)
        _GFunc.muschar = 1;
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MULSCHAR) == 0) {
        _GFunc.mschar = 1;
        _GFunc.muschar = 1;
    }
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MULINT) == 0)
        _GFunc.mint = 1;
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MULLONG) == 0)
        _GFunc.mlong = 1;

    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, DIVSCHAR) == 0) {
        _GFunc.dschar = 1;
        _GFunc.duschar = 1;
    }
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, DIVUSCHAR) == 0)
        _GFunc.duschar = 1;
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MODSCHAR) == 0) {
        _GFunc.modschar = 1;
        _GFunc.dschar = 1;
        _GFunc.duschar = 1;
    }
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, MODUSCHAR) == 0) {
        _GFunc.moduschar = 1;
        _GFunc.duschar = 1;
    }
    if (strcmp(OP_SYMBOL(IC_LEFT(ic))->name, "_moduschar") == 0) {
        _GFunc.moduschar = 1;
        _GFunc.duschar = 1;
    }

    /* pop used registers into the registers */
    if (!_G.isCalleSaves && !IFFUNC_CALLEESAVES(OP_SYMBOL(IC_LEFT(ic))->type)) {
        for (i = SF_IDX; i >= S0_IDX; i--) {
            r = pblaze_regWithIdx(i);
            if (bitVectBitValue(rSaved, i)) {
                popStack(i, 1);
            }
        }
    }

    /* if we need assign a result value */
    if (IS_ITEMP(IC_RESULT(ic)) && OP_SYMBOL(IC_RESULT(ic))->liveTo > ic->seq) {
        pblaze_assignResultValue(ic, IC_RESULT(ic));

    }

}

/*-----------------------------------------------------------------*/
/* genPcall - generates a call by pointer statement                */
/*-----------------------------------------------------------------*/
static void genPcall(iCode * ic)
{
    /* not easy to implement without access to the Instruction pointer */
    fprintf(stderr, "%s:%d: pblaze port error: function pointers are not supported\n", __FILE__, __LINE__);
    exit(1);
}


/*-----------------------------------------------------------------*/
/* genFunction - generated code for function entry                 */
/*-----------------------------------------------------------------*/
static void genFunction(iCode * ic)
{
    symbol *sym;
    sym_link *ftype;

    sym = OP_SYMBOL(IC_LEFT(ic));

    /* create the function header */
    D(pblaze_emitcode(";", "-----------------------------------------"));
    D(pblaze_emitcode(";", " function %s", sym->name));
    D(pblaze_emitcode(";", "-----------------------------------------"));

    pblaze_emitcode("", "%s:", sym->rname);
    lineCurr->isLabel = 1;
    ftype = operandType(IC_LEFT(ic));

    if (IFFUNC_CALLEESAVES(sym->type)) {
        _G.isCalleSaves = 1;
    }

    /* is an interrupt function */
    if (IFFUNC_ISISR(sym->type)) {

        if (!pblaze_interrupt)
            pblaze_interrupt = sym;
        else if (FUNC_INTNO(sym->type) > FUNC_INTNO(pblaze_interrupt->type))
            pblaze_interrupt = sym;

        _G.isCalleSaves = 1;
    }

    /* if critical function then turn interrupts off */
    if (IFFUNC_ISCRITICAL(ftype)) {
        if (pblaze_options.dialect) {
            pblaze_emitcode("DISABLE INTERRUPT", "");
        } else {
            pblaze_emitcode("DINT", "");
        }
    }
}

/*-----------------------------------------------------------------*/
/* genEndFunction - generates epilogue for functions               */
/*-----------------------------------------------------------------*/
static void genEndFunction(iCode * ic)
{
    int i;

    D(pblaze_emitcode(";", "genEndFunction"));

    symbol *sym = OP_SYMBOL(IC_LEFT(ic));

    _G.isCalleSaves = 0;

    /* interrupt routine or callee saves - pop saved registers back */
    if (IFFUNC_ISISR(sym->type) || IFFUNC_CALLEESAVES(sym->type)) {

        for (i = pblaze_nRegs - 1; i >= 0; i--) {
            if (bitVectBitValue(_G.rUsedVect, i))
                popStack(i, 0);
        }
        clearBitVect(_G.rUsedVect);
    }

    /* store globals. if changed */
    freeGlobalsFromReg();

    if (options.debug && currFunc) {
        debugFile->writeEndFunction(currFunc, ic, 1);
    }

    if (pblaze_options.dialect) {
        if (IFFUNC_ISCRITICAL(sym->type))
            pblaze_emitcode("ENABLE INTERRUPT", "");

        if (IFFUNC_ISISR(sym->type)) {
            pblaze_emitcode("RETURNI ENABLE", "");
        } else {
            pblaze_emitcode("RETURN", "");
        }
    } else {
        if (IFFUNC_ISCRITICAL(sym->type))
            pblaze_emitcode("EINT", "");

        if (IFFUNC_ISISR(sym->type)) {
            pblaze_emitcode("RETI ENABLE", "");
        } else {
            pblaze_emitcode("RET", "");
        }

    }
    // clear
    clearMemEndFunc();
}

/*-----------------------------------------------------------------*/
/* genRet - generate code for return statement                     */
/*-----------------------------------------------------------------*/
static void genRet(iCode * ic)
{
    int size, i;
    operand *left;
    char *s;

    D(pblaze_emitcode(";", "genRet"));

    /* we have something to return then move the return value into place */
    if (IC_LEFT(ic)) {
        left = IC_LEFT(ic);
        size = getSize(operandType(left));

        if (isOperandLiteral(left)) {
            assignLiteralRegs(size, fPBLAZEReturn, left);
        } else {
            for (i = size - 1; i >= 0; i--) {
                s = aopGetRegName(ic, left, i);
                if (strcmp(s, fPBLAZEReturn[i]) != 0)
                    pblaze_emitcode("LOAD", "%s, %s", fPBLAZEReturn[i], s);
            }
        }
    }

    /*
       if (!(ic->next && ic->next->op == LABEL &&
       IC_LABEL (ic->next) == returnLabel))

       pblaze_emitcode ("JUMP", "_L%05d", LBL_KEY(returnLabel) );
     */
}

/*-----------------------------------------------------------------*/
/* genLabel - generates a label                                    */
/*-----------------------------------------------------------------*/
static void genLabel(iCode * ic)
{
    if (strcmp(IC_LABEL(ic)->name, entryLabel->name) == 0)
        return;

    pblaze_emitLabel(IC_LABEL(ic));
}

/*-----------------------------------------------------------------*/
/* genGoto - generates a jmp                                      */
/*-----------------------------------------------------------------*/
static void genGoto(iCode * ic)
{
    D(pblaze_emitcode(";", "genGoto"));
    pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_LABEL(ic)));
}


/*-----------------------------------------------------------------*/
/* genPlus - generates code for addition                           */
/*-----------------------------------------------------------------*/
static void genPlus(iCode * ic)
{
    if (isInOutRef(IC_LEFT(ic))) {
        addInOutRef(IC_RESULT(ic), IC_RIGHT(ic));
        return;
    }

    int size, sizeL;
    int i;
    bool swappedLR = FALSE, loadOpt = FALSE;
    unsigned long lit = 0L;
    operand *leftOp, *rightOp, *result;
    int optim = 0;

    D(pblaze_emitcode(";", "genPlus"));

    /* optimize assigment before adding */
    if (ic->next && ic->next->op == '=' && !isOperandLiteral(IC_LEFT(ic)) && OP_LIVETO(IC_RESULT(ic)) == ic->next->seq
        && pblaze_operandsEqu(IC_RESULT(ic), IC_RIGHT(ic->next))
        && pblaze_operandsEqu(IC_LEFT(ic), IC_RESULT(ic->next))) {
        IC_RESULT(ic) = IC_LEFT(ic);
        ic->next->generated = 1;
        optim = 1;
    } else if (ic->next && ic->next->op == '=' && !isOperandLiteral(IC_RIGHT(ic))
               && OP_LIVETO(IC_RESULT(ic)) == ic->next->seq && pblaze_operandsEqu(IC_RESULT(ic), IC_RIGHT(ic->next))
               && pblaze_operandsEqu(IC_RIGHT(ic), IC_RESULT(ic->next))) {
        operand *t = IC_RIGHT(ic);
        IC_RIGHT(ic) = IC_LEFT(ic);
        IC_LEFT(ic) = t;
        IC_RESULT(ic) = IC_LEFT(ic);
        ic->next->generated = 1;
        optim = 1;
    } else if (isOperandLiteral(IC_LEFT(ic)) || pblaze_operandsEqu(IC_RESULT(ic), IC_RIGHT(ic)) ||
               (IC_LEFT(ic)->type == SYMBOL && !isOpInReg(IC_LEFT(ic)) && IC_RIGHT(ic)->type == SYMBOL
                && isOpInReg(IC_RIGHT(ic))) || (IS_OP_GLOBAL(IC_LEFT(ic)) && !IS_OP_GLOBAL(IC_RIGHT(ic))
                                                && !isOperandLiteral(IC_RIGHT(ic)))) {
        operand *t = IC_RIGHT(ic);
        IC_RIGHT(ic) = IC_LEFT(ic);
        IC_LEFT(ic) = t;
        swappedLR = TRUE;
    }

    result = IC_RESULT(ic);
    rightOp = IC_RIGHT(ic);
    leftOp = IC_LEFT(ic);


    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(IC_RESULT(ic), IC_LEFT(ic))) {

        /* assign optimalization (left symbol may ends at this position) */
        if (ASSIGN_OPT(result, leftOp)) {
            assignOpt(ic, result, leftOp);
            loadOpt = TRUE;
        }

        sizeL = getSize(operandType(leftOp));
        size = getSize(operandType(result));

        if (!loadOpt) {
            copyRegisters(ic, result, leftOp, 0, size - 1);
        }

    }

    /*  right operand is value */
    if (isOperandLiteral(rightOp)) {

        /* get value and size */
        lit = ulFromVal(OP_VALUE(rightOp));
        size = getSize(operandType(result));

        pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(valueOffset(lit, 0)));
        aopUpdateOpInMem(ic, result, 0);
        for (i = 1; i < size; i++) {
            pblaze_emitcodeADDCY(aopGetRegName(ic, result, i), dialectNum(valueOffset(lit, i)));
            aopUpdateOpInMem(ic, result, i);
        }
    }

    /*  right operand is symbol */
    else if (OP_SYMBOL(rightOp)) {

        size = getSize(operandType(result));
        sizeL = getSize(operandType(rightOp));

        pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, rightOp, 0));
        aopUpdateOpInMem(ic, result, 0);
        for (i = 1; i < size; i++) {
            if (i < sizeL) {
                pblaze_emitcodeADDCY(aopGetRegName(ic, result, i), aopGetRegName(ic, rightOp, i));
                aopUpdateOpInMem(ic, result, i);
            } else {
                pblaze_emitcodeADDCY(aopGetRegName(ic, result, i), dialectNum(0));
                aopUpdateOpInMem(ic, result, i);
            }
        }

    }
    if (optim && IS_OP_GLOBAL(result))
        globalChanged(result, IN_REG);

}

/*-----------------------------------------------------------------*/
/* genMinus - generates code for subtraction                       */
/*-----------------------------------------------------------------*/
static void genMinus(iCode * ic)
{
    if (isInOutRef(IC_LEFT(ic))) {
        addInOutRef(IC_RESULT(ic), IC_RIGHT(ic));
        return;
    }

    operand *leftOp, *rightOp, *result;
    int i, size, sizeR;
    unsigned long lit = 0L;

    D(pblaze_emitcode(";", "genMinus"));

    if (ic->next && ic->next->op == '=' && !isOperandLiteral(IC_LEFT(ic)) && OP_LIVETO(IC_RESULT(ic)) == ic->next->seq
        && pblaze_operandsEqu(IC_RESULT(ic), IC_RIGHT(ic->next))
        && pblaze_operandsEqu(IC_LEFT(ic), IC_RESULT(ic->next))) {
        IC_RESULT(ic) = IC_LEFT(ic);
        ic->next->generated = 1;
    }

    result = IC_RESULT(ic);
    rightOp = IC_RIGHT(ic);
    leftOp = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(IC_RESULT(ic), IC_LEFT(ic))) {
        /* left operand is a literal */
        if (isOperandLiteral(leftOp)) {
            assignLiteral(result, leftOp, ic);
        }

        /* assign optimalization (left symbol may ends at this position) */
        else if (ASSIGN_OPT(result, leftOp)) {
            assignOpt(ic, result, leftOp);
        }
        /* copy left operand into result operand */
        else {
            copyRegisters(ic, result, leftOp, 0, size - 1);
        }
    }

    /*  right operand is a value */
    if (isOperandLiteral(rightOp)) {

        /* get value and size */
        lit = ulFromVal(OP_VALUE(rightOp));
        size = getSize(operandType(result));

        pblaze_emitcode("SUB", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(valueOffset(lit, 0)));
        aopUpdateOpInMem(ic, result, 0);
        for (i = 1; i < size; i++) {
            pblaze_emitcodeSUBCY(aopGetRegName(ic, result, i), dialectNum(valueOffset(lit, i)));
            aopUpdateOpInMem(ic, result, i);
        }
    }

    /*  right operand is a symbol */
    else if (OP_SYMBOL(rightOp)) {

        size = getSize(operandType(result));
        sizeR = getSize(operandType(rightOp));

        pblaze_emitcode("SUB", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, rightOp, 0));
        aopUpdateOpInMem(ic, result, 0);
        for (i = 1; i < size; i++) {
            if (i < sizeR) {
                pblaze_emitcodeSUBCY(aopGetRegName(ic, result, i), aopGetRegName(ic, rightOp, i));
                aopUpdateOpInMem(ic, result, i);
            } else {
                pblaze_emitcodeSUBCY(aopGetRegName(ic, result, i), dialectNum(0));
                aopUpdateOpInMem(ic, result, i);
            }
        }
    }
}


/*-----------------------------------------------------------------*/
/* genMult - generates code for multiplication                     */
/*-----------------------------------------------------------------*/
static void genMult(iCode * ic)
{
    /* should have been converted to function call */
    assert(0);
}



/*-----------------------------------------------------------------*/
/* genDiv - generates code for division                            */
/*-----------------------------------------------------------------*/
static void genDiv(iCode * ic)
{
    /* should have been converted to function call */
    assert(0);
}

/*-----------------------------------------------------------------*/
/* genMod - generates code for division                            */
/*-----------------------------------------------------------------*/
static void genMod(iCode * ic)
{
    /* should have been converted to function call */
    assert(0);

}



/*-----------------------------------------------------------------*/
/* genMulDivFunc - generates function for multiply and division    */
/*-----------------------------------------------------------------*/
void genMulDivFunc(FILE * of)
{
    if (_GFunc.mschar)
        genMultChar(of);
    if (_GFunc.muschar)
        genMultUnsignedChar(of);
    if (_GFunc.mint)
        genMultInt(of);
    if (_GFunc.mlong)
        genMultLong(of);

    if (_GFunc.modschar)
        genModChar(of);
    if (_GFunc.moduschar)
        genModUnsignedChar(of);
    if (_GFunc.dschar)
        genDivChar(of);
    if (_GFunc.duschar)
        genDivUnsignedChar(of);

    if (_GFunc.modsint)
        genModInt(of);
    if (_GFunc.modusint)
        genModUnsignedInt(of);
    if (_GFunc.dsint)
        genDivInt(of);
    if (_GFunc.dusint)
        genDivUnsignedInt(of);

    if (_GFunc.modslong)
        genModLong(of);
    if (_GFunc.moduslong)
        genModUnsignedLong(of);
    if (_GFunc.dslong)
        genDivLong(of);
    if (_GFunc.duslong)
        genDivUnsignedLong(of);
}


/*-----------------------------------------------------------------*/
/* genCmp - compare left < right                                        */
/*-----------------------------------------------------------------*/
static void genCmp(iCode * ic, operand * left, operand * right, operand * result, iCode * ifx)
{
    int size;
    unsigned long lit = 0L;
    value *aop_lit = NULL;
    symbol *lblo, *lble;

    D(pblaze_emitcode(";", "genCompare"));

    size = max(getSize(operandType(left)), getSize(operandType(right)));

    /* next operation is IFX */
    if (ifx) {
        /* right operand is a literal value */
        if (isOperandLiteral(right)) {
            /* get value and size */
            lit = ulFromVal(OP_VALUE(right));

            /* true label will be generated */
            if (IC_TRUE(ifx)) {

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), dialectNum(valueOffset(lit, size)));
                    pblaze_emitcode("JUMP", "C, _L%05d", LBL_KEY(IC_TRUE(ifx)));
                }
            }

            /* false label will be generated */
            else {
                lble = newiTempLabel(NULL);

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), dialectNum(valueOffset(lit, size)));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lble));
                }

                pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_FALSE(ifx)));
                pblaze_emitLabelC(lble);
            }
        }
        /* left operand is a literal value */
        else if (isOperandLiteral(left)) {
            regs *reg;
            aop_lit = OP_VALUE(left);
            reg = getReg(ic);
            lockReg(reg);
            /* get value and size */
            lit = ulFromVal(aop_lit);

            /* true label will be generated */
            if (IC_TRUE(ifx)) {
                while (size--) {
                    pblaze_emitcode("LOAD", "%s, %s", reg->name, dialectNum(valueOffset(lit, size)));
                    pblaze_emitcodeCompare(reg->name, aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _L%05d", LBL_KEY(IC_TRUE(ifx)));
                }
            }

            /* false label will be generated */
            else {
                lble = newiTempLabel(NULL);

                while (size--) {
                    pblaze_emitcode("LOAD", "%s, %s", reg->name, dialectNum(valueOffset(lit, size)));
                    pblaze_emitcodeCompare(reg->name, aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lble));
                }

                pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_FALSE(ifx)));
                pblaze_emitLabelC(lble);
            }
            unlockReg(reg);
        }
        /* both are in the registers */
        else {
            /* true label will be generated */
            if (IC_TRUE(ifx)) {

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _L%05d", LBL_KEY(IC_TRUE(ifx)));
                }

            }
            /* false label will be generated */
            else {
                lble = newiTempLabel(NULL);

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lble));
                }

                pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_FALSE(ifx)));
                pblaze_emitLabelC(lble);
            }
        }

        ifx->generated = 1;

    }
    /* next instruction is not IFX */
    else {

        aopPutVal(ic, result, dialectNum(0), 0);

        if (size == 1) {

            if (isOperandLiteral(right))
                aop_lit = OP_VALUE(right);
            if (isOperandLiteral(left))
                aop_lit = OP_VALUE(left);

            lit = ulFromVal(aop_lit);

            /* right side is a literal value */
            if (isOperandLiteral(right))
                pblaze_emitcodeCompare(aopGetRegName(ic, left, 0), dialectNum(valueOffset(lit, 0)));

            /* left side is a literal value */
            else if (isOperandLiteral(left)) {
                regs *reg;
                reg = getReg(ic);
                lockReg(reg);
                pblaze_emitcode("LOAD", "%s, %s", reg->name, dialectNum(valueOffset(lit, 0)));
                pblaze_emitcodeCompare(reg->name, aopGetRegName(ic, right, 0));
                unlockReg(reg);
            } else
                pblaze_emitcodeCompare(aopGetRegName(ic, left, 0), aopGetRegName(ic, right, 0));

            pblaze_emitcodeADDCY(aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
        } else {
            /* right side is a literal value */
            if (isOperandLiteral(right)) {

                lblo = newiTempLabel(NULL);
                lble = newiTempLabel(NULL);

                /* get value and size */
                lit = ulFromVal(OP_VALUE(right));

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), dialectNum(valueOffset(lit, size)));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lblo));
                }

                pblaze_emitcode("JUMP", "_LC%05d", LBL_KEY(lble));
                pblaze_emitLabelC(lblo);

                aopPutVal(ic, result, dialectNum(1), 0);
                pblaze_emitLabelC(lble);
            }
            /* left side is a literal value */
            else if (isOperandLiteral(left)) {
                regs *reg;
                lblo = newiTempLabel(NULL);
                lble = newiTempLabel(NULL);
                aop_lit = OP_VALUE(left);
                reg = getReg(ic);
                lockReg(reg);
                /* get value and size */
                lit = ulFromVal(aop_lit);

                while (size--) {
                    pblaze_emitcode("LOAD", "%s, %s", reg->name, dialectNum(valueOffset(lit, size)));
                    pblaze_emitcodeCompare(reg->name, aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lblo));
                }
                unlockReg(reg);

                pblaze_emitcode("JUMP", "_LC%05d", LBL_KEY(lble));
                pblaze_emitLabelC(lblo);
                pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));
                aopUpdateOpInMem(ic, result, 0);
                pblaze_emitLabelC(lble);


            } else {
                lblo = newiTempLabel(NULL);
                lble = newiTempLabel(NULL);

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, size), aopGetRegName(ic, right, size));
                    pblaze_emitcode("JUMP", "C, _LC%05d", LBL_KEY(lblo));
                }

                pblaze_emitcode("JUMP", "_LC%05d", LBL_KEY(lble));
                pblaze_emitLabelC(lblo);

                aopPutVal(ic, result, dialectNum(1), 0);
                pblaze_emitLabelC(lble);

            }
        }
    }
}

/*-----------------------------------------------------------------*/
/* genCmpGt :- greater than comparison                             */
/*-----------------------------------------------------------------*/
static void genCmpGt(iCode * ic, iCode * ifx)
{
    operand *left, *right, *result;

    D(pblaze_emitcode(";", "genCmpGt"));

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);

    genCmp(ic, right, left, result, ifx);
}

/*-----------------------------------------------------------------*/
/* genCmpLt - less than comparisons                                */
/*-----------------------------------------------------------------*/
static void genCmpLt(iCode * ic, iCode * ifx)
{
    operand *left, *right, *result;

    D(pblaze_emitcode(";", "genCmpLt"));

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);

    genCmp(ic, left, right, result, ifx);
}

/*-----------------------------------------------------------------*/
/* genCmpEq - generates code for equal to                          */
/*-----------------------------------------------------------------*/
static void genCmpEq(iCode * ic, iCode * ifx)
{
    operand *left, *right, *result;
    int size, sizeL, sizeR, offset = 0;

    D(pblaze_emitcode(";", "genCmpEq"));


    if (isOperandLiteral(IC_LEFT(ic)) && !isOperandLiteral(IC_RIGHT(ic))) {
        operand *t = IC_RIGHT(ic);
        IC_RIGHT(ic) = IC_LEFT(ic);
        IC_LEFT(ic) = t;
    }

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);

    sizeL = getSize(operandType(left));
    sizeR = getSize(operandType(right));
    size = max(sizeL, sizeR);

    /* next operation is IFX */
    if (ifx) {
        /* true label exists */
        if (IC_TRUE(ifx)) {

            symbol *lblfl = newiTempLabel(NULL);
            /* right operand is a literal */
            if (isOperandLiteral(right)) {
                unsigned long lit = ulFromVal(OP_VALUE(right));

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), dialectNum(valueOffset(lit, offset)));
                    pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lblfl));
                    offset++;
                }

                pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_TRUE(ifx)));

                pblaze_emitLabelC(lblfl);
            }

            /* right operand is in the registers */
            else {
                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), aopGetRegName(ic, right, offset));
                    pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lblfl));
                    offset++;
                }

                pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_TRUE(ifx)));

                pblaze_emitLabelC(lblfl);
            }
        }

        /* false label exists */
        else {
            /* right operand is a literal */
            if (isOperandLiteral(right)) {
                unsigned long lit = ulFromVal(OP_VALUE(right));

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), dialectNum(valueOffset(lit, offset)));
                    pblaze_emitcode("JUMP", "NZ, _L%05d", LBL_KEY(IC_FALSE(ifx)));
                    offset++;
                }
            }

            /* right operand is in the registers */
            else {

                while (size--) {
                    pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), aopGetRegName(ic, right, offset));
                    pblaze_emitcode("JUMP", "NZ, _L%05d", LBL_KEY(IC_FALSE(ifx)));
                    offset++;
                }
            }
        }
        ifx->generated = 1;
    }

    /* next operation is not IFX */
    else {
        symbol *lblfl = newiTempLabel(NULL);

        /* right operand is a literal */
        if (isOperandLiteral(right)) {
            unsigned long lit = ulFromVal(OP_VALUE(right));

            aopPutVal(ic, result, dialectNum(0), 0);

            while (size--) {
                pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), dialectNum(valueOffset(lit, offset)));
                pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lblfl));
                offset++;
            }

            aopPutVal(ic, result, dialectNum(1), 0);
            pblaze_emitLabelC(lblfl);
        }

        /* right operand is in the registers */
        else {
            aopPutVal(ic, result, dialectNum(0), 0);

            while (size--) {
                pblaze_emitcodeCompare(aopGetRegName(ic, left, offset), aopGetRegName(ic, right, offset));
                pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lblfl));
                offset++;
            }

            aopPutVal(ic, result, dialectNum(1), 0);
            pblaze_emitLabelC(lblfl);
        }
    }
}

/*-----------------------------------------------------------------*/
/* ifxForOp - returns the icode containing the ifx for operand     */
/*-----------------------------------------------------------------*/
static iCode *ifxForOp(operand * op, iCode * ic)
{
    /* if true symbol then needs to be assigned */
    if (IS_TRUE_SYMOP(op))
        return NULL;

    /* if this has register type condition and
       the next instruction is ifx with the same operand
       and live to of the operand is upto the ifx only then */
    if (ic->next && ic->next->op == IFX && IC_COND(ic->next)->key == op->key && OP_SYMBOL(op)->liveTo <= ic->next->seq)
        return ic->next;

    return NULL;
}

/*-----------------------------------------------------------------*/
/* genAndOp - for && operation                                     */
/*-----------------------------------------------------------------*/
static void genAndOp(iCode * ic)
{
    operand *left, *right, *result;
    symbol *tlbl;
    regs *r;

    D(pblaze_emitcode(";", "genAnd"));

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);

    tlbl = newiTempLabel(NULL);

    /* only for size == 0 */
    aopPutVal(ic, result, dialectNum(0), 0);

    r = toBoolean(ic, left);
    pblaze_emitcodeCompare(r->name, dialectNum(0));
    pblaze_emitcode("JUMP", "Z, _LC%05d", LBL_KEY(tlbl));

    r = toBoolean(ic, right);
    pblaze_emitcodeCompare(r->name, dialectNum(0));
    pblaze_emitcode("JUMP", "Z, _LC%05d", LBL_KEY(tlbl));

    aopPutVal(ic, result, dialectNum(1), 0);
    pblaze_emitLabelC(tlbl);

}

/*-----------------------------------------------------------------*/
/* genOrOp - for || operation                                      */
/*-----------------------------------------------------------------*/
static void genOrOp(iCode * ic)
{
    operand *left, *right, *result;
    symbol *tlbl;
    regs *r;

    D(pblaze_emitcode(";", "genOrOp"));

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);
    /* only size == 0 */

    tlbl = newiTempLabel(NULL);

    pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));
    aopUpdateOpInMem(ic, result, 0);

    r = toBoolean(ic, left);
    pblaze_emitcodeCompare(r->name, dialectNum(0));
    pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(tlbl));
    r = toBoolean(ic, right);
    pblaze_emitcodeCompare(r->name, dialectNum(0));
    pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(tlbl));

    aopPutVal(ic, result, dialectNum(0), 0);
    pblaze_emitLabelC(tlbl);
}

enum {
    PBLAZE_AND = 0, PBLAZE_OR, PBLAZE_XOR
};

/*-----------------------------------------------------------------*/
/* genBitWise - generate bitwise operations                        */
/*-----------------------------------------------------------------*/
static void genBitWise(iCode * ic, iCode * ifx, int bitop)
{
    operand *left, *right, *result;
    int size, sizeL, sizeR, offset = 0;

    D(pblaze_emitcode(";", "genBitWise"));


    if ((isOperandLiteral(IC_LEFT(ic)) && !isOperandLiteral(IC_RIGHT(ic))) ||
        (!isOperandLiteral(IC_RIGHT(ic)) && OP_LIVETO(IC_LEFT(ic)) > ic->seq && OP_LIVETO(IC_RIGHT(ic)) == ic->seq)) {
        operand *t = IC_RIGHT(ic);
        IC_RIGHT(ic) = IC_LEFT(ic);
        IC_LEFT(ic) = t;
    }

    left = IC_LEFT(ic);
    right = IC_RIGHT(ic);
    result = IC_RESULT(ic);

    sizeL = getSize(operandType(left));
    sizeR = getSize(operandType(right));
    size = max(sizeL, sizeR);


    /* right symbol may ends at this position */
    if (ASSIGN_OPT(result, left) && assignOptTest(ic, IC_RESULT(ic))) {
        assignOpt(ic, result, left);
    } else {
        copyRegisters(ic, result, left, 0, size - 1);
    }

    /* right operand is a literal value */
    if (isOperandLiteral(right)) {
        unsigned long lit = ulFromVal(OP_VALUE(right));

        while (size--) {
            if (bitop == PBLAZE_AND) {
                pblaze_emitcode("AND", "%s, %s", aopGetRegName(ic, result, offset),
                                dialectNum(valueOffset(lit, offset)));
                aopUpdateOpInMem(ic, result, offset);
            }

            else if (bitop == PBLAZE_OR) {
                pblaze_emitcode("OR", "%s, %s", aopGetRegName(ic, result, offset),
                                dialectNum(valueOffset(lit, offset)));
                aopUpdateOpInMem(ic, result, offset);
            } else if (bitop == PBLAZE_XOR) {
                pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, offset),
                                dialectNum(valueOffset(lit, offset)));
                aopUpdateOpInMem(ic, result, offset);
            }
            offset++;
        }
    }

    else {
        while (size--) {
            if (bitop == PBLAZE_AND) {
                pblaze_emitcode("AND", "%s, %s", aopGetRegName(ic, result, offset), aopGetRegName(ic, right, offset));
                aopUpdateOpInMem(ic, result, offset);
            } else if (bitop == PBLAZE_OR) {
                pblaze_emitcode("OR", "%s, %s", aopGetRegName(ic, result, offset), aopGetRegName(ic, right, offset));
                aopUpdateOpInMem(ic, result, offset);
            } else if (bitop == PBLAZE_XOR) {
                pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, offset), aopGetRegName(ic, right, offset));
                aopUpdateOpInMem(ic, result, offset);
            }
            offset++;
        }
    }
}

/*-----------------------------------------------------------------*/
/* genAnd  - code for and                                          */
/*-----------------------------------------------------------------*/
static void genAnd(iCode * ic, iCode * ifx)
{
    D(pblaze_emitcode(";", "genAND"));

    genBitWise(ic, ifx, PBLAZE_AND);
}

/*-----------------------------------------------------------------*/
/* genOr  - code for or                                            */
/*-----------------------------------------------------------------*/
static void genOr(iCode * ic, iCode * ifx)
{
    D(pblaze_emitcode(";", "genOR"));

    genBitWise(ic, ifx, PBLAZE_OR);
}

/*-----------------------------------------------------------------*/
/* genXor - code for xclusive or                                   */
/*-----------------------------------------------------------------*/
static void genXor(iCode * ic, iCode * ifx)
{
    D(pblaze_emitcode(";", "genXOR"));

    genBitWise(ic, ifx, PBLAZE_XOR);
}

/*-----------------------------------------------------------------*/
/* genInline - write the inline code out                           */
/*-----------------------------------------------------------------*/
static void genInline(iCode * ic)
{
    char *buffer, *bp, *bp1;
    bool inComment = FALSE;

    D(pblaze_emitcode(";", "genInline"));

    _G.inLine += (!options.asmpeep);

    buffer = bp = bp1 = Safe_strdup(IC_INLINE(ic));

    /* emit each line as a code */
    while (*bp) {
        switch (*bp) {
        case ';':
            inComment = TRUE;
            ++bp;
            break;

        case '\n':
            inComment = FALSE;
            *bp++ = '\0';
            pblaze_emitcode(bp1, "");
            bp1 = bp;
            break;

        default:
            if (!inComment && (*bp == ':') && (isspace((unsigned char) bp[1]))) {
                ++bp;
                *bp = '\0';
                ++bp;
                pblaze_emitcode(bp1, "");
                bp1 = bp;
            } else
                ++bp;
            break;
        }
    }
    if (bp1 != bp)
        pblaze_emitcode(bp1, "");

    Safe_free(buffer);

    _G.inLine -= (!options.asmpeep);
}

/*-----------------------------------------------------------------*/
/* genRRC - rotate right with carry                                */
/*-----------------------------------------------------------------*/
static void genRRC(iCode * ic)
{
    int offset = 0;
    int size;
    operand *result, *left;

    D(pblaze_emitcode(";", "genRRC"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(IC_RESULT(ic), IC_LEFT(ic))) {
        /* assign optimalization (left symbol may ends at this position) */
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
    }

    if (size == 1) {
        pblaze_emitcode("RR", "%s", aopGetRegName(ic, result, 0));
        aopUpdateOpInMem(ic, result, 0);
    } else {
        pblaze_emitcode("TEST", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));

        while (size--) {
            pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, offset));
            aopUpdateOpInMem(ic, result, offset);
            offset++;
        }

    }
}

/*-----------------------------------------------------------------*/
/* genRLC - generate code for rotate left with carry               */
/*-----------------------------------------------------------------*/
static void genRLC(iCode * ic)
{
    int offset = 0;
    int size;
    operand *result, *left;

    D(pblaze_emitcode(";", "genRLC"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(IC_RESULT(ic), IC_LEFT(ic))) {
        /* assign optimalization (left symbol may ends at this position) */
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
    }

    if (size == 1) {
        pblaze_emitcode("RL", "%s", aopGetRegName(ic, result, 0));
        aopUpdateOpInMem(ic, result, 0);
    } else {
        pblaze_emitcode("TEST", "%s, %s", aopGetRegName(ic, result, size - 1), dialectNum(128));

        while (size--) {
            pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, offset));
            aopUpdateOpInMem(ic, result, offset);
            offset++;
        }

    }
}

/*-----------------------------------------------------------------*/
/* genGetHbit - generates code get highest order bit               */
/*-----------------------------------------------------------------*/
static void genGetHbit(iCode * ic)
{
    int offset = 0;
    int size, sizeL;
    operand *result, *left;

    D(pblaze_emitcode(";", "genGetHBit"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));
    sizeL = getSize(operandType(left));

    while (size--) {
        pblaze_emitcode("XOR", "%s, %s", aopGetRegName(ic, result, offset), aopGetRegName(ic, result, offset));
        aopUpdateOpInMem(ic, result, offset);

        if (size == 0) {
            pblaze_emitcode("TEST", "%s, %s", aopGetRegName(ic, left, sizeL - 1), dialectNum(128));
            pblaze_emitcodeADDCY(aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
        }

        offset++;
    }
}

/*-----------------------------------------------------------------*/
/* leftMaskNumber - generates bit mask for AND operation           */
/*-----------------------------------------------------------------*/
int leftMaskNumber(int ones)
{
    int num = 0;
    if (ones >= 1)
        num += 128;
    if (ones >= 2)
        num += 64;
    if (ones >= 3)
        num += 32;
    if (ones >= 4)
        num += 16;
    if (ones >= 5)
        num += 8;
    if (ones >= 6)
        num += 4;
    if (ones >= 7)
        num += 2;
    if (ones >= 8)
        num += 1;
    return num;
}

/*-----------------------------------------------------------------*/
/* rightMaskNumber - generates bit mask for AND operation          */
/*-----------------------------------------------------------------*/
int rightMaskNumber(int ones)
{
    int num = 0;
    if (ones >= 1)
        num += 1;
    if (ones >= 2)
        num += 2;
    if (ones >= 3)
        num += 4;
    if (ones >= 4)
        num += 8;
    if (ones >= 5)
        num += 16;
    if (ones >= 6)
        num += 32;
    if (ones >= 7)
        num += 64;
    if (ones >= 8)
        num += 128;
    return num;
}

/*-----------------------------------------------------------------*/
/* genShiftLeftLit - shift left by a known amount                  */
/*-----------------------------------------------------------------*/
static void genShiftLeftLit(iCode * ic)
{
    operand *left, *right, *result;
    int i, size, shCount, lByteZ, offset = 0;

    D(pblaze_emitcode(";", "genShiftLeftLit"));

    result = IC_RESULT(ic);
    right = IC_RIGHT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    shCount = (int) ulFromVal(OP_VALUE(right));

    /* shift count = 0 */
    if (shCount == 0) {
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        } else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
        return;
    }

    /* shift count > size */
    if (shCount >= (size * 8)) {
        while (size--)
            aopPutVal(ic, result, dialectNum(0), offset++);
        return;
    }
    offset = 0;

    switch (size) {
    case 1:

        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, 0);
        }

        if (shCount <= 4) {
            while (shCount--) {
                pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
        }
        // shift left more than 4 times can be converted to RR & AND (less instructions requied)
        else {
            i = shCount = 8 - shCount;
            while (shCount--) {
                pblaze_emitcode("RR", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
            pblaze_emitcode("AND", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(leftMaskNumber(i)));
            aopUpdateOpInMem(ic, result, 0);
        }
        break;

    case 2:

        if (shCount >= 8) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), aopGetRegName(ic, left, 0));
            aopUpdateOpInMem(ic, result, 1);

            shCount -= 8;

            while (shCount--) {
                pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 1));
                aopUpdateOpInMem(ic, result, 1);
            }
        } else {
            if (ASSIGN_OPT(result, left)) {
                assignOpt(ic, result, left);
            } else {
                copyRegisters(ic, result, left, 0, size - 1);
            }

            while (shCount--) {
                pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
                pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 1));
                aopUpdateOpInMem(ic, result, 1);
            }
        }
        break;

    case 3:
        assert("unknown type\n");
        break;

    case 4:
        lByteZ = 0;
        if (shCount >= 24) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), dialectNum(0));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), dialectNum(0));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), aopGetRegName(ic, left, 0));
            aopUpdateOpInMem(ic, result, 3);
            lByteZ = 3;
            shCount -= 24;
        }
        if (shCount >= 16) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), dialectNum(0));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), aopGetRegName(ic, left, 0));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), aopGetRegName(ic, left, 1));
            aopUpdateOpInMem(ic, result, 3);
            lByteZ = 2;
            shCount -= 16;
        }

        if (shCount >= 8) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(0));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), aopGetRegName(ic, left, 0));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), aopGetRegName(ic, left, 1));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), aopGetRegName(ic, left, 2));
            aopUpdateOpInMem(ic, result, 3);
            lByteZ = 1;
            shCount -= 8;
        }

        if (lByteZ == 0) {
            if (ASSIGN_OPT(result, left)) {
                assignOpt(ic, result, left);
            } else {
                copyRegisters(ic, result, left, 0, size - 1);
            }
        }
        if (shCount) {
            switch (lByteZ) {
            case 0:
                while (shCount--) {
                    pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 0));
                    aopUpdateOpInMem(ic, result, 0);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 1));
                    aopUpdateOpInMem(ic, result, 1);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 2));
                    aopUpdateOpInMem(ic, result, 2);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 3));
                    aopUpdateOpInMem(ic, result, 3);
                }
                break;

            case 1:
                while (shCount--) {
                    pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 1));
                    aopUpdateOpInMem(ic, result, 1);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 2));
                    aopUpdateOpInMem(ic, result, 2);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 3));
                    aopUpdateOpInMem(ic, result, 3);
                }
                break;

            case 2:
                while (shCount--) {
                    pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 2));
                    aopUpdateOpInMem(ic, result, 2);
                    pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, 3));
                    aopUpdateOpInMem(ic, result, 3);
                }
                break;

            case 3:
                while (shCount--) {
                    pblaze_emitcode("SL0", "%s", aopGetRegName(ic, result, 3));
                    aopUpdateOpInMem(ic, result, 3);
                }
                break;
            }
        }
        break;
    }
}

/*-----------------------------------------------------------------*/
/* genLeftShift - generates code for left shifting                 */
/*-----------------------------------------------------------------*/
static void genLeftShift(iCode * ic)
{
    operand *left, *right, *result;
    int size, offset = 0;
    symbol *slbl, *elbl;
    regs *reg;
    int notTemp;

    D(pblaze_emitcode(";", "genShiftLeft"));

    if (isOperandLiteral(IC_RIGHT(ic))) {
        genShiftLeftLit(ic);
        return;
    }

    result = IC_RESULT(ic);
    right = IC_RIGHT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));


    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(result, left)) {
        /* assign optimalization (left symbol may ends at this position) */
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
    }

    /* shift count is unknown then we have to form a loop
       Note: we take only the lower order byte since shifting
       more that 32 bits make no sense anyway, */

    if (ic->seq >= OP_SYMBOL(right)->liveTo) {
        reg = aopGetReg(ic, right, 0);
        notTemp = 1;
    } else {
        reg = getReg(ic);
        lockReg(reg);
        pblaze_emitcode("LOAD", "%s, %s", reg->name, aopGetRegName(ic, right, 0));
        notTemp = 0;
    }


    elbl = newiTempLabel(NULL);
    slbl = newiTempLabel(NULL);

    pblaze_emitLabelC(slbl);

    pblaze_emitcodeCompare(reg->name, dialectNum(0));
    pblaze_emitcode("JUMP", "Z, _LC%05d", LBL_KEY(elbl));

    pblaze_emitcode("SUB", "%s, %s", reg->name, dialectNum(1));
    if (notTemp)
        aopUpdateOpInMem(ic, right, 0);
    // zero carry flag
    pblaze_emitcode("AND", "sB, sB");

    while (size--) {
        pblaze_emitcode("SLA", "%s", aopGetRegName(ic, result, offset++));
        aopUpdateOpInMem(ic, result, offset);
    }

    pblaze_emitcode("JUMP", "_LC%05d", LBL_KEY(slbl));

    pblaze_emitLabelC(elbl);

    unlockReg(reg);
}

/*-----------------------------------------------------------------*/
/* genShiftRightLit - generate for right shift with known count    */
/*-----------------------------------------------------------------*/
static void genShiftRightLit(iCode * ic)
{
    operand *left, *right, *result;
    int i, size, shCount, hByteZ, offset = 0;

    D(pblaze_emitcode(";", "genShiftRightLit"));

    result = IC_RESULT(ic);
    right = IC_RIGHT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    shCount = (int) ulFromVal(OP_VALUE(right));
    if (shCount == 0) {
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        } else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
        return;
    }

    if (shCount >= (size * 8)) {
        while (size--) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, offset), dialectNum(0));
            aopUpdateOpInMem(ic, result, offset);
            offset++;
        }
        return;
    }
    offset = 0;
    switch (size) {
    case 1:

        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, 0);
        }

        if (shCount <= 4) {
            while (shCount--) {
                pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
        }
        // shift right more than 4 times can be converted to RL & AND (less instructions requied)
        else {
            i = shCount = 8 - shCount;
            while (shCount--) {
                pblaze_emitcode("RL", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
            pblaze_emitcode("AND", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(rightMaskNumber(i)));
            aopUpdateOpInMem(ic, result, 0);
        }
        break;

    case 2:

        if (shCount >= 8) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, left, 1));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), dialectNum(1));
            aopUpdateOpInMem(ic, result, 1);

            shCount -= 8;

            while (shCount--) {
                pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
        } else {
            if (ASSIGN_OPT(result, left)) {
                assignOpt(ic, result, left);
            } else {
                copyRegisters(ic, result, left, 0, size - 1);
            }

            while (shCount--) {
                pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 1));
                aopUpdateOpInMem(ic, result, 1);
                pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 0));
                aopUpdateOpInMem(ic, result, 0);
            }
        }
        break;

    case 3:
        assert("unknown type\n");
        break;

    case 4:
        hByteZ = 0;
        if (shCount >= 24) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, left, 3));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), dialectNum(0));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), dialectNum(0));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), dialectNum(0));
            aopUpdateOpInMem(ic, result, 3);

            hByteZ = 3;
            shCount -= 24;
        }
        if (shCount >= 16) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, left, 2));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), aopGetRegName(ic, left, 3));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), dialectNum(0));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), dialectNum(0));
            aopUpdateOpInMem(ic, result, 3);

            hByteZ = 2;
            shCount -= 16;
        }

        if (shCount >= 8) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 0), aopGetRegName(ic, left, 1));
            aopUpdateOpInMem(ic, result, 0);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 1), aopGetRegName(ic, left, 2));
            aopUpdateOpInMem(ic, result, 1);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 2), aopGetRegName(ic, left, 3));
            aopUpdateOpInMem(ic, result, 2);
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, 3), dialectNum(0));
            aopUpdateOpInMem(ic, result, 3);

            hByteZ = 1;
            shCount -= 8;
        }

        if (hByteZ == 0) {
            if (ASSIGN_OPT(result, left)) {
                assignOpt(ic, result, left);
            } else {
                copyRegisters(ic, result, left, 0, size - 1);
            }
        }
        if (shCount) {
            switch (hByteZ) {
            case 0:
                while (shCount--) {
                    pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 3));
                    aopUpdateOpInMem(ic, result, 3);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 2));
                    aopUpdateOpInMem(ic, result, 2);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 1));
                    aopUpdateOpInMem(ic, result, 1);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 0));
                    aopUpdateOpInMem(ic, result, 0);
                }
                break;

            case 1:
                while (shCount--) {
                    pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 2));
                    aopUpdateOpInMem(ic, result, 2);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 1));
                    aopUpdateOpInMem(ic, result, 1);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 0));
                    aopUpdateOpInMem(ic, result, 0);
                }
                break;

            case 2:
                while (shCount--) {
                    pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 1));
                    aopUpdateOpInMem(ic, result, 1);
                    pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, 0));
                    aopUpdateOpInMem(ic, result, 0);
                }
                break;

            case 3:
                while (shCount--) {
                    pblaze_emitcode("SR0", "%s", aopGetRegName(ic, result, 0));
                    aopUpdateOpInMem(ic, result, 0);
                }
                break;
            }
        }
        break;
    }

}

/*-----------------------------------------------------------------*/
/* genRightShift - generate code for right shifting                */
/*-----------------------------------------------------------------*/
static void genRightShift(iCode * ic)
{
    operand *left, *right, *result;
    int size;
    symbol *slbl, *elbl;
    regs *reg;
    int notTemp;

    D(pblaze_emitcode(";", "genShiftRight"));

    if (isOperandLiteral(IC_RIGHT(ic))) {
        genShiftRightLit(ic);
        return;
    }

    result = IC_RESULT(ic);
    right = IC_RIGHT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));


    /* left and result operands aren't the same */
    if (!pblaze_operandsEqu(result, left)) {
        /* assign optimalization (left symbol may ends at this position) */
        if (ASSIGN_OPT(result, left)) {
            assignOpt(ic, result, left);
        }
        /* assign left operand into result operand */
        else {
            copyRegisters(ic, result, left, 0, size - 1);
        }
    }

    /* shift count is unknown then we have to form a loop
       Note: we take only the lower order byte since shifting
       more that 32 bits make no sense anyway, */

    if (ic->seq >= OP_SYMBOL(right)->liveTo) {
        reg = aopGetReg(ic, right, 0);
        notTemp = 1;
    } else {
        reg = getReg(ic);
        lockReg(reg);
        pblaze_emitcode("LOAD", "%s, %s", reg->name, aopGetRegName(ic, right, 0));
        notTemp = 0;
    }


    elbl = newiTempLabel(NULL);
    slbl = newiTempLabel(NULL);

    pblaze_emitLabelC(slbl);

    pblaze_emitcodeCompare(reg->name, dialectNum(0));
    pblaze_emitcode("JUMP", "Z, _LC%05d", LBL_KEY(elbl));

    pblaze_emitcode("SUB", "%s, %s", reg->name, dialectNum(1));
    if (notTemp)
        aopUpdateOpInMem(ic, right, 0);

    // zero carry flag
    pblaze_emitcode("AND", "sB, sB");

    while (size--) {
        pblaze_emitcode("SRA", "%s", aopGetRegName(ic, result, size));
        aopUpdateOpInMem(ic, result, size);
    }

    pblaze_emitcode("JUMP", "_LC%05d", LBL_KEY(slbl));

    pblaze_emitLabelC(elbl);

    unlockReg(reg);
}

/*-----------------------------------------------------------------*/
/* genIfx - generate code for Ifx statement                        */
/*-----------------------------------------------------------------*/
static void genIfx(iCode * ic, iCode * popIc)
{
    operand *cond = IC_COND(ic);
    symbol *lbl;
    regs *reg;

    D(pblaze_emitcode(";", "genIFX"));

    lbl = newiTempLabel(NULL);

    reg = toBoolean(ic, cond);
    pblaze_emitcodeCompare(reg->name, dialectNum(0));

    if (IC_TRUE(ic)) {
        pblaze_emitcode("JUMP", "Z, _LC%05d", LBL_KEY(lbl));
        pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_TRUE(ic)));
        pblaze_emitLabelC(lbl);
    }

    else {
        pblaze_emitcode("JUMP", "NZ, _LC%05d", LBL_KEY(lbl));
        pblaze_emitcode("JUMP", "_L%05d", LBL_KEY(IC_FALSE(ic)));
        pblaze_emitLabelC(lbl);
    }

}

/*-----------------------------------------------------------------*/
/* genAddrOf - generates code for address of                       */
/*-----------------------------------------------------------------*/
static void genAddrOf(iCode * ic)
{
    D(pblaze_emitcode(";", "genAddrOf"));

    operand *result, *left;
    int size, inR;
    memMap *mAddr;

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);

    if (isInOutRef(left)) {
        addInOutRef(result, NULL);
        return;
    }

    size = getSize(operandType(result));

    mAddr = isOpInMem(left);
    inR = isOpInReg(left);

    if (!mAddr && inR) {
        moveOpToMem(left);
        mAddr = isOpInMem(left);
    }  
    else if (!mAddr) {
        mAddr = firstFreeMem();
    }
    if (!mAddr) {
        fprintf(stderr, "%s:%d: pblaze port error: operand not in the memory\n", __FILE__, __LINE__);
        exit(1);
    }
    if (!operName(mAddr->addr))
        aopPutVal(ic, result, dialectNum(mAddr->addr), 0);
    else
        aopPutVal(ic, result, operName(mAddr->addr), 0);

    _G.ptrOff = 0;
}

/*-----------------------------------------------------------------*/
/* genValueAtAddr - generates code for value at addres             */
/*-----------------------------------------------------------------*/
static void genValueAtAddr(iCode * ic)
{
    D(pblaze_emitcode(";", "genValueAtAddr"));

    int size, i;
    unsigned long lit = 0L;
    operand *result, *left;

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));

    /* address given as a literal value */
    if (isOperandLiteral(left)) {

        lit = ulFromVal(OP_VALUE(left));

        for (i = size - 1; i >= 0; i--) {
            pblaze_emitcodeFetch(aopGetRegName(ic, result, i), dialectNum(valueOffset(lit, 0)));
            lit++;
        }

    } else {

        if (size == 1) {
            /* left operand is an INPUT reference */
            if (isInOutRef(left)) {
                pblaze_emitcodeInput(ic, result, 0, left);
            } else {
                pblaze_emitcodeFetch(aopGetRegName(ic, result, 0), aopGetRegName(ic, left, 0));
            }
            aopUpdateOpInMem(ic, result, 0);
        } else if (size > 1) {
            /* left operand is an INPUT reference */
            if (isInOutRef(left)) {
                pblaze_emitcodeInput(ic, result, 0, left);
                aopUpdateOpInMem(ic, result, 0);
                for (i = 1; i < size; i++) {
                    aopPutVal(ic, result, dialectNum(0), i);
                    aopUpdateOpInMem(ic, result, i);
                }
                
            } else {

                for (i = size - 1; i >= 0; i--) {
                    pblaze_emitcodeFetch(aopGetRegName(ic, result, i), aopGetRegName(ic, left, 0));
                    aopUpdateOpInMem(ic, result, i);

                    if (i != 0) {
                        pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, left, 0), dialectNum(1));
                        aopUpdateOpInMem(ic, left, 0);
                    }
                }

                /* pointer will be used later, return to the begining */
                if (OP_LIVETO(left) > ic->seq) {
                    pblaze_emitcode("SUB", "%s, %s", aopGetRegName(ic, left, 0), dialectNum(size - 1));
                    aopUpdateOpInMem(ic, left, 0);
                }
            }
        }
    }
}

/*-----------------------------------------------------------------*/
/* genAssign - generate code for assignment                        */
/*-----------------------------------------------------------------*/
static void genAssign(iCode * ic)
{
    operand *result, *right;
    int size, offset;
    int i;
    memMap *mem;

    D(pblaze_emitcode(";", "genAssign"));

    result = IC_RESULT(ic);
    right = IC_RIGHT(ic);

    /* if they are the same */
    if (pblaze_operandsEqu(result, right))
        return;

    size = getSize(operandType(result));

    /* assign from memory */
    if (IS_OP_GLOBALVOLATILE(right) || right->isaddr) { 
    
        if(isInOutRef(result)) {
            pblaze_emitcodeOutput(ic, aopGetRegName(ic, right, 0), result);
        } else {
            for (i = 0; i < size; i++) {
                aopMoveReg(ic, result, aopGetReg(ic, right, i), i);
            }
        }
    }

    /* right side is a literal value */
    else if (isOperandLiteral(right)) {
        /* assign literal values into registers */
        assignLiteral(result, right, ic);
    }

    /* should be on the stack */
    else if (IS_OP_PARM(right) && strlen(OP_SYMBOL(right)->rname) == 0) {
        size = getSize(operandType(right));
        offset = size - 1;

        while (size--) {
            popStack(aopGetReg(ic, result, offset)->rIdx, 1);
            offset--;
        }
    }

    /* right side is a symbol */
    else if (OP_SYMBOL(right)) {
        size = getSize(operandType(right));

        /* result is a pointer into memory */
        if (POINTER_SET(ic)) {

            for (i = size - 1; i >= 0; i--) {
                aopPutReg(ic, result, aopGetReg(ic, right, i), i);
                if (i > 0) {
                    pblaze_emitcode("ADD", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(1));
                    aopUpdateOpInMem(ic, result, 0);
                }
            }
            /* pointer will be used later, return to the begining */
            if (size > 1 && OP_LIVETO(result) > ic->seq) {
                pblaze_emitcode("SUB", "%s, %s", aopGetRegName(ic, result, 0), dialectNum(size - 1));
                aopUpdateOpInMem(ic, result, 0);
            }

        }

        /* assign optimalization (right symbol may ends at this position) */
        else if (ASSIGN_OPT(result, right) && assignOptTest(ic, IC_RESULT(ic))) {
            assignOpt(ic, result, right);
        }

        /* assign registers */
        else if (size == getSize(operandType(result))) {
            /* copy values from the right operand into the result operand */
            copyRegisters(ic, result, right, 0, size - 1);
        }
        //
        else {
            fprintf(stderr, "pblaze port error: genAssign unknown error\n");
            exit(1);
        }
    }

    if (IS_OP_GLOBAL(result) && !isOpVolatile(result)) {

        /* probably global value assigment */
        if (GLOB_ASSIGN) {
            size = getSize(operandType(result));

            for (i = size - 1; i >= 0; i--) {
                if (OP_SYMBOL(result)->regs[i] && (mem = isOffsetInMem(result, i)) != NULL)
                    pblaze_emitcodeStore(OP_SYMBOL(result)->regs[i]->name, operName(mem->addr));
            }
        } else {
            globalChanged(result, IN_REG);
        }
    }
}

/*-----------------------------------------------------------------*/
/* genJumpTab - genrates code for jump table                       */
/*-----------------------------------------------------------------*/
static void genJumpTab(iCode * ic)
{
    // D (pblaze_emitcode (";", "genJumpTab"));
    /* not easy to implement without access to the Instruction pointer */
    assert(0);
}

/*-----------------------------------------------------------------*/
/* genCast - gen code for casting                                  */
/*-----------------------------------------------------------------*/
static void genCast(iCode * ic)
{
    D(pblaze_emitcode(";", "genCast"));

    operand *result = IC_RESULT(ic);

    sym_link *rtype = operandType(IC_RIGHT(ic));
    operand *right = IC_RIGHT(ic);
    int sizeRes, sizeRight, i, opt = 0;

    sizeRes = getSize(operandType(result));
    sizeRight = getSize(operandType(right));

    /* if they are equivalent then do nothing */
    if (pblaze_operandsEqu(IC_RESULT(ic), IC_RIGHT(ic)))
        return;

    //literal and bool
    if (isOperandLiteral(right)) {

    }

    else if (IS_PTR(rtype)) {
        if (OP_LIVETO(right) > ic->seq)
            copyRegisters(ic, result, right, 0, 0);
        else
            assignOpt(ic, result, right);
    }

    /* if they are the same size or less */
    else if (sizeRes <= sizeRight) {

        /* right symbol may ends at this position */
        if (ASSIGN_OPT(result, right) && assignOptTest(ic, IC_RESULT(ic))) {
            assignOpt(ic, result, right);
        } else {
            /* assign the casted value */
            copyRegisters(ic, result, right, 0, sizeRes - 1);
        }
    }

    /* the size of destination is greater than the size of the source */
    else {

        /* right symbol may ends at this position */
        if (ASSIGN_OPT(result, right) && assignOptTest(ic, IC_RESULT(ic))) {
            assignOpt(ic, result, right);
            opt = 1;
        } else {

            copyRegisters(ic, result, right, 0, sizeRight - 1);
        }

        /* we need to extend the sign */
        if (opt)
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, sizeRight), dialectNum(0));
        aopUpdateOpInMem(ic, result, sizeRight);
        pblaze_emitcode("TEST", "%s, %s", aopGetRegName(ic, result, sizeRight - 1), dialectNum(128));
        pblaze_emitcodeSUBCY(aopGetRegName(ic, result, sizeRight), dialectNum(0));
        aopUpdateOpInMem(ic, result, sizeRight);

        for (i = sizeRight + 1; i < sizeRes; i++) {
            pblaze_emitcode("LOAD", "%s, %s", aopGetRegName(ic, result, i), aopGetRegName(ic, result, sizeRight));
            aopUpdateOpInMem(ic, result, i);
        }
    }

}

/*-----------------------------------------------------------------*/
/* genReceive - generate code for a receive iCode                  */
/*-----------------------------------------------------------------*/
static void genReceive(iCode * ic)
{
    operand *result, *left;
    symbol *name;
    regs *r;
    value *val;
    char *valName;
    int size, params;
    int i;
    int rMax = SEND_REG_COUNT;
    int rfrst = SEND_REG_FIRST;

    D(pblaze_emitcode(";", "genReceive"));

    result = IC_RESULT(ic);
    left = IC_LEFT(ic);
    size = getSize(operandType(result));
    params = 0;

    /* test parameter */
    if (result && left) {

        name = OP_SYMBOL(left);
        val = FUNC_ARGS(name->type);

        if (SPIL_LOC(result))
            valName = SPIL_LOC(result)->rname;
        else
            valName = OP_SYMBOL(result)->rname;
        /* find parameter position */
        while (val) {
            sprintf(buffer, "%s%s_", name->rname, val->name);
            if (strstr(valName, buffer))
                break;

            params += getSize(val->type);
            val = val->next;
        }

        recvCnt = params;
    }

    /* symbol is in the registers */
    if (recvCnt <= rMax && (rMax - recvCnt) >= size) {
        for (i = 0; i < size; i++) {
            aopPutReg(ic, result, pblaze_regWithIdx(rfrst + recvCnt), i);
            recvCnt++;
        }
    }
    /* not enough registers -> is in the stack */
    else {
        if (OP_LIVETO(result) > ic->seq) {
            for (i = size - 1; i >= 0; i--) {
                if (isOpVolatile(result)) {
                    r = getReg(ic);
                    lockReg(r);
                    popStack(r->rIdx, 0);
                    aopPutReg(ic, result, r, i);
                    unlockReg(r);
                } else {
                    aopGetReg(ic, result, i);
                    popStack(OP_SYMBOL(result)->regs[i]->rIdx, 0);
                    aopUpdateOpInMem(ic, result, i);
                }
            }
        } else {
            pblaze_emitcode("ADD", "sF, %s", dialectNum(size));
        }
    }

}



/*-----------------------------------------------------------------*/
/* genDummyRead - generate code for dummy read of volatiles        */
/*-----------------------------------------------------------------*/
static void genDummyRead(iCode * ic)
{
    pblaze_emitcode(";     genDummyRead", "");
    pblaze_emitcode(";     not implemented", "");

    ic = ic;
}

/*-----------------------------------------------------------------*/
/* genPBLAZECode - generate code for XILINX PicoBlaze controllers  */
/*-----------------------------------------------------------------*/
void genPBLAZECode(iCode * lic)
{
    iCode *ic;
    int cln = 0;
    lineHead = lineCurr = NULL;
    deleteSet(&_G.inOutSet);

    if (!initGen) {
        _G.rUsedVect = newBitVect(pblaze_nRegs);
        clearBitVect(_G.rUsedVect);
        _G.isCalleSaves = 0;
        _G.onStack = 0;
        _GFunc.mschar = 0;
        _GFunc.muschar = 0;
        _GFunc.mint = 0;
        _GFunc.mlong = 0;
        _GFunc.dschar = 0;
        _GFunc.duschar = 0;
        _GFunc.modschar = 0;
        _GFunc.moduschar = 0;
        _GFunc.dsint = 0;
        _GFunc.dusint = 0;
        _GFunc.modsint = 0;
        _GFunc.modusint = 0;
        _GFunc.dslong = 0;
        _GFunc.duslong = 0;
        _GFunc.modslong = 0;
        _GFunc.moduslong = 0;
        initGen = 1;
    }

    recvCnt = 0;

    /* print the allocation information */
    //if (allocInfo && currFunc)
    //  printAllocInfo (currFunc, codeOutBuf);

    /* if debug information required */
    if (options.debug && currFunc) {
        debugFile->writeFunction(currFunc, lic);
    }

    for (ic = lic; ic; ic = ic->next) {
        if (ic->generated)
            continue;

        _G.current_iCode = ic;

        if (ic->lineno && cln != ic->lineno) {
            if (options.debug) {
                debugFile->writeCLine(ic);
            }
            if (!options.noCcodeInAsm) {
                pblaze_emitcode(";", "%s:%d: %s", ic->filename, ic->lineno, printCLine(ic->filename, ic->lineno));
            }
            cln = ic->lineno;
        }

        if (!(ic->op == CALL || ic->op == SEND)) {
            clearUnusedOpFromReg(ic);
            clearUnusedOpFromMem(ic);

        }

        /* depending on the operation */
        switch (ic->op) {
        case '!':
            genNot(ic);
            break;

        case '~':
            genCpl(ic);
            break;

        case UNARYMINUS:
            genUminus(ic);
            break;

        case IPUSH:
            genIpush(ic);
            break;

        case IPOP:
            genIpop(ic);
            break;

        case CALL:
            genCall(ic);
            break;

        case PCALL:
            genPcall(ic);
            break;

        case FUNCTION:
            genFunction(ic);
            break;

        case ENDFUNCTION:
            genEndFunction(ic);
            break;

        case RETURN:
            genRet(ic);
            break;

        case LABEL:
            genLabel(ic);
            break;

        case GOTO:
            genGoto(ic);
            break;

        case '+':
            genPlus(ic);
            break;

        case '-':
            genMinus(ic);
            break;

        case '*':
            genMult(ic);
            break;

        case '/':
            genDiv(ic);
            break;

        case '%':
            genMod(ic);
            break;

        case '>':
            genCmpGt(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case '<':
            genCmpLt(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case LE_OP:
        case GE_OP:
        case NE_OP:
            /* note these two are xlated by algebraic equivalence
               in decorateType() in SDCCast.c */
            werror(E_INTERNAL_ERROR, __FILE__, __LINE__, "got '>=' or '<=' shouldn't have come here");
            break;

        case EQ_OP:
            genCmpEq(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case AND_OP:
            genAndOp(ic);
            break;

        case OR_OP:
            genOrOp(ic);
            break;

        case '^':
            genXor(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case '|':
            genOr(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case BITWISEAND:
            genAnd(ic, ifxForOp(IC_RESULT(ic), ic));
            break;

        case INLINEASM:
            genInline(ic);
            break;

        case RRC:
            genRRC(ic);
            break;

        case RLC:
            genRLC(ic);
            break;

        case GETHBIT:
            genGetHbit(ic);
            break;

        case LEFT_OP:
            genLeftShift(ic);
            break;

        case RIGHT_OP:
            genRightShift(ic);
            break;

        case '=':
            genAssign(ic);
            break;

        case IFX:
            genIfx(ic, NULL);
            break;

        case ADDRESS_OF:
            genAddrOf(ic);
            break;

        case GET_VALUE_AT_ADDRESS:
            genValueAtAddr(ic);
            break;

        case JUMPTABLE:
            genJumpTab(ic);
            break;

        case CAST:
            genCast(ic);
            break;

        case RECEIVE:
            genReceive(ic);
            break;

        case SEND:
            addSet(&_G.sendSet, ic);
            break;

        case DUMMY_READ_VOLATILE:
            genDummyRead(ic);
            break;

        default:
            ic = ic;
            printf("nogen: %d\n", ic->op);
        }
    }

    //now we are ready to call the peep hole optimizer 
    if (!options.nopeep)
        peepHole(&lineHead);


    /* now do the actual printing */
    printLine(lineHead, codeOutBuf);
    return;
}
