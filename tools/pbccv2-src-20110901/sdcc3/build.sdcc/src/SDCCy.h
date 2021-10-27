/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 313 "SDCCy.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SDCCY_H_INCLUDED  */
