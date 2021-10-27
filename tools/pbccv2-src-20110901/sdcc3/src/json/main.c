/** @file main.c
    json specific general functions.

    Note that mlh prepended _json_ on the static functions.  Makes
    it easier to set a breakpoint using the debugger.
*/
#include "common.h"
#include "main.h"
#include "ralloc.h"
#include "gen.h"
#include "device.h"

static char _defaultRules[] = {
#include "peeph.rul"
};

/* list of key words used by msc51 */
static char *_json_keywords[] = {
	"at",
	"code",
	"critical",
	"eeprom",
	"interrupt",
	"sfr",
	"xdata",
	"_code",
	"_eeprom",
	"_generic",
	"_xdata",
	"sram",
	"_sram",
	"flash",
	"_flash",
	NULL
};

static int regParmFlg = 0;	/* determine if we can register a parameter */
json_options_t json_options;

static void
_json_init (void)
{
	asm_addTree (&asm_asxxxx_mapping);
}

static void
_json_reset_regparm (void)
{
	regParmFlg = 0;
}


void _json_genInitStartup (FILE * of)
{
  
}


static int
_json_regparm (sym_link * l, bool reentrant)
{
	/* the first eight bytes will be passed in
	   registers r16-r23. but we won't split variables
	   i.e. if not enough registers left to hold
	   the parameter then the whole parameter along
	   with rest of the parameters go onto the stack */
	if (regParmFlg < 8) {
		int size;
		if ((size = getSize (l)) > (8 - regParmFlg)) {
			/* all remaining go on stack */
			regParmFlg = 8;
			return 0;
		}
		regParmFlg += size;
		return 1;
	}

	return 0;
}

void json_assignRegisters (ebbIndex *);

#define GEN_JSON		    "--json"
#define GEN_JSONFILE	  "--json-file="
#define ISOPT(str)  !strncmp(argv[ *i ], str, strlen(str) )



// TODO
OPTION json_optionsTable[]= {
	/* json debugging options */   /* code generation options */
  	{ 0, GEN_JSON,          &json_options.json_flag, "dump iCodes in JSON format"},
  	{ 0, GEN_JSONFILE,      &json_options.json_dumpfile, "JSON output filename"},
   { 0, NULL,              NULL, NULL}
};

static bool
_json_parseOptions (int *pargc, char **argv, int *i)
{
	/* TODO: allow port-specific command line options to specify
	 * segment names here.
	 */
  int j=0;
  //char *stkmodel;

    /* check for arguments that have associated an integer variable */
    while(json_optionsTable[j].pparameter) {
      if(ISOPT( json_optionsTable[j].longOpt )) {
        (*(int *)json_optionsTable[j].pparameter)++;
        return TRUE;
      }
      j++;
    }
/*
    if(ISOPT(STACK_MODEL)) {
      stkmodel = getStringArg(STACK_MODEL, argv, i, *pargc);
      if(!STRCASECMP(stkmodel, "small"))picoBlaze_options.stack_model = 0;
      else if(!STRCASECMP(stkmodel, "large"))picoBlaze_options.stack_model = 1;
      else {
        fprintf(stderr, "Unknown stack model: %s", stkmodel);
        exit(EXIT_FAILURE);
      }
      return TRUE;
    }

    if(ISOPT(IVT_LOC)) {
      picoBlaze_options.ivt_loc = getIntArg(IVT_LOC, argv, i, *pargc);
      fprintf(stderr, "%s:%d setting interrupt vector addresses 0x%x\n", __FILE__, __LINE__, picoBlaze_options.ivt_loc);
      return TRUE;
    }

    if(ISOPT(USE_CRT)) {
      picoBlaze_options.no_crt = 0;
      picoBlaze_options.crt_name = Safe_strdup( getStringArg(USE_CRT, argv, i, *pargc) );

      return TRUE;
    }

    if (ISOPT(NO_OPTIMIZE_GOTO)) {
      picoBlaze_options.opt_flags |= OF_NO_OPTIMIZE_GOTO;
      return TRUE;
    }

    if(ISOPT(OPTIMIZE_CMP)) {
      picoBlaze_options.opt_flags |= OF_OPTIMIZE_CMP;
      return TRUE;
    }

    if (ISOPT(OPTIMIZE_DF)) {
      picoBlaze_options.opt_flags |= OF_OPTIMIZE_DF;
      return TRUE;
    }
*/

	if (ISOPT(GEN_JSON)) {
		json_options.json_flag = TRUE;
		if (ISOPT(GEN_JSONFILE)) {	// inside block because JSON and JSON-FILE have common starting substring checked in arguments
			json_options.json_dumpfile = Safe_strdup( getStringArg(GEN_JSONFILE, argv, i, *pargc) );
		}
		return TRUE;
	}

  return FALSE;
}

static void
_json_finaliseOptions (void)
{
	port->mem.default_local_map = port->mem.default_globl_map = xdata;
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
	istack =
		allocMap (0, 1, 0, 0, 0, 0, options.stack_loc, ISTACK_NAME,
			  'B', FPOINTER);

	/* also change xdata to be direct space since we can use lds/sts */
	xdata->direct = 1;

}

static void
_json_setDefaultOptions (void)
{
	options.stackAuto = 1;
	json_options.json_flag = 0;
  json_options.json_dumpfile = "iCodeDumpFile.txt";
}

static const char *
_json_getRegName (struct regs *reg)
{
	if (reg)
		return reg->name;
	return "err";
}

static void
_json_genAssemblerPreamble (FILE * of)
{

}

/* Generate interrupt vector table. */
static int
_json_genIVT (struct dbuf_s * oBuf, symbol ** interrupts, int maxInterrupts)
{
  return TRUE;
}

/* Indicate which extended bit operations this port supports */
static bool
hasExtBitOp (int op, int size)
{
  if (op == RRC
      || op == RLC
      || op == GETHBIT
     )
    return TRUE;
  else
    return FALSE;
}

/* Indicate the expense of an access to an output storage class */
static int
oclsExpense (struct memmap *oclass)
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
	//"linkjson", "", "\"$1\"", NULL
	NULL
};

/* $3 is replaced by assembler.debug_opts resp. port->assembler.plain_opts */
static const char *_asmCmd[] = {
	//"asjson", "$l" , "$3", "\"$1.s\"", NULL
	NULL
};

/* Globals */
PORT json_port = {
        TARGET_ID_JSON,
	"json",
	"Json iCodes",	/* Target name */
	NULL,			/* processor */
	{
         glue,
	 TRUE,			/* Emit glue around main */
	 MODEL_LARGE | MODEL_SMALL,
	 MODEL_SMALL,
         NULL,                       /* model == target */
	},
	{
	 _asmCmd,
         NULL,
	 "-plosgff",		/* Options with debug */
	 "-plosgff",		/* Options without debug */
	 0,
	".s",
	 NULL,			/* no do_assemble */
	},
	{
	       NULL,
         NULL,
	 NULL,
	 ".rel",
	 1},
	{
	 _defaultRules},
	{
	 /* Sizes: char, short, int, long, ptr, fptr, gptr, bit, float, max */
	 1, 2, 2, 4, 1, 2, 2, 1, 4, 4},
	
	 /* tags for generic pointers */
	{ 0x00, 0x40, 0x60, 0x80 },		/* far, near, xstack, code */
	
	{
	 "XSEG",
	 "STACK",
	 "CSEG",
	 "DSEG",
	 "ISEG",
	 NULL, //PSEG
	 "XSEG",
	 "BSEG",
	 "RSEG",
	 "GSINIT",
	 "OSEG",
	 "GSFINAL",
	 "HOME",
	 NULL, // initialized xdata
	 NULL, // a code copy of xiseg
	 "CONST   (CODE)",           // const_name - const data (code or not)
	 "CABS    (ABS,CODE)",       // cabs_name - const absolute data (code or not)
	 "XABS    (ABS,XDATA)",      // xabs_name - absolute xdata/pdata
	 "IABS    (ABS,DATA)",       // iabs_name - absolute idata/data
	 NULL,
	 NULL,
	 0,
	 },
        { NULL, NULL },
	{
	 -1, 1, 4, 1, 1, 0},
	/* pblaze hasn't any mul */
	{
          1, -1
        },
	{
          json_emitDebuggerSymbol
	},
	{
	  32,      /* maxCount */
	  2,          /* sizeofElement */
	  /* The rest of these costs are bogus. They approximate */
	  /* the behavior of src/SDCCicode.c 1.207 and earlier.  */
	  {2,2,2},    /* sizeofMatchJump[] */
	  {0,0,0},    /* sizeofRangeCompare[] */
	  0,          /* sizeofSubtract */
	  2,          /* sizeofDispatch */
	},
	"_",
	_json_init,
	_json_parseOptions,
	json_optionsTable,
	NULL,
	_json_finaliseOptions,
	_json_setDefaultOptions,
	json_assignRegisters,
	_json_getRegName,
	_json_keywords,
	_json_genAssemblerPreamble,
	NULL,				/* no genAssemblerEnd */
	_json_genIVT,
	NULL, // _json_genXINIT
	_json_genInitStartup,			/* genInitStartup */
	_json_reset_regparm,
	_json_regparm,
        NULL,
	NULL,
        NULL,
	hasExtBitOp,		/* hasExtBitOp */
	oclsExpense,		/* oclsExpense */
	FALSE,
	TRUE,			/* little endian */
	0,			/* leave lt */
	1,			/* transform gt ==> not le */
	0,			/* leave le */
	0,			/* leave ge */
	0,			/* leave !=  */
	0,			/* leave == */
	FALSE,                  /* No array initializer support. */
	0,                      /* no CSE cost estimation yet */
	NULL, 			/* no builtin functions */
	GPOINTER,		/* treat unqualified pointers as "generic" pointers */
	1,			/* reset labelKey to 1 */
	1,			/* globals & local static allowed */
	PORT_MAGIC
};



