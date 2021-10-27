/*-------------------------------------------------------------------------
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

#ifndef SDCCGEN_JSON_H
#define SDCCGEN_JSON_H

enum
  {
    AOP_LIT = 1,
    AOP_REG, AOP_DIR,
    AOP_STK,AOP_STR
  };

/* type asmop : a homogenised type for 
   all the different spaces an operand can be
   in */
typedef struct asmop
  {

    short type;			/* can have values
				   AOP_LIT    -  operand is a literal value
				   AOP_REG    -  must be loaded into a register
				   AOP_DIR    -  direct just a name   

				 */
    short coff;			/* current offset */
    short size;			/* total size */
    unsigned freed:1;		/* already freed    */
    union
      {
	value *aop_lit;		/* if literal */
	regs *aop_reg[4];	/* array of registers */
	char *aop_dir;		/* if direct  */
      }
    aopu;
  }
asmop;

void genJSONCode (iCode *);
void json_emitDebuggerSymbol (const char *);

#endif
