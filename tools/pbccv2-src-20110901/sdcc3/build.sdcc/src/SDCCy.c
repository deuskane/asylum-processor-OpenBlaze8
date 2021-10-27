/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 24 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "SDCCglobl.h"
#include "SDCCsymt.h"
#include "SDCChasht.h"
#include "SDCCval.h"
#include "SDCCmem.h"
#include "SDCCast.h"
#include "port.h"
#include "newalloc.h"
#include "SDCCerr.h"
#include "SDCCutil.h"

extern int yyerror (char *);
extern FILE     *yyin;
int NestLevel = 0 ;     /* current NestLevel       */
int stackPtr  = 1 ;     /* stack pointer           */
int xstackPtr = 0 ;     /* xstack pointer          */
int reentrant = 0 ;
int blockNo   = 0 ;     /* sequential block number  */
int currBlockno=0 ;
int inCritical= 0 ;
int seqPointNo= 1 ;     /* sequence point number */
int ignoreTypedefType=0;
extern int yylex();
int yyparse(void);
extern int noLineno ;
char lbuff[1024];      /* local buffer */

/* break & continue stacks */
STACK_DCL(continueStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(breakStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(forStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(swStk   ,ast   *,MAX_NEST_LEVEL)
STACK_DCL(blockNum,int,MAX_NEST_LEVEL*3)

value *cenum = NULL  ;  /* current enumeration  type chain*/
bool uselessDecl = TRUE;

#define YYDEBUG 1


#line 115 "SDCCy.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SDCCY_H_INCLUDED
# define YY_YY_SDCCY_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    TYPE_NAME = 259,
    CONSTANT = 260,
    STRING_LITERAL = 261,
    SIZEOF = 262,
    TYPEOF = 263,
    OFFSETOF = 264,
    PTR_OP = 265,
    INC_OP = 266,
    DEC_OP = 267,
    LEFT_OP = 268,
    RIGHT_OP = 269,
    LE_OP = 270,
    GE_OP = 271,
    EQ_OP = 272,
    NE_OP = 273,
    AND_OP = 274,
    OR_OP = 275,
    MUL_ASSIGN = 276,
    DIV_ASSIGN = 277,
    MOD_ASSIGN = 278,
    ADD_ASSIGN = 279,
    SUB_ASSIGN = 280,
    LEFT_ASSIGN = 281,
    RIGHT_ASSIGN = 282,
    AND_ASSIGN = 283,
    XOR_ASSIGN = 284,
    OR_ASSIGN = 285,
    TYPEDEF = 286,
    EXTERN = 287,
    STATIC = 288,
    AUTO = 289,
    REGISTER = 290,
    CODE = 291,
    EEPROM = 292,
    INTERRUPT = 293,
    SFR = 294,
    SFR16 = 295,
    SFR32 = 296,
    AT = 297,
    SBIT = 298,
    REENTRANT = 299,
    USING = 300,
    XDATA = 301,
    DATA = 302,
    IDATA = 303,
    PDATA = 304,
    VAR_ARGS = 305,
    CRITICAL = 306,
    NONBANKED = 307,
    BANKED = 308,
    SHADOWREGS = 309,
    WPARAM = 310,
    BOOL = 311,
    CHAR = 312,
    SHORT = 313,
    INT = 314,
    LONG = 315,
    SIGNED = 316,
    UNSIGNED = 317,
    FLOAT = 318,
    DOUBLE = 319,
    FIXED16X16 = 320,
    CONST = 321,
    VOLATILE = 322,
    VOID = 323,
    BIT = 324,
    STRUCT = 325,
    UNION = 326,
    ENUM = 327,
    RANGE = 328,
    FAR = 329,
    CASE = 330,
    DEFAULT = 331,
    IF = 332,
    ELSE = 333,
    SWITCH = 334,
    WHILE = 335,
    DO = 336,
    FOR = 337,
    GOTO = 338,
    CONTINUE = 339,
    BREAK = 340,
    RETURN = 341,
    NAKED = 342,
    JAVANATIVE = 343,
    OVERLAY = 344,
    INLINEASM = 345,
    IFX = 346,
    ADDRESS_OF = 347,
    GET_VALUE_AT_ADDRESS = 348,
    SPIL = 349,
    UNSPIL = 350,
    GETHBIT = 351,
    GETABIT = 352,
    GETBYTE = 353,
    GETWORD = 354,
    BITWISEAND = 355,
    UNARYMINUS = 356,
    IPUSH = 357,
    IPOP = 358,
    PCALL = 359,
    ENDFUNCTION = 360,
    JUMPTABLE = 361,
    RRC = 362,
    RLC = 363,
    CAST = 364,
    CALL = 365,
    PARAM = 366,
    NULLOP = 367,
    BLOCK = 368,
    LABEL = 369,
    RECEIVE = 370,
    SEND = 371,
    ARRAYINIT = 372,
    DUMMY_READ_VOLATILE = 373,
    ENDCRITICAL = 374,
    SWAP = 375,
    INLINE = 376,
    RESTRICT = 377
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPE_NAME 259
#define CONSTANT 260
#define STRING_LITERAL 261
#define SIZEOF 262
#define TYPEOF 263
#define OFFSETOF 264
#define PTR_OP 265
#define INC_OP 266
#define DEC_OP 267
#define LEFT_OP 268
#define RIGHT_OP 269
#define LE_OP 270
#define GE_OP 271
#define EQ_OP 272
#define NE_OP 273
#define AND_OP 274
#define OR_OP 275
#define MUL_ASSIGN 276
#define DIV_ASSIGN 277
#define MOD_ASSIGN 278
#define ADD_ASSIGN 279
#define SUB_ASSIGN 280
#define LEFT_ASSIGN 281
#define RIGHT_ASSIGN 282
#define AND_ASSIGN 283
#define XOR_ASSIGN 284
#define OR_ASSIGN 285
#define TYPEDEF 286
#define EXTERN 287
#define STATIC 288
#define AUTO 289
#define REGISTER 290
#define CODE 291
#define EEPROM 292
#define INTERRUPT 293
#define SFR 294
#define SFR16 295
#define SFR32 296
#define AT 297
#define SBIT 298
#define REENTRANT 299
#define USING 300
#define XDATA 301
#define DATA 302
#define IDATA 303
#define PDATA 304
#define VAR_ARGS 305
#define CRITICAL 306
#define NONBANKED 307
#define BANKED 308
#define SHADOWREGS 309
#define WPARAM 310
#define BOOL 311
#define CHAR 312
#define SHORT 313
#define INT 314
#define LONG 315
#define SIGNED 316
#define UNSIGNED 317
#define FLOAT 318
#define DOUBLE 319
#define FIXED16X16 320
#define CONST 321
#define VOLATILE 322
#define VOID 323
#define BIT 324
#define STRUCT 325
#define UNION 326
#define ENUM 327
#define RANGE 328
#define FAR 329
#define CASE 330
#define DEFAULT 331
#define IF 332
#define ELSE 333
#define SWITCH 334
#define WHILE 335
#define DO 336
#define FOR 337
#define GOTO 338
#define CONTINUE 339
#define BREAK 340
#define RETURN 341
#define NAKED 342
#define JAVANATIVE 343
#define OVERLAY 344
#define INLINEASM 345
#define IFX 346
#define ADDRESS_OF 347
#define GET_VALUE_AT_ADDRESS 348
#define SPIL 349
#define UNSPIL 350
#define GETHBIT 351
#define GETABIT 352
#define GETBYTE 353
#define GETWORD 354
#define BITWISEAND 355
#define UNARYMINUS 356
#define IPUSH 357
#define IPOP 358
#define PCALL 359
#define ENDFUNCTION 360
#define JUMPTABLE 361
#define RRC 362
#define RLC 363
#define CAST 364
#define CALL 365
#define PARAM 366
#define NULLOP 367
#define BLOCK 368
#define LABEL 369
#define RECEIVE 370
#define SEND 371
#define ARRAYINIT 372
#define DUMMY_READ_VOLATILE 373
#define ENDCRITICAL 374
#define SWAP 375
#define INLINE 376
#define RESTRICT 377

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 70 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"

    symbol     *sym ;      /* symbol table pointer       */
    structdef  *sdef;      /* structure definition       */
    char       yychar[SDCC_NAME_MAX+1];
    sym_link   *lnk ;      /* declarator  or specifier   */
    int        yyint;      /* integer value returned     */
    value      *val ;      /* for integer constant       */
    initList   *ilist;     /* initial list               */
    const char *yyinline;  /* inlined assembler code     */
    ast        *asts;      /* expression tree            */

#line 423 "SDCCy.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SDCCY_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  102
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1523

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  147
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  106
/* YYNRULES -- Number of rules.  */
#define YYNRULES  289
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  435

#define YYUNDEFTOK  2
#define YYMAXUTOK   377


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   134,     2,     2,     2,   136,   129,     2,
     126,   127,   130,   131,   128,   132,   123,   135,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   142,   144,
     137,   143,   138,   141,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   124,     2,   125,   139,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   145,   140,   146,   133,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   140,   144,   145,   149,   152,   178,   183,
     192,   193,   197,   201,   204,   207,   210,   213,   216,   222,
     225,   228,   234,   243,   244,   252,   253,   253,   260,   267,
     268,   269,   270,   274,   278,   279,   280,   282,   286,   286,
     293,   293,   300,   302,   307,   308,   312,   313,   314,   315,
     316,   317,   318,   319,   323,   324,   325,   326,   327,   328,
     332,   333,   337,   338,   339,   340,   344,   345,   346,   350,
     351,   352,   356,   357,   358,   359,   360,   364,   365,   366,
     370,   371,   375,   376,   380,   381,   385,   386,   386,   391,
     392,   392,   397,   398,   398,   406,   407,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   466,   467,
     467,   471,   475,   482,   499,   502,   503,   508,   509,   514,
     515,   523,   524,   528,   529,   534,   538,   542,   546,   550,
     557,   564,   565,   578,   583,   588,   593,   598,   603,   608,
     613,   618,   622,   626,   630,   635,   640,   644,   648,   652,
     656,   660,   664,   673,   681,   686,   692,   701,   705,   713,
     717,   725,   736,   747,   760,   759,   808,   827,   828,   832,
     833,   841,   853,   854,   867,   893,   894,   902,   903,   916,
     932,   937,   942,   962,   976,   977,   978,   986,  1009,  1022,
    1035,  1036,  1044,  1045,  1049,  1050,  1058,  1059,  1091,  1092,
    1093,  1102,  1134,  1135,  1135,  1161,  1171,  1172,  1184,  1190,
    1229,  1236,  1239,  1241,  1249,  1250,  1258,  1259,  1263,  1264,
    1272,  1288,  1298,  1306,  1332,  1333,  1334,  1341,  1342,  1347,
    1353,  1359,  1367,  1368,  1369,  1381,  1381,  1405,  1406,  1407,
    1411,  1412,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,
    1434,  1443,  1453,  1455,  1462,  1462,  1471,  1479,  1483,  1484,
    1485,  1486,  1489,  1493,  1506,  1532,  1533,  1537,  1538,  1542,
    1543,  1548,  1548,  1556,  1556,  1581,  1595,  1610,  1629,  1629,
    1638,  1648,  1676,  1677,  1681,  1686,  1699,  1709,  1718,  1730
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPE_NAME", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "TYPEOF", "OFFSETOF", "PTR_OP", "INC_OP",
  "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP",
  "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN",
  "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "CODE", "EEPROM", "INTERRUPT", "SFR", "SFR16", "SFR32", "AT",
  "SBIT", "REENTRANT", "USING", "XDATA", "DATA", "IDATA", "PDATA",
  "VAR_ARGS", "CRITICAL", "NONBANKED", "BANKED", "SHADOWREGS", "WPARAM",
  "BOOL", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT",
  "DOUBLE", "FIXED16X16", "CONST", "VOLATILE", "VOID", "BIT", "STRUCT",
  "UNION", "ENUM", "RANGE", "FAR", "CASE", "DEFAULT", "IF", "ELSE",
  "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "NAKED", "JAVANATIVE", "OVERLAY", "INLINEASM", "IFX", "ADDRESS_OF",
  "GET_VALUE_AT_ADDRESS", "SPIL", "UNSPIL", "GETHBIT", "GETABIT",
  "GETBYTE", "GETWORD", "BITWISEAND", "UNARYMINUS", "IPUSH", "IPOP",
  "PCALL", "ENDFUNCTION", "JUMPTABLE", "RRC", "RLC", "CAST", "CALL",
  "PARAM", "NULLOP", "BLOCK", "LABEL", "RECEIVE", "SEND", "ARRAYINIT",
  "DUMMY_READ_VOLATILE", "ENDCRITICAL", "SWAP", "INLINE", "RESTRICT",
  "'.'", "'['", "']'", "'('", "')'", "','", "'&'", "'*'", "'+'", "'-'",
  "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'",
  "'='", "';'", "'{'", "'}'", "$accept", "file", "program",
  "external_definition", "function_definition", "function_attribute",
  "function_attributes", "function_body", "offsetof_member_designator",
  "$@1", "primary_expr", "string_literal", "postfix_expr", "$@2", "$@3",
  "argument_expr_list", "unary_expr", "unary_operator", "cast_expr",
  "multiplicative_expr", "additive_expr", "shift_expr", "relational_expr",
  "equality_expr", "and_expr", "exclusive_or_expr", "inclusive_or_expr",
  "logical_and_expr", "$@4", "logical_or_expr", "$@5", "conditional_expr",
  "$@6", "assignment_expr", "assignment_operator", "expr", "$@7",
  "constant_expr", "declaration", "declaration_specifiers",
  "declaration_specifiers_", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "function_specifier", "Interrupt_storage",
  "type_specifier", "sfr_reg_bit", "sfr_attributes",
  "struct_or_union_specifier", "$@8", "struct_or_union", "opt_stag",
  "stag", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "opt_assign_expr", "declarator",
  "declarator3", "function_declarator", "declarator2_function_attributes",
  "declarator2", "function_declarator2", "$@9", "pointer",
  "unqualified_pointer", "type_specifier_list", "type_specifier_list_",
  "identifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "type_name", "abstract_declarator",
  "abstract_declarator2", "$@10", "initializer", "initializer_list",
  "statement", "critical", "critical_statement", "labeled_statement",
  "@11", "start_block", "end_block", "compound_statement",
  "declaration_list", "statement_list", "expression_statement",
  "else_statement", "selection_statement", "$@12", "@13", "while", "do",
  "for", "iteration_statement", "$@14", "expr_opt", "jump_statement",
  "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,    46,    91,    93,    40,    41,    44,    38,
      42,    43,    45,   126,    33,    47,    37,    60,    62,    94,
     124,    63,    58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF (-366)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-193)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1144,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
     -29,  -366,  -366,   985,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,     9,  -366,  -366,    11,  -366,    41,
    1144,  -366,  -366,  -366,    47,  -366,  1361,  1361,  1361,  -366,
    -366,  -366,    62,  -366,   -51,   616,   -89,   -46,   254,    12,
    1236,  -366,  -366,  -366,  -366,  1027,  1037,   -39,  1037,  1037,
     885,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,    74,
    -366,   985,  -366,   -60,    80,   129,    48,   164,   -24,   -25,
     -47,   107,   -12,  -366,  -366,  -366,    62,    -6,     1,   -51,
    -366,    12,  -366,  -366,  -366,   -62,  -366,     6,   616,    12,
    -366,  -366,  -366,  -366,    27,  -366,   833,   -11,  -366,  -366,
    -366,    47,   414,  -366,   616,     8,   985,  -366,   985,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,   254,  -366,
     -89,  -366,  -366,    21,  1401,   885,  -366,   985,  -366,  1361,
    -366,  -366,   413,  -366,  -366,   106,    69,    52,  -366,  -366,
    -366,  -366,   985,   843,  -366,   985,   985,   985,   985,   985,
     985,   985,   985,   985,   985,   985,   985,   985,   985,   985,
     985,  -366,  -366,  -366,  -101,  -366,    32,    62,  -366,   -51,
      11,  -366,   596,  -366,    49,  -366,    71,  -366,  -366,   985,
    -366,    75,   100,  -366,  -366,  -366,    62,    70,    84,   743,
     114,  -366,  -366,   -54,  -366,   688,  -366,  -366,  -366,  -366,
     414,   500,  -366,  -366,   124,   688,   142,  -366,  -366,   123,
    -366,  -366,  -366,  1361,   108,  -366,  -366,  -366,  -366,  -366,
    -366,   143,   141,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,   985,  -366,  -366,   895,  1190,   -22,
    -366,    -9,   985,    62,    62,   -82,  -366,   144,   145,  -366,
    -366,  -366,   -60,   -60,    80,    80,   129,   129,   129,   129,
      48,    48,   164,   -24,   -25,   985,   985,   985,    62,  -366,
     985,  -366,   -98,  -366,   596,  -366,  -366,  1401,  -366,   130,
     132,   985,   985,   134,  -366,  -366,  -366,   -50,  -366,  -366,
    -366,  -366,   500,  -366,  -366,   985,   199,   985,  -366,    10,
     155,   156,  -366,  -366,  -366,    62,  -366,    62,  -366,   985,
    -366,   160,  -366,   162,   163,    -9,   975,   166,  -366,  -366,
    -366,  -366,  -366,   985,   -47,   107,     5,  -366,  -366,  -366,
    -366,   -79,   740,  -366,    50,  -366,  -366,   113,   118,  -366,
    -366,  -366,   121,   165,   167,   152,  1019,  -366,    20,  -366,
    1314,  -366,    86,  -366,  -366,  -366,  -366,  -366,  -366,   175,
    -366,  1361,  -366,   985,   586,  -366,  -366,  -366,   985,   -49,
    -366,   159,  -366,  -366,  -366,   985,   985,  -366,  -366,  -366,
     985,  -366,  -366,   177,  -366,  -366,  -366,  -366,    50,  -366,
     985,   688,   688,   688,   127,   158,    62,   -28,  -366,  -366,
    -366,   232,  -366,  -366,   169,   985,  -366,  -366,   688,  -366,
    -366,   187,  -366,   688,  -366
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   289,   156,   125,   126,   127,   128,   129,   147,   148,
     160,   162,   163,     0,   158,   146,   149,   150,   151,   133,
     134,   135,   136,   137,   138,   139,   144,   145,   141,   142,
     140,   152,   167,   168,     0,   130,   143,     0,   210,     0,
       3,     4,     6,     7,     0,   114,   115,   119,   117,   157,
     159,   154,   170,   155,     0,     0,   194,   193,   196,     0,
     206,   198,   161,    30,    33,     0,     0,     0,     0,     0,
       0,    54,    55,    56,    57,    58,    59,    34,    31,    46,
      60,     0,    62,    66,    69,    72,    77,    80,    82,    84,
      86,    89,    92,   111,   153,    29,     0,   183,     0,   190,
     192,     0,     1,     5,   112,     0,   121,   123,     0,     0,
     116,   120,   118,   164,   166,   171,     0,     0,   256,     8,
     263,     0,     0,    23,     0,   203,   131,    13,     0,    14,
      18,    21,    19,    20,    15,    16,    17,   197,    10,    22,
     195,   212,   208,   207,   211,     0,    50,     0,    52,     0,
      47,    48,    62,    95,   108,     0,   222,     0,    40,    42,
      43,    38,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    90,    93,     0,   184,   189,     0,   199,   191,
       0,   113,     0,     9,     0,   200,     0,   262,   250,     0,
     254,     0,     0,   275,   276,   277,     0,     0,     0,     0,
       0,   267,   257,     0,   265,     0,   248,   242,   258,   243,
       0,     0,   244,   245,     0,     0,     0,   246,   247,    29,
     264,    24,   202,     0,     0,   214,   132,    12,    11,   209,
     213,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,    97,     0,    32,   109,     0,     0,   224,
     223,   225,     0,     0,     0,     0,    36,     0,    44,    63,
      64,    65,    67,    68,    70,    71,    75,    76,    73,    74,
      78,    79,    81,    83,    85,     0,     0,     0,   185,   181,
       0,   187,     0,   122,     0,   237,   124,     0,   201,     0,
       0,     0,     0,     0,   285,   286,   287,     0,   249,   268,
     251,   260,     0,   266,   259,     0,     0,   282,   252,   222,
       0,   216,   218,   221,   205,     0,    51,     0,    96,     0,
     228,     0,   232,     0,     0,   226,     0,   235,    61,    41,
      39,    35,    37,     0,    88,    91,     0,   186,   188,   182,
     240,     0,     0,   172,   180,   253,   255,     0,     0,   284,
     288,   261,     0,     0,   283,     0,     0,   220,   224,   204,
       0,   215,     0,    25,   110,   229,   233,   227,   230,     0,
     234,     0,    45,     0,     0,   238,   165,   173,     0,     0,
     175,   177,   271,   273,   278,     0,   282,   217,   219,    26,
       0,    53,   231,     0,    94,   239,   241,   178,   180,   174,
       0,     0,     0,     0,     0,     0,     0,     0,   236,   176,
     179,   270,   274,   279,     0,   282,    27,    28,     0,   272,
     280,     0,   269,     0,   281
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -366,  -366,  -366,   271,  -366,   178,  -366,   207,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,   -26,   139,  -366,   -10,    88,
      89,    44,    90,   146,   149,   140,    36,    37,  -366,    35,
    -366,     4,  -366,  -141,  -366,   -64,  -366,  -107,     7,    29,
     184,  -366,   147,  -366,  -366,  -366,   -55,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,   -23,  -366,   -75,  -366,   148,
      46,  -366,   -36,     2,   294,    18,  -366,  -366,  -366,    28,
    -366,   279,  -366,  -366,  -229,  -366,   -21,   -37,  -242,  -249,
    -366,  -274,  -366,  -189,  -366,  -366,  -366,  -366,  -366,  -164,
     -17,   222,   125,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -365,  -366,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,   137,   138,   119,   372,   416,
      77,    78,    79,   264,   263,   267,    80,    81,   152,    83,
      84,    85,    86,    87,    88,    89,    90,    91,   285,    92,
     286,   153,   287,   154,   254,   213,   329,    94,   120,   121,
      45,   105,   106,    46,    47,   139,    48,    49,    50,    51,
     194,    52,   113,   114,   352,   353,   389,   390,    53,   184,
     185,   291,   107,    99,    55,   100,    57,    58,   233,   101,
      60,   354,   144,   234,   333,   321,   322,   323,   260,   261,
     381,   296,   351,   214,   215,   216,   217,   300,   122,   218,
     219,   124,   221,   222,   429,   223,   411,   412,   224,   225,
     226,   227,   413,   365,   228,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    98,    54,    82,   320,   141,   155,    43,   182,   196,
     335,     1,     1,     1,     1,     1,   334,    93,    56,   236,
     350,   237,   268,     1,    62,   182,   310,   288,    59,    44,
     288,   415,   313,   157,    97,  -192,   316,    61,   123,  -192,
      61,   102,    54,   341,    61,   289,   256,    43,   349,   384,
       1,   295,   115,     1,  -192,  -192,   311,   314,    56,    61,
     431,    54,    56,   172,   173,     1,   190,   385,    59,    44,
     165,   164,   109,   116,   256,   166,   167,   140,   256,   408,
     125,   155,   191,   155,   158,   159,   160,   149,   142,   240,
     309,   123,   299,   180,   360,   409,   186,   427,   265,   156,
     256,    61,   257,   189,   258,   178,    82,   231,   241,    61,
     406,   189,   242,   328,   179,   336,    82,   337,    82,   335,
      93,    61,   229,   313,   334,   235,   181,   140,   188,   183,
      93,   230,    93,   197,   257,   232,   366,    37,    37,   187,
      38,    38,   170,   171,   257,   307,   366,   383,   361,   192,
     331,    38,   403,   295,    96,   269,   270,   271,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,   239,  -169,    37,   156,   290,    37,    38,   156,   262,
      38,   176,   177,   348,   259,   174,   175,   186,   374,    82,
      61,   104,   388,   257,   297,   258,   298,   161,   162,    38,
     163,   301,   268,    93,   146,   148,   303,   150,   151,   399,
     400,   168,   169,   401,   304,   229,   276,   277,   278,   279,
     229,   229,   421,   422,   423,   229,   302,   230,   305,   379,
     110,   111,   112,   255,   256,   324,   325,   357,   358,   432,
     392,   256,   141,   295,   434,   393,   256,    82,   394,   256,
     315,   362,   338,   364,   424,   256,   272,   273,   308,   274,
     275,    93,   319,   339,   340,   318,   280,   281,   317,   327,
     326,   342,   355,   343,   356,    82,    82,    82,   359,   363,
      82,   407,   369,   367,   370,   375,   259,   319,   186,   376,
     377,   395,   126,   380,    93,   256,   396,   141,   127,   128,
     402,   410,   425,   420,   418,   129,   130,   131,   132,   133,
     428,   103,   229,   430,   433,   193,   238,   382,   391,    61,
     284,   344,   346,   345,   282,   371,    82,   373,   283,   387,
      98,   414,   364,   419,   347,   292,   417,   293,   108,   143,
      93,   134,   135,   136,   220,   312,     0,   368,     0,   398,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
       0,   364,     0,     0,     0,     0,    61,     0,    61,     0,
     189,     0,   391,    82,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,     0,     0,     0,   404,     0,     0,
       0,     0,    93,     0,   368,   319,     0,     0,     0,   319,
      82,     0,     0,     0,     0,     0,     0,     0,    61,     0,
     319,   229,   229,   229,    93,   117,   426,     1,     2,    63,
      64,    65,    66,    67,     0,    68,    69,     0,   229,     0,
       0,     0,     0,   229,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,     0,     3,     4,     5,     6,     7,
       8,     9,     0,    10,    11,    12,    13,    14,     0,     0,
      15,    16,    17,    18,     0,   198,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,     0,    27,
      28,    29,    30,    31,    32,    33,    34,     0,     0,   199,
     200,   201,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   117,     0,     1,   210,    63,    64,    65,    66,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
      70,     0,     0,    71,    72,    73,    74,    75,    76,     0,
       0,   198,     0,     0,     0,     0,   253,     0,   211,   118,
     212,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   199,   200,   201,     0,   202,
     203,   204,   205,   206,   207,   208,   209,     0,     0,     1,
     210,    63,    64,    65,    66,    67,     0,    68,    69,     1,
       0,    63,    64,    65,    66,    67,     0,    68,    69,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,     0,
       2,     0,     0,     0,     0,     0,    70,     0,     0,    71,
      72,    73,    74,    75,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   211,   118,   212,     3,     4,     5,
       6,     7,     8,     9,     0,    10,    11,    12,    13,    14,
       0,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,    31,    32,    33,    34,   117,
       0,     1,     0,    63,    64,    65,    66,    67,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,     0,     0,    71,    72,    73,    74,    75,
      76,     0,    70,     0,     0,    71,    72,    73,    74,    75,
      76,   294,   405,     0,     0,     0,     0,    35,    36,   198,
       0,   294,     0,     0,     2,     0,     1,     0,    63,    64,
      65,    66,    67,     0,    68,    69,     0,     0,     0,     0,
       0,   118,     0,   199,   200,   201,     0,   202,   203,   204,
     205,   206,   207,   208,   209,     0,     8,     9,   210,    10,
      11,    12,    13,    14,     0,     0,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,     0,    27,    28,    29,    30,    31,
      32,    33,    34,     0,    70,     0,     0,    71,    72,    73,
      74,    75,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   211,   118,     0,     0,     1,     0,    63,    64,
      65,    66,    67,     0,    68,    69,     1,     0,    63,    64,
      65,    66,    67,     0,    68,    69,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,    70,
       0,     0,    71,    72,    73,    74,    75,    76,     0,     0,
       0,     0,     0,     0,     0,     0,   386,   306,     1,     2,
      63,    64,    65,    66,    67,     0,    68,    69,     1,     0,
      63,    64,    65,    66,    67,     0,    68,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     8,     9,     0,    10,    11,    12,    13,    14,     0,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,     0,
      27,    28,    29,    30,    31,    32,    33,    34,   195,    70,
       0,     0,    71,    72,    73,    74,    75,    76,     0,    70,
     266,     0,    71,    72,    73,    74,    75,    76,     1,     0,
      63,    64,    65,    66,    67,     0,    68,    69,     1,     0,
      63,    64,    65,    66,    67,     0,    68,    69,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,     0,
       0,    70,     0,     0,    71,    72,    73,    74,    75,    76,
     330,    70,     1,     2,    71,    72,    73,    74,    75,    76,
       1,     0,    63,    64,    65,    66,    67,     0,    68,    69,
       1,     0,    63,    64,    65,    66,    67,     0,    68,    69,
       3,     4,     5,     6,     7,     8,     9,     0,    10,    11,
      12,    13,    14,     0,     0,    15,    16,    17,    18,     0,
       0,     0,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,     0,    27,    28,    29,    30,    31,    32,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
     378,    70,     0,     0,    71,    72,    73,    74,    75,    76,
       0,    70,     0,     0,    71,    72,    73,    74,    75,    76,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,   257,     0,   366,   332,     1,     2,    38,
       0,     0,     0,   145,     0,     0,    71,    72,    73,    74,
      75,    76,     0,   147,     0,     0,    71,    72,    73,    74,
      75,    76,     0,     0,     0,     3,     4,     5,     6,     7,
       8,     9,     0,    10,    11,    12,    13,    14,     0,     0,
      15,    16,    17,    18,     2,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,     0,    27,
      28,    29,    30,    31,    32,    33,    34,     0,     0,     0,
       0,     3,     4,     5,     6,     7,     8,     9,     0,    10,
      11,    12,    13,    14,     0,     0,    15,    16,    17,    18,
       2,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,     0,    27,    28,    29,    30,    31,
      32,    33,    34,     0,     0,    35,    36,     0,     0,     0,
      37,     0,     8,     9,    38,    10,    11,    12,    13,    14,
       0,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,    31,    32,    33,    34,     0,
       0,    35,    36,     0,   257,     0,   258,   332,     2,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     6,     7,
       8,     9,     0,    10,    11,    12,    13,    14,    36,     0,
      15,    16,    17,    18,   397,     2,    38,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,     0,    27,
      28,    29,    30,    31,    32,    33,    34,     0,     0,     0,
       0,     0,     3,     4,     5,     6,     7,     8,     9,     0,
      10,    11,    12,    13,    14,     2,     0,    15,    16,    17,
      18,     0,     0,     0,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,     0,    27,    28,    29,    30,
      31,    32,    33,    34,     0,    35,    36,     8,     9,     0,
      10,    11,    12,    13,    14,     0,     0,    15,    16,    17,
      18,     0,     0,     0,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,     0,    27,    28,    29,    30,
      31,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36
};

static const yytype_int16 yycheck[] =
{
       0,    37,     0,    13,   233,    60,    70,     0,    20,   116,
     259,     3,     3,     3,     3,     3,   258,    13,     0,   126,
     294,   128,   163,     3,    53,    20,   215,   128,     0,     0,
     128,   396,   221,    70,    34,   124,   225,    37,    55,   128,
      40,     0,    40,   125,    44,   146,   128,    40,   146,   128,
       3,   192,    52,     3,   143,   144,   220,   221,    40,    59,
     425,    59,    44,    15,    16,     3,   128,   146,    40,    40,
     130,    81,    44,   124,   128,   135,   136,    59,   128,   128,
     126,   145,   144,   147,    10,    11,    12,   126,    60,   144,
     144,   108,   199,   140,   144,   144,    96,   125,   162,    70,
     128,   101,   124,   101,   126,   129,   116,   124,   145,   109,
     384,   109,   149,   254,   139,   124,   126,   126,   128,   368,
     116,   121,   122,   312,   366,   125,    19,   109,   127,   141,
     126,   124,   128,   144,   124,   127,   126,   126,   126,   145,
     130,   130,    13,    14,   124,   209,   126,   142,   312,   143,
     257,   130,   381,   294,   145,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   143,   145,   126,   145,   143,   126,   130,   149,   127,
     130,    17,    18,   290,   156,   137,   138,   187,   329,   199,
     190,   144,   142,   124,   145,   126,   125,   123,   124,   130,
     126,   126,   343,   199,    65,    66,   206,    68,    69,   123,
     124,   131,   132,   127,   144,   215,   172,   173,   174,   175,
     220,   221,   411,   412,   413,   225,   126,   220,   144,   336,
      46,    47,    48,   127,   128,   127,   128,   301,   302,   428,
     127,   128,   297,   384,   433,   127,   128,   257,   127,   128,
     126,   315,   262,   317,   127,   128,   168,   169,   144,   170,
     171,   257,   233,   263,   264,   142,   176,   177,   126,   128,
     127,   127,   142,   128,   142,   285,   286,   287,   144,    80,
     290,   388,   127,   319,   128,   125,   258,   258,   288,   127,
     127,   126,    38,   127,   290,   128,   144,   352,    44,    45,
     125,   142,   144,   410,   127,    51,    52,    53,    54,    55,
      78,    40,   312,   144,   127,   108,   138,   343,   354,   319,
     180,   285,   287,   286,   178,   325,   336,   327,   179,   352,
     366,   395,   396,   408,   288,   187,   400,   190,    44,    60,
     336,    87,    88,    89,   122,   220,    -1,   319,    -1,   370,
      -1,    -1,    -1,    -1,   354,    -1,    -1,    -1,    -1,    -1,
      -1,   425,    -1,    -1,    -1,    -1,   366,    -1,   368,    -1,
     368,    -1,   408,   383,    -1,    -1,    -1,    -1,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   383,    -1,    -1,
      -1,    -1,   388,    -1,   366,   366,    -1,    -1,    -1,   370,
     410,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,
     381,   411,   412,   413,   410,     1,   416,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    -1,   428,    -1,
      -1,    -1,    -1,   433,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    75,
      76,    77,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,     1,    -1,     3,    90,     5,     6,     7,     8,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
      -1,    51,    -1,    -1,    -1,    -1,   143,    -1,   144,   145,
     146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    -1,    -1,     3,
      90,     5,     6,     7,     8,     9,    -1,    11,    12,     3,
      -1,     5,     6,     7,     8,     9,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
       4,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      -1,    -1,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,     1,
      -1,     3,    -1,     5,     6,     7,     8,     9,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   126,    -1,    -1,   129,   130,   131,   132,   133,
     134,   145,   146,    -1,    -1,    -1,    -1,   121,   122,    51,
      -1,   145,    -1,    -1,     4,    -1,     3,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,   145,    -1,    75,    76,    77,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    36,    37,    90,    39,
      40,    41,    42,    43,    -1,    -1,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,   126,    -1,    -1,   129,   130,   131,
     132,   133,   134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,    -1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,     3,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,   129,   130,   131,   132,   133,   134,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   146,   144,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,     3,    -1,
       5,     6,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,   125,   126,
      -1,    -1,   129,   130,   131,   132,   133,   134,    -1,   126,
     127,    -1,   129,   130,   131,   132,   133,   134,     3,    -1,
       5,     6,     7,     8,     9,    -1,    11,    12,     3,    -1,
       5,     6,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,
      -1,   126,    -1,    -1,   129,   130,   131,   132,   133,   134,
     125,   126,     3,     4,   129,   130,   131,   132,   133,   134,
       3,    -1,     5,     6,     7,     8,     9,    -1,    11,    12,
       3,    -1,     5,     6,     7,     8,     9,    -1,    11,    12,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,    -1,    -1,   129,   130,   131,   132,   133,   134,
      -1,   126,    -1,    -1,   129,   130,   131,   132,   133,   134,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,    -1,   124,    -1,   126,   127,     3,     4,   130,
      -1,    -1,    -1,   126,    -1,    -1,   129,   130,   131,   132,
     133,   134,    -1,   126,    -1,    -1,   129,   130,   131,   132,
     133,   134,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,     4,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    -1,    -1,    46,    47,    48,    49,
       4,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,    -1,    36,    37,   130,    39,    40,    41,    42,    43,
      -1,    -1,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,   121,   122,    -1,   124,    -1,   126,   127,     4,    -1,
     130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,   122,    -1,
      46,    47,    48,    49,    50,     4,   130,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,     4,    -1,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,   121,   122,    36,    37,    -1,
      39,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    31,    32,    33,    34,    35,    36,    37,
      39,    40,    41,    42,    43,    46,    47,    48,    49,    56,
      57,    58,    59,    60,    61,    62,    63,    65,    66,    67,
      68,    69,    70,    71,    72,   121,   122,   126,   130,   148,
     149,   150,   151,   185,   186,   187,   190,   191,   193,   194,
     195,   196,   198,   205,   210,   211,   212,   213,   214,   216,
     217,   252,    53,     5,     6,     7,     8,     9,    11,    12,
     126,   129,   130,   131,   132,   133,   134,   157,   158,   159,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   176,   178,   184,   252,   145,   252,   209,   210,
     212,   216,     0,   150,   144,   188,   189,   209,   211,   216,
     187,   187,   187,   199,   200,   252,   124,     1,   145,   154,
     185,   186,   235,   237,   238,   126,    38,    44,    45,    51,
      52,    53,    54,    55,    87,    88,    89,   152,   153,   192,
     212,   193,   216,   218,   219,   126,   163,   126,   163,   126,
     163,   163,   165,   178,   180,   182,   186,   224,    10,    11,
      12,   123,   124,   126,   165,   130,   135,   136,   131,   132,
      13,    14,    15,    16,   137,   138,    17,    18,   129,   139,
     140,    19,    20,   141,   206,   207,   252,   145,   127,   210,
     128,   144,   143,   154,   197,   125,   184,   144,    51,    75,
      76,    77,    79,    80,    81,    82,    83,    84,    85,    86,
      90,   144,   146,   182,   230,   231,   232,   233,   236,   237,
     238,   239,   240,   242,   245,   246,   247,   248,   251,   252,
     185,   237,   127,   215,   220,   252,   184,   184,   152,   216,
     193,   224,   224,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   143,   181,   127,   128,   124,   126,   216,
     225,   226,   127,   161,   160,   182,   127,   162,   180,   165,
     165,   165,   166,   166,   167,   167,   168,   168,   168,   168,
     169,   169,   170,   171,   172,   175,   177,   179,   128,   146,
     143,   208,   206,   189,   145,   180,   228,   145,   125,   184,
     234,   126,   126,   252,   144,   144,   144,   182,   144,   144,
     230,   236,   239,   230,   236,   126,   230,   126,   142,   186,
     221,   222,   223,   224,   127,   128,   127,   128,   180,   183,
     125,   184,   127,   221,   225,   226,   124,   126,   165,   252,
     252,   125,   127,   128,   173,   174,   176,   207,   184,   146,
     228,   229,   201,   202,   218,   142,   142,   182,   182,   144,
     144,   236,   182,    80,   182,   250,   126,   209,   216,   127,
     128,   252,   155,   252,   180,   125,   127,   127,   125,   184,
     127,   227,   162,   142,   128,   146,   146,   202,   142,   203,
     204,   209,   127,   127,   127,   126,   144,    50,   223,   123,
     124,   127,   125,   221,   178,   146,   228,   184,   128,   144,
     142,   243,   244,   249,   182,   250,   156,   182,   127,   204,
     184,   230,   230,   230,   127,   144,   252,   125,    78,   241,
     144,   250,   230,   127,   230
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   147,   148,   148,   149,   149,   150,   150,   151,   151,
     152,   152,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   154,   154,   155,   156,   155,   155,   157,
     157,   157,   157,   158,   159,   159,   159,   159,   160,   159,
     161,   159,   159,   159,   162,   162,   163,   163,   163,   163,
     163,   163,   163,   163,   164,   164,   164,   164,   164,   164,
     165,   165,   166,   166,   166,   166,   167,   167,   167,   168,
     168,   168,   169,   169,   169,   169,   169,   170,   170,   170,
     171,   171,   172,   172,   173,   173,   174,   175,   174,   176,
     177,   176,   178,   179,   178,   180,   180,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   182,   183,
     182,   184,   185,   185,   186,   187,   187,   187,   187,   187,
     187,   188,   188,   189,   189,   190,   190,   190,   190,   190,
     191,   192,   192,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     195,   195,   195,   195,   197,   196,   196,   198,   198,   199,
     199,   200,   201,   201,   202,   203,   203,   204,   204,   204,
     204,   205,   205,   205,   206,   206,   206,   207,   208,   208,
     209,   209,   210,   210,   211,   211,   212,   212,   213,   213,
     213,   213,   214,   215,   214,   214,   216,   216,   216,   216,
     217,   218,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   224,   224,   225,   225,   225,   226,   226,   226,
     226,   226,   226,   226,   226,   227,   226,   228,   228,   228,
     229,   229,   230,   230,   230,   230,   230,   230,   230,   230,
     231,   232,   233,   233,   234,   233,   235,   236,   237,   237,
     237,   237,   237,   238,   238,   239,   239,   240,   240,   241,
     241,   243,   242,   244,   242,   245,   246,   247,   249,   248,
     248,   248,   250,   250,   251,   251,   251,   251,   251,   252
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     2,     3,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     0,     4,     4,     1,
       1,     1,     3,     1,     1,     4,     3,     4,     0,     4,
       0,     4,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     0,     4,     1,
       0,     4,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     2,     3,     1,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     0,     6,     2,     1,     1,     1,
       0,     1,     1,     2,     3,     1,     3,     1,     2,     3,
       0,     4,     5,     2,     1,     2,     3,     2,     2,     0,
       1,     2,     1,     1,     1,     2,     1,     2,     1,     3,
       3,     4,     3,     0,     5,     4,     1,     2,     2,     3,
       1,     1,     1,     2,     1,     3,     1,     3,     1,     3,
       2,     1,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     2,     3,     3,     0,     5,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     3,     0,     3,     1,     1,     2,     3,
       3,     4,     2,     1,     2,     1,     2,     1,     2,     2,
       0,     0,     7,     0,     6,     1,     1,     1,     0,     6,
       7,     9,     0,     1,     3,     2,     2,     2,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 137 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        { if (!options.lessPedantic)
                    werror(W_EMPTY_SOURCE_FILE);
        }
#line 2198 "SDCCy.c"
    break;

  case 6:
#line 149 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                             {
                               blockNo=0;
                             }
#line 2206 "SDCCy.c"
    break;

  case 7:
#line 152 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                             {
                               ignoreTypedefType = 0;
                               if ((yyvsp[0].sym) && (yyvsp[0].sym)->type
                                && IS_FUNC((yyvsp[0].sym)->type))
                               {
                                   /* The only legal storage classes for
                                    * a function prototype (declaration)
                                    * are extern and static. extern is the
                                    * default. Thus, if this function isn't
                                    * explicitly marked static, mark it
                                    * extern.
                                    */
                                   if ((yyvsp[0].sym)->etype
                                    && IS_SPEC((yyvsp[0].sym)->etype)
                                    && !SPEC_STAT((yyvsp[0].sym)->etype))
                                   {
                                        SPEC_EXTR((yyvsp[0].sym)->etype) = 1;
                                   }
                               }
                               addSymChain (&(yyvsp[0].sym));
                               allocVariables ((yyvsp[0].sym)) ;
                               cleanUpLevel (SymbolTab,1);
                             }
#line 2234 "SDCCy.c"
    break;

  case 8:
#line 178 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        {   /* function type not specified */
                                   /* assume it to be 'int'       */
                                   addDecl((yyvsp[-1].sym),0,newIntLink());
                                   (yyval.asts) = createFunction((yyvsp[-1].sym),(yyvsp[0].asts));
                               }
#line 2244 "SDCCy.c"
    break;

  case 9:
#line 184 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                {
                                    pointerTypes((yyvsp[-1].sym)->type,copyLinkChain((yyvsp[-2].lnk)));
                                    addDecl((yyvsp[-1].sym),0,(yyvsp[-2].lnk));
                                    (yyval.asts) = createFunction((yyvsp[-1].sym),(yyvsp[0].asts));
                                }
#line 2254 "SDCCy.c"
    break;

  case 11:
#line 193 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                            { (yyval.lnk) = mergeSpec((yyvsp[-1].lnk),(yyvsp[0].lnk),"function_attribute"); }
#line 2260 "SDCCy.c"
    break;

  case 12:
#line 197 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                          {
                        (yyval.lnk) = newLink(SPECIFIER) ;
                        FUNC_REGBANK((yyval.lnk)) = (int) ulFromVal(constExprValue((yyvsp[0].asts),TRUE));
                     }
#line 2269 "SDCCy.c"
    break;

  case 13:
#line 201 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {  (yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISREENT((yyval.lnk))=1;
                     }
#line 2277 "SDCCy.c"
    break;

  case 14:
#line 204 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {  (yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISCRITICAL((yyval.lnk)) = 1;
                     }
#line 2285 "SDCCy.c"
    break;

  case 15:
#line 207 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {  (yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISNAKED((yyval.lnk))=1;
                     }
#line 2293 "SDCCy.c"
    break;

  case 16:
#line 210 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {  (yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISJAVANATIVE((yyval.lnk))=1;
                     }
#line 2301 "SDCCy.c"
    break;

  case 17:
#line 213 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {  (yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISOVERLAY((yyval.lnk))=1;
                     }
#line 2309 "SDCCy.c"
    break;

  case 18:
#line 216 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_NONBANKED((yyval.lnk)) = 1;
                        if (FUNC_BANKED((yyval.lnk))) {
                            werror(W_BANKED_WITH_NONBANKED);
                        }
                     }
#line 2320 "SDCCy.c"
    break;

  case 19:
#line 222 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISSHADOWREGS((yyval.lnk)) = 1;
                     }
#line 2328 "SDCCy.c"
    break;

  case 20:
#line 225 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_ISWPARAM((yyval.lnk)) = 1;
                     }
#line 2336 "SDCCy.c"
    break;

  case 21:
#line 228 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_BANKED((yyval.lnk)) = 1;
                        if (FUNC_NONBANKED((yyval.lnk))) {
                            werror(W_BANKED_WITH_NONBANKED);
                        }
                     }
#line 2347 "SDCCy.c"
    break;

  case 22:
#line 235 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {
                        (yyval.lnk) = newLink (SPECIFIER) ;
                        FUNC_INTNO((yyval.lnk)) = (yyvsp[0].yyint) ;
                        FUNC_ISISR((yyval.lnk)) = 1;
                     }
#line 2357 "SDCCy.c"
    break;

  case 24:
#line 245 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {
                       werror (E_OLD_STYLE, ((yyvsp[-1].sym) ? (yyvsp[-1].sym)->name: "")) ;
                       exit (1);
                     }
#line 2366 "SDCCy.c"
    break;

  case 25:
#line 252 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.asts) = newAst_VALUE (symbolVal ((yyvsp[0].sym))); }
#line 2372 "SDCCy.c"
    break;

  case 26:
#line 253 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { ignoreTypedefType = 1; }
#line 2378 "SDCCy.c"
    break;

  case 27:
#line 254 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {
                       ignoreTypedefType = 0;
                       (yyvsp[0].sym) = newSymbol ((yyvsp[0].sym)->name, NestLevel);
                       (yyvsp[0].sym)->implicit = 1;
                       (yyval.asts) = newNode ('.', (yyvsp[-3].asts), newAst_VALUE (symbolVal ((yyvsp[0].sym)))) ;
                     }
#line 2389 "SDCCy.c"
    break;

  case 28:
#line 261 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {
                       (yyval.asts) = newNode ('[', (yyvsp[-3].asts), (yyvsp[-1].asts));
                     }
#line 2397 "SDCCy.c"
    break;

  case 29:
#line 267 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.asts) = newAst_VALUE (symbolVal ((yyvsp[0].sym))); }
#line 2403 "SDCCy.c"
    break;

  case 30:
#line 268 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.asts) = newAst_VALUE ((yyvsp[0].val)); }
#line 2409 "SDCCy.c"
    break;

  case 32:
#line 270 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.asts) = (yyvsp[-1].asts); }
#line 2415 "SDCCy.c"
    break;

  case 33:
#line 274 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.asts) = newAst_VALUE((yyvsp[0].val)); }
#line 2421 "SDCCy.c"
    break;

  case 35:
#line 279 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.asts) = newNode  ('[', (yyvsp[-3].asts), (yyvsp[-1].asts)) ; }
#line 2427 "SDCCy.c"
    break;

  case 36:
#line 280 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.asts) = newNode  (CALL,(yyvsp[-2].asts),NULL);
                                          (yyval.asts)->left->funcName = 1;}
#line 2434 "SDCCy.c"
    break;

  case 37:
#line 283 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
          {
            (yyval.asts) = newNode  (CALL,(yyvsp[-3].asts),(yyvsp[-1].asts)) ; (yyval.asts)->left->funcName = 1;
          }
#line 2442 "SDCCy.c"
    break;

  case 38:
#line 286 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      { ignoreTypedefType = 1; }
#line 2448 "SDCCy.c"
    break;

  case 39:
#line 287 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      {
                        ignoreTypedefType = 0;
                        (yyvsp[0].sym) = newSymbol((yyvsp[0].sym)->name,NestLevel);
                        (yyvsp[0].sym)->implicit = 1;
                        (yyval.asts) = newNode(PTR_OP,newNode('&',(yyvsp[-3].asts),NULL),newAst_VALUE(symbolVal((yyvsp[0].sym))));
                      }
#line 2459 "SDCCy.c"
    break;

  case 40:
#line 293 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         { ignoreTypedefType = 1; }
#line 2465 "SDCCy.c"
    break;

  case 41:
#line 294 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      {
                        ignoreTypedefType = 0;
                        (yyvsp[0].sym) = newSymbol((yyvsp[0].sym)->name,NestLevel);
                        (yyvsp[0].sym)->implicit = 1;
                        (yyval.asts) = newNode(PTR_OP,(yyvsp[-3].asts),newAst_VALUE(symbolVal((yyvsp[0].sym))));
                      }
#line 2476 "SDCCy.c"
    break;

  case 42:
#line 301 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      { (yyval.asts) = newNode(INC_OP,(yyvsp[-1].asts),NULL);}
#line 2482 "SDCCy.c"
    break;

  case 43:
#line 303 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      { (yyval.asts) = newNode(DEC_OP,(yyvsp[-1].asts),NULL); }
#line 2488 "SDCCy.c"
    break;

  case 45:
#line 308 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                            { (yyval.asts) = newNode(PARAM,(yyvsp[-2].asts),(yyvsp[0].asts)); }
#line 2494 "SDCCy.c"
    break;

  case 47:
#line 313 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newNode (INC_OP, NULL, (yyvsp[0].asts)); }
#line 2500 "SDCCy.c"
    break;

  case 48:
#line 314 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newNode (DEC_OP, NULL, (yyvsp[0].asts)); }
#line 2506 "SDCCy.c"
    break;

  case 49:
#line 315 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newNode ((yyvsp[-1].yyint), (yyvsp[0].asts), NULL); }
#line 2512 "SDCCy.c"
    break;

  case 50:
#line 316 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newNode (SIZEOF, NULL, (yyvsp[0].asts)); }
#line 2518 "SDCCy.c"
    break;

  case 51:
#line 317 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newAst_VALUE (sizeofOp ((yyvsp[-1].lnk))); }
#line 2524 "SDCCy.c"
    break;

  case 52:
#line 318 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { (yyval.asts) = newNode (TYPEOF, NULL, (yyvsp[0].asts)); }
#line 2530 "SDCCy.c"
    break;

  case 53:
#line 319 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                               { (yyval.asts) = offsetofOp((yyvsp[-3].lnk), (yyvsp[-1].asts)); }
#line 2536 "SDCCy.c"
    break;

  case 54:
#line 323 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '&' ;}
#line 2542 "SDCCy.c"
    break;

  case 55:
#line 324 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '*' ;}
#line 2548 "SDCCy.c"
    break;

  case 56:
#line 325 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '+' ;}
#line 2554 "SDCCy.c"
    break;

  case 57:
#line 326 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '-' ;}
#line 2560 "SDCCy.c"
    break;

  case 58:
#line 327 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '~' ;}
#line 2566 "SDCCy.c"
    break;

  case 59:
#line 328 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            { (yyval.yyint) = '!' ;}
#line 2572 "SDCCy.c"
    break;

  case 61:
#line 333 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyval.asts) = newNode(CAST,newAst_LINK((yyvsp[-2].lnk)),(yyvsp[0].asts)); }
#line 2578 "SDCCy.c"
    break;

  case 63:
#line 338 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       { (yyval.asts) = newNode('*',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2584 "SDCCy.c"
    break;

  case 64:
#line 339 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       { (yyval.asts) = newNode('/',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2590 "SDCCy.c"
    break;

  case 65:
#line 340 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       { (yyval.asts) = newNode('%',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2596 "SDCCy.c"
    break;

  case 67:
#line 345 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                           { (yyval.asts)=newNode('+',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2602 "SDCCy.c"
    break;

  case 68:
#line 346 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                           { (yyval.asts)=newNode('-',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2608 "SDCCy.c"
    break;

  case 70:
#line 351 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       { (yyval.asts) = newNode(LEFT_OP,(yyvsp[-2].asts),(yyvsp[0].asts)); }
#line 2614 "SDCCy.c"
    break;

  case 71:
#line 352 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       { (yyval.asts) = newNode(RIGHT_OP,(yyvsp[-2].asts),(yyvsp[0].asts)); }
#line 2620 "SDCCy.c"
    break;

  case 73:
#line 357 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                      { (yyval.asts) = newNode('<',  (yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2626 "SDCCy.c"
    break;

  case 74:
#line 358 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                      { (yyval.asts) = newNode('>',  (yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2632 "SDCCy.c"
    break;

  case 75:
#line 359 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                      { (yyval.asts) = newNode(LE_OP,(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2638 "SDCCy.c"
    break;

  case 76:
#line 360 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                      { (yyval.asts) = newNode(GE_OP,(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2644 "SDCCy.c"
    break;

  case 78:
#line 365 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                         { (yyval.asts) = newNode(EQ_OP,(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2650 "SDCCy.c"
    break;

  case 79:
#line 366 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                         { (yyval.asts) = newNode(NE_OP,(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2656 "SDCCy.c"
    break;

  case 81:
#line 371 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyval.asts) = newNode('&',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2662 "SDCCy.c"
    break;

  case 83:
#line 376 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.asts) = newNode('^',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2668 "SDCCy.c"
    break;

  case 85:
#line 381 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                             { (yyval.asts) = newNode('|',(yyvsp[-2].asts),(yyvsp[0].asts));}
#line 2674 "SDCCy.c"
    break;

  case 87:
#line 386 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                             { seqPointNo++;}
#line 2680 "SDCCy.c"
    break;

  case 88:
#line 387 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyval.asts) = newNode(AND_OP,(yyvsp[-3].asts),(yyvsp[0].asts));}
#line 2686 "SDCCy.c"
    break;

  case 90:
#line 392 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           { seqPointNo++;}
#line 2692 "SDCCy.c"
    break;

  case 91:
#line 393 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyval.asts) = newNode(OR_OP,(yyvsp[-3].asts),(yyvsp[0].asts)); }
#line 2698 "SDCCy.c"
    break;

  case 93:
#line 398 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         { seqPointNo++;}
#line 2704 "SDCCy.c"
    break;

  case 94:
#line 399 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {
                        (yyval.asts) = newNode(':',(yyvsp[-2].asts),(yyvsp[0].asts)) ;
                        (yyval.asts) = newNode('?',(yyvsp[-5].asts),(yyval.asts)) ;
                     }
#line 2713 "SDCCy.c"
    break;

  case 96:
#line 408 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     {

                             switch ((yyvsp[-1].yyint)) {
                             case '=':
                                     (yyval.asts) = newNode((yyvsp[-1].yyint),(yyvsp[-2].asts),(yyvsp[0].asts));
                                     break;
                             case MUL_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '*', (yyvsp[0].asts));
                                     break;
                             case DIV_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '/', (yyvsp[0].asts));
                                     break;
                             case MOD_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '%', (yyvsp[0].asts));
                                     break;
                             case ADD_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '+', (yyvsp[0].asts));
                                     break;
                             case SUB_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '-', (yyvsp[0].asts));
                                     break;
                             case LEFT_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), LEFT_OP, (yyvsp[0].asts));
                                     break;
                             case RIGHT_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), RIGHT_OP, (yyvsp[0].asts));
                                     break;
                             case AND_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '&', (yyvsp[0].asts));
                                     break;
                             case XOR_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '^', (yyvsp[0].asts));
                                     break;
                             case OR_ASSIGN:
                                     (yyval.asts) = createRMW((yyvsp[-2].asts), '|', (yyvsp[0].asts));
                                     break;
                             default :
                                     (yyval.asts) = NULL;
                             }

                     }
#line 2759 "SDCCy.c"
    break;

  case 97:
#line 452 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.yyint) = '=' ;}
#line 2765 "SDCCy.c"
    break;

  case 109:
#line 467 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
              { seqPointNo++;}
#line 2771 "SDCCy.c"
    break;

  case 110:
#line 467 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                               { (yyval.asts) = newNode(',',(yyvsp[-3].asts),(yyvsp[0].asts));}
#line 2777 "SDCCy.c"
    break;

  case 112:
#line 476 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
      {
         if (uselessDecl)
           werror(W_USELESS_DECL);
         uselessDecl = TRUE;
         (yyval.sym) = NULL ;
      }
#line 2788 "SDCCy.c"
    break;

  case 113:
#line 483 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
      {
         /* add the specifier list to the id */
         symbol *sym , *sym1;

         for (sym1 = sym = reverseSyms((yyvsp[-1].sym));sym != NULL;sym = sym->next) {
             sym_link *lnk = copyLinkChain((yyvsp[-2].lnk));
             /* do the pointer stuff */
             pointerTypes(sym->type,lnk);
             addDecl (sym,0,lnk) ;
         }

         uselessDecl = TRUE;
         (yyval.sym) = sym1 ;
      }
#line 2807 "SDCCy.c"
    break;

  case 114:
#line 499 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                 { (yyval.lnk) = finalizeSpec((yyvsp[0].lnk)); }
#line 2813 "SDCCy.c"
    break;

  case 115:
#line 502 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                                        { (yyval.lnk) = (yyvsp[0].lnk); }
#line 2819 "SDCCy.c"
    break;

  case 116:
#line 503 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                     {
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     (yyval.lnk) = mergeDeclSpec((yyvsp[-1].lnk), (yyvsp[0].lnk), "storage_class_specifier declaration_specifiers - skipped");
   }
#line 2829 "SDCCy.c"
    break;

  case 117:
#line 508 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                    { (yyval.lnk) = (yyvsp[0].lnk); }
#line 2835 "SDCCy.c"
    break;

  case 118:
#line 509 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                    {
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     (yyval.lnk) = mergeDeclSpec((yyvsp[-1].lnk), (yyvsp[0].lnk), "type_specifier declaration_specifiers - skipped");
   }
#line 2845 "SDCCy.c"
    break;

  case 119:
#line 514 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                    { (yyval.lnk) = (yyvsp[0].lnk); }
#line 2851 "SDCCy.c"
    break;

  case 120:
#line 515 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                    {
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     (yyval.lnk) = mergeDeclSpec((yyvsp[-1].lnk), (yyvsp[0].lnk), "function_specifier declaration_specifiers - skipped");
   }
#line 2861 "SDCCy.c"
    break;

  case 122:
#line 524 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                   { (yyvsp[0].sym)->next = (yyvsp[-2].sym) ; (yyval.sym) = (yyvsp[0].sym);}
#line 2867 "SDCCy.c"
    break;

  case 123:
#line 528 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyvsp[0].sym)->ival = NULL ; }
#line 2873 "SDCCy.c"
    break;

  case 124:
#line 529 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                 { (yyvsp[-2].sym)->ival = (yyvsp[0].ilist)   ; }
#line 2879 "SDCCy.c"
    break;

  case 125:
#line 534 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_TYPEDEF((yyval.lnk)) = 1 ;
               }
#line 2888 "SDCCy.c"
    break;

  case 126:
#line 538 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink(SPECIFIER);
                  SPEC_EXTR((yyval.lnk)) = 1 ;
               }
#line 2897 "SDCCy.c"
    break;

  case 127:
#line 542 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_STAT((yyval.lnk)) = 1 ;
               }
#line 2906 "SDCCy.c"
    break;

  case 128:
#line 546 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_AUTO  ;
               }
#line 2915 "SDCCy.c"
    break;

  case 129:
#line 550 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_REGISTER ;
               }
#line 2924 "SDCCy.c"
    break;

  case 130:
#line 557 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_INLINE((yyval.lnk)) = 1 ;
               }
#line 2933 "SDCCy.c"
    break;

  case 131:
#line 564 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               { (yyval.yyint) = INTNO_UNSPEC ; }
#line 2939 "SDCCy.c"
    break;

  case 132:
#line 566 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        { int intno = (int) ulFromVal(constExprValue((yyvsp[0].asts),TRUE));
          if ((intno >= 0) && (intno <= INTNO_MAX))
            (yyval.yyint) = intno;
          else
            {
              werror(E_INT_BAD_INTNO, intno);
              (yyval.yyint) = INTNO_UNSPEC;
            }
        }
#line 2953 "SDCCy.c"
    break;

  case 133:
#line 578 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_BOOL   ;
                  ignoreTypedefType = 1;
               }
#line 2963 "SDCCy.c"
    break;

  case 134:
#line 583 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_CHAR  ;
                  ignoreTypedefType = 1;
               }
#line 2973 "SDCCy.c"
    break;

  case 135:
#line 588 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_SHORT((yyval.lnk)) = 1 ;
                  ignoreTypedefType = 1;
               }
#line 2983 "SDCCy.c"
    break;

  case 136:
#line 593 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_INT   ;
                  ignoreTypedefType = 1;
               }
#line 2993 "SDCCy.c"
    break;

  case 137:
#line 598 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_LONG((yyval.lnk)) = 1       ;
                  ignoreTypedefType = 1;
               }
#line 3003 "SDCCy.c"
    break;

  case 138:
#line 603 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  (yyval.lnk)->select.s.b_signed = 1;
                  ignoreTypedefType = 1;
               }
#line 3013 "SDCCy.c"
    break;

  case 139:
#line 608 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_USIGN((yyval.lnk)) = 1      ;
                  ignoreTypedefType = 1;
               }
#line 3023 "SDCCy.c"
    break;

  case 140:
#line 613 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_VOID  ;
                  ignoreTypedefType = 1;
               }
#line 3033 "SDCCy.c"
    break;

  case 141:
#line 618 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_CONST((yyval.lnk)) = 1;
               }
#line 3042 "SDCCy.c"
    break;

  case 142:
#line 622 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_VOLATILE((yyval.lnk)) = 1 ;
               }
#line 3051 "SDCCy.c"
    break;

  case 143:
#line 626 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_RESTRICT((yyval.lnk)) = 1 ;
               }
#line 3060 "SDCCy.c"
    break;

  case 144:
#line 630 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_FLOAT;
                  ignoreTypedefType = 1;
               }
#line 3070 "SDCCy.c"
    break;

  case 145:
#line 635 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_FIXED16X16;
                  ignoreTypedefType = 1;
               }
#line 3080 "SDCCy.c"
    break;

  case 146:
#line 640 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_XDATA  ;
               }
#line 3089 "SDCCy.c"
    break;

  case 147:
#line 644 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_CODE ;
               }
#line 3098 "SDCCy.c"
    break;

  case 148:
#line 648 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_EEPROM ;
               }
#line 3107 "SDCCy.c"
    break;

  case 149:
#line 652 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_DATA   ;
               }
#line 3116 "SDCCy.c"
    break;

  case 150:
#line 656 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_IDATA  ;
               }
#line 3125 "SDCCy.c"
    break;

  case 151:
#line 660 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_PDATA  ;
               }
#line 3134 "SDCCy.c"
    break;

  case 152:
#line 664 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {
                  (yyval.lnk)=newLink(SPECIFIER);
                  SPEC_NOUN((yyval.lnk)) = V_BIT   ;
                  SPEC_SCLS((yyval.lnk)) = S_BIT   ;
                  SPEC_BLEN((yyval.lnk)) = 1;
                  SPEC_BSTR((yyval.lnk)) = 0;
                  ignoreTypedefType = 1;
               }
#line 3147 "SDCCy.c"
    break;

  case 153:
#line 673 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      {
                  (yyval.lnk)=newLink(SPECIFIER);
                  /* add this to the storage class specifier  */
                  SPEC_ABSA((yyval.lnk)) = 1;   /* set the absolute addr flag */
                  /* now get the abs addr from value */
                  SPEC_ADDR((yyval.lnk)) = (unsigned int) ulFromVal(constExprValue((yyvsp[0].asts),TRUE)) ;
               }
#line 3159 "SDCCy.c"
    break;

  case 154:
#line 681 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                {
                                   uselessDecl = FALSE;
                                   (yyval.lnk) = (yyvsp[0].lnk) ;
                                   ignoreTypedefType = 1;
                                }
#line 3169 "SDCCy.c"
    break;

  case 155:
#line 686 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        {
                           cenum = NULL ;
                           uselessDecl = FALSE;
                           ignoreTypedefType = 1;
                           (yyval.lnk) = (yyvsp[0].lnk) ;
                        }
#line 3180 "SDCCy.c"
    break;

  case 156:
#line 693 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
            symbol *sym;
            sym_link   *p  ;
            sym = findSym(TypedefTab,NULL,(yyvsp[0].yychar)) ;
            (yyval.lnk) = p = copyLinkChain(sym ? sym->type : NULL);
            SPEC_TYPEDEF(getSpec(p)) = 0;
            ignoreTypedefType = 1;
         }
#line 3193 "SDCCy.c"
    break;

  case 158:
#line 705 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            {
               (yyval.lnk) = newLink(SPECIFIER) ;
               SPEC_NOUN((yyval.lnk)) = V_SBIT;
               SPEC_SCLS((yyval.lnk)) = S_SBIT;
               SPEC_BLEN((yyval.lnk)) = 1;
               SPEC_BSTR((yyval.lnk)) = 0;
               ignoreTypedefType = 1;
            }
#line 3206 "SDCCy.c"
    break;

  case 160:
#line 717 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 0;
               SPEC_NOUN((yyval.lnk))    = V_CHAR;
               SPEC_SCLS((yyval.lnk))    = S_SFR ;
               SPEC_USIGN((yyval.lnk))   = 1 ;
               ignoreTypedefType = 1;
            }
#line 3219 "SDCCy.c"
    break;

  case 161:
#line 725 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 1;
               SPEC_NOUN((yyval.lnk))    = V_CHAR;
               SPEC_SCLS((yyval.lnk))    = S_SFR ;
               SPEC_USIGN((yyval.lnk))   = 1 ;
               ignoreTypedefType = 1;
            }
#line 3232 "SDCCy.c"
    break;

  case 162:
#line 736 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 0;
               SPEC_NOUN((yyval.lnk))    = V_INT;
               SPEC_SCLS((yyval.lnk))    = S_SFR;
               SPEC_USIGN((yyval.lnk))   = 1 ;
               ignoreTypedefType = 1;
            }
#line 3245 "SDCCy.c"
    break;

  case 163:
#line 747 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
            {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 0;
               SPEC_NOUN((yyval.lnk))    = V_INT;
               SPEC_SCLS((yyval.lnk))    = S_SFR;
               SPEC_LONG((yyval.lnk))    = 1;
               SPEC_USIGN((yyval.lnk))   = 1;
               ignoreTypedefType = 1;
            }
#line 3259 "SDCCy.c"
    break;

  case 164:
#line 760 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
           if (!(yyvsp[0].sdef)->type)
             {
               (yyvsp[0].sdef)->type = (yyvsp[-1].yyint);
             }
           else
             {
               if ((yyvsp[0].sdef)->type != (yyvsp[-1].yyint))
                 werror(E_BAD_TAG, (yyvsp[0].sdef)->tag, (yyvsp[-1].yyint)==STRUCT ? "struct" : "union");
             }

        }
#line 3276 "SDCCy.c"
    break;

  case 165:
#line 773 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
           structdef *sdef ;
           symbol *sym, *dsym;

           // check for errors in structure members
           for (sym=(yyvsp[-1].sym); sym; sym=sym->next) {
             if (IS_ABSOLUTE(sym->etype)) {
               werrorfl(sym->fileDef, sym->lineDef, E_NOT_ALLOWED, "'at'");
               SPEC_ABSA(sym->etype) = 0;
             }
             if (IS_SPEC(sym->etype) && SPEC_SCLS(sym->etype)) {
               werrorfl(sym->fileDef, sym->lineDef, E_NOT_ALLOWED, "storage class");
               printTypeChainRaw (sym->type,NULL);
               SPEC_SCLS(sym->etype) = 0;
             }
             for (dsym=sym->next; dsym; dsym=dsym->next) {
               if (*dsym->name && strcmp(sym->name, dsym->name)==0) {
                 werrorfl(sym->fileDef, sym->lineDef, E_DUPLICATE_MEMBER,
                        (yyvsp[-5].yyint)==STRUCT ? "struct" : "union", sym->name);
                 werrorfl(dsym->fileDef, dsym->lineDef, E_PREVIOUS_DEF);
               }
             }
           }

           /* Create a structdef   */
           sdef = (yyvsp[-4].sdef) ;
           sdef->fields   = reverseSyms((yyvsp[-1].sym)) ;   /* link the fields */
           sdef->size  = compStructSize((yyvsp[-5].yyint),sdef);   /* update size of  */
           promoteAnonStructs ((yyvsp[-5].yyint), sdef);

           /* Create the specifier */
           (yyval.lnk) = newLink (SPECIFIER) ;
           SPEC_NOUN((yyval.lnk)) = V_STRUCT;
           SPEC_STRUCT((yyval.lnk))= sdef ;
        }
#line 3316 "SDCCy.c"
    break;

  case 166:
#line 809 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
            (yyval.lnk) = newLink(SPECIFIER) ;
            SPEC_NOUN((yyval.lnk)) = V_STRUCT;
            SPEC_STRUCT((yyval.lnk)) = (yyvsp[0].sdef);

           if (!(yyvsp[0].sdef)->type)
             {
               (yyvsp[0].sdef)->type = (yyvsp[-1].yyint);
             }
           else
             {
               if ((yyvsp[0].sdef)->type != (yyvsp[-1].yyint))
                 werror(E_BAD_TAG, (yyvsp[0].sdef)->tag, (yyvsp[-1].yyint)==STRUCT ? "struct" : "union");
             }
         }
#line 3336 "SDCCy.c"
    break;

  case 167:
#line 827 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.yyint) = STRUCT ; ignoreTypedefType = 1; }
#line 3342 "SDCCy.c"
    break;

  case 168:
#line 828 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { (yyval.yyint) = UNION  ; ignoreTypedefType = 1; }
#line 3348 "SDCCy.c"
    break;

  case 170:
#line 833 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
   {  /* synthesize a name add to structtable */
     ignoreTypedefType = 0;
     (yyval.sdef) = newStruct(genSymName(NestLevel)) ;
     (yyval.sdef)->level = NestLevel ;
     addSym (StructTab, (yyval.sdef), (yyval.sdef)->tag,(yyval.sdef)->level,currBlockno, 0);
}
#line 3359 "SDCCy.c"
    break;

  case 171:
#line 841 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {  /* add name to structure table */
     ignoreTypedefType = 0;
     (yyval.sdef) = findSymWithBlock (StructTab,(yyvsp[0].sym),currBlockno);
     if (! (yyval.sdef) ) {
       (yyval.sdef) = newStruct((yyvsp[0].sym)->name) ;
       (yyval.sdef)->level = NestLevel ;
       addSym (StructTab, (yyval.sdef), (yyval.sdef)->tag,(yyval.sdef)->level,currBlockno,0);
     }
}
#line 3373 "SDCCy.c"
    break;

  case 173:
#line 855 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
       {
           symbol *sym=(yyvsp[0].sym);

           /* go to the end of the chain */
           while (sym->next) sym=sym->next;
           sym->next = (yyvsp[-1].sym) ;

           (yyval.sym) = (yyvsp[0].sym);
       }
#line 3387 "SDCCy.c"
    break;

  case 174:
#line 868 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
       {
           /* add this type to all the symbols */
           symbol *sym ;
           for ( sym = (yyvsp[-1].sym) ; sym != NULL ; sym = sym->next ) {
               sym_link *btype = copyLinkChain((yyvsp[-2].lnk));

               /* make the symbol one level up */
               sym->level-- ;

               pointerTypes(sym->type,btype);
               if (!sym->type) {
                   sym->type = btype;
                   sym->etype = getSpec(sym->type);
               }
               else
                 addDecl (sym,0,btype);
               /* make sure the type is complete and sane */
               checkTypeSanity(sym->etype, sym->name);
           }
           ignoreTypedefType = 0;
           (yyval.sym) = (yyvsp[-1].sym);
       }
#line 3414 "SDCCy.c"
    break;

  case 176:
#line 895 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
       {
           (yyvsp[0].sym)->next  = (yyvsp[-2].sym) ;
           (yyval.sym) = (yyvsp[0].sym) ;
       }
#line 3423 "SDCCy.c"
    break;

  case 178:
#line 903 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        {
                           unsigned int bitsize;
                           (yyval.sym) = newSymbol (genSymName(NestLevel),NestLevel) ;
                           bitsize = (unsigned int) ulFromVal(constExprValue((yyvsp[0].asts),TRUE));
                           if (bitsize > (port->s.int_size * 8)) {
                             bitsize = port->s.int_size * 8;
                             werror(E_BITFLD_SIZE, bitsize);
                           }
                           if (!bitsize)
                             bitsize = BITVAR_PAD;
                           (yyval.sym)->bitVar = bitsize;
                           (yyval.sym)->bitUnnamed = 1;
                        }
#line 3441 "SDCCy.c"
    break;

  case 179:
#line 917 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        {
                          unsigned int bitsize;
                          bitsize = (unsigned int) ulFromVal(constExprValue((yyvsp[0].asts),TRUE));
                          if (bitsize > (port->s.int_size * 8)) {
                            bitsize = port->s.int_size * 8;
                            werror(E_BITFLD_SIZE, bitsize);
                          }
                          if (!bitsize) {
                            (yyval.sym) = newSymbol (genSymName(NestLevel),NestLevel) ;
                            (yyval.sym)->bitVar = BITVAR_PAD;
                            werror(W_BITFLD_NAMED);
                          }
                          else
                            (yyvsp[-2].sym)->bitVar = bitsize;
                        }
#line 3461 "SDCCy.c"
    break;

  case 180:
#line 932 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
     { (yyval.sym) = newSymbol ("", NestLevel) ; }
#line 3467 "SDCCy.c"
    break;

  case 181:
#line 937 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                             {
           (yyval.lnk) = newEnumType ((yyvsp[-1].sym));       //copyLinkChain(cenum->type);
           SPEC_SCLS(getSpec((yyval.lnk))) = 0;
         }
#line 3476 "SDCCy.c"
    break;

  case 182:
#line 942 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                             {
     symbol *csym ;
     sym_link *enumtype;

     csym=findSym(enumTab,(yyvsp[-3].sym),(yyvsp[-3].sym)->name);
     if ((csym && csym->level == (yyvsp[-3].sym)->level))
       {
         werrorfl((yyvsp[-3].sym)->fileDef, (yyvsp[-3].sym)->lineDef, E_DUPLICATE_TYPEDEF,csym->name);
         werrorfl(csym->fileDef, csym->lineDef, E_PREVIOUS_DEF);
       }

     enumtype = newEnumType ((yyvsp[-1].sym));       //copyLinkChain(cenum->type);
     SPEC_SCLS(getSpec(enumtype)) = 0;
     (yyvsp[-3].sym)->type = enumtype;

     /* add this to the enumerator table */
     if (!csym)
       addSym ( enumTab,(yyvsp[-3].sym),(yyvsp[-3].sym)->name,(yyvsp[-3].sym)->level,(yyvsp[-3].sym)->block, 0);
     (yyval.lnk) = copyLinkChain(enumtype);
   }
#line 3501 "SDCCy.c"
    break;

  case 183:
#line 962 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                             {
     symbol *csym ;

     /* check the enumerator table */
     if ((csym = findSym(enumTab,(yyvsp[0].sym),(yyvsp[0].sym)->name)))
       (yyval.lnk) = copyLinkChain(csym->type);
     else  {
       (yyval.lnk) = newLink(SPECIFIER) ;
       SPEC_NOUN((yyval.lnk)) = V_INT   ;
     }
   }
#line 3517 "SDCCy.c"
    break;

  case 186:
#line 979 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
      {
        (yyvsp[0].sym)->next = (yyvsp[-2].sym) ;
        (yyval.sym) = (yyvsp[0].sym)  ;
      }
#line 3526 "SDCCy.c"
    break;

  case 187:
#line 987 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
      {
        symbol *sym;

        /* make the symbol one level up */
        (yyvsp[-1].sym)->level-- ;
        // check if the symbol at the same level already exists
        if ((sym = findSymWithLevel (SymbolTab, (yyvsp[-1].sym))) &&
          sym->level == (yyvsp[-1].sym)->level)
          {
            werrorfl ((yyvsp[-1].sym)->fileDef, (yyvsp[-1].sym)->lineDef, E_DUPLICATE_MEMBER, "enum", (yyvsp[-1].sym)->name);
            werrorfl (sym->fileDef, sym->lineDef, E_PREVIOUS_DEF);
          }
        (yyvsp[-1].sym)->type = copyLinkChain ((yyvsp[0].val)->type);
        (yyvsp[-1].sym)->etype= getSpec ((yyvsp[-1].sym)->type);
        SPEC_ENUM ((yyvsp[-1].sym)->etype) = 1;
        (yyval.sym) = (yyvsp[-1].sym) ;
        // do this now, so we can use it for the next enums in the list
        addSymChain (&(yyvsp[-1].sym));
      }
#line 3550 "SDCCy.c"
    break;

  case 188:
#line 1009 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              value *val ;

                              val = constExprValue((yyvsp[0].asts),TRUE);
                              if (!IS_INT(val->type) && !IS_CHAR(val->type) && !IS_BOOL(val->type))
                                {
                                  werror(E_ENUM_NON_INTEGER);
                                  SNPRINTF(lbuff, sizeof(lbuff),
                                          "%d", (int) ulFromVal(val));
                                  val = constVal(lbuff);
                                }
                              (yyval.val) = cenum = val ;
                           }
#line 3568 "SDCCy.c"
    break;

  case 189:
#line 1022 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              if (cenum)  {
                                 SNPRINTF(lbuff, sizeof(lbuff),
                                          "%d", (int) ulFromVal(cenum)+1);
                                 (yyval.val) = cenum = constVal(lbuff);
                              }
                              else {
                                 (yyval.val) = cenum = constCharVal(0);
                              }
                           }
#line 3583 "SDCCy.c"
    break;

  case 190:
#line 1035 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.sym) = (yyvsp[0].sym) ; }
#line 3589 "SDCCy.c"
    break;

  case 191:
#line 1037 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             addDecl ((yyvsp[0].sym),0,reverseLink((yyvsp[-1].lnk)));
             (yyval.sym) = (yyvsp[0].sym) ;
         }
#line 3598 "SDCCy.c"
    break;

  case 192:
#line 1044 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.sym) = (yyvsp[0].sym) ; }
#line 3604 "SDCCy.c"
    break;

  case 193:
#line 1045 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.sym) = (yyvsp[0].sym) ; }
#line 3610 "SDCCy.c"
    break;

  case 194:
#line 1049 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 3616 "SDCCy.c"
    break;

  case 195:
#line 1051 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             addDecl ((yyvsp[0].sym),0,reverseLink((yyvsp[-1].lnk)));
             (yyval.sym) = (yyvsp[0].sym) ;
         }
#line 3625 "SDCCy.c"
    break;

  case 196:
#line 1058 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                          { (yyval.sym) = (yyvsp[0].sym) ; }
#line 3631 "SDCCy.c"
    break;

  case 197:
#line 1059 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              {
           // copy the functionAttributes (not the args and hasVargs !!)
           struct value *args;
           unsigned hasVargs;
           sym_link *funcType=(yyvsp[-1].sym)->type;

           while (funcType && !IS_FUNC(funcType))
             funcType = funcType->next;

           if (!funcType)
             werror (E_FUNC_ATTR);
           else
             {
               args=FUNC_ARGS(funcType);
               hasVargs=FUNC_HASVARARGS(funcType);

               memcpy (&funcType->funcAttrs, &(yyvsp[0].lnk)->funcAttrs,
                   sizeof((yyvsp[0].lnk)->funcAttrs));

               FUNC_ARGS(funcType)=args;
               FUNC_HASVARARGS(funcType)=hasVargs;

               // just to be sure
               memset (&(yyvsp[0].lnk)->funcAttrs, 0,
                   sizeof((yyvsp[0].lnk)->funcAttrs));

               addDecl ((yyvsp[-1].sym),0,(yyvsp[0].lnk));
             }
   }
#line 3665 "SDCCy.c"
    break;

  case 199:
#line 1092 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                            { (yyval.sym) = (yyvsp[-1].sym); }
#line 3671 "SDCCy.c"
    break;

  case 200:
#line 1094 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
            sym_link   *p;

            p = newLink (DECLARATOR);
            DCL_TYPE(p) = ARRAY ;
            DCL_ELEM(p) = 0     ;
            addDecl((yyvsp[-2].sym),0,p);
         }
#line 3684 "SDCCy.c"
    break;

  case 201:
#line 1103 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
            sym_link *p;
            value *tval;
            int size;

            tval = constExprValue((yyvsp[-1].asts), TRUE);
            /* if it is not a constant then Error  */
            p = newLink (DECLARATOR);
            DCL_TYPE(p) = ARRAY;

            if (!tval || (SPEC_SCLS(tval->etype) != S_LITERAL))
              {
                werror(E_CONST_EXPECTED);
                /* Assume a single item array to limit the cascade */
                /* of additional errors. */
                size = 1;
              }
            else
              {
                if ((size = (int) ulFromVal(tval)) < 0)
                  {
                    werror(E_NEGATIVE_ARRAY_SIZE, (yyvsp[-3].sym)->name);
                    size = 1;
                  }
              }
            DCL_ELEM(p) = size;
            addDecl((yyvsp[-3].sym), 0, p);
         }
#line 3717 "SDCCy.c"
    break;

  case 202:
#line 1134 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                {  addDecl ((yyvsp[-2].sym),FUNCTION,NULL) ;   }
#line 3723 "SDCCy.c"
    break;

  case 203:
#line 1135 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                { NestLevel++ ; currBlockno++;  }
#line 3729 "SDCCy.c"
    break;

  case 204:
#line 1137 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             sym_link *funcType;

             addDecl ((yyvsp[-4].sym),FUNCTION,NULL) ;

             funcType = (yyvsp[-4].sym)->type;
             while (funcType && !IS_FUNC(funcType))
               funcType = funcType->next;

             assert (funcType);

             FUNC_HASVARARGS(funcType) = IS_VARG((yyvsp[-1].val));
             FUNC_ARGS(funcType) = reverseVal((yyvsp[-1].val));

             /* nest level was incremented to take care of the parms  */
             NestLevel-- ;
             currBlockno--;

             // if this was a pointer (to a function)
             if (!IS_FUNC((yyvsp[-4].sym)->type))
               cleanUpLevel(SymbolTab,NestLevel+1);

             (yyval.sym) = (yyvsp[-4].sym);
         }
#line 3758 "SDCCy.c"
    break;

  case 205:
#line 1162 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
           werror(E_OLD_STYLE,(yyvsp[-3].sym)->name) ;
           /* assume it returns an int */
           (yyvsp[-3].sym)->type = (yyvsp[-3].sym)->etype = newIntLink();
           (yyval.sym) = (yyvsp[-3].sym) ;
         }
#line 3769 "SDCCy.c"
    break;

  case 206:
#line 1171 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         { (yyval.lnk) = (yyvsp[0].lnk) ;}
#line 3775 "SDCCy.c"
    break;

  case 207:
#line 1173 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             (yyval.lnk) = (yyvsp[-1].lnk)  ;
             if (IS_SPEC((yyvsp[0].lnk))) {
                 DCL_TSPEC((yyvsp[-1].lnk)) = (yyvsp[0].lnk);
                 DCL_PTR_CONST((yyvsp[-1].lnk)) = SPEC_CONST((yyvsp[0].lnk));
                 DCL_PTR_VOLATILE((yyvsp[-1].lnk)) = SPEC_VOLATILE((yyvsp[0].lnk));
                 DCL_PTR_RESTRICT((yyvsp[-1].lnk)) = SPEC_RESTRICT((yyvsp[0].lnk));
             }
             else
                 werror (W_PTR_TYPE_INVALID);
         }
#line 3791 "SDCCy.c"
    break;

  case 208:
#line 1185 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             (yyval.lnk) = (yyvsp[-1].lnk) ;
             (yyval.lnk)->next = (yyvsp[0].lnk) ;
             DCL_TYPE((yyvsp[0].lnk))=port->unqualified_pointer;
         }
#line 3801 "SDCCy.c"
    break;

  case 209:
#line 1191 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
             (yyval.lnk) = (yyvsp[-2].lnk) ;
             if (IS_SPEC((yyvsp[-1].lnk)) && DCL_TYPE((yyvsp[0].lnk)) == UPOINTER) {
                 DCL_PTR_CONST((yyvsp[-2].lnk)) = SPEC_CONST((yyvsp[-1].lnk));
                 DCL_PTR_VOLATILE((yyvsp[-2].lnk)) = SPEC_VOLATILE((yyvsp[-1].lnk));
                 DCL_PTR_RESTRICT((yyvsp[-2].lnk)) = SPEC_RESTRICT((yyvsp[-1].lnk));
                 switch (SPEC_SCLS((yyvsp[-1].lnk))) {
                 case S_XDATA:
                     DCL_TYPE((yyvsp[0].lnk)) = FPOINTER;
                     break;
                 case S_IDATA:
                     DCL_TYPE((yyvsp[0].lnk)) = IPOINTER ;
                     break;
                 case S_PDATA:
                     DCL_TYPE((yyvsp[0].lnk)) = PPOINTER ;
                     break;
                 case S_DATA:
                     DCL_TYPE((yyvsp[0].lnk)) = POINTER ;
                     break;
                 case S_CODE:
                     DCL_TYPE((yyvsp[0].lnk)) = CPOINTER ;
                     break;
                 case S_EEPROM:
                     DCL_TYPE((yyvsp[0].lnk)) = EEPPOINTER;
                     break;
                 default:
                   // this could be just "constant"
                   // werror(W_PTR_TYPE_INVALID);
                     ;
                 }
             }
             else
                 werror (W_PTR_TYPE_INVALID);
             (yyval.lnk)->next = (yyvsp[0].lnk) ;
         }
#line 3841 "SDCCy.c"
    break;

  case 210:
#line 1230 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
      {
        (yyval.lnk) = newLink(DECLARATOR);
        DCL_TYPE((yyval.lnk))=UPOINTER;
      }
#line 3850 "SDCCy.c"
    break;

  case 211:
#line 1236 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                           { (yyval.lnk) = finalizeSpec((yyvsp[0].lnk)); }
#line 3856 "SDCCy.c"
    break;

  case 213:
#line 1241 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                         {
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     (yyval.lnk) = mergeDeclSpec((yyvsp[-1].lnk), (yyvsp[0].lnk), "type_specifier_list type_specifier skipped");
   }
#line 3866 "SDCCy.c"
    break;

  case 215:
#line 1251 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
           (yyvsp[0].sym)->next = (yyvsp[-2].sym);
           (yyval.sym) = (yyvsp[0].sym) ;
         }
#line 3875 "SDCCy.c"
    break;

  case 217:
#line 1259 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                      { (yyvsp[-2].val)->vArgs = 1;}
#line 3881 "SDCCy.c"
    break;

  case 219:
#line 1265 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
         {
            (yyvsp[0].val)->next = (yyvsp[-2].val) ;
            (yyval.val) = (yyvsp[0].val) ;
         }
#line 3890 "SDCCy.c"
    break;

  case 220:
#line 1273 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
          symbol *loop;

          if (IS_SPEC ((yyvsp[-1].lnk)) && !IS_VALID_PARAMETER_STORAGE_CLASS_SPEC ((yyvsp[-1].lnk)))
            {
              werror (E_STORAGE_CLASS_FOR_PARAMETER, (yyvsp[0].sym)->name);
            }
          pointerTypes ((yyvsp[0].sym)->type, (yyvsp[-1].lnk));
          addDecl ((yyvsp[0].sym), 0, (yyvsp[-1].lnk));
          for (loop = (yyvsp[0].sym); loop; loop->_isparm = 1, loop = loop->next)
            ;
          addSymChain (&(yyvsp[0].sym));
          (yyval.val) = symbolVal ((yyvsp[0].sym));
          ignoreTypedefType = 0;
        }
#line 3910 "SDCCy.c"
    break;

  case 221:
#line 1289 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
          (yyval.val) = newValue ();
          (yyval.val)->type = (yyvsp[0].lnk);
          (yyval.val)->etype = getSpec ((yyval.val)->type);
          ignoreTypedefType = 0;
         }
#line 3921 "SDCCy.c"
    break;

  case 222:
#line 1299 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
          if (IS_SPEC ((yyvsp[0].lnk)) && !IS_VALID_PARAMETER_STORAGE_CLASS_SPEC ((yyvsp[0].lnk)))
            {
              werror (E_STORAGE_CLASS_FOR_PARAMETER, "type name");
            }
          (yyval.lnk) = (yyvsp[0].lnk); ignoreTypedefType = 0;
        }
#line 3933 "SDCCy.c"
    break;

  case 223:
#line 1307 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {
          /* go to the end of the list */
          sym_link *p;

          if (IS_SPEC ((yyvsp[-1].lnk)) && !IS_VALID_PARAMETER_STORAGE_CLASS_SPEC ((yyvsp[-1].lnk)))
            {
              werror (E_STORAGE_CLASS_FOR_PARAMETER, "type name");
            }
          pointerTypes ((yyvsp[0].lnk),(yyvsp[-1].lnk));
          for (p = (yyvsp[0].lnk); p && p->next; p = p->next)
            ;
          if (!p)
            {
              werror(E_SYNTAX_ERROR, yytext);
            }
          else
            {
              p->next = (yyvsp[-1].lnk) ;
            }
          (yyval.lnk) = (yyvsp[0].lnk) ;
          ignoreTypedefType = 0;
        }
#line 3960 "SDCCy.c"
    break;

  case 224:
#line 1332 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
             { (yyval.lnk) = reverseLink((yyvsp[0].lnk)); }
#line 3966 "SDCCy.c"
    break;

  case 226:
#line 1334 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyvsp[-1].lnk) = reverseLink((yyvsp[-1].lnk)); (yyvsp[-1].lnk)->next = (yyvsp[0].lnk) ; (yyval.lnk) = (yyvsp[-1].lnk);
          if (IS_PTR((yyvsp[-1].lnk)) && IS_FUNC((yyvsp[0].lnk)))
            DCL_TYPE((yyvsp[-1].lnk)) = CPOINTER;
        }
#line 3975 "SDCCy.c"
    break;

  case 227:
#line 1341 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.lnk) = (yyvsp[-1].lnk) ; }
#line 3981 "SDCCy.c"
    break;

  case 228:
#line 1342 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    {
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = 0     ;
                                    }
#line 3991 "SDCCy.c"
    break;

  case 229:
#line 1347 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    {
                                       value *val ;
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = (int) ulFromVal(val = constExprValue((yyvsp[-1].asts),TRUE));
                                    }
#line 4002 "SDCCy.c"
    break;

  case 230:
#line 1353 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    {
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = 0     ;
                                       (yyval.lnk)->next = (yyvsp[-2].lnk) ;
                                    }
#line 4013 "SDCCy.c"
    break;

  case 231:
#line 1360 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    {
                                       value *val ;
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = (int) ulFromVal(val = constExprValue((yyvsp[-1].asts),TRUE));
                                       (yyval.lnk)->next = (yyvsp[-3].lnk) ;
                                    }
#line 4025 "SDCCy.c"
    break;

  case 232:
#line 1367 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.lnk) = NULL;}
#line 4031 "SDCCy.c"
    break;

  case 233:
#line 1368 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.lnk) = NULL;}
#line 4037 "SDCCy.c"
    break;

  case 234:
#line 1369 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                  {
     // $1 must be a pointer to a function
     sym_link *p=newLink(DECLARATOR);
     DCL_TYPE(p) = FUNCTION;
     if (!(yyvsp[-2].lnk)) {
       // ((void (code *) ()) 0) ()
       (yyvsp[-2].lnk)=newLink(DECLARATOR);
       DCL_TYPE((yyvsp[-2].lnk))=CPOINTER;
       (yyval.lnk) = (yyvsp[-2].lnk);
     }
     (yyvsp[-2].lnk)->next=p;
   }
#line 4054 "SDCCy.c"
    break;

  case 235:
#line 1381 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                              { NestLevel++ ; currBlockno++; }
#line 4060 "SDCCy.c"
    break;

  case 236:
#line 1381 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                                                                       {
       sym_link *p=newLink(DECLARATOR);
       DCL_TYPE(p) = FUNCTION;

       FUNC_HASVARARGS(p) = IS_VARG((yyvsp[-1].val));
       FUNC_ARGS(p) = reverseVal((yyvsp[-1].val));

       /* nest level was incremented to take care of the parms  */
       NestLevel-- ;
       currBlockno--;
       if (!(yyvsp[-4].lnk)) {
         /* ((void (code *) (void)) 0) () */
         (yyvsp[-4].lnk)=newLink(DECLARATOR);
         DCL_TYPE((yyvsp[-4].lnk))=CPOINTER;
         (yyval.lnk) = (yyvsp[-4].lnk);
       }
       (yyvsp[-4].lnk)->next=p;

       // remove the symbol args (if any)
       cleanUpLevel(SymbolTab,NestLevel+1);
   }
#line 4086 "SDCCy.c"
    break;

  case 237:
#line 1405 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.ilist) = newiList(INIT_NODE,(yyvsp[0].asts)); }
#line 4092 "SDCCy.c"
    break;

  case 238:
#line 1406 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.ilist) = newiList(INIT_DEEP,revinit((yyvsp[-1].ilist))); }
#line 4098 "SDCCy.c"
    break;

  case 239:
#line 1407 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                    { (yyval.ilist) = newiList(INIT_DEEP,revinit((yyvsp[-2].ilist))); }
#line 4104 "SDCCy.c"
    break;

  case 241:
#line 1412 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       {  (yyvsp[0].ilist)->next = (yyvsp[-2].ilist); (yyval.ilist) = (yyvsp[0].ilist); }
#line 4110 "SDCCy.c"
    break;

  case 249:
#line 1423 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         {
                            ast *ex;
                            seqPointNo++;
                            ex = newNode(INLINEASM,NULL,NULL);
                            ex->values.inlineasm = strdup((yyvsp[-1].yyinline));
                            seqPointNo++;
                            (yyval.asts) = ex;
                         }
#line 4123 "SDCCy.c"
    break;

  case 250:
#line 1434 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                {
                   inCritical++;
                   STACK_PUSH(continueStack,NULL);
                   STACK_PUSH(breakStack,NULL);
                   (yyval.sym) = NULL;
                }
#line 4134 "SDCCy.c"
    break;

  case 251:
#line 1443 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         {
                   STACK_POP(breakStack);
                   STACK_POP(continueStack);
                   inCritical--;
                   (yyval.asts) = newNode(CRITICAL,(yyvsp[0].asts),NULL);
                }
#line 4145 "SDCCy.c"
    break;

  case 252:
#line 1453 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       {  (yyval.asts) = createLabel((yyvsp[-1].sym),NULL);
                                          (yyvsp[-1].sym)->isitmp = 0;  }
#line 4152 "SDCCy.c"
    break;

  case 253:
#line 1456 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
     {
       if (STACK_EMPTY(swStk))
         (yyval.asts) = createCase(NULL,(yyvsp[-1].asts),NULL);
       else
         (yyval.asts) = createCase(STACK_PEEK(swStk),(yyvsp[-1].asts),NULL);
     }
#line 4163 "SDCCy.c"
    break;

  case 254:
#line 1462 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
             { (yyval.asts) = newNode(DEFAULT,NULL,NULL); }
#line 4169 "SDCCy.c"
    break;

  case 255:
#line 1463 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
     {
       if (STACK_EMPTY(swStk))
         (yyval.asts) = createDefault(NULL,(yyvsp[-1].asts),NULL);
       else
         (yyval.asts) = createDefault(STACK_PEEK(swStk),(yyvsp[-1].asts),NULL);
     }
#line 4180 "SDCCy.c"
    break;

  case 256:
#line 1472 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
              {
                STACK_PUSH(blockNum,currBlockno);
                currBlockno = ++blockNo ;
                ignoreTypedefType = 0;
              }
#line 4190 "SDCCy.c"
    break;

  case 257:
#line 1479 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                      { currBlockno = STACK_POP(blockNum); }
#line 4196 "SDCCy.c"
    break;

  case 258:
#line 1483 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              { (yyval.asts) = createBlock(NULL, NULL); }
#line 4202 "SDCCy.c"
    break;

  case 259:
#line 1484 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              { (yyval.asts) = createBlock(NULL, (yyvsp[-1].asts)); }
#line 4208 "SDCCy.c"
    break;

  case 260:
#line 1485 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              { (yyval.asts) = createBlock((yyvsp[-1].sym), NULL); }
#line 4214 "SDCCy.c"
    break;

  case 261:
#line 1488 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              {(yyval.asts) = createBlock((yyvsp[-2].sym), (yyvsp[-1].asts)); }
#line 4220 "SDCCy.c"
    break;

  case 262:
#line 1489 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                              { (yyval.asts) = NULL ; }
#line 4226 "SDCCy.c"
    break;

  case 263:
#line 1494 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
     {
       /* if this is typedef declare it immediately */
       if ( (yyvsp[0].sym) && IS_TYPEDEF((yyvsp[0].sym)->etype)) {
         allocVariables ((yyvsp[0].sym));
         (yyval.sym) = NULL ;
       }
       else
         (yyval.sym) = (yyvsp[0].sym) ;
       ignoreTypedefType = 0;
       addSymChain(&(yyvsp[0].sym));
     }
#line 4242 "SDCCy.c"
    break;

  case 264:
#line 1507 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
     {
       symbol   *sym;

       /* if this is a typedef */
       if ((yyvsp[0].sym) && IS_TYPEDEF((yyvsp[0].sym)->etype)) {
         allocVariables ((yyvsp[0].sym));
         (yyval.sym) = (yyvsp[-1].sym) ;
       }
       else {
         /* get to the end of the previous decl */
         if ( (yyvsp[-1].sym) ) {
           (yyval.sym) = sym = (yyvsp[-1].sym) ;
           while (sym->next)
             sym = sym->next ;
           sym->next = (yyvsp[0].sym);
         }
         else
           (yyval.sym) = (yyvsp[0].sym) ;
       }
       ignoreTypedefType = 0;
       addSymChain(&(yyvsp[0].sym));
     }
#line 4269 "SDCCy.c"
    break;

  case 266:
#line 1533 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                       {  (yyval.asts) = newNode(NULLOP,(yyvsp[-1].asts),(yyvsp[0].asts)) ;}
#line 4275 "SDCCy.c"
    break;

  case 267:
#line 1537 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        { (yyval.asts) = NULL;}
#line 4281 "SDCCy.c"
    break;

  case 268:
#line 1538 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        { (yyval.asts) = (yyvsp[-1].asts); seqPointNo++;}
#line 4287 "SDCCy.c"
    break;

  case 269:
#line 1542 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        { (yyval.asts) = (yyvsp[0].asts)  ; }
#line 4293 "SDCCy.c"
    break;

  case 270:
#line 1543 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        { (yyval.asts) = NULL;}
#line 4299 "SDCCy.c"
    break;

  case 271:
#line 1548 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                     { seqPointNo++;}
#line 4305 "SDCCy.c"
    break;

  case 272:
#line 1549 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              noLineno++ ;
                              (yyval.asts) = createIf ((yyvsp[-4].asts), (yyvsp[-1].asts), (yyvsp[0].asts) );
                              (yyval.asts)->lineno = (yyvsp[-4].asts)->lineno;
                              (yyval.asts)->filename = (yyvsp[-4].asts)->filename;
                              noLineno--;
                           }
#line 4317 "SDCCy.c"
    break;

  case 273:
#line 1556 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              ast *ex ;
                              static   int swLabel = 0 ;

                              seqPointNo++;
                              /* create a node for expression  */
                              ex = newNode(SWITCH,(yyvsp[-1].asts),NULL);
                              STACK_PUSH(swStk,ex);   /* save it in the stack */
                              ex->values.switchVals.swNum = swLabel ;

                              /* now create the label */
                              SNPRINTF(lbuff, sizeof(lbuff),
                                       "_swBrk_%d",swLabel++);
                              (yyval.sym)  =  newSymbol(lbuff,NestLevel);
                              /* put label in the break stack  */
                              STACK_PUSH(breakStack,(yyval.sym));
                           }
#line 4339 "SDCCy.c"
    break;

  case 274:
#line 1573 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              /* get back the switch form the stack  */
                              (yyval.asts) = STACK_POP(swStk)  ;
                              (yyval.asts)->right = newNode (NULLOP,(yyvsp[0].asts),createLabel((yyvsp[-1].sym),NULL));
                              STACK_POP(breakStack);
                           }
#line 4350 "SDCCy.c"
    break;

  case 275:
#line 1581 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
               {  /* create and push the continue , break & body labels */
                  static int Lblnum = 0 ;
                  /* continue */
                  SNPRINTF (lbuff, sizeof(lbuff), "_whilecontinue_%d",Lblnum);
                  STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
                  /* break */
                  SNPRINTF (lbuff, sizeof(lbuff), "_whilebreak_%d",Lblnum);
                  STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
                  /* body */
                  SNPRINTF (lbuff, sizeof(lbuff), "_whilebody_%d",Lblnum++);
                  (yyval.sym) = newSymbol(lbuff,NestLevel);
               }
#line 4367 "SDCCy.c"
    break;

  case 276:
#line 1595 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
        {  /* create and push the continue , break & body Labels */
           static int Lblnum = 0 ;

           /* continue */
           SNPRINTF(lbuff, sizeof(lbuff), "_docontinue_%d",Lblnum);
           STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
           /* break */
           SNPRINTF(lbuff, sizeof(lbuff), "_dobreak_%d",Lblnum);
           STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
           /* do body */
           SNPRINTF(lbuff, sizeof(lbuff), "_dobody_%d",Lblnum++);
           (yyval.sym) = newSymbol (lbuff,NestLevel);
        }
#line 4385 "SDCCy.c"
    break;

  case 277:
#line 1610 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
          { /* create & push continue, break & body labels */
            static int Lblnum = 0 ;

            /* continue */
            SNPRINTF(lbuff, sizeof(lbuff), "_forcontinue_%d",Lblnum);
            STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
            /* break    */
            SNPRINTF(lbuff, sizeof(lbuff), "_forbreak_%d",Lblnum);
            STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
            /* body */
            SNPRINTF(lbuff, sizeof(lbuff), "_forbody_%d",Lblnum);
            (yyval.sym) = newSymbol(lbuff,NestLevel);
            /* condition */
            SNPRINTF(lbuff, sizeof(lbuff), "_forcond_%d",Lblnum++);
            STACK_PUSH(forStack,newSymbol(lbuff,NestLevel));
          }
#line 4406 "SDCCy.c"
    break;

  case 278:
#line 1629 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        { seqPointNo++;}
#line 4412 "SDCCy.c"
    break;

  case 279:
#line 1630 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                         {
                           noLineno++ ;
                           (yyval.asts) = createWhile ( (yyvsp[-5].sym), STACK_POP(continueStack),
                                              STACK_POP(breakStack), (yyvsp[-3].asts), (yyvsp[0].asts) );
                           (yyval.asts)->lineno = (yyvsp[-5].sym)->lineDef;
                           (yyval.asts)->filename = (yyvsp[-5].sym)->fileDef;
                           noLineno-- ;
                         }
#line 4425 "SDCCy.c"
    break;

  case 280:
#line 1639 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        {
                          seqPointNo++;
                          noLineno++ ;
                          (yyval.asts) = createDo ( (yyvsp[-6].sym) , STACK_POP(continueStack),
                                          STACK_POP(breakStack), (yyvsp[-2].asts), (yyvsp[-5].asts));
                          (yyval.asts)->lineno = (yyvsp[-6].sym)->lineDef;
                          (yyval.asts)->filename = (yyvsp[-6].sym)->fileDef;
                          noLineno-- ;
                        }
#line 4439 "SDCCy.c"
    break;

  case 281:
#line 1649 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                        {
                          noLineno++ ;

                          /* if break or continue statement present
                             then create a general case loop */
                          if (STACK_PEEK(continueStack)->isref ||
                              STACK_PEEK(breakStack)->isref) {
                              (yyval.asts) = createFor ((yyvsp[-8].sym), STACK_POP(continueStack),
                                              STACK_POP(breakStack) ,
                                              STACK_POP(forStack)   ,
                                              (yyvsp[-6].asts) , (yyvsp[-4].asts) , (yyvsp[-2].asts), (yyvsp[0].asts) );
                          } else {
                              (yyval.asts) = newNode(FOR,(yyvsp[0].asts),NULL);
                              AST_FOR((yyval.asts),trueLabel) = (yyvsp[-8].sym);
                              AST_FOR((yyval.asts),continueLabel) =  STACK_POP(continueStack);
                              AST_FOR((yyval.asts),falseLabel) = STACK_POP(breakStack);
                              AST_FOR((yyval.asts),condLabel)  = STACK_POP(forStack)  ;
                              AST_FOR((yyval.asts),initExpr)   = (yyvsp[-6].asts);
                              AST_FOR((yyval.asts),condExpr)   = (yyvsp[-4].asts);
                              AST_FOR((yyval.asts),loopExpr)   = (yyvsp[-2].asts);
                          }

                          noLineno-- ;
                        }
#line 4468 "SDCCy.c"
    break;

  case 282:
#line 1676 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                { (yyval.asts) = NULL ; seqPointNo++; }
#line 4474 "SDCCy.c"
    break;

  case 283:
#line 1677 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                                { (yyval.asts) = (yyvsp[0].asts) ; seqPointNo++; }
#line 4480 "SDCCy.c"
    break;

  case 284:
#line 1681 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
                              (yyvsp[-1].sym)->islbl = 1;
                              (yyval.asts) = newAst_VALUE(symbolVal((yyvsp[-1].sym)));
                              (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
                           }
#line 4490 "SDCCy.c"
    break;

  case 285:
#line 1686 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
       /* make sure continue is in context */
       if (STACK_EMPTY(continueStack) || STACK_PEEK(continueStack) == NULL) {
           werror(E_BREAK_CONTEXT);
           (yyval.asts) = NULL;
       }
       else {
           (yyval.asts) = newAst_VALUE(symbolVal(STACK_PEEK(continueStack)));
           (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
           /* mark the continue label as referenced */
           STACK_PEEK(continueStack)->isref = 1;
       }
   }
#line 4508 "SDCCy.c"
    break;

  case 286:
#line 1699 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
       if (STACK_EMPTY(breakStack) || STACK_PEEK(breakStack) == NULL) {
           werror(E_BREAK_CONTEXT);
           (yyval.asts) = NULL;
       } else {
           (yyval.asts) = newAst_VALUE(symbolVal(STACK_PEEK(breakStack)));
           (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
           STACK_PEEK(breakStack)->isref = 1;
       }
   }
#line 4523 "SDCCy.c"
    break;

  case 287:
#line 1709 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
       seqPointNo++;
       if (inCritical) {
           werror(E_INVALID_CRITICAL);
           (yyval.asts) = NULL;
       } else {
           (yyval.asts) = newNode(RETURN,NULL,NULL);
       }
   }
#line 4537 "SDCCy.c"
    break;

  case 288:
#line 1718 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                           {
       seqPointNo++;
       if (inCritical) {
           werror(E_INVALID_CRITICAL);
           (yyval.asts) = NULL;
       } else {
           (yyval.asts) = newNode(RETURN,NULL,(yyvsp[-1].asts));
       }
   }
#line 4551 "SDCCy.c"
    break;

  case 289:
#line 1730 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"
                  { (yyval.sym) = newSymbol ((yyvsp[0].yychar),NestLevel) ; }
#line 4557 "SDCCy.c"
    break;


#line 4561 "SDCCy.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1732 "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/src/SDCC.y"

