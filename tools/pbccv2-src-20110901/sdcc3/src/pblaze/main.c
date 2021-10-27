/** @file main.c
    pblaze specific general functions.
    
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
#include "main.h"
#include "ralloc.h"
#include "gen.h"
#include "ralloc.h"
#include "pbglue.h"
#include "dbuf_string.h"

static char _defaultRules[] = {
#include "peeph.rul"
};

#define DIALECT_OPT           "--dialect="
#define PORTKW_OPT           "--portkw="
#define ACKNOWLEDGEMENT_OPT   "--acknowledgement"

pblaze_options_t pblaze_options;

OPTION pblaze_optionsTable[] = {
    {0, DIALECT_OPT, &pblaze_options.dialect,
     "(kcpsm3 or pblazeide) selects the assembler dialect for the chosen target platform (see argument --target) as there are some minor differences between the PicoBlaze-3 Assembler for HDL/HEX production (KCPSM3) and for the simulation (pBlazeIDE). (Default: pblazeide)"},
    {0, PORTKW_OPT, &pblaze_options.portKw,
     "set proper keyword used for INPUT/OUTPUT operations (default: PBLAZEPORT)"},
    {0, ACKNOWLEDGEMENT_OPT, NULL,
     "The development of this pblaze-port was supported by the Czech Ministry of Education, Youth and Sports grant 2C06008 Virtual Laboratory of Microprocessor Technology Application (visit the website http://www.vlam.cz)."},
    {0, NULL, NULL, NULL}
};

/* list of key words used by msc51 */
static char *_pblaze_keywords[] = {
    "at",
    "code",
    "critical",
    "interrupt",
    "xdata",
    "_code",
    "_generic",
    "_xdata",
    "_NECO",
    NULL
};

static int regParmFlg = 0;	/* determine if we can register a parameter */

static void _pblaze_init(void)
{
    asm_addTree(&asm_asxxxx_mapping);
}

static void _pblaze_reset_regparm(void)
{
    regParmFlg = 0;
}


void _pblaze_genInitStartup(FILE * of)
{
    printConstants(of);
}


static int _pblaze_regparm(sym_link * l, bool reentrant)
{
    /* we won't split variables
       i.e. if not enough registers left to hold
       the parameter then the whole parameter along
       with rest of the parameters go onto the stack */
    if (regParmFlg < SEND_REG_COUNT) {
	int size;
	if ((size = getSize(l)) > (SEND_REG_COUNT - regParmFlg)) {
	    /* all remaining go on stack */
	    regParmFlg = SEND_REG_COUNT;
	    return 0;
	}
	regParmFlg += size;
	return 1;
    }

    return 0;
}

void pblaze_assignRegisters(ebbIndex *);

#define ISOPT(str)  !strncmp(argv[ *i ], str, strlen(str) )

static bool _pblaze_parseOptions(int *pargc, char **argv, int *i)
{
    char *dialecttype;

    if (ISOPT(DIALECT_OPT)) {
      dialecttype = getStringArg(DIALECT_OPT, argv, i, *pargc);
    	if (!STRCASECMP(dialecttype, "pblazeide"))
    	    pblaze_options.dialect = 0;
    	else if (!STRCASECMP(dialecttype, "kcpsm3"))
    	    pblaze_options.dialect = 1;
    	else {
    	    fprintf(stderr, "Unknown dialect type: %s\nAvaiable options: pblazeide or kcpsm3\n", dialecttype);
    	    exit(EXIT_FAILURE);
    	}
	    return TRUE;
    }
    
    if (ISOPT(PORTKW_OPT)) {
        pblaze_options.portKw = Safe_strdup(getStringArg(PORTKW_OPT, argv, i, *pargc));
        return TRUE;
    }

    if (ISOPT(ACKNOWLEDGEMENT_OPT)) {
	    fprintf(stderr, "The development of this pblaze-port was supported by the Czech Ministry of Education, Youth and Sports grant 2C06008 Virtual Laboratory of Microprocessor Technology Application (visit the website http://www.vlam.cz).");
	    exit(EXIT_FAILURE);
	    return TRUE;
    }

    return FALSE;
}


static void _pblaze_finaliseOptions(void)
{
    port->mem.default_local_map = port->mem.default_globl_map = data;
    /* change stack to be in far space */
    /* internal stack segment ;   
       SFRSPACE       -   NO
       FAR-SPACE      -   YES
       PAGED          -   NO
       DIRECT-ACCESS  -   NO
       BIT-ACCESS     -   NO
       CODE-ACESS     -   NO 
       DEBUG-NAME     -   'B'
       POINTER-TYPE   -   FPOINTER
     */
    istack = allocMap(0, 1, 0, 0, 0, 0, options.stack_loc, ISTACK_NAME, 'B', FPOINTER);

    /* also change xdata to be direct space since we can use lds/sts */
    xdata->direct = 1;

}

static void _pblaze_setDefaultOptions(void)
{
    pblaze_options.dialect = 1;
    pblaze_options.portKw = "PBLAZEPORT";
    options.stackAuto = 1;
}

static const char *_pblaze_getRegName(struct regs *reg)
{
    if (reg)
	return reg->name;
    return "err";
}

static void _pblaze_genAssemblerPreamble(FILE * of)
{

}

static void _pblaze_genAssemblerEnd(FILE * of)
{
    genMulDivFunc(of);
}

/* Generate interrupt vector table. */
static int _pblaze_genIVT(struct dbuf_s *oBuf, symbol ** interrupts, int maxInterrupts)
{
    if (pblaze_interrupt) {
	if (pblaze_options.dialect) {
	    dbuf_printf(oBuf, "\tADDRESS\t3ff\n");
	} else {
	    dbuf_printf(oBuf, "\tORG\t$3ff\n");
	}
	dbuf_printf(oBuf, "\tJUMP\t%s\n", pblaze_interrupt->name);
    }

    return TRUE;
}

/* Indicate which extended bit operations this port supports */
static bool hasExtBitOp(int op, int size)
{
    if (op == RRC || op == RLC || op == GETHBIT)
	return TRUE;
    else
	return FALSE;
}

/* Indicate the expense of an access to an output storage class */
static int oclsExpense(struct memmap *oclass)
{
    if (IN_FARSPACE(oclass))
	return 1;

    return 0;
}

/** $1 is always the basename.
    $2 is always the output file.
    $3 varies
    $l is the list of extra options that should be there somewhere...
    MUST be terminated with a NULL.
*/
static const char *_linkCmd[] = {
    "linkpblaze", "", "\"$1\"", NULL
};

/* $3 is replaced by assembler.debug_opts resp. port->assembler.plain_opts */
static const char *_asmCmd[] = {
    "aspblaze", "$l", "$3", "\"$1.s\"", NULL
};

/* Globals */
PORT pblaze_port = {
    TARGET_ID_PBLAZE,
    "pblaze",
    "XILINX PicoBlaze",		/* Target name */
    NULL,			/* processor */
    {
     pblaze_glue,
     TRUE,			/* Emit glue around main */
     MODEL_SMALL,
     MODEL_SMALL,
     NULL,			/* model == target */
     },
    {
     _asmCmd,
     NULL,
     "-plosgff",		/* Options with debug */
     "-plosgff",		/* Options without debug */
     0,
     ".psm",
     NULL,			/* no do_assemble */
     },
    {
     _linkCmd,
     NULL,
     NULL,
     ".rel",
     1},
    {
     _defaultRules},
    {
     /* Sizes: char, short, int, long, ptr, fptr, gptr, bit, float, max */
     1, 2, 2, 4, 1, 1, 1, 1, 0, 4},

    /* tags for generic pointers */
    {0x00, 0x40, 0x60, 0x80},	/* far, near, xstack, code */

    {
     "XSEG",
     "STACK",
     "CSEG",
     "DSEG",
     "ISEG",
     NULL,			//PSEG
     "XSEG",
     "BSEG",
     "RSEG",
     "GSINIT",
     "OSEG",
     "GSFINAL",
     "HOME",
     NULL,			// initialized xdata
     NULL,			// a code copy of xiseg
     "CONST   (CODE)",		// const_name - const data (code or not)
     "CABS    (ABS,CODE)",	// cabs_name - const absolute data (code or not)
     "XABS    (ABS,XDATA)",	// xabs_name - absolute xdata/pdata
     "IABS    (ABS,DATA)",	// iabs_name - absolute idata/data
     NULL,
     NULL,
     0,
     },
    {NULL, NULL},
    {
     -1, 1, 4, 1, 1, 0},
    /* pblaze hasn't any mul */
    {
     0, -1},
    {
     pblaze_emitDebuggerSymbol},
    {
     32,			/* maxCount */
     2,				/* sizeofElement */
     /* the behavior of src/SDCCicode.c 1.207 and earlier.  */
     {2, 2, 2},			/* sizeofMatchJump[] */
     {0, 0, 0},			/* sizeofRangeCompare[] */
     0,				/* sizeofSubtract */
     2,				/* sizeofDispatch */
     },
    "_",
    _pblaze_init,
    _pblaze_parseOptions,
    pblaze_optionsTable,
    NULL,
    _pblaze_finaliseOptions,
    _pblaze_setDefaultOptions,
    pblaze_assignRegisters,
    _pblaze_getRegName,
    _pblaze_keywords,
    _pblaze_genAssemblerPreamble,
    _pblaze_genAssemblerEnd,	/* no genAssemblerEnd */
    _pblaze_genIVT,
    NULL,			// _pblaze_genXINIT
    _pblaze_genInitStartup,	/* genInitStartup */
    _pblaze_reset_regparm,
    _pblaze_regparm,
    NULL,
    NULL,
    NULL,
    hasExtBitOp,		/* hasExtBitOp */
    oclsExpense,		/* oclsExpense */
    FALSE,
    TRUE,			/* little endian */
    0,				/* leave lt */
    0,				/* leave gt */
    1,				/* transform <= to ! > */
    1,				/* transform >= to ! < */
    1,				/* transform != to !(a == b) */
    0,				/* leave == */
    FALSE,			/* No array initializer support. */
    0,				/* no CSE cost estimation yet */
    NULL,			/* no builtin functions */
    GPOINTER,			/* treat unqualified pointers as "generic" pointers */
    0,				/* reset labelKey to 1 */
    1,				/* globals & local static allowed */
    PORT_MAGIC
};
