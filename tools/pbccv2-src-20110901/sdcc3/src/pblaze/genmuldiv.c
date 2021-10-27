/*-------------------------------------------------------------------------
genmuldiv.c - source file for code generation of MUL/DIV operations for
              XILINX PICOBLAZE

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

#define LBL_KEY(x) x->key+10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SDCCglobl.h"
#include "newalloc.h"

#include "common.h"
#include "ralloc.h"
#include "main.h"
#include "gen.h"


/*-----------------------------------------------------------------*/
/* genMultChar - mult function 1B x 1B -> 2B                       */
/*-----------------------------------------------------------------*/
void genMultChar(FILE * of)
{
    symbol *lbls1 = newiTempLabel(NULL);
    symbol *lbls2 = newiTempLabel(NULL);
    symbol *lblend = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__mulschar:\n");
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tTEST\tsB, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls1));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls1));
    fprintf(of, "\tTEST\tsC, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls2));
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsC, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls2));
    fprintf(of, "\tCALL\t__muluchar\n");
    fprintf(of, "\tTEST\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsC, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}


/*-----------------------------------------------------------------*/
/* genMultUnsignedChar - mult function 1B x 1B -> 2B               */
/*-----------------------------------------------------------------*/
void genMultUnsignedChar(FILE * of)
{
    symbol *lbladd = newiTempLabel(NULL);
    symbol *lblc = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__muluchar:\n");
    fprintf(of, "\tLOAD\tsE, %s08\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\tsD, sC\n");
    fprintf(of, "\tLOAD\tsC, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    fprintf(of, "\tTEST\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tADD\tsC, sD\n");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));
    fprintf(of, "\tSR0\tsC\n");
    fprintf(of, "\tSRA\tsB\n");
    fprintf(of, "\tSUB\tsE, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}


/*-----------------------------------------------------------------*/
/* genMultInt - signed & unsigned 2B x 2B -> 2B                    */
/*-----------------------------------------------------------------*/
void genMultInt(FILE * of)
{

    symbol *lbladd = newiTempLabel(NULL);
    symbol *lblc = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__mulint:\n");
    fprintf(of, "\tLOAD\ts7, %s10\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts8, sD\n");
    fprintf(of, "\tLOAD\ts9, sE\n");
    fprintf(of, "\tLOAD\tsD, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\tsE, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    fprintf(of, "\tTEST\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tADD\tsD, s8\n");
    fprintf(of, "\tADDC%s\tsE, s9\n", pblaze_options.dialect ? "Y" : "");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));
    fprintf(of, "\tSR0\tsE\n");
    fprintf(of, "\tSRA\tsD\n");
    fprintf(of, "\tSRA\tsC\n");
    fprintf(of, "\tSRA\tsB\n");

    fprintf(of, "\tSUB\ts7, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}



/*-----------------------------------------------------------------*/
/* genMultLong - signed & unsigned 4B x 4B -> 4B                    */
/*-----------------------------------------------------------------*/
void genMultLong(FILE * of)
{
    symbol *lbladd = newiTempLabel(NULL);
    symbol *lblc = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__mullong:\n");

    // load multiplicand, multiplier is stored in registers sE..sB
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts6, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts5, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts4, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts3, (sF)\n");

    // 32 cycles
    fprintf(of, "\tLOAD\ts2, %s20\n", pblaze_options.dialect ? "" : "$");

    // clear upper 4B of the result (but only lower 4B are used as the result)
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts9, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts8, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts7, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    // add multiplicand to the result if the lowest bit of the multiplier is 1
    fprintf(of, "\tTEST\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tADD\ts7, s3\n");
    fprintf(of, "\tADDC%s\ts8, s4\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tADDC%s\ts9, s5\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tADDC%s\tsA, s6\n", pblaze_options.dialect ? "Y" : "");

    // result is shifted right
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));
    fprintf(of, "\tSR0\tsA\n");
    fprintf(of, "\tSRA\ts9\n");
    fprintf(of, "\tSRA\ts8\n");
    fprintf(of, "\tSRA\ts7\n");
    fprintf(of, "\tSRA\tsE\n");
    fprintf(of, "\tSRA\tsD\n");
    fprintf(of, "\tSRA\tsC\n");
    fprintf(of, "\tSRA\tsB\n");

    fprintf(of, "\tSUB\ts2, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genModChar - function 1B mod 1B -> 1B                       */
/*-----------------------------------------------------------------*/
void genModChar(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__modschar:\n");
    fprintf(of, "\tCALL\t__divschar\n");
    fprintf(of, "\tTEST\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsC, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, sC\n");
    fprintf(of, "\tXOR\tsC, sB\n");
    fprintf(of, "\tXOR\tsB, sC\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genModUnsignedChar - mod function 1B / 1B -> 1B                       */
/*-----------------------------------------------------------------*/
void genModUnsignedChar(FILE * of)
{

    fprintf(of, "\n");
    fprintf(of, "__moduchar:\n");
    fprintf(of, "__moduschar:\n");
    fprintf(of, "\tCALL\t__divuschar\n");

    fprintf(of, "\tXOR\tsB, sC\n");
    fprintf(of, "\tXOR\tsC, sB\n");
    fprintf(of, "\tXOR\tsB, sC\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivChar - Div function 1B / 1B -> 1B                       */
/*-----------------------------------------------------------------*/
void genDivChar(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);
    symbol *lbls1 = newiTempLabel(NULL);
    symbol *lbls2 = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divschar:\n");
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tTEST\tsB, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls1));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls1));
    fprintf(of, "\tTEST\tsC, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls2));
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsC, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s02\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls2));
    fprintf(of, "\tCALL\t__divuchar\n");
    fprintf(of, "\tTEST\tsA, %s03\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNC, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivUnsignedChar - mDiv function 1B / 1B -> 1B               */
/*-----------------------------------------------------------------*/
void genDivUnsignedChar(FILE * of)
{
    symbol *lblc = newiTempLabel(NULL);
    symbol *lbladd = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divuchar:\n");
    fprintf(of, "\tLOAD\tsE, %s08\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\tsD, sC\n");
    fprintf(of, "\tLOAD\tsC, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    fprintf(of, "\tSL0\tsB\n");
    fprintf(of, "\tSLA\tsC\n");
    fprintf(of, "\tCOMP%s\tsC, sD\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tSUB\tsC, sD\n");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));

    fprintf(of, "\tSUB\tsE, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}


/*-----------------------------------------------------------------*/
/* genModInt                                               */
/*-----------------------------------------------------------------*/
void genModInt(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__modsint:\n");
    fprintf(of, "\tCALL\t__divsint\n");
    fprintf(of, "\tTEST\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsD, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsE, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsD, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsE, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, sD\n");
    fprintf(of, "\tXOR\tsD, sB\n");
    fprintf(of, "\tXOR\tsB, sD\n");

    fprintf(of, "\tXOR\tsE, sC\n");
    fprintf(of, "\tXOR\tsC, sE\n");
    fprintf(of, "\tXOR\tsE, sC\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genModUnsignedInt                                               */
/*-----------------------------------------------------------------*/
void genModUnsignedInt(FILE * of)
{

    fprintf(of, "\n");
    fprintf(of, "__moduint:\n");
    fprintf(of, "\tCALL\t__divuint\n");

    fprintf(of, "\tXOR\tsB, sD\n");
    fprintf(of, "\tXOR\tsD, sB\n");
    fprintf(of, "\tXOR\tsB, sD\n");

    fprintf(of, "\tXOR\tsE, sC\n");
    fprintf(of, "\tXOR\tsC, sE\n");
    fprintf(of, "\tXOR\tsE, sC\n");

    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivInt 					           */
/*-----------------------------------------------------------------*/
void genDivInt(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);
    symbol *lbls1 = newiTempLabel(NULL);
    symbol *lbls2 = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divsint:\n");
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tTEST\tsC, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls1));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsC, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s01\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls1));
    fprintf(of, "\tTEST\tsE, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls2));
    fprintf(of, "\tXOR\tsD, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsE, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsD, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsE, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s02\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls2));
    fprintf(of, "\tCALL\t__divuint\n");
    fprintf(of, "\tTEST\tsA, %s03\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNC, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsC, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivUnsignedInt 					           */
/*-----------------------------------------------------------------*/
void genDivUnsignedInt(FILE * of)
{
    symbol *lblc = newiTempLabel(NULL);
    symbol *lbladd = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divuint:\n");
    fprintf(of, "\tLOAD\ts7, %s10\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts8, sD\n");
    fprintf(of, "\tLOAD\ts9, sE\n");
    fprintf(of, "\tLOAD\tsD, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\tsE, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    fprintf(of, "\tSL0\tsB\n");
    fprintf(of, "\tSLA\tsC\n");
    fprintf(of, "\tSLA\tsD\n");
    fprintf(of, "\tSLA\tsE\n");

    fprintf(of, "\tCOMP%s\tsE, s9\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tCOMP%s\tsD, s8\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));

    fprintf(of, "\tSUB\tsD, s8\n");
    fprintf(of, "\tSUBC%s\tsE, s9\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));

    fprintf(of, "\tSUB\ts7, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivUnsignedLong - signed & unsigned 4B x 4B -> 4B             */
/*-----------------------------------------------------------------*/
void genDivUnsignedLong(FILE * of)
{
    symbol *lbladd = newiTempLabel(NULL);
    symbol *lbldo = newiTempLabel(NULL);
    symbol *lblc = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divulong:\n");

    fprintf(of, "\tCALL\t__divuslongload\n");
    fprintf(of, "\tCALL\t__divuslongdiv\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");

    fprintf(of, "__divuslongdiv:\n");
    // 32 cycles
    fprintf(of, "\tLOAD\ts2, %s20\n", pblaze_options.dialect ? "" : "$");

    // clear upper 4B of the result (but only lower 4B are used as the result)
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts9, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts8, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tLOAD\ts7, %s00\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblc));
    // result is shifted left
    fprintf(of, "\tSL0\tsB\n");
    fprintf(of, "\tSLA\tsC\n");
    fprintf(of, "\tSLA\tsD\n");
    fprintf(of, "\tSLA\tsE\n");
    fprintf(of, "\tSLA\ts7\n");
    fprintf(of, "\tSLA\ts8\n");
    fprintf(of, "\tSLA\ts9\n");
    fprintf(of, "\tSLA\tsA\n");

    fprintf(of, "\tCOMP%s\tsA, s6\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lbldo));
    fprintf(of, "\tCOMP%s\ts9, s5\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lbldo));
    fprintf(of, "\tCOMP%s\ts8, s4\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lbldo));
    fprintf(of, "\tCOMP%s\ts7, s3\n", pblaze_options.dialect ? "ARE" : "");
    fprintf(of, "\tJUMP\tC, _LM%04d\n", LBL_KEY(lbladd));

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbldo));
    fprintf(of, "\tSUB\ts7, s3\n");
    fprintf(of, "\tSUBC%s\ts8, s4\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tSUBC%s\ts9, s5\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tSUBC%s\tsA, s6\n", pblaze_options.dialect ? "Y" : "");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbladd));

    fprintf(of, "\tSUB\ts2, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNZ, _LM%04d\n", LBL_KEY(lblc));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");

    fprintf(of, "__divuslongload:\n");
    // load divisor, divident is stored in registers sE..sB
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts6, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts5, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts4, (sF)\n");
    fprintf(of, "\tADD\tsF, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tFETCH\ts3, (sF)\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genDivLong -                                                    */
/*-----------------------------------------------------------------*/
void genDivLong(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);
    symbol *lbls1 = newiTempLabel(NULL);
    symbol *lbls2 = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__divslong:\n");
    fprintf(of, "\tCALL\t__divuslongload\n");
    fprintf(of, "\tLOAD\tsA, %s00\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tTEST\tsC, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls1));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsD, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsE, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsC, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsD, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsE, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s01\n", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls1));
    fprintf(of, "\tTEST\tsE, %s80\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lbls2));
    fprintf(of, "\tXOR\ts3, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\ts4, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\ts5, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\ts6, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\ts3, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\ts4, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\ts5, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\ts6, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tOR\tsA, %s02\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lbls2));
    fprintf(of, "\tCALL\t__divuslongdiv\n");
    fprintf(of, "\tTEST\tsA, %s03\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tNC, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsC, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsD, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsE, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\tsB, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsC, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsD, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsE, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genModLong - mod function 4B / 4B -> 4B                         */
/*-----------------------------------------------------------------*/
void genModLong(FILE * of)
{

    symbol *lblend = newiTempLabel(NULL);

    fprintf(of, "\n");
    fprintf(of, "__modslong:\n");
    fprintf(of, "\tCALL\t__divslong\n");
    fprintf(of, "\tTEST\tsA, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tJUMP\tZ, _LM%04d\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\ts7, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\ts8, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\ts9, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tXOR\tsA, %sFF\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADD\ts7, %s01\n", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\ts8, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\ts9, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");
    fprintf(of, "\tADDC%s\tsA, %s00\n", pblaze_options.dialect ? "Y" : "", pblaze_options.dialect ? "" : "$");

    fprintf(of, "_LM%04d:\n", LBL_KEY(lblend));
    fprintf(of, "\tXOR\tsB, s7\n");
    fprintf(of, "\tXOR\ts7, sB\n");
    fprintf(of, "\tXOR\tsB, s7\n");

    fprintf(of, "\tXOR\ts8, sC\n");
    fprintf(of, "\tXOR\tsC, s8\n");
    fprintf(of, "\tXOR\ts8, sC\n");

    fprintf(of, "\tXOR\tsD, s9\n");
    fprintf(of, "\tXOR\ts9, sD\n");
    fprintf(of, "\tXOR\tsD, s9\n");

    fprintf(of, "\tXOR\tsE, sA\n");
    fprintf(of, "\tXOR\tsA, sE\n");
    fprintf(of, "\tXOR\tsE, sA\n");
    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}

/*-----------------------------------------------------------------*/
/* genModUnsignedLong - mod function 4B / 4B -> 4B                 */
/*-----------------------------------------------------------------*/
void genModUnsignedLong(FILE * of)
{

    fprintf(of, "\n");
    fprintf(of, "__modulong:\n");
    fprintf(of, "\tCALL\t__divulong\n");

    fprintf(of, "\tXOR\tsB, s7\n");
    fprintf(of, "\tXOR\ts7, sB\n");
    fprintf(of, "\tXOR\tsB, s7\n");

    fprintf(of, "\tXOR\ts8, sC\n");
    fprintf(of, "\tXOR\tsC, s8\n");
    fprintf(of, "\tXOR\ts8, sC\n");

    fprintf(of, "\tXOR\tsD, s9\n");
    fprintf(of, "\tXOR\ts9, sD\n");
    fprintf(of, "\tXOR\tsD, s9\n");

    fprintf(of, "\tXOR\tsE, sA\n");
    fprintf(of, "\tXOR\tsA, sE\n");
    fprintf(of, "\tXOR\tsE, sA\n");

    if (pblaze_options.dialect)
	fprintf(of, "\tRETURN\n");
    else
	fprintf(of, "\tRET\n");
}
