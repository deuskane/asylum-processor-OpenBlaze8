/*-------------------------------------------------------------------------
main.h - header file for XILINX PICOBLAZE

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

#ifndef MAIN_INCLUDE
#define MAIN_INCLUDE

bool x_parseOptions(char **argv, int *pargc);
void x_setDefaultOptions(void);
void x_finaliseOptions(void);

typedef struct {
    int dialect;
    char *portKw;
} pblaze_options_t;

symbol *pblaze_interrupt;
extern pblaze_options_t pblaze_options;

#endif
