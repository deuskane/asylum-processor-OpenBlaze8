/*-------------------------------------------------------------------------
  gen.c - source file for code generation into JSON
  
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

#include "json/json.h"

extern int allocInfo;

// unsigned fJSONReturnSize = 4;    /* shared with ralloc.c */

static struct {
        short xPushed;
        short zPushed;
        short accInUse;
        short inLine;
        short debugLine;
        short nRegsSaved;
        set *sendSet;
} _G;

extern int json_ptrRegReq;
extern int json_nRegs;
extern struct dbuf_s *codeOutBuf;


static lineNode *lineHead = NULL;
static lineNode *lineCurr = NULL;

#define LSB     0
#define MSB16   1
#define MSB24   2
#define MSB32   3

/*-----------------------------------------------------------------*/
/* emitcode - writes the code into a file                          */
/*-----------------------------------------------------------------*/
static void
emitcode (char *inst, char *fmt, ...)
{
        va_list ap;
        char lb[INITIAL_INLINEASM];
        char *lbp = lb;

        va_start (ap, fmt);

        if (inst && *inst) {
                if (fmt && *fmt)
                        sprintf (lb, "%s\t", inst);
                else
                        sprintf (lb, "%s", inst);
                vsprintf (lb + (strlen (lb)), fmt, ap);
        }
        else
                vsprintf (lb, fmt, ap);

        while (isspace ((unsigned char)*lbp))
                lbp++;

        if (lbp && *lbp)
                lineCurr = (lineCurr ?
                            connectLine (lineCurr, newLineNode (lb)) :
                            (lineHead = newLineNode (lb)));
        lineCurr->isInline = _G.inLine;
        lineCurr->isDebug = _G.debugLine;
        va_end (ap);
}

/*-----------------------------------------------------------------*/
/* json_emitDebuggerSymbol - associate the current code location  */
/*   with a debugger symbol                                        */
/*-----------------------------------------------------------------*/
void
json_emitDebuggerSymbol (const char * debugSym)
{
  _G.debugLine = 1;
  emitcode ("", "%s ==.", debugSym);
  _G.debugLine = 0;
}


/*-----------------------------------------------------------------*/
/* newAsmop - creates a new asmOp                                  */
/*-----------------------------------------------------------------*/
static asmop *
newAsmop (short type)
{
        asmop *aop;

        aop = Safe_calloc (1, sizeof (asmop));
        aop->type = type;
        return aop;
}

/*-----------------------------------------------------------------*/
/* pointerCode - returns the code for a pointer type               */
/*-----------------------------------------------------------------*/
static int
pointerCode (sym_link * etype)
{

        return PTR_TYPE (SPEC_OCLS (etype));

}


/*-----------------------------------------------------------------*/
/* regsInCommon - two operands have some registers in common       */
/*-----------------------------------------------------------------*/
static bool
regsInCommon (operand * op1, operand * op2)
{
        symbol *sym1, *sym2;
        int i;

        /* if they have registers in common */
        if (!IS_SYMOP (op1) || !IS_SYMOP (op2))
                return FALSE;

        sym1 = OP_SYMBOL (op1);
        sym2 = OP_SYMBOL (op2);

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
/* operandsEqu - equivalent                                        */
/*-----------------------------------------------------------------*/
static bool
operandsEqu (operand * op1, operand * op2)
{
        symbol *sym1, *sym2;

        /* if they not symbols */
        if (!IS_SYMOP (op1) || !IS_SYMOP (op2))
                return FALSE;

        sym1 = OP_SYMBOL (op1);
        sym2 = OP_SYMBOL (op2);

        /* if they are the same */
        if (sym1 == sym2)
                return TRUE;

        if (strcmp (sym1->rname, sym2->rname) == 0)
                return TRUE;


        /* if left is a tmp & right is not */
        if (IS_ITEMP (op1) &&
            !IS_ITEMP (op2) && sym1->isspilt && (sym1->usl.spillLoc == sym2))
                return TRUE;

        if (IS_ITEMP (op2) &&
            !IS_ITEMP (op1) &&
            sym2->isspilt && sym1->level > 0 && (sym2->usl.spillLoc == sym1))
                return TRUE;

        return FALSE;
}


/*-----------------------------------------------------------------*/
/* aopOp - allocates an asmop for an operand  :                    */
/*-----------------------------------------------------------------*/
static void
aopOp (operand * op, iCode * ic, bool result)
{
        asmop *aop;
        symbol *sym;
        int i;

        if (!op)
                return;

        /* if this a literal */
        if (IS_OP_LITERAL (op)) {
                op->aop = aop = newAsmop (AOP_LIT);
                aop->aopu.aop_lit = op->operand.valOperand;
                aop->size = getSize (operandType (op));
                return;
        }
	
	        /* if already has a asmop then continue */
        if (op->aop)
                return;
	
	/* must be load into a register */
        sym->aop = op->aop = aop = newAsmop (AOP_REG);
        aop->size = sym->nRegs;
	//getReg (op, aop);

}

/*-----------------------------------------------------------------*/
/* freeAsmop - free up the asmop given to an operand               */
/*----------------------------------------------------------------*/
static void
freeAsmop (operand * op, asmop * aaop, iCode * ic)
{
        asmop *aop;

        if (!op)
                aop = aaop;
        else
                aop = op->aop;

        if (!aop)
                return;
	
        if (op) {
                op->aop = NULL;
        }
}



/*-----------------------------------------------------------------*/
/* genNotFloat - generates not for float operations                */
/*-----------------------------------------------------------------*/
static void
genNotFloat (operand * op, operand * res)
{

}

/*-----------------------------------------------------------------*/
/* genNot - generate code for ! operation                          */
/*-----------------------------------------------------------------*/
static void
genNot (iCode * ic)
{

}


/*-----------------------------------------------------------------*/
/* genCpl - generate code for complement                           */
/*-----------------------------------------------------------------*/
static void
genCpl (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genUminusFloat - unary minus for floating points                */
/*-----------------------------------------------------------------*/
static void
genUminusFloat (operand * op, operand * result)
{

}

/*-----------------------------------------------------------------*/
/* genUminus - unary minus code generation                         */
/*-----------------------------------------------------------------*/
static void
genUminus (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genIpush - genrate code for pushing this gets a little complex  */
/*-----------------------------------------------------------------*/
static void
genIpush (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genIpop - recover the registers: can happen only for spilling   */
/*-----------------------------------------------------------------*/
static void
genIpop (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genCall - generates a call statement                            */
/*-----------------------------------------------------------------*/
static void
genCall (iCode * ic)
{

   
}

/*-----------------------------------------------------------------*/
/* genPcall - generates a call by pointer statement                */
/*-----------------------------------------------------------------*/
static void
genPcall (iCode * ic)
{

}


/*-----------------------------------------------------------------*/
/* genFunction - generated code for function entry                 */
/*-----------------------------------------------------------------*/
static void
genFunction (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genEndFunction - generates epilogue for functions               */
/*-----------------------------------------------------------------*/
static void
genEndFunction (iCode * ic)
{
 

}

/*-----------------------------------------------------------------*/
/* genRet - generate code for return statement                     */
/*-----------------------------------------------------------------*/
static void
genRet (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genLabel - generates a label                                    */
/*-----------------------------------------------------------------*/
static void
genLabel (iCode * ic)
{
        /* special case never generate */
        if (IC_LABEL (ic) == entryLabel)
                return;

        emitcode ("", "L%05d:", IC_LABEL (ic)->key);
}

/*-----------------------------------------------------------------*/
/* genGoto - generates a ljmp                                      */
/*-----------------------------------------------------------------*/
static void
genGoto (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genPlusIncr :- does addition with increment if possible         */
/*-----------------------------------------------------------------*/
static bool
genPlusIncr (iCode * ic)
{
return FALSE;
}


/*-----------------------------------------------------------------*/
/* genPlus - generates code for addition                           */
/*-----------------------------------------------------------------*/
static void
genPlus (iCode * ic)
{
 
  
   emitcode ("add", "%d, %d",4,5 );  
}

/*-----------------------------------------------------------------*/
/* genMinusDec :- does subtraction with deccrement if possible     */
/*-----------------------------------------------------------------*/
static bool
genMinusDec (iCode * ic)
{
 
return FALSE;
}

/*-----------------------------------------------------------------*/
/* genMinus - generates code for subtraction                       */
/*-----------------------------------------------------------------*/
static void
genMinus (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genMultOneByte : 8 bit multiplication & division                */
/*-----------------------------------------------------------------*/
static void
genMultOneByte (operand * left, operand * right, operand * result)
{
 
}

/*-----------------------------------------------------------------*/
/* genMult - generates code for multiplication                     */
/*-----------------------------------------------------------------*/
static void
genMult (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genDiv - generates code for division                            */
/*-----------------------------------------------------------------*/
static void
genDiv (iCode * ic)
{
        /* should have been converted to function call */
        assert (0);
}

/*-----------------------------------------------------------------*/
/* genMod - generates code for division                            */
/*-----------------------------------------------------------------*/
static void
genMod (iCode * ic)
{
        /* should have been converted to function call */
        assert (0);

}

enum {
        PBLAZE_EQ = 0,
        PBLAZE_NE,
        PBLAZE_LT,
        PBLAZE_GE
};

/*-----------------------------------------------------------------*/
/* revpblazecnd - reverse a conditional for pblaze                       */
/*-----------------------------------------------------------------*/
static int
revpblazecnd (int type)
{
        static struct {
                int type, rtype;
        } rar[] = {
                {
                PBLAZE_EQ, PBLAZE_NE}
                , {
                PBLAZE_LT, PBLAZE_GE}
        };
        int i;

        for (i = 0; i < (sizeof (rar) / sizeof (rar[0])); i++) {
                if (rar[i].type == type)
                        return rar[i].rtype;
                if (rar[i].rtype == type)
                        return rar[i].type;
        }
        assert (0);             /* cannot happen */
        return 0;               /* makes the compiler happy */
}


/*-----------------------------------------------------------------*/
/* genBranch - generate the branch instruction                     */
/*-----------------------------------------------------------------*/
static void
genBranch (iCode * ifx, int br_type, int sign)
{

}

/*-----------------------------------------------------------------*/
/* genCmp - compare & jump                                         */
/*-----------------------------------------------------------------*/
static void
genCmp (iCode * ic, iCode * ifx, int br_type)
{
 
}

/*-----------------------------------------------------------------*/
/* genCmpGt :- greater than comparison                             */
/*-----------------------------------------------------------------*/
static void
genCmpGt (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genCmpLt - less than comparisons                                */
/*-----------------------------------------------------------------*/
static void
genCmpLt (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genCmpEq - generates code for equal to                          */
/*-----------------------------------------------------------------*/
static void
genCmpEq (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genCmpNe - generates code for not equal to                      */
/*-----------------------------------------------------------------*/
static void
genCmpNe (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genCmpGe - generates code for greater than equal to             */
/*-----------------------------------------------------------------*/
static void
genCmpGe (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genCmpLe - generates code for less than equal to                */
/*-----------------------------------------------------------------*/
static void
genCmpLe (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* ifxForOp - returns the icode containing the ifx for operand     */
/*-----------------------------------------------------------------*/
static iCode *
ifxForOp (operand * op, iCode * ic)
{
        /* if true symbol then needs to be assigned */
        if (IS_TRUE_SYMOP (op))
                return NULL;

        /* if this has register type condition and
           the next instruction is ifx with the same operand
           and live to of the operand is upto the ifx only then */
        if (ic->next &&
            ic->next->op == IFX &&
            IC_COND (ic->next)->key == op->key &&
            OP_SYMBOL (op)->liveTo <= ic->next->seq) return ic->next;

        return NULL;
}

/*-----------------------------------------------------------------*/
/* genAndOp - for && operation                                     */
/*-----------------------------------------------------------------*/
static void
genAndOp (iCode * ic)
{
 
}


/*-----------------------------------------------------------------*/
/* genOrOp - for || operation                                      */
/*-----------------------------------------------------------------*/
static void
genOrOp (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genBitWise - generate bitwise operations                        */
/*-----------------------------------------------------------------*/
static void
genBitWise (iCode * ic, iCode * ifx, int bitop)
{
 
}

/*-----------------------------------------------------------------*/
/* genAnd  - code for and                                          */
/*-----------------------------------------------------------------*/
static void
genAnd (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genOr  - code for or                                            */
/*-----------------------------------------------------------------*/
static void
genOr (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genXor - code for xclusive or                                   */
/*-----------------------------------------------------------------*/
static void
genXor (iCode * ic, iCode * ifx)
{

}

/*-----------------------------------------------------------------*/
/* genInline - write the inline code out                           */
/*-----------------------------------------------------------------*/
static void
genInline (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genRotC - rotate right/left with carry , lr = 1 rotate right    */
/*-----------------------------------------------------------------*/
static void
genRotC (iCode * ic, int lr)
{

}

/*-----------------------------------------------------------------*/
/* genRRC - rotate right with carry                                */
/*-----------------------------------------------------------------*/
static void
genRRC (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genRLC - generate code for rotate left with carry               */
/*-----------------------------------------------------------------*/
static void
genRLC (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genGetHbit - generates code get highest order bit               */
/*-----------------------------------------------------------------*/
static void
genGetHbit (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genShiftLeftLit - shift left by a known amount                  */
/*-----------------------------------------------------------------*/
static void
genShiftLeftLit (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genLeftShift - generates code for left shifting                 */
/*-----------------------------------------------------------------*/
static void
genLeftShift (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genShiftRightLit - generate for right shift with known count    */
/*-----------------------------------------------------------------*/
static void
genShiftRightLit (iCode * ic)
{
 
}

/*-----------------------------------------------------------------*/
/* genRightShift - generate code for right shifting                */
/*-----------------------------------------------------------------*/
static void
genRightShift (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* RRsh - shift right rn by known count                            */
/*-----------------------------------------------------------------*/
static void
RRsh (int shCount,int reg)
{

}

/*-----------------------------------------------------------------*/
/* RLsh - shift left rn by known count                             */
/*-----------------------------------------------------------------*/
static void
RLsh (int shCount, int reg)
{

}

/*-----------------------------------------------------------------*/
/* genUnpackBits - generates code for unpacking bits               */
/*-----------------------------------------------------------------*/
static void
genUnpackBits (operand * result, char *rname, int ptype)
{
 
}

/*-----------------------------------------------------------------*/
/* genDataPointerGet - generates code when ptr offset is known     */
/*-----------------------------------------------------------------*/
static void
genDataPointerGet (operand * left, operand * result, iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genNearPointerGet - emitcode for near pointer fetch             */
/*-----------------------------------------------------------------*/
static void
genMemPointerGet (operand * left, operand * result, iCode * ic, iCode *pi)
{
 
}

/*-----------------------------------------------------------------*/
/* genCodePointerGet - gget value from code space                  */
/*-----------------------------------------------------------------*/
static void
genCodePointerGet (operand * left, operand * result, iCode * ic, iCode *pi)
{


}

/*-----------------------------------------------------------------*/
/* genPointerGet - generate code for pointer get                   */
/*-----------------------------------------------------------------*/
static void
genPointerGet (iCode * ic, iCode *pi)
{

}

/*-----------------------------------------------------------------*/
/* genPackBits - generates code for packed bit storage             */
/*-----------------------------------------------------------------*/
static void
genPackBits (sym_link * etype,
             operand * right,
             char *rname, int p_type)
{
 
}

/*-----------------------------------------------------------------*/
/* genDataPointerSet - remat pointer to data space                 */
/*-----------------------------------------------------------------*/
static void
genDataPointerSet (operand * right, operand * result, iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genNearPointerSet - emitcode for near pointer put               */
/*-----------------------------------------------------------------*/
static void
genMemPointerSet (operand * right, operand * result, iCode * ic, iCode *pi)
{
 
}

/*-----------------------------------------------------------------*/
/* genGenPointerSet - set value from generic pointer space         */
/*-----------------------------------------------------------------*/
static void
genGenPointerSet (operand * right, operand * result, iCode * ic, iCode *pi)
{

}

/*-----------------------------------------------------------------*/
/* genPointerSet - stores the value into a pointer location        */
/*-----------------------------------------------------------------*/
static void
genPointerSet (iCode * ic, iCode *pi)
{
 
}

/*-----------------------------------------------------------------*/
/* genIfx - generate code for Ifx statement                        */
/*-----------------------------------------------------------------*/
static void
genIfx (iCode * ic, iCode * popIc)
{
 
}

/*-----------------------------------------------------------------*/
/* genAddrOf - generates code for address of                       */
/*-----------------------------------------------------------------*/
static void
genAddrOf (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genFarFarAssign - assignment when both are in far space         */
/*-----------------------------------------------------------------*/
static void
genFarFarAssign (operand * result, operand * right, iCode * ic)
{


}

/*-----------------------------------------------------------------*/
/* genAssign - generate code for assignment                        */
/*-----------------------------------------------------------------*/
static void
genAssign (iCode * ic)
{
  operand *result, *right;
  int size, offset;
  unsigned long lit = 0L;
  int i;

  D(emitcode (";", "genAssign"));
  
  result = IC_RESULT (ic);
  right = IC_RIGHT (ic);
  
  
  // TODO: all options
  /* right side is a literal value */
  if (IS_OP_LITERAL (right)) {
    value *aop_lit;

    aop_lit = right->operand.valOperand;
    
    /* get value and size */
    lit = ulFromVal (aop_lit);
    size = getSize ( operandType (right) );
      
    
    /* left side is a symbol - register */
    if( OP_SYMBOL(result) ) {
      
      OP_SYMBOL(result)->nRegs = size;
      
      /* assign registers */
      assignReg (result);
      
      
      for(i = 0; i<size; i++) {
	emitcode ("load", "%s, %02x", OP_SYMBOL(result)->regs[i]->name , (unsigned int) ((lit >> (i * 8)) & 0x0FFL) );
    
      }
      
      
    }
    
    // printf("ic:%d\tsize:%d\n",ic->key,size);
    
    
    
  }
 
}

/*-----------------------------------------------------------------*/
/* genJumpTab - genrates code for jump table                       */
/*-----------------------------------------------------------------*/
static void
genJumpTab (iCode * ic)
{
 

}

/*-----------------------------------------------------------------*/
/* genCast - gen code for casting                                  */
/*-----------------------------------------------------------------*/
static void
genCast (iCode * ic)
{
 

}

/*-----------------------------------------------------------------*/
/* genReceive - generate code for a receive iCode                  */
/*-----------------------------------------------------------------*/
static void
genReceive (iCode * ic)
{

}

/*-----------------------------------------------------------------*/
/* genDummyRead - generate code for dummy read of volatiles        */
/*-----------------------------------------------------------------*/
static void
genDummyRead (iCode * ic)
{
  emitcode (";     genDummyRead","");
  emitcode (";     not implemented","");

  ic = ic;
}

/*-----------------------------------------------------------------*/
/* gen51Code - generate code for 8051 based controllers            */
/*-----------------------------------------------------------------*/
void
genJSONCode (iCode * lic)
{
        iCode *ic;
        int cln = 0;


        for (ic = lic; ic; ic = ic->next) {

		if( IS_ARITHMETIC_OP(ic) ) {
	    
		  operand *left = IC_LEFT (ic);
		  if( OP_SYMBOL(left) ) {
		    printf("name:%s\n", left->operand.symOperand->rname );
		  }
		  
		}
		    // printf("oper:%d\n", ic->op);
	      
                if (cln != ic->lineno) {
                        if (options.debug) {
                                debugFile->writeCLine (ic);
                        }
                        emitcode (";", "%s %d", ic->filename, ic->lineno);
                        cln = ic->lineno;
                }

                /* depending on the operation */
                switch (ic->op) {
                case '!':
                        genNot (ic);
                        break;

                case '~':
                        genCpl (ic);
                        break;

                case UNARYMINUS:
                        genUminus (ic);
                        break;

                case IPUSH:
                        genIpush (ic);
                        break;

                case IPOP:
                        genIpop (ic);
                        break;

                case CALL:
                        genCall (ic);
                        break;

                case PCALL:
                        genPcall (ic);
                        break;

                case FUNCTION:
                        genFunction (ic);
                        break;

                case ENDFUNCTION:
                        genEndFunction (ic);
                        break;

                case RETURN:
                        genRet (ic);
                        break;

                case LABEL:
                        genLabel (ic);
                        break;

                case GOTO:
                        genGoto (ic);
                        break;

                case '+':
                        genPlus (ic);
                        break;

                case '-':
                        genMinus (ic);
                        break;

                case '*':
                        genMult (ic);
                        break;

                case '/':
                        genDiv (ic);
                        break;

                case '%':
                        genMod (ic);
                        break;

                case '>':
                        genCmpGt (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case '<':
                        genCmpLt (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case LE_OP:
                        genCmpLe (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case GE_OP:
                        genCmpGe (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case NE_OP:
                        genCmpNe (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case EQ_OP:
                        genCmpEq (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case AND_OP:
                        genAndOp (ic);
                        break;

                case OR_OP:
                        genOrOp (ic);
                        break;

                case '^':
                        genXor (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case '|':
                        genOr (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case BITWISEAND:
                        genAnd (ic, ifxForOp (IC_RESULT (ic), ic));
                        break;

                case INLINEASM:
                        genInline (ic);
                        break;

                case RRC:
                        genRRC (ic);
                        break;

                case RLC:
                        genRLC (ic);
                        break;

                case GETHBIT:
                        genGetHbit (ic);
                        break;

                case LEFT_OP:
                        genLeftShift (ic);
                        break;

                case RIGHT_OP:
                        genRightShift (ic);
                        break;

                case '=':
                        genAssign (ic);
                        break;

                case IFX:
                        genIfx (ic, NULL);
                        break;

                case ADDRESS_OF:
                        genAddrOf (ic);
                        break;

                case JUMPTABLE:
                        genJumpTab (ic);
                        break;

                case CAST:
                        genCast (ic);
                        break;

                case RECEIVE:
                        genReceive (ic);
                        break;

                case SEND:
                        addSet (&_G.sendSet, ic);
                        break;

                case DUMMY_READ_VOLATILE:
                        genDummyRead (ic);
                        break;

                default:
                        ic = ic;
                }
        }


        /* now we are ready to call the
           peep hole optimizer 
        if (!options.nopeep)
                peepHole (&lineHead);

	*/
        /* now do the actual printing */
        printLine (lineHead, codeOutBuf);
        return;
}
