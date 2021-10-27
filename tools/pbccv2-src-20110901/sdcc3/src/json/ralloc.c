/*------------------------------------------------------------------------

  SDCCralloc.c - source file for register allocation. (XILINX PICOBLAZE) specific

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


extern void genJSONCode (iCode *);

/* Global data */
static struct {
	bitVect *spiltSet;
	set *stackSpil;
	bitVect *regAssigned;
	short blockSpil;
	int slocNum;
	bitVect *funcrUsed;	/* registers used in a function */
	int stackExtend;
	int dataExtend;
} _G;

/* Shared with gen.c */
int json_ptrRegReq;		/* pointer register required */

/* JSON registers */
regs regsJSON[] = {
	{REG_GPR, S0_IDX,   "s0", NULL,  0, 1},
	{REG_GPR, S1_IDX,   "s1", NULL,  0, 1},
	{REG_GPR, S2_IDX,   "s2", NULL,  0, 1},
	{REG_GPR, S3_IDX,   "s3", NULL,  0, 1},
	{REG_GPR, S4_IDX,   "s4", NULL,  0, 1},
	{REG_GPR, S5_IDX,   "s5", NULL,  0, 1},
	{REG_GPR, S6_IDX,   "s6", NULL,  0, 1},
	{REG_GPR, S7_IDX,   "s7", NULL,  0, 1},
	{REG_GPR, S8_IDX,   "s8", NULL,  0, 1},
	{REG_GPR, S9_IDX,   "s9", NULL,  0, 1},
	{REG_GPR, SA_IDX,   "sA", NULL,  0, 1},
	{REG_GPR, SB_IDX,   "sB", NULL,  0, 1},
	{REG_GPR, SC_IDX,   "sC", NULL,  0, 1},
	{REG_GPR, SD_IDX,   "sD", NULL,  0, 1},
	{REG_GPR, SE_IDX,   "sE", NULL,  0, 1},
	{REG_GPR, SF_IDX,   "sF", NULL,  0, 1},
};
int json_nRegs = 16;
int json_fReg = 0;		/* first allocatable register */




/*-----------------------------------------------------------------*/
/* json_regWithIdx - returns pointer to register with index number*/
/*-----------------------------------------------------------------*/
regs *
json_regWithIdx (int idx)
{
	int i;

	for (i = 0; i < json_nRegs; i++)
		if (regsJSON[i].rIdx == idx)
			return &regsJSON[i];

	werror (E_INTERNAL_ERROR, __FILE__, __LINE__, "regWithIdx not found");
	exit (1);
}

/*-----------------------------------------------------------------*/
/* firstFreeReg - returns first free register                      */
/*-----------------------------------------------------------------*/
static regs *
firstFreeReg (void)
{
  int i;

  for (i = 0; i < json_nRegs; i++) {
    if(regsJSON[i].isFree == 1)
      return &regsJSON[i];
    
  }
  
  return NULL;
}



/*-----------------------------------------------------------------*/
/* freeReg - frees a register                                      */
/*-----------------------------------------------------------------*/
static void
freeReg (regs * reg)
{
	reg->isFree = 1;
	reg->currSymbol = NULL;
}


/*-----------------------------------------------------------------*/
/* nFreeRegs - returns number of free registers                    */
/*-----------------------------------------------------------------*/
static int
nFreeRegs (void)
{
	int i;
	int nfr = 0;

	for (i = json_fReg; i < json_nRegs; i++)
		if (regsJSON[i].isFree )
			nfr++;
	return nfr;
}


/*-----------------------------------------------------------------*/
/* isSymbolInReg - test if symbol is in registers                  */
/*-----------------------------------------------------------------*/
static int isSymbolInReg( symbol *s)
{
  int i, size, found = 0;
  
  if(!s)
    return 0;
  
  
  size = getSize ( s->type );
  
  
  // && s->regs[ regsJSON[i].offset ] ==  &regsJSON[i]
  
  
  for (i = json_fReg; i < json_nRegs; i++)
  {
    if (regsJSON[i].currSymbol == s ) {
      found++;
    }
    
  }
  
  if (found == size) return 1;
  else if (found == 0) return 0;
  
  wassertl(FALSE, "chybi cast operandu v registrech");
}


/*-----------------------------------------------------------------*/
/* assignReg - assign registers to the symbol                      */
/*-----------------------------------------------------------------*/
void
XXXassignReg (operand * op)
{
  regs *rtmp;
  int i, size;
  
  // Q? pouze typ Symbol
  if(op->type == SYMBOL) {
    
    /* get number of requied registers */
    size = getSize ( operandType (op) );
    //size = OP_SYMBOL(op)->nRegs;   
    
    /* symbol is already in the registers */
    if ( isSymbolInReg( OP_SYMBOL(op) ) ) {
      
      
    }
    
    
    /* symbol is not in the registers and there is a sufficient number of registers for assigment */
    else if (nFreeRegs() >= size) {
    
      //printf("Size:%d\n", size);
    
      OP_SYMBOL(op)->nRegs = size;
      
      for(i = 0; i<size; i++) {
	
	rtmp = firstFreeReg();
	if(!rtmp) assert ("neosetreno\n");
	
	rtmp->isFree = 0;
	rtmp->currSymbol = OP_SYMBOL(op);
	rtmp->offset = i;
      
	OP_SYMBOL(op)->regs[i] = rtmp;
      
      }
    
    }
    
    // TODO: nedostatek registru,
    // Q?: potreba uvolnit -> pamet / zasobnik
    else {
      
      
      
    }
    
  }
}



/*-----------------------------------------------------------------*/
/* assignRegisters                                                 */
/*-----------------------------------------------------------------*/
void
json_assignRegisters (ebbIndex * ebbi)
{
	eBBlock ** ebbs = ebbi->bbOrder;
	int count = ebbi->count;
	iCode *ic;
	int i;

	setToNull ((void *) &_G.funcrUsed);
	//json_ptrRegReq = _G.stackExtend = _G.dataExtend = 0;



	/* now get back the chain */
	//ic = iCodeLabelOptimize (iCodeFromeBBlock (ebbs, count));
	
	//symbol *sym, *tempsym;
	//sym = (symbol *) findSymWithLevel(SymbolTab,tempsym);
	//printf("sym:%s\n", SymbolTab[0]->name);

	
	ic = iCodeFromeBBlock (ebbs, count);
	
	genJSONCode (ic);
	/*     for (; ic ; ic = ic->next) */
	/*          piCode(ic,stdout); */
	/* free up any _G.stackSpil locations allocated */

	_G.slocNum = 0;

	/* mark all registers as free */

	return;
}
